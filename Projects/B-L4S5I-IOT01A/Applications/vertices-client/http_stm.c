//
// Created by Cyril on 17/09/2021.
//

#include <net_connect.h>
#include <http.h>
#include <vertices_log.h>
#include "vertices_http.h"

#define HTTP_READ_WRITE_BUFFER_SIZE 1024

#define SOCKET_INVALID_VALUE (-1)
static int m_socket = SOCKET_INVALID_VALUE;

static char m_hostname[64] = {0};

#define HTTP_HEADER "HTTP/1.1"

static size_t
(*m_response_payload_cb)(char *received_data,
                         size_t size);

static void *
response_realloc(void *opaque, void *ptr, int size)
{
    return realloc(ptr, size);
}

static void
response_body(void *opaque, const char *data, int size)
{
    m_response_payload_cb((char *) data, size);
}

static void
response_header(void *opaque,
                const char *ckey,
                int nkey,
                const char *cvalue,
                int nvalue) { /* doesn't care about headers */ }

static void
response_code(void *opaque, int code)
{
    *(uint32_t *) opaque = code;

    LOG_INFO("HTTP response code: %u", code);
}

static http_funcs_t responseFuncs = {
    response_realloc,
    response_body,
    response_header,
    response_code
};

static ret_code_t
parse_url(char *url, bool *is_secure)
{
    *is_secure = false;

#define HT_PX  "http://"
#define HTS_PX  "https://"

    // reset hostname
    memset(m_hostname, 0, sizeof(m_hostname));

    if (0 == strncmp(url, HTS_PX, strlen(HTS_PX)))
    {
        memcpy(m_hostname, &url[sizeof(HTS_PX) - 1], sizeof(m_hostname) - sizeof(HTS_PX) - 1);
        *is_secure = true;
    }
    else if (0 == strncmp(url, HT_PX, strlen(HT_PX)))
    {
        memcpy(m_hostname, &url[sizeof(HT_PX) - 1], sizeof(m_hostname) - sizeof(HT_PX) - 1);
        *is_secure = false;
    }

    // remove trailing `/`
    if (m_hostname[strlen(m_hostname) - 1] == '/')
    {
        m_hostname[strlen(m_hostname) - 1] = 0;
    }

    return VTC_SUCCESS;
}

static ret_code_t
http_connect(const provider_info_t *provider, char *url)
{
    sockaddr_in_t addr = {0};
    addr.sin_len = sizeof(sockaddr_in_t);

    if (net_if_gethostbyname(NULL, (sockaddr_t *) &addr, (char_t *) m_hostname) < 0)
    {
        LOG_ERROR("Could not find hostname ipaddr %s", m_hostname);
        return VTC_ERROR_HTTP_BASE;
    }

    addr.sin_port = NET_HTONS(provider->port);
    int ret = net_connect(m_socket, (sockaddr_t *) &addr, sizeof(addr));
    if (ret != NET_OK)
    {
        return VTC_ERROR_HTTP_BASE;
    }

    return VTC_SUCCESS;
}

ret_code_t
http_init(const provider_info_t *provider,
          size_t (*response_payload_cb)(char *chunk,
                                        size_t chunk_size))
{
    // check if socket already open?
    if (m_socket >= 0)
    {
        return VTC_ERROR_INVALID_STATE;
    }

    m_socket = net_socket(NET_AF_INET, NET_SOCK_STREAM, NET_IPPROTO_TCP);
    if (m_socket < 0)
    {
        m_socket = SOCKET_INVALID_VALUE;

        return VTC_ERROR_INTERNAL;
    }

    bool is_secure = false;

    // remove HTTP/HTTPS protocol from URL
    ret_code_t err_code = parse_url(provider->url, &is_secure);
    VTC_ASSERT(err_code);

    if (is_secure)
    {
        int config_socket_ret = net_setsockopt(m_socket,
                                               NET_SOL_SOCKET,
                                               NET_SO_SECURE,
                                               NULL, 0);
        config_socket_ret |= net_setsockopt(m_socket,
                                            NET_SOL_SOCKET,
                                            NET_SO_TLS_CA_CERT,
                                            (void *) provider->cert_pem,
                                            strlen(provider->cert_pem) + 1);
        config_socket_ret |= net_setsockopt(m_socket,
                                            NET_SOL_SOCKET,
                                            NET_SO_TLS_SERVER_NAME,
                                            (void *) m_hostname,
                                            strlen(m_hostname) + 1);
        if (config_socket_ret != NET_OK)
        {
            return VTC_ERROR_INTERNAL;
        }
    }

    // trying to connect
    err_code = http_connect(provider, m_hostname);
    if (err_code != VTC_SUCCESS)
    {
        m_socket = SOCKET_INVALID_VALUE;

        return err_code;
    }

    // socket is created, we can store the callback function
    if (response_payload_cb != NULL)
    {
        m_response_payload_cb = response_payload_cb;
    }

    return VTC_SUCCESS;
}

ret_code_t
http_get(const provider_info_t *provider,
         const char *relative_path,
         const char *headers,
         uint32_t *response_code)
{
    int32_t ret = 0;

    if (m_socket < 0)
    {
        return VTC_ERROR_INVALID_STATE;
    }

    char request_str[HTTP_READ_WRITE_BUFFER_SIZE] = {0};

    if (m_hostname[0] == 0)
    {
        bool is_secure;
        parse_url(provider->url, &is_secure);
    }

    int32_t bytes_to_send = snprintf(request_str,
                                     sizeof(request_str),
                                     "GET /%s %s\r\n"
                                     "Host: %s\r\n"
                                     "%s\r\n\r\n",
                                     relative_path[0] == '/' ? &relative_path[1] : relative_path,
                                     HTTP_HEADER,
                                     m_hostname,
                                     (headers == NULL) ? "" : headers);
    VTC_ASSERT_BOOL(bytes_to_send < sizeof(request_str));

    // sending headers
    ret = net_send(m_socket, (uint8_t *) request_str, bytes_to_send, 0);
    if (bytes_to_send != ret)
    {
        return VTC_ERROR_HTTP_BASE;
    }

    http_roundtripper_t rt;
    http_parser_init(&rt, responseFuncs, response_code);

    bool needmore = true;
    uint8_t buffer[HTTP_READ_WRITE_BUFFER_SIZE];
    while (needmore)
    {
        const char *data = (char *) buffer;
        int ndata = net_recv(m_socket, buffer, sizeof(buffer), 0);
        if (ndata <= 0)
        {
            LOG_ERROR("Error receiving data\r\n");
            http_parser_free(&rt);
            return VTC_ERROR_HTTP_BASE;
        }

        while (needmore && ndata)
        {
            int read;
            needmore = http_parser_data(&rt, data, ndata, &read);
            ndata -= read;
            data += read;
        }
    }

    return VTC_SUCCESS;
}

ret_code_t
http_post(const provider_info_t *provider,
          const char *relative_path,
          char *headers,
          const char *body,
          size_t body_size,
          uint32_t *response_code)
{
    int32_t ret = 0;

    if (m_socket < 0)
    {
        return VTC_ERROR_INVALID_STATE;
    }

    char request_str[HTTP_READ_WRITE_BUFFER_SIZE] = {0};

    if (m_hostname[0] == 0)
    {
        bool is_secure;
        parse_url(provider->url, &is_secure);
    }

    int32_t bytes_to_send = snprintf(request_str,
                                     sizeof(request_str),
                                     "POST /%s %s\r\n"
                                     "Host: %s\r\n"
                                     "Content-Length: %d\r\n"
                                     "%s\r\n\r\n",
                                     relative_path[0] == '/' ? &relative_path[1] : relative_path,
                                     HTTP_HEADER,
                                     m_hostname,
                                     body_size,
                                     (headers == NULL) ? "" : headers);
    VTC_ASSERT_BOOL(bytes_to_send < sizeof(request_str));

    // send headers
    ret = net_send(m_socket, (uint8_t *) request_str, bytes_to_send, 0);
    if (bytes_to_send != ret)
    {
        LOG_ERROR("Error sending header: %i", ret);

        return VTC_ERROR_HTTP_BASE;
    }

    // send body
    ret = net_send(m_socket, (uint8_t *) body, body_size, 0);
    if (ret != body_size)
    {
        LOG_ERROR("Error sending body: %i", ret);

        return VTC_ERROR_HTTP_BASE;
    }

    http_roundtripper_t rt;
    http_parser_init(&rt, responseFuncs, response_code);

    bool needmore = true;
    uint8_t buffer[HTTP_READ_WRITE_BUFFER_SIZE];
    while (needmore)
    {
        const char *data = (char *) buffer;
        int ndata = net_recv(m_socket, buffer, sizeof(buffer), 0);
        if (ndata <= 0)
        {
            LOG_ERROR("Error receiving data");
            http_parser_free(&rt);
            return VTC_ERROR_HTTP_BASE;
        }

        while (needmore && ndata)
        {
            int read;
            needmore = http_parser_data(&rt, data, ndata, &read);
            ndata -= read;
            data += read;
        }
    }

    return VTC_SUCCESS;
}

void
http_close(void)
{
    int32_t ret = NET_OK;
    if (m_socket >= 0)
    {
        ret = net_closesocket(m_socket);
        if (ret != NET_OK)
        {
            LOG_INFO("ERROR: net_closesocket ret %i", ret);
        }
    }

    m_socket = SOCKET_INVALID_VALUE;
    memset(m_hostname, 0, sizeof(m_hostname));
}

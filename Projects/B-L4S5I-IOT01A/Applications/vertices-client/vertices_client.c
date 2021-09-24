//
// Created by Cyril on 17/09/2021.
//

#include <stdio.h>
#include <cmsis_os.h>
#include <vertices.h>
#include "vertices_client.h"

static ret_code_t
vertices_evt_handler(vtc_evt_t *evt);

static provider_info_t providers =
    {
        .url = (char *) SERVER_URL,
        .port = SERVER_PORT,
        .header = (char *) SERVER_TOKEN_HEADER,
        .cert_pem = SERVER_CA
    };

static ret_code_t
vertices_evt_handler(vtc_evt_t *evt)
{
    ret_code_t err_code = VTC_SUCCESS;

    printf("💥 Evt: %u\r\n", evt->type);

    return err_code;
}

/**
 * @brief  Require Root Certificate for TLS.
 * @param  None
 * @retval Always true
 */
bool
app_needs_root_ca(void)
{
    return true;
}

static vertex_t m_vertex = {
    .provider = &providers,
    .vertices_evt_handler = vertices_evt_handler};
/**
  * @brief  IOTA client task
  * @param  arg Task arg
  * @retval None
  */
_Noreturn void
vertices_wallet_run(void const *arg)
{
    printf("Vertices wallet, let's go!\r\n");

    // create new vertex
    ret_code_t err_code = vertices_new(&m_vertex);
    VTC_ASSERT(err_code);

    // making sure the provider is accessible
    vertices_ping();
    VTC_ASSERT(err_code);

    provider_version_t version = {0};
    err_code = vertices_version(&version);
    if (err_code == VTC_ERROR_OFFLINE)
    {
        printf("Version might not be accurate: old value is being used\r\n");
    }
    else
    {
        VTC_ASSERT(err_code);
    }

    printf("🏎 Running on %s v.%u.%u.%u\r\n",
           version.network,
           version.major,
           version.minor,
           version.patch);



    while (1)
    {
        printf("👋\r\n");
        osDelay(1000);
    }
}

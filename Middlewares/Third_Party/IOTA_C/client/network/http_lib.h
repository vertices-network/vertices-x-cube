/**
  ******************************************************************************
  * @file    http_lib.h
  * @author  MCD Application Team
  * @brief   Helper functions for building HTTP GET and POST requests, and 
  *          stream reading.
  *          Header for http_util.c
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef HTTP_LIB_H
#define HTTP_LIB_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

#include "byte_buffer.h"

/** @defgroup IOTA_C IOTA_C
 * @{
 */

/** @defgroup CLIENT Client
 * @{
 */

/** @defgroup NETWORK Network
 * @{
 */

/** @defgroup NETWORK_EXPORTED_CONSTANTS Exported Constants
 * @{
 */

/* Exported constants --------------------------------------------------------*/
#define HTTP_OK                0
#define HTTP_ERR               -1
#define HTTP_ERR_HTTP          -2  /**< HTTP error */
#define HTTP_ERR_CLOSED        -3  /**< The HTTP connection was closed by the server. */

/**
 * @}
 */

/** @defgroup NETWORK_EXPORTED_TYPES Exported Types
 * @{
 */

/* Exported types ------------------------------------------------------------*/
typedef void * http_handle_t;

typedef enum {
  HTTP_PROTO_NONE = 0,
  HTTP_PROTO_HTTP,
  HTTP_PROTO_HTTPS
} http_proto_t;

typedef struct
{
  byte_buf_t* body;
  int code;
} http_response_t;

/**
 * @}
 */

/** @defgroup NETWORK_EXPORTED_FUNCTIONS Exported Functions
 * @{
 */

/* Exported functions --------------------------------------------------------*/
int http_open(http_handle_t * const pHnd, const char *url);
int http_close(const http_handle_t hnd);
bool http_is_open(const http_handle_t hnd);

int http_read(const http_handle_t hnd,
              http_response_t* response,
              const char * const extra_headers,
              byte_buf_t* const post_buffer);

int http_url_parse(char * const host,
                   const int host_max_len,
                   int * const port,
                   bool * tls,
                   char * const query,
                   const int query_max_len,
                   const char * url);

int http_req_create(char ** const req_buf,
                    const char * const query,
                    const char * const hostname,
                    const char * const extra_headers,
                    byte_buf_t* const post_buffer);

void http_req_destroy(const char *req_buf);


/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* HTTP_LIB_H */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

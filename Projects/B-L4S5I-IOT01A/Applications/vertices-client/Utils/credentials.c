/**
  ******************************************************************************
  * @file    credentials.c
  * @author  Based on MCD Application Team
  * @brief   set the device connection credentials
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019-2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <credentials.h>
#include <vertices_log.h>
#include "net_connect.h"

static const char DEFAULT_SSID[] = CONFIG_WIFI_SSID;
static const char DEFAULT_PSK[] = CONFIG_WIFI_PSK;

/* Functions Definition ------------------------------------------------------*/

/**
  * @brief  Prompt and set the credentials for the network interface
  * @param  pnetif     Pointer to the network interface

  * @retval NET_OK               in case of success
  *         NET_ERROR_FRAMEWORK  if unable to set the parameters
  */
int32_t
set_network_credentials(net_if_handle_t *pnetif)
{
    static net_wifi_credentials_t wifi_cred = {0};

    LOG_INFO("*** WIFI connection ***");

    wifi_cred.ssid = DEFAULT_SSID;
    wifi_cred.psk = DEFAULT_PSK;
    wifi_cred.security_mode = 3;

    if (net_wifi_set_credentials(pnetif, &wifi_cred) != NET_OK)
    {
        LOG_ERROR("Can not set the Wi-Fi credentials");
        return NET_ERROR_FRAMEWORK;
    }
    return NET_OK;
}


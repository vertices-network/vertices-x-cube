/**
  ******************************************************************************
  * @file    cloud.c
  * @author  MCD Application Team
  * @brief   cloud application common functions
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics International N.V.
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
#include <stdio.h>
#include <stdbool.h>
#include <vertices_errors.h>
#include <credentials.h>
#include <vertices_log.h>
#include "net_connect.h"
#include "timedate.h"
#include "cloud.h"
#include "sensors_data.h"

/* Private function prototypes -----------------------------------------------*/
static void
hnet_notify(void *context,
            uint32_t event_class,
            uint32_t event_id,
            void *event_data);

extern int32_t
es_wifi_driver(net_if_handle_t *pnetif);
net_if_driver_init_func device_driver_ptr = &es_wifi_driver;

net_if_handle_t netif;

const net_event_handler_t net_handler = {hnet_notify, &netif};

/* Private defines -----------------------------------------------------------*/
#define STATE_TRANSITION_TIMEOUT        100000

/* Exported functions --------------------------------------------------------*/
/**
 * @brief  Ask yes/no question.
 * @param  s question string
 * @retval 1 yes 0 no
 */
bool
dialog_ask(char *s)
{
    char console_yn;
    do
    {
        LOG_INFO("%s", s);
        console_yn = getchar();
        LOG_INFO("\b");
    }
    while ((console_yn != 'y') && (console_yn != 'n') && (console_yn != '\n'));
    if (console_yn == 'y')
    {
        return true;
    }
    return false;
}

/**
 * @brief  Init the platform.
 * @param  None
 * @retval 0 success -1 error
 */
int
platform_init(void)
{
#if defined(HEAP_DEBUG) && !defined(HAS_RTOS)
    stack_measure_prologue();
#endif

    LOG_INFO("");
    LOG_INFO("*************************************************************");
    LOG_INFO("***   STM32 IoT Discovery kit for STM32L4S5VI MCU");
    LOG_INFO("***   Vertices Client");
//  LOG_INFO("***   FW version: %d.%d.%d - %s",
//         FW_VERSION_MAJOR, FW_VERSION_MINOR, FW_VERSION_PATCH, FW_VERSION_DATE);
    LOG_INFO("*************************************************************");

    LOG_INFO("*** Board personalization ***");
    /* Network initialization */

    if (net_if_init(&netif, device_driver_ptr, &net_handler) != NET_OK)
    {
        LOG_ERROR("Can not set-up the network interface structure");
        return NET_ERROR_FRAMEWORK;
    }
    else
    {
        if (net_if_wait_state(&netif, NET_STATE_INITIALIZED, STATE_TRANSITION_TIMEOUT) != NET_OK)
        {
            LOG_ERROR("The network interface can not be initialized");
            return NET_ERROR_FRAMEWORK;
        }
    }

    set_network_credentials(&netif);

    if (net_if_start(&netif) != NET_OK)
    {
        LOG_ERROR("The network interface can not be started");
        return NET_ERROR_FRAMEWORK;
    }

    if (net_if_connect(&netif) != NET_OK)
    {
        LOG_ERROR("Unable to connect netif");
        return -1;
    }
    else
    {
        net_if_wait_state(&netif, NET_STATE_CONNECTED, STATE_TRANSITION_TIMEOUT);
    }

    /* End of network initialization */

    LOG_INFO("Setting the RTC from the network time.");
    int err_code = setRTCTimeDateFromNetwork(true);
    if (err_code != TD_OK)
    {
        VTC_ASSERT(VTC_ERROR_HTTP_BASE);
    }

    int res = init_sensors();
    VTC_ASSERT(res);

    return NET_OK;
}

/**
 * @brief  Deinit the platform.
 * @param  None
 * @retval None
 */
void
platform_deinit()
{
    net_if_deinit(&netif);

#if defined(HEAP_DEBUG) && !defined(HAS_RTOS)
    stack_measure_epilogue();
    uint32_t heap_max, heap_current, stack_size;

    heap_stat(&heap_max, &heap_current, &stack_size);
    LOG_INFO("Heap Max allocation 0x%lx (%lu), current allocation 0x%lx (%lu), Stack max size 0x%lx (%lu)", heap_max, heap_max, heap_current, heap_current, stack_size, stack_size);
#endif
}

/* Private functions ---------------------------------------------------------*/
static void
hnet_notify(void *context,
            uint32_t event_class,
            uint32_t event_id,
            void *event_data)
{
    net_if_handle_t *netif = context;

    if (NET_EVENT_STATE_CHANGE == event_class)
    {
        net_state_t new_state = (net_state_t) event_id;
        switch (new_state)
        {
            case NET_STATE_INITIALIZED:LOG_INFO("- Network Interface initialized: ");
                break;

            case NET_STATE_STARTING:LOG_INFO("- Network Interface starting: ");
                break;

            case NET_STATE_STARTED:LOG_INFO("- Network Interface started: ");
                LOG_INFO("   - Device Name : %s. ", netif->DeviceName);
                LOG_INFO("   - Device ID : %s. ", netif->DeviceID);
                LOG_INFO("   - Device Version : %s. ", netif->DeviceVer);
#ifndef STM32L496xx
                LOG_INFO("   - MAC address: %02X:%02X:%02X:%02X:%02X:%02X. ",
                       netif->macaddr.mac[0],
                       netif->macaddr.mac[1],
                       netif->macaddr.mac[2],
                       netif->macaddr.mac[3],
                       netif->macaddr.mac[4],
                       netif->macaddr.mac[5]);
#endif
                break;

            case NET_STATE_CONNECTING:LOG_INFO("- Network Interface connecting: ");
                break;

            case NET_STATE_CONNECTED:LOG_INFO("- Network Interface connected: ");
                LOG_INFO("   - IP address :  %s. ", net_ntoa(&netif->ipaddr));
                break;

            case NET_STATE_DISCONNECTING:LOG_INFO("- Network Interface disconnecting");
                break;

            case NET_STATE_DISCONNECTED:LOG_INFO("- Network Interface disconnected");
                break;

            case NET_STATE_STOPPING:LOG_INFO("- Network Interface stopping");
                break;

            case NET_STATE_STOPPED:LOG_INFO("- Network Interface stopped");
                break;

            case NET_STATE_DEINITIALIZED:LOG_INFO("- Network Interface de-initialized");
                break;

            default:break;
        }
    }
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

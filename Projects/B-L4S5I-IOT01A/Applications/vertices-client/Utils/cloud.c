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
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <vertices_errors.h>
#include <credentials.h>
#include "main.h"
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
        printf("%s", s);
        console_yn = getchar();
        printf("\b");
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

    printf("\n");
    printf("*************************************************************\n");
    printf("***   STM32 IoT Discovery kit for STM32L4S5VI MCU\n");
    printf("***   Vertices Client\n");
//  printf("***   FW version: %d.%d.%d - %s\n",
//         FW_VERSION_MAJOR, FW_VERSION_MINOR, FW_VERSION_PATCH, FW_VERSION_DATE);
    printf("*************************************************************\n");

    printf("\n*** Board personalization ***\n\n");
    /* Network initialization */

    if (net_if_init(&netif, device_driver_ptr, &net_handler) != NET_OK)
    {
        msg_error("Can not set-up the network interface structure\n");
        return NET_ERROR_FRAMEWORK;
    }
    else
    {
        if (net_if_wait_state(&netif, NET_STATE_INITIALIZED, STATE_TRANSITION_TIMEOUT) != NET_OK)
        {
            msg_error("The network interface can not be initialized\n");
            return NET_ERROR_FRAMEWORK;
        }
    }

    set_network_credentials(&netif);

    if (net_if_start(&netif) != NET_OK)
    {
        msg_error("The network interface can not be started\n");
        return NET_ERROR_FRAMEWORK;
    }

    if (net_if_connect(&netif) != NET_OK)
    {
        msg_error("Unable to connect netif\n");
        return -1;
    }
    else
    {
        net_if_wait_state(&netif, NET_STATE_CONNECTED, STATE_TRANSITION_TIMEOUT);
    }

    /* End of network initialization */

    msg_info("Setting the RTC from the network time.\n");
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
    /* Close IOTA Client demonstration */
    printf("\n*** IOTA Client demonstration ***\n\n");
    printf("IOTA Client demonstration completed\n");

    net_if_deinit(&netif);

#if defined(HEAP_DEBUG) && !defined(HAS_RTOS)
    stack_measure_epilogue();
    uint32_t heap_max, heap_current, stack_size;

    heap_stat(&heap_max, &heap_current, &stack_size);
    msg_info("Heap Max allocation 0x%lx (%lu), current allocation 0x%lx (%lu), Stack max size 0x%lx (%lu)\n", heap_max, heap_max, heap_current, heap_current, stack_size, stack_size);
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
            case NET_STATE_INITIALIZED:printf("- Network Interface initialized: \n");
                break;

            case NET_STATE_STARTING:printf("- Network Interface starting: \n");
                break;

            case NET_STATE_STARTED:printf("- Network Interface started: \n");
                printf("   - Device Name : %s. \n", netif->DeviceName);
                printf("   - Device ID : %s. \n", netif->DeviceID);
                printf("   - Device Version : %s. \n", netif->DeviceVer);
#ifndef STM32L496xx
                printf("   - MAC address: %02X:%02X:%02X:%02X:%02X:%02X. \n",
                       netif->macaddr.mac[0],
                       netif->macaddr.mac[1],
                       netif->macaddr.mac[2],
                       netif->macaddr.mac[3],
                       netif->macaddr.mac[4],
                       netif->macaddr.mac[5]);
#endif
                break;

            case NET_STATE_CONNECTING:printf("- Network Interface connecting: \n");
                break;

            case NET_STATE_CONNECTED:printf("- Network Interface connected: \n");
                printf("   - IP address :  %s. \n", net_ntoa(&netif->ipaddr));
                break;

            case NET_STATE_DISCONNECTING:printf("- Network Interface disconnecting\n");
                break;

            case NET_STATE_DISCONNECTED:printf("- Network Interface disconnected\n");
                break;

            case NET_STATE_STOPPING:printf("- Network Interface stopping\n");
                break;

            case NET_STATE_STOPPED:printf("- Network Interface stopped\n");
                break;

            case NET_STATE_DEINITIALIZED:printf("- Network Interface de-initialized\n");
                break;

            default:break;
        }
    }
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

//
// Created by Cyril on 17/09/2021.
//

#ifndef VERTICES_STM32CUBE_PROJECTS_B_L4S5I_IOT01A_APPLICATIONS_VERTICES_CLIENT_HARDFAULT_H
#define VERTICES_STM32CUBE_PROJECTS_B_L4S5I_IOT01A_APPLICATIONS_VERTICES_CLIENT_HARDFAULT_H

typedef struct __attribute__((packed)) context_state_frame {
    uint32_t r0;
    uint32_t r1;
    uint32_t r2;
    uint32_t r3;
    uint32_t r12;
    uint32_t lr;
    uint32_t return_address;
    uint32_t xpsr;
} context_state_frame_t;

// NOTE: If you are using CMSIS, the registers can also be
// accessed through CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk
#define HALT_IF_DEBUGGING()                              \
  do {                                                   \
    if ((*(volatile uint32_t *)0xE000EDF0) & (1 << 0)) { \
      __BKPT(1);                                         \
    }                                                    \
} while (0)

void
hardfault_handler_c(context_state_frame_t *frame);

#endif //VERTICES_STM32CUBE_PROJECTS_B_L4S5I_IOT01A_APPLICATIONS_VERTICES_CLIENT_HARDFAULT_H

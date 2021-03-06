//
// Created by Cyril on 21/07/2021.
//

#include <stdbool.h>
#include <stm32l4xx.h>
#include <core_cm4.h>
#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include <vertices_log.h>
#include "hardfault.h"

static void
recover_from_task_fault(void)
{
    LOG_ERROR("Recovered from %s\r\n", pcTaskGetName(NULL));

    // TODO get back to running state by restarting the task somehow
    // at the moment we still reset the target as there is no proper handling
    NVIC_SystemReset();
}

// Disable optimizations for this function so "frame" argument
// does not get optimized away
__attribute__((optimize("O0")))
void
hardfault_handler_c(context_state_frame_t *frame)
{
    volatile uint32_t *cfsr = (volatile uint32_t *) 0xE000ED28;
    const uint32_t usage_fault_mask = 0xffff0000;
    const bool non_usage_fault_occurred =
        (*cfsr & ~usage_fault_mask) != 0;

    // the bottom 8 bits of the xpsr hold the exception number of the
    // executing exception or 0 if the processor is in Thread mode
    const bool faulted_from_exception = ((frame->xpsr & 0xFF) != 0);

    if (faulted_from_exception || non_usage_fault_occurred)
    {
        // If and only if a debugger is attached, execute a breakpoint
        // instruction so we can take a look at what triggered the fault
        HALT_IF_DEBUGGING();

        NVIC_SystemReset();
    }

    // Checking Usage fault
    // if UNDEFINSTR bit set, undefined behavior -> probably due to sanitizer
    // Analyze the stack to get the error origin
    if (SCB->CFSR & SCB_CFSR_UNDEFINSTR_Msk)
    {
        HALT_IF_DEBUGGING();
    }

    // Clear any logged faults from the CFSR
    *cfsr |= *cfsr;

    // the instruction we will return to when we exit from the exception
    // after these changes we will exit from hardfault_handler_c and start executing the function
    // at frame->return_address
    frame->return_address = (uint32_t) recover_from_task_fault;

    // the function we are returning to should never branch
    // so set lr to a pattern that would fault if it did
    frame->lr = 0xdeadbeef;

    // reset the psr state and only leave the
    // "thumb instruction interworking" bit set
    frame->xpsr = (1 << 24);
}
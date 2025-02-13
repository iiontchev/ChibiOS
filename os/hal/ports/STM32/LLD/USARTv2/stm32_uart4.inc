/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file    USARTv2/stm32_uart4.inc
 * @brief   Shared UART4 handler.
 *
 * @addtogroup STM32_UART4_HANDLER
 * @{
 */

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/* Registry checks for robustness.*/
#if !defined(STM32_HAS_UART4)
#error "STM32_HAS_UART4 not defined in registry"
#endif

#if STM32_HAS_UART4 == FALSE
#error "UART4 not present"
#endif

/* Priority settings checks.*/
#if !defined(STM32_IRQ_UART4_PRIORITY)
#error "STM32_IRQ_UART4_PRIORITY not defined in mcuconf.h"
#endif

#if !OSAL_IRQ_IS_VALID_PRIORITY(STM32_IRQ_UART4_PRIORITY)
#error "Invalid IRQ priority assigned to STM32_IRQ_UART4_PRIORITY"
#endif

/* Other checks.*/
#if (HAL_USE_SERIAL && STM32_SERIAL_USE_UART4) &&                           \
    (HAL_USE_UART && STM32_UART_USE_UART4)
#error "UART4 used by multiple drivers"
#endif

#if (HAL_USE_SERIAL && STM32_SERIAL_USE_UART4) ||                           \
    (HAL_USE_UART && STM32_UART_USE_UART4)
#define STM32_UART4_IS_USED         TRUE
#else
#define STM32_UART4_IS_USED         FALSE
#endif

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

static inline void uart4_irq_init(void) {
#if STM32_UART4_IS_USED
  nvicEnableVector(STM32_UART4_NUMBER, STM32_IRQ_UART4_PRIORITY);
#endif
}

static inline void uart4_irq_deinit(void) {
#if STM32_UART4_IS_USED
  nvicDisableVector(STM32_UART4_NUMBER);
#endif
}

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

#if STM32_UART4_IS_USED || defined(__DOXYGEN__)
/**
 * @brief   UART4 interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(STM32_UART4_HANDLER) {

  OSAL_IRQ_PROLOGUE();

#if HAL_USE_SERIAL
#if STM32_SERIAL_USE_UART4
  sd_lld_serve_interrupt(&SD4);
#endif
#endif
#if HAL_USE_UART
#if STM32_UART_USE_UART4
  uart_lld_serve_interrupt(&UARTD4);
#endif
#endif

  OSAL_IRQ_EPILOGUE();
}
#endif

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/** @} */

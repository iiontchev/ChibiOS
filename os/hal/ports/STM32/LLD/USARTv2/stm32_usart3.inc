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
 * @file    USARTv2/stm32_usart3.inc
 * @brief   Shared USART3 handler.
 *
 * @addtogroup STM32_USART3_HANDLER
 * @{
 */

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/* Registry checks for robustness.*/
#if !defined(STM32_HAS_USART3)
#error "STM32_HAS_USART3 not defined in registry"
#endif

#if STM32_HAS_USART3 == FALSE
#error "USART3 not present"
#endif

/* Priority settings checks.*/
#if !defined(STM32_IRQ_USART3_PRIORITY)
#error "STM32_IRQ_USART3_PRIORITY not defined in mcuconf.h"
#endif

#if !OSAL_IRQ_IS_VALID_PRIORITY(STM32_IRQ_USART3_PRIORITY)
#error "Invalid IRQ priority assigned to STM32_IRQ_USART3_PRIORITY"
#endif

/* Other checks.*/
#if (HAL_USE_SERIAL && STM32_SERIAL_USE_USART3) &&                          \
    (HAL_USE_UART && STM32_UART_USE_USART3)
#error "USART3 used by multiple drivers"
#endif

#if (HAL_USE_SERIAL && STM32_SERIAL_USE_USART3) ||                          \
    (HAL_USE_UART && STM32_UART_USE_USART3)
#define STM32_USART3_IS_USED        TRUE
#else
#define STM32_USART3_IS_USED        FALSE
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

static inline void usart3_irq_init(void) {
#if STM32_USART3_IS_USED
  nvicEnableVector(STM32_USART3_NUMBER, STM32_IRQ_USART3_PRIORITY);
#endif
}

static inline void usart3_irq_deinit(void) {
#if STM32_USART3_IS_USED
  nvicDisableVector(STM32_USART3_NUMBER);
#endif
}

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

#if STM32_USART3_IS_USED || defined(__DOXYGEN__)
/**
 * @brief   USART3 interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(STM32_USART3_HANDLER) {

  OSAL_IRQ_PROLOGUE();

#if HAL_USE_SERIAL
#if STM32_SERIAL_USE_USART3
  sd_lld_serve_interrupt(&SD3);
#endif
#endif
#if HAL_USE_UART
#if STM32_UART_USE_USART3
  uart_lld_serve_interrupt(&UARTD3);
#endif
#endif

  OSAL_IRQ_EPILOGUE();
}
#endif

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/** @} */

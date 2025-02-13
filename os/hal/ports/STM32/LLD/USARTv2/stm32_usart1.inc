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
 * @file    USARTv2/stm32_usart1.inc
 * @brief   Shared USART1 handler.
 *
 * @addtogroup STM32_USART1_HANDLER
 * @{
 */

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/* Registry checks for robustness.*/
#if !defined(STM32_HAS_USART1)
#error "STM32_HAS_USART1 not defined in registry"
#endif

#if STM32_HAS_USART1 == FALSE
#error "USART1 not present"
#endif

/* Priority settings checks.*/
#if !defined(STM32_IRQ_USART1_PRIORITY)
#error "STM32_IRQ_USART1_PRIORITY not defined in mcuconf.h"
#endif

#if !OSAL_IRQ_IS_VALID_PRIORITY(STM32_IRQ_USART1_PRIORITY)
#error "Invalid IRQ priority assigned to STM32_IRQ_USART1_PRIORITY"
#endif

/* Other checks.*/
#if (HAL_USE_SERIAL && STM32_SERIAL_USE_USART1) &&                          \
    (HAL_USE_UART && STM32_UART_USE_USART1)
#error "USART1 used by multiple drivers"
#endif

#if (HAL_USE_SERIAL && STM32_SERIAL_USE_USART1) ||                          \
    (HAL_USE_UART && STM32_UART_USE_USART1)
#define STM32_USART1_IS_USED        TRUE
#else
#define STM32_USART1_IS_USED        FALSE
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

static inline void usart1_irq_init(void) {
#if STM32_USART1_IS_USED
  nvicEnableVector(STM32_USART1_NUMBER, STM32_IRQ_USART1_PRIORITY);
#endif
}

static inline void usart1_irq_deinit(void) {
#if STM32_USART1_IS_USED
  nvicDisableVector(STM32_USART1_NUMBER);
#endif
}

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

#if STM32_USART1_IS_USED|| defined(__DOXYGEN__)
/**
 * @brief   USART1 interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(STM32_USART1_HANDLER) {

  OSAL_IRQ_PROLOGUE();

#if HAL_USE_SERIAL
#if STM32_SERIAL_USE_USART1
  sd_lld_serve_interrupt(&SD1);
#endif
#endif
#if HAL_USE_UART
#if STM32_UART_USE_USART1
  uart_lld_serve_interrupt(&UARTD1);
#endif
#endif

  OSAL_IRQ_EPILOGUE();
}
#endif

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/** @} */

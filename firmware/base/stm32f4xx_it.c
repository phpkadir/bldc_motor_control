/**
  ******************************************************************************
  * @file    GPIO/GPIO_IOToggle/stm32f4xx_it.c
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    04-November-2016
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"

/** @addtogroup STM32F4xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup GPIO_IOToggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
volatile uint64_t _ms_ticks = 0;
void SysTick_Handler(void)
{
	/* overflows in eternity */
	++_ms_ticks;
}

/* return time in ms, from startup */
uint64_t get_time(void)
{
	return _ms_ticks;
}

void delay(uint32_t ms)
{
	uint64_t hold_time = _ms_ticks;
	while (_ms_ticks < hold_time + ms)
		;
}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f40xx.s/startup_stm32f427x.s/startup_stm32f429x.s).    */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/
void ihm07_hall_state_change_callback(void) __attribute__ ((weak));
void EXTI15_10_IRQHandler(void)
{
        /**
         * NVIC_IRQChannelPreemptionPriority = 0;
         * NVIC_IRQChannelSubPriority = 0;
         */
        if (EXTI_GetITStatus(EXTI_Line15) == SET) {

                EXTI_ClearITPendingBit(EXTI_Line15);
                ihm07_hall_state_change_callback();
        }

        if (EXTI_GetITStatus(EXTI_Line10) == SET) {
                EXTI_ClearITPendingBit(EXTI_Line10);
                ihm07_hall_state_change_callback();
        }
}

void EXTI3_IRQHandler(void)
{
        /**
         * NVIC_IRQChannelPreemptionPriority = 0;
         * NVIC_IRQChannelSubPriority = 0;
         */

        if (EXTI_GetITStatus(EXTI_Line3) == SET) {

                EXTI_ClearITPendingBit(EXTI_Line3);
                ihm07_hall_state_change_callback();
        }
}

void ihm07_pwm_duty_interrupt_callback(void) __attribute__ ((weak));
void TIM1_CC_IRQHandler(void)
{
        /**
         * NVIC_IRQChannelPreemptionPriority = 0;
         * NVIC_IRQChannelSubPriority = 1;
         */
        if (TIM_GetITStatus(TIM1, TIM_IT_CC4) == SET) {
                TIM_ClearITPendingBit(TIM1, TIM_IT_CC4);
                ihm07_pwm_duty_interrupt_callback();
        }
}

extern void serial_packet_read(uint8_t byt);
void USART1_IRQHandler(void)
{
        /**
         * NVIC_IRQChannelPreemptionPriority = 0;
         * NVIC_IRQChannelSubPriority = 2;
         */
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET) {
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		uint16_t data = USART_ReceiveData(USART1);
                serial_packet_read((uint8_t) data);
        }
}

void ihm07_adc_eoc_callback(void) __attribute__ ((weak));
void ADC_IRQHandler(void)
{
        /**
         * NVIC_IRQChannelPreemptionPriority = 1;
         * NVIC_IRQChannelSubPriority = 0;
         */
        if (ADC_GetITStatus(ADC1, ADC_IT_EOC) == SET) {
                ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
                ihm07_adc_eoc_callback();
        }
}

void ihm07_adc_dma_transfer_complete_callback(void) __attribute__ ((weak));
void DMA2_Stream0_IRQHandler(void)
{
        /**
         * NVIC_IRQChannelPreemptionPriority = 0;
         * NVIC_IRQChannelSubPriority = 3;
         */
        if (DMA_GetITStatus(DMA2_Stream0, DMA_IT_TCIF0) == SET) {
                DMA_ClearITPendingBit(DMA2_Stream0, DMA_IT_TCIF0);
                ihm07_adc_dma_transfer_complete_callback();
        }
}

void ang_spd_sensor_timer_overflow_callback(void) __attribute__ ((weak));
void TIM2_IRQHandler(void)
{
        /**
         * NVIC_IRQChannelPreemptionPriority = 1;
         * NVIC_IRQChannelSubPriority = 1;
         */
        if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) {
                TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
                ang_spd_sensor_timer_overflow_callback();
        }
}
/**
  * @}
  */

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

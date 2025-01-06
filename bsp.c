/*
 * bsp.c
 *
 *  Created on: Dec 30, 2024
 *      Author: Minsig
 */


#include "bsp.h"

void SystemClock_Config(void);

void bspInit(void)
{
  HAL_Init(); // cubeMX lib
      SystemClock_Config(); // cubeMX lib

      // GPIO Clock Enable
      __HAL_RCC_GPIOC_CLK_ENABLE(); // 추가 (PC13 사용)
      __HAL_RCC_GPIOD_CLK_ENABLE(); // 기존 유지
      __HAL_RCC_GPIOA_CLK_ENABLE(); // 기존 유지

      GPIO_InitTypeDef GPIO_InitStruct = {0};

      // Configure GPIO pin : PC13 (Interrupt 설정)
      GPIO_InitStruct.Pin = GPIO_PIN_13;
      GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
      GPIO_InitStruct.Pull = GPIO_NOPULL;
      HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

      // EXTI interrupt init (PC13에 대한 인터럽트 활성화)
      HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
      HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

      // Configure GPIO pin : PA5 (Open-Drain 설정)
      GPIO_InitStruct.Pin = GPIO_PIN_5;
      GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD; // Open-Drain 설정
      GPIO_InitStruct.Pull = GPIO_NOPULL;
      GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
      HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

      // PA5 초기값 설정 (Open-Drain 스타일)
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
      delay(100); // 외부에서 구현된 delay 함수
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);

      MX_USART2_UART_Init();
}

void delay(uint32_t ms)
{
  HAL_Delay(ms);
}

uint32_t millis(void)
{
  return HAL_GetTick();
}

//lib에서 가져옴
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

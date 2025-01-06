/*
 * ap.c
 *
 *  Created on: Dec 30, 2024
 *      Author: Minsig
 */


#include "ap.h"

uint8_t rx_data;

void apInit(void)
{

}

int __io_putchar(int ch)
{
     (void) HAL_UART_Transmit(&huart2, (uint8_t*) &ch, 1, 100);
     return ch;
}

void print_cmd()
{
  printf("----------\r\n%s\r\n%s\r\n----------\r\nEnter Command: ",
      "1: LED On",
      "2: LED Off");
}

void apMain(void)
{
  //const char *message = "Hello, UART!\r\n";

  print_cmd();

  HAL_UART_Receive_IT(&huart2, &rx_data, 1);

  while(1)
  {
    //HAL_UART_Transmit(&huart2, (uint8_t *)message, strlen(message), HAL_MAX_DELAY);
    //ledToggle(_DEF_LED1);
    //delay(500);
  }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == GPIO_PIN_13)
  {
    printf("Button Pressed\r\n");
  }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART2) {
    if (rx_data == '1')
    {
      printf("LED On execute\r\n");
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
    }
    else if (rx_data == '2')
    {
      printf("LED Off execute\r\n");
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
    }
    else
    {
      printf("Invalid input!\r\n");
    }
    HAL_UART_Receive_IT(&huart2, &rx_data, 1);
    print_cmd();
  }
}


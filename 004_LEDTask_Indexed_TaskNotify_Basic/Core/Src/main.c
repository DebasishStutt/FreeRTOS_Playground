/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
// #include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
#define DWT_CTRL_CNT *((volatile uint32_t*)0xE0001000)
TaskHandle_t greenLedTaskHandle;
TaskHandle_t tickCountingTaskHandle;
TaskHandle_t sendDataToPCHandle;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
static void greenLedTask_handler(void* parameters);
static void tickCountingTask_handler(void* parameters);

extern  void SEGGER_UART_init(uint32_t);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
static void greenLedTask_handler(void *parameters) {
	char msg[100];
	int count = 1;
	int count2 = 0;

	BaseType_t notifyResult = 0u;
	TickType_t prevWakeTime = xTaskGetTickCount();
	TickType_t frequency = 200;

	 while(1) {
		 notifyResult = xTaskNotifyWaitIndexed(0, 0, 0, NULL, 2000); //(0, 0, 0, 2000);

		 if (notifyResult == pdTRUE) {
		 	snprintf(msg,100,"%s\n", "Notification at greenLED task received\n");
		 	SEGGER_SYSVIEW_PrintfTarget(msg);
		 }
		//snprintf(msg,100,"%s\n", (char*)parameters);
		//SEGGER_SYSVIEW_PrintfTarget(msg);
		if (count == 6) {
			count = 1;
		}

		count2 = count;
		while (count2 > 0) {
			HAL_GPIO_TogglePin(GPIOA, greenLed);

			// using fixed delay span
			// vTaskDelay(pdMS_TO_TICKS(200));

			// using fixed task wake up
			vTaskDelayUntil(&prevWakeTime, frequency);

			HAL_GPIO_TogglePin(GPIOA, greenLed);


			// using fixed delay span
		    // vTaskDelay(pdMS_TO_TICKS(200));

			// using fixed task wake up
			vTaskDelayUntil(&prevWakeTime, frequency);
			count2--;
		}
		count++;
		// HAL_GPIO_TogglePin(GPIOA, greenLed);
		HAL_GPIO_WritePin(GPIOA, greenLed, 0u);
		//vTaskDelay(pdMS_TO_TICKS(2000));
		vTaskDelayUntil(&prevWakeTime, (frequency*10u));

		// printf("%s\n", (char *)parameters);
		// taskYIELD();
		xTaskNotifyIndexed(tickCountingTaskHandle, 0, 0, eNoAction); //(tickCountingTaskHandle, 0, 0);
	 }
}

static void sendDataToPC_handler(void *parameters) {
	char msg[100];
	char time[50];
	uint32_t notificationVal;
	while(1) {
		// printf("%s\n", (char *)parameters);
		// snprintf(msg,100,"%s\n", (char*)parameters);
		// SEGGER_SYSVIEW_PrintfTarget(msg);
		// taskYIELD();
		if ((xTaskNotifyWaitIndexed(1, 0, 0, &notificationVal, 2000)) == pdTRUE) {
			snprintf(msg, 100, "%s", (char*)parameters);

			snprintf(time, 50, "%lu\n", notificationVal);

			strcat(msg, time);

			SEGGER_SYSVIEW_PrintfTarget(msg);

			// xTaskNotifyIndexed(tickCountingTaskHandle, 1, 0, eNoAction);
			xTaskGenericNotify( tickCountingTaskHandle, 1, 0, eNoAction, NULL );
		} else {
			// while (1);
		}


	}
}

static void tickCountingTask_handler(void *parameters) {
	char msg[100];
	uint32_t secElapsed = 0u;
	uint32_t currSysTimeMS = xTaskGetTickCount() * (1/configTICK_RATE_HZ) * 1000;
	uint32_t prevSysTimeMS = currSysTimeMS;
	while(1) {
		// printf("%s\n", (char *)parameters);
		// snprintf(msg,100,"%s\n", (char*)parameters);
		// SEGGER_SYSVIEW_PrintfTarget(msg);
		// taskYIELD();
		if ((currSysTimeMS - prevSysTimeMS) >= 1000) {
			prevSysTimeMS = currSysTimeMS;
			secElapsed++;
			xTaskNotifyIndexed(sendDataToPCHandle, 1, secElapsed, eSetValueWithOverwrite);
			if ((xTaskNotifyWaitIndexed(1, 0, 0, NULL, 2000)) == pdFALSE) {
				while (1);
			}
		}
		xTaskNotifyIndexed(greenLedTaskHandle, 0, 0, eNoAction); //(greenLedTaskHandle, 0, 0);

		BaseType_t notifyResult = xTaskNotifyWaitIndexed(0, 0, 0, NULL, 2000); //(0, 0, 0, 2000);

		if (notifyResult == pdTRUE) {
			snprintf(msg,100,"%s\n", "Notification at tickcount received\n");
			SEGGER_SYSVIEW_PrintfTarget(msg);
		}

		currSysTimeMS = xTaskGetTickCount();//  * (1/configTICK_RATE_HZ) * 1000;
	}
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */


	BaseType_t status;

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
  // enable cycle counter register to have proper time stamps in SysVIew
  DWT_CTRL_CNT |= (1 << 0);

  SEGGER_UART_init(500000);

  // configure and call sysview apis to record
  SEGGER_SYSVIEW_Conf();
  // SEGGER_SYSVIEW_Start();


  // create tasks
  status = xTaskCreate(greenLedTask_handler, "greenLedTask", 200, "Hello from greenLedTask", 2, &greenLedTaskHandle);
  configASSERT(status == pdPASS);

  status = xTaskCreate(tickCountingTask_handler, "tickCountingTask", 200, "Hello from tickCountingTask", 2, &tickCountingTaskHandle);
  configASSERT(status == pdPASS);

  status = xTaskCreate(sendDataToPC_handler, "sendDataToPCTask", 200, "Hello from sendDataToPCTask: ", 2, &sendDataToPCHandle);
    configASSERT(status == pdPASS);

  // start scheduler to run tasks
  vTaskStartScheduler();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : USART_TX_Pin USART_RX_Pin */
  GPIO_InitStruct.Pin = USART_TX_Pin|USART_RX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
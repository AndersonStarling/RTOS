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
#include "rtc.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "FreeRTOS.h"
#include "task.h"
#include "OS_Task.h"
#include "DWT_Counter.h"
#include "Rtc_Lib.h"
#include "Led_Mode.h"
#include "RTOS_State_Machine.h"
#include "queue.h"

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
TaskHandle_t Task_Print_Queue_Kernel_Ptr;
TaskHandle_t Task_Print_Menu_Kernel_Ptr;
TaskHandle_t Task_Led_Effect_Kernel_Ptr;
TaskHandle_t Task_RTC_Kernel_Ptr;
TaskHandle_t Task_Handle_Received_Command_Kernel_Ptr;
TaskHandle_t Task_RTC_Configure_Hour_Kernel_Ptr;
TaskHandle_t Task_RTC_Configure_Min_Kernel_Ptr;
TaskHandle_t Task_RTC_Configure_Second_Kernel_Ptr;
TaskHandle_t Task_RTC_Configure_Time_Kernel_Ptr;
TaskHandle_t Task_RTC_Configure_Date_Kernel_Ptr;
TaskHandle_t Task_RTC_Configure_Day_Kernel_Ptr;
TaskHandle_t Task_RTC_Configure_Month_Kernel_Ptr;
TaskHandle_t Task_RTC_Configure_Year_Kernel_Ptr;

QueueHandle_t Queue_Data;
QueueHandle_t Queue_Print;

uint8_t App_Data = 0;

RTOS_State_Machine_enum_t Global_State = main_menu;




/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void SEGGER_UART_init(U32 baud);
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
  MX_RTC_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

    DWT_Enable();
    SEGGER_UART_init(250000);

    SEGGER_SYSVIEW_Conf();

    /* Create task 1 */
    status = xTaskCreate(   Task_Print_Queue,
                            "Task_1",
                            400,
                            "Task Print Queue",
                            2,
                            &Task_Print_Queue_Kernel_Ptr
                          );

    /* Check xTaskCreate status */
    configASSERT(status == pdPASS);

    /* Create task 2 */
    status = xTaskCreate(   Task_Print_Menu,
                            "Task_2",
                            400,
                            "Task Print Menu",
                            2,
                            &Task_Print_Menu_Kernel_Ptr
                          );

    /* Check xTaskCreate status */
    configASSERT(status == pdPASS);

    /* Create task 3 */
    status = xTaskCreate(   Task_Led_Effect,
                            "Task_3",
                            400,
                            "Task Led Effect",
                            2,
                            &Task_Led_Effect_Kernel_Ptr
                          );

    /* Check xTaskCreate status */
    configASSERT(status == pdPASS);

    /* Create task 4 */
    status = xTaskCreate(   Task_RTC,
                            "Task_4",
                            400,
                            "Task RTC",
                            2,
                            &Task_RTC_Kernel_Ptr
                          );

    /* Check xTaskCreate status */
    configASSERT(status == pdPASS);

    /* Create task 5 */
    status = xTaskCreate(   Task_Handle_Received_Command,
                            "Task_5",
                            400,
                            "Task Handle received command",
                            2,
                            &Task_Handle_Received_Command_Kernel_Ptr
                          );

    /* Check xTaskCreate status */
    configASSERT(status == pdPASS);

    /* Create task 6 */
    status = xTaskCreate(   Task_RTC_Configure_Hour,
                            "Task_6",
                            400,
                            "Task RTC configure Hour",
                            2,
                            &Task_RTC_Configure_Hour_Kernel_Ptr
                          );

    /* Check xTaskCreate status */
    configASSERT(status == pdPASS);

    /* Create task 7 */
    status = xTaskCreate(   Task_RTC_Configure_Min,
                            "Task_7",
                            400,
                            "Task RTC configure Min",
                            2,
                            &Task_RTC_Configure_Min_Kernel_Ptr
                          );

    /* Check xTaskCreate status */
    configASSERT(status == pdPASS);

    /* Create task 8 */
    status = xTaskCreate(   Task_RTC_Configure_Second,
                            "Task_8",
                            400,
                            "Task RTC configure Second",
                            2,
                            &Task_RTC_Configure_Second_Kernel_Ptr
                          );

    /* Check xTaskCreate status */
    configASSERT(status == pdPASS);

    /* Create task 9 */
    status = xTaskCreate(   Task_RTC_Configure_Time,
                            "Task_9",
                            400,
                            "Task RTC configure Time",
                            2,
                            &Task_RTC_Configure_Time_Kernel_Ptr
                          );

    /* Check xTaskCreate status */
    configASSERT(status == pdPASS);

    /* Create task 10 */
    status = xTaskCreate(   Task_RTC_Configure_Date,
                            "Task_10",
                            400,
                            "Task RTC configure Date",
                            2,
                            &Task_RTC_Configure_Date_Kernel_Ptr
                          );

    /* Check xTaskCreate status */
    configASSERT(status == pdPASS);

    /* Create task 11 */
    status = xTaskCreate(   Task_RTC_Configure_Day,
                            "Task_11",
                            400,
                            "Task RTC configure Day",
                            2,
                            &Task_RTC_Configure_Day_Kernel_Ptr
                          );

    /* Check xTaskCreate status */
    configASSERT(status == pdPASS);

    /* Create task 12 */
    status = xTaskCreate(   Task_RTC_Configure_Month,
                            "Task_12",
                            400,
                            "Task RTC configure Month",
                            2,
                            &Task_RTC_Configure_Month_Kernel_Ptr
                          );

    /* Create task 13 */
    status = xTaskCreate(   Task_RTC_Configure_Year,
                            "Task_13",
                            400,
                            "Task RTC configure Year",
                            2,
                            &Task_RTC_Configure_Year_Kernel_Ptr
                          );

    /* Check xTaskCreate status */
    configASSERT(status == pdPASS);

    /* Create task 14 */
    status = xTaskCreate(   Task_RTC_Configure_Date,
                            "Task_14",
                            400,
                            "Task RTC configure Date",
                            2,
                            &Task_RTC_Configure_Date_Kernel_Ptr
                          );

    /* Check xTaskCreate status */
    configASSERT(status == pdPASS);

    LED_Mode_Off();

    /* Create queue print */
    Queue_Data = xQueueCreate (10, sizeof(char));
	configASSERT(Queue_Data != NULL);

    /* Create queue print */
    Queue_Print = xQueueCreate (10, sizeof(size_t));
	configASSERT(Queue_Print != NULL);

    /* Enable UART data byte reception again in IT mode */
	HAL_UART_Receive_IT(&huart1, (uint8_t*)&App_Data, 1);

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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 84;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM3 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM3) {
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

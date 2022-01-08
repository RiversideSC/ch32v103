/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2020/12/1
* Description        : Main program body.
*******************************************************************************/

/*
 *@Note
 ���ڴ�ӡ�������̣�
 USART1_Tx(PA9)��
 ��������ʾ PA11��PA12 ��ơ�

*/

#include "debug.h"
#include "Config.h"
#include "FreeRTOS.h"
#include "task.h"
/* Global typedef */

/* Global define */
//-------------���������ڲ���-------------
#define TASK1_TASK_PRIO     2           //---���ȼ�---
#define TASK1_STK_SIZE      128         //----����ջ���ȣ���Ҫע������M3��ͬ������ջͬʱҲ��Ҫ���ж�ʹ��----
TaskHandle_t Task1Task_Handler;         //---������---
#define TASK2_TASK_PRIO     2
#define TASK2_STK_SIZE      128
TaskHandle_t Task2Task_Handler;

/* Global Variable */

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
void task1_task(void *pvParameters)
{
    while(1)
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_12);
        vTaskDelay(700);
        GPIO_ResetBits(GPIOA, GPIO_Pin_12);
        vTaskDelay(700);
    }
}
void task2_task(void *pvParameters)
{
    while(1)
    {
        GPIO_ResetBits(GPIOA, GPIO_Pin_11);
        vTaskDelay(700);
        GPIO_SetBits(GPIOA, GPIO_Pin_11);
        vTaskDelay(700);
    }
}

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);    //------����ʹ�÷���1��ֱ�Ӳ������ȼ��Ĵ���------
	NVIC_HaltPushCfg(DISABLE);          //-----Ӳ��ѹջ�ر�-----
	init_keyAndLed();                   //-----�������У�����Ϊ��ʼ��LED-----
    //---------------������������--------------------
	xTaskCreate((TaskFunction_t )task2_task,
	                    (const char*    )"task2_task",
	                    (uint16_t       )TASK2_STK_SIZE,
	                    (void*          )NULL,
	                    (UBaseType_t    )TASK2_TASK_PRIO,
	                    (TaskHandle_t*  )&Task2Task_Handler);

	xTaskCreate((TaskFunction_t )task1_task,
                    (const char*    )"task1_task",
                    (uint16_t       )TASK1_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )TASK1_TASK_PRIO,
                    (TaskHandle_t*  )&Task1Task_Handler);
	//--------����������--------
	vTaskStartScheduler();
	while(1)
	{
	    ;
	}
}


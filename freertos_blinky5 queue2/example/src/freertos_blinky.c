/*
 * @brief FreeRTOS Blinky example
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2014
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
//xQueueHandle xQueueCreate(5,sizeof( unsigned long ));
//
//#define LED0_GPIO_PORT_NUM                      0
//#define LED1_GPIO_PORT_NUM                      1
//#define LED2_GPIO_PORT_NUM                      2
//#define QUEUE_LENGTH    						10
//#define ITEM_SIZE       sizeof( uint8_t )



/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/
  //xQueueHandle Global_Queue_Handle = 0;
//  xQueueHandle xQueue = NULL;
//xQueueHandle xQueue = NULL;
 //xQueue = xQueueCreate( 10, sizeof(uint8_t));
/* Sets up system hardware */

 //xQueue = xQueueCreate( 5,sizeof( uint8_t ) );
//static xQueue = xQueueCreate( 5, sizeof( uint8_t ) );


//xQueue = xQueueCreate(5,sizeof(uint8_t ));

static void prvSetupHardware(void)
  {

  	SystemCoreClockUpdate();
  	Board_Init();

  	/* Initial LED0 state is off */
  	Board_LED_Set(0, false);
  	 Board_LED_Set(1, false);
  	 Board_LED_Set(2, false);
  	 Board_LED_Set(0, TRUE);
  	 Board_LED_Set(1, TRUE);
  	 Board_LED_Set(2, TRUE);
  }
xQueueHandle xQueue;
/* LED1 toggle thread */
static void sender_task(void *pvParameters) {
	//xQueueHandle xQueue = NULL;
	//bool LedState = false;
//	xQueue = xQueueCreate( 5, sizeof(int) );
	//int32_t lValueToSend;
	//BASE_TYPE_t xStatus;
	//xQueue = xQueueCreate( 10, sizeof(uint8_t));

int x=(0,1,2);
//int Datatosend = x;
//const unsigned long DataToSend = 100UL;
//volatile j=0;
//RGB_LED_t LED_colour = *((RGB_LED_t*) pvParameters);
//const  xBlockTime = pdMSTOTICKS( 200 );
//lValueToSend = ( int32_t ) pvParameters;
//
//TickType_t xNextWakeTime;
//xNextWakeTime = xTaskGetTickCount();


		while (1)
		{

			Board_LED_Set(x, false);
		if(!	xQueueSend( xQueue,&x,portMAX_DELAY));
		{

				Board_LED_Set(x, TRUE);

		}
vTaskDelay(configTICK_RATE_HZ / 1);
		}
//			if(x==1)
//			{
//				Board_LED_Set(1, false);
//				vTaskDelay(configTICK_RATE_HZ / 1);
//				Board_LED_Set(1, TRUE);
//			}
//
//			if(x==2){
//				Board_LED_Set(2, false);
//				vTaskDelay(configTICK_RATE_HZ / 1);
//				Board_LED_Set(2, TRUE);
//			}

//
//		/* About a 3Hz on/off toggle rate */
		//vTaskDelay(configTICK_RATE_HZ / 6);
	}


/* LED2 toggle thread */
static void receivertask(void *pvParameters) {
	//int32_t lReceivedValue;
	//extern xQueueHandle xQueue;
	//volatile j=0;

	//const TICK_COUNT xBlockTime = pdMSTOTICKS( 200 );
int y=(0,1,2);
//unsigned long ulDatatoreceive;
//const unsigned long ulExpectedValue = 100UL;

//int Datatosend=x;
//int  Datatoreceive = Datatosend;
while (1) {


	if(!xQueueReceive(xQueue,&y, portMAX_DELAY));{
		Board_LED_Set(0, false);
		vTaskDelay(configTICK_RATE_HZ / 1);
		Board_LED_Set(0, TRUE);
	}

		if(!xQueueReceive(xQueue,&y, portMAX_DELAY));
		{
		Board_LED_Set(1, false);
		vTaskDelay(configTICK_RATE_HZ / 1);
		Board_LED_Set(1, TRUE);
	}

		if(!xQueueReceive(xQueue,&y, portMAX_DELAY));{
			Board_LED_Set(2, false);
		vTaskDelay(configTICK_RATE_HZ / 1);
			Board_LED_Set(2, TRUE);
		}
}/* About a 7Hz on/off toggle rate */
}/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief	main routine for FreeRTOS blinky example
 * @return	Nothing, function should not exit
 */
int main(void)
{
	// xQueueHandle xQueue = NULL;
	xQueue = xQueueCreate( 5, sizeof( int ));
	//int x= 0;
	prvSetupHardware();

//	xQueue_led = xQueueCreate(10,sizeof(uint32_t ));

	//Global_Queue_Handle = xQueueCreate(3, sizeof(int));
	/* LED1 toggle thread */
	//if(xQueue = NULL)
//	xQueueHandle xQueueCreate(5,sizeof( unsigned long ));
	xTaskCreate(sender_task, (signed char *) "vTaskLed1",
				configMINIMAL_STACK_SIZE,NULL , (tskIDLE_PRIORITY + 2UL),
				(xTaskHandle *) NULL);

	/* LED2 toggle thread */
	xTaskCreate(receivertask, (signed char *) "vTaskLed2",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
				(xTaskHandle *) NULL);

	/* Start the scheduler */
	vTaskStartScheduler();

	/* Should never arrive here */
	return 1;
}

/**
 * @}
 */

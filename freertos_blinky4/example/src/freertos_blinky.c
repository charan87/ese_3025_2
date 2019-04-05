/* Authors:
 * @ charan87, mohammed abdul aziz
* Here in this code we are using semaphore mutex to blink sequential leds with lpc1769 board
*/
#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
/* created semaphore referenced to this handle*/
xSemaphoreHandle xSemaphore = 0;
/* Sets up system hardware */
static void prvSetupHardware(void)
{
SystemCoreClockUpdate();
Board_Init();

/* Initial LED state is off when TRUE
 * Initial LED state is on when False
 * LED0 refered to Redcolor
 * LED1 Refered to Greencolor
 * LED2 Refered to Bluecolor */

Board_LED_Set(0, false);
Board_LED_Set(1, false);
Board_LED_Set(2, false);
Board_LED_Set(0, TRUE);
Board_LED_Set(1, TRUE);
Board_LED_Set(2, TRUE);

}

/* Creating LED1 task */
static void vLEDTask1(void *pvParameters) {
while (1) {
if(xSemaphoreTake(xSemaphore,portMAX_DELAY)){
Board_LED_Set(0, false);
vTaskDelay(configTICK_RATE_HZ / 1);
Board_LED_Set(0, TRUE);
xSemaphoreGive(xSemaphore);
}
}
}
/*Creating LED2 task  */
static void vLEDTask2(void *pvParameters) {
while (1) {
if(xSemaphoreTake(xSemaphore,portMAX_DELAY)){
Board_LED_Set(1, false);
vTaskDelay(configTICK_RATE_HZ / 1);
Board_LED_Set(1, TRUE);
xSemaphoreGive(xSemaphore);
}
}
}
/* Creating LED3 task */
static void vLEDTask3(void *pvParameters) {
while (1) {
if(xSemaphoreTake(xSemaphore,portMAX_DELAY)){
Board_LED_Set(2, false);
vTaskDelay(configTICK_RATE_HZ / 1);
Board_LED_Set(2, TRUE);
	 xSemaphoreGive(xSemaphore);

}
}
}
int main(void)
{
prvSetupHardware();
/*creating semaphore Mutex*/
xSemaphore = xSemaphoreCreateMutex();
/* LED1 Task creating here */
xTaskCreate(vLEDTask1, (signed char *) "vTaskLed1",
configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
(xTaskHandle *) NULL);
/* LED2 Task creating here */
xTaskCreate(vLEDTask2, (signed char *) "vTaskLed2",
			configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
			(xTaskHandle *) NULL);
/* LED3 Task creating here */
xTaskCreate(vLEDTask3, (signed char *) "vTaskLed3",
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
*/

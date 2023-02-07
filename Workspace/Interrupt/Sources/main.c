#include "MK64F12.h"

void DelayFunction(void);

int main(void)
{

	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK; /*Enable Port B Clock Gate Control*/
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;/*Enable Port C Clock Gate Control*/
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK; /*Enable Port A Clock Gate Control*/
	PORTB_PCR21 = 0x100; /*Blue Led, configured as Alternative 1 (GPIO)*/
	PORTB_PCR22 = 0x100;/*Red Led, configured as Alternative 1 (GPIO)*/
	PORTC_PCR6 = 0x90100; /*PORTC_PCR6: ISF=0,IRQC=9,MUX=1 */
	PORTA_PCR4 = 0x100;/*Changing the NMI to GPIO*/
	GPIOB_PDDR |= (1 << 21);/*Setting the bit 21 of the port B as Output*/
	GPIOB_PDDR |= (1 << 22);/*Setting the bit 22 of the port B as Output*/
	GPIOC_PDDR |= (0 << 6);/*Setting the bit 6 of the port C as Input*/
	/*Turn off Red and Blue Leds*/
	GPIOB_PDOR |= (1 << 22);/*Turn Off Red Led*/
	GPIOB_PDOR |= (1 << 21);/*Turn Off Blue Led*/

	PORTC_ISFR = PORT_ISFR_ISF(0x40); /* Clear interrupt status flag */
	NVIC_EnableIRQ(PORTC_IRQn);/*Enable the PORTC interrupt*/

	for(;;)
	{
		GPIOB_PTOR |= (1 << 22); /*Red LED blinking*/
		DelayFunction();
	}
	return 0;
}

void PORTC_IRQHandler(void)
{
	DelayFunction();
	GPIOB_PSOR |= (1 << 22);/*Turn Off Red Led*/
	GPIOB_PCOR |= (1 << 21);/*Turn On Blue Led*/
	DelayFunction();
	GPIOB_PSOR |= (1 << 21);/*Turn Off Blue Led*/
	DelayFunction();
	PORTC_ISFR = PORT_ISFR_ISF(0x40);/* Clear interrupt status flag */
}

void DelayFunction(void)
{
	int cnt;
	for(cnt=0; cnt<1000000; cnt++)
	{

	}
}

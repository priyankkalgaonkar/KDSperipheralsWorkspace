#include "MK64F12.h"

int main(void)
{

	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK; /*Enable Port B Clock Gate Control*/
	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;/*Enable Port E Clock Gate Control*/
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;/*Enable Port C Clock Gate Control*/
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK; /*Enable Port A Clock Gate Control*/
	PORTB_PCR21 = 0x100; /*Blue Led, configured as Alternative 1 (GPIO)*/
	PORTB_PCR22 = 0x100;/*Red Led, configured as Alternative 1 (GPIO)*/
	PORTE_PCR26 = 0x100;/*Green Led, configured as Alternative 1 (GPIO)*/
	PORTC_PCR6 = 0X100;/*Switch 2, configured as Alternative 1 (GPIO)*/
	PORTA_PCR4 = 0x100;/*Changing the NMI to GPIO*/
	GPIOB_PDDR |= (1 << 21);/*Setting the bit 21 of the port B as Output*/
	GPIOB_PDDR |= (1 << 22);/*Setting the bit 22 of the port B as Output*/
	GPIOE_PDDR |= (1 << 26);/*Setting the bit 26 of the port E as Output*/
	GPIOC_PDDR |= (0 << 6);/*Setting the bit 6 of the port C as Input*/
	/*Turn off RGB Leds*/
	GPIOB_PDOR |= (1 << 22);/*Turn Off Red Led*/
	GPIOB_PDOR |= (1 << 21);/*Turn Off Blue Led*/
	GPIOE_PDOR |= (1 << 26);/*Turn Off Green Led*/

	unsigned long Counter = 0x100000;/*Delay Value*/

	for(;;)
	{
		if(GPIOC_PDIR == 0)/*If the Switch 2 was press*/
		{
			GPIOB_PDOR = (1 << 21);/*Turn On Red Led*/
			while(Counter != 0)/*Wait Delay Value*/
			{
				Counter--;
			}
			Counter = 0x100000;/*Recharger the Delay*/
			GPIOB_PDOR = (1 << 22) | ( 1 << 21); /*Turn Off Red Led*/
			while(Counter != 0)/*Wait Delay Value*/
			{
				Counter--;
			}
			Counter = 0x100000;/*Recharger the Delay*/
			GPIOE_PDOR = (0 << 26);/*Turn On Green Led*/
			while(Counter != 0)/*Wait Delay Value*/
			{
				Counter--;
			}
			Counter = 0x100000;/*Recharger the Delay*/
			GPIOE_PDOR = (1 << 26); /*Turn Off Green Led*/
			while(Counter != 0)/*Wait Delay Value*/
			{
				Counter--;
			}
			Counter = 0x100000;/*Recharger the Delay*/
			GPIOB_PDOR = (1 << 22);/*Turn On Blue Led*/
			while(Counter != 0)/*Wait Delay Value*/
			{
				Counter--;
			}
			Counter = 0x100000;/*Recharger the Delay*/
			GPIOB_PDOR = (1 << 21) | (1 << 22); /*Turn Off Blue Led*/
			while(Counter != 0)/*Wait Delay Value*/
			{
				Counter--;
			}
			Counter = 0x100000;/*Recharger the Delay*/
		}
	}
	return 0;
}


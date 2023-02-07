#include "MK64F12.h"

void uart_putchar(char ch);
unsigned short ADC_read16b(void);
void put(char *ptr_str);
void DelayFunction(void);

int main(void)
{
    SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;/*Enable the ADC0 Clock*/
    ADC0_CFG1 |= ADC_CFG1_MODE(3);/*16bits ADC*/
    ADC0_SC1A |= ADC_SC1_ADCH(31);/*Disable the module, ADCH = 11111 */
    uint16_t ubd;/*Variable to save the baud rate*/
    uint8_t temp;
    SIM_SCGC4 |= SIM_SCGC4_UART0_MASK; /*Enable the UART clock*/
    SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;/*Enable the PORTB clock*/
    PORTB_PCR16 |= PORT_PCR_MUX(3);
    PORTB_PCR17 |= PORT_PCR_MUX(3);
    UART0_C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK ); /*Disable Tx and Rx*/
    UART0_C1 = 0; /*Dafaultsettings of the register*/
    ubd= (uint16_t)((21000*1000)/(9600 * 16)); /* Calculate baud settings */
    temp = UART0_BDH & ~(UART_BDH_SBR(0x1F)); /*Save the value of UART0_BDH except SBR*/
    UART0_BDH = temp | (((ubd& 0x1F00) >> 8));
    UART0_BDL = (uint8_t)(ubd& UART_BDL_SBR_MASK);
    UART0_C2 |= (UART_C2_TE_MASK | UART_C2_RE_MASK ); /* Enable receiver and transmitter */
    uint8_t ch;
    unsigned short bADCData;
    put("\r\n ADC code example\r\n");
    for (;;)
    {
        bADCData = ADC_read16b();
        DelayFunction();
    }
    return 0;
}

unsigned short ADC_read16b(void)
{
    ADC0_SC1A = 26 & ADC_SC1_ADCH_MASK; //Write to SC1A to start conversion
    while(ADC0_SC2 & ADC_SC2_ADACT_MASK); //Conversion in progress
    while(!(ADC0_SC1A & ADC_SC1_COCO_MASK));//Until conversion complete
    return ADC0_RA;
}

void uart_putchar(char ch)
{
    /* Wait until space is available in the FIFO */
    while(!(UART0_S1 & UART_S1_TDRE_MASK));
    /* Send the character */
    UART0_D = (uint8_t)ch;
}

void put(char *ptr_str)
{
    while(*ptr_str)
    uart_putchar(*ptr_str++);
}

void DelayFunction(void)
{
    unsigned long Counter = 0xFFFFF;
    do
    {
        Counter--;
    } while(Counter);
}

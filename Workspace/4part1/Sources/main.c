#include "fsl_device_registers.h"
#include "fsl_gpio_hal.h"
#include "fsl_sim_hal.h"
#include "fsl_port_hal.h"
#include "fsl_pit_hal.h"




#define PORT_PIN	      0x1A
#define PIT_Module        0
#define PIT_Period        60000
#define SIM_BASE          (0x40047000u)
#define PORTE_BASE        (0x4004D000u)
#define PTE_BASE          (0x400FF100u)
#define PIT_BASE          (0x40037000u)

#define PIT_Overflow      PIT_HAL_IsIntPending(PIT_BASE, 0)

void PIT_Delay (long pit_delay);


int main(void)
{

  SIM_HAL_EnableClock(SIM_BASE, kSimClockGatePortE); // Enable Port E Clock Gate
  SIM_HAL_EnableClock(SIM_BASE, kSimClockGatePit0); // Enable PIT Clock Gates

  PORT_HAL_SetMuxMode(PORTE_BASE, PORT_PIN, kPortMuxAsGpio);           // Configure PORTE, Pin 26, MUX as a GPIO

  GPIO_HAL_SetPinDir(PTE_BASE, PORT_PIN, kGpioDigitalOutput);          // Configure PORTE, Pin 26, as an Output


  // Initialize PIT 0
  PIT_HAL_SetTimerRunInDebugCmd(PIT_BASE, true);                       // Allow PIT timer to run in Debug Mode
  PIT_HAL_Enable(PIT_BASE);                                            // Enables PIT timers
  PIT_HAL_StopTimer(PIT_BASE, PIT_Module);                             // Disable PIT0 Timer
  PIT_HAL_SetTimerPeriodByCount(PIT_BASE, PIT_Module, PIT_Period);     // PIT0 Timer count value, PIT Period=1ms, busclk=60,000,000Hz, Period=1ms/(1/60000000Hz)=60000
  PIT_HAL_StartTimer(PIT_BASE, PIT_Module);                            // Start PIT0 Timer


  for (;;)
  {

    PIT_Delay(100);                                                      // Delay 100ms
    GPIO_HAL_TogglePinOutput(PTE_BASE, PORT_PIN);                        // Toggle GREEN LED

  }

  return 0;                                                            // Main.c return
}

void PIT_Delay (long pit_delay)                                      // Delay in multiples of 1ms (e.g. use 1000 for 1 second)
{long pit_i; for (pit_i=0;pit_i<pit_delay;pit_i++) {while (!PIT_Overflow); PIT_HAL_ClearIntFlag(PIT_BASE, PIT_Module);}}

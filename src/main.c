
#include <stdio.h>
#include <stdlib.h>
#include "diag/trace.h"

#include "rtos/os.h"
#include "rtos/tasks.h"


#include "timer.h"
#include "led.h"

// Keep the LED on for 2/3 of a second.
#define BLINK_ON_TICKS  ((uint32_t)configTICK_RATE_HZ * 3 / 4)
#define BLINK_OFF_TICKS ((uint32_t)configTICK_RATE_HZ - BLINK_ON_TICKS)

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

cpu_t stk1[128];
cpu_t stk2[128];
cpu_t stk3[128];
cpu_t stk4[128];

TCB_t tcb1, tcb2, tcb3, tcb4;

int main(int argc, char* argv[]) {

  // Init LEDs and enable GPIO Peripheral clock
  enable_gpio_peripheral_clock();
  blink_led_init(BLINK_PIN_NUMBER_GREEN);
  blink_led_init(BLINK_PIN_NUMBER_ORANGE);
  blink_led_init(BLINK_PIN_NUMBER_RED);
  blink_led_init(BLINK_PIN_NUMBER_BLUE);

  InstallTask(&tcb1, task1, 4, stk1, sizeof(stk1));
  InstallTask(&tcb2, task2, 2, stk2, sizeof(stk2));
  InstallTask(&tcb3, task3, 3, stk3, sizeof(stk3));
  InstallTask(&tcb4, task4, 1, stk4, sizeof(stk4));

  start_os();

  while (1){
  }
}

#pragma GCC diagnostic pop

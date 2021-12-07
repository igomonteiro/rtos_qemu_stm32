/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "led.h"

// ----------------------------------------------------------------------------

void enable_gpio_peripheral_clock() {
  SET_BIT(RCC->AHB1ENR, BLINK_RCC_MASKx(BLINK_PORT_NUMBER));
}

void blink_led_init(int led_pin) {
  GPIO_InitTypeDef GPIO_InitStructure;

  // Configure pin in output push/pull mode
  GPIO_InitStructure.Pin = BLINK_PIN_MASK(led_pin);
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStructure.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(BLINK_GPIOx(BLINK_PORT_NUMBER), &GPIO_InitStructure);

  // Start with led turned off
  blink_led_off(led_pin);
}

void blink_led_on(int led_pin){
  if (BLINK_ACTIVE_LOW){
    HAL_GPIO_WritePin(BLINK_GPIOx(BLINK_PORT_NUMBER),
      BLINK_PIN_MASK(led_pin), GPIO_PIN_RESET);
  }else{
    HAL_GPIO_WritePin(BLINK_GPIOx(BLINK_PORT_NUMBER),
      BLINK_PIN_MASK(led_pin), GPIO_PIN_SET);
  }
}

void blink_led_off(int led_pin){
  if (BLINK_ACTIVE_LOW){
    HAL_GPIO_WritePin(BLINK_GPIOx(BLINK_PORT_NUMBER),
	  BLINK_PIN_MASK(led_pin), GPIO_PIN_SET);
  }else{
    HAL_GPIO_WritePin(BLINK_GPIOx(BLINK_PORT_NUMBER),
	  BLINK_PIN_MASK(led_pin), GPIO_PIN_RESET);
  }
}

//void
//blink_led_on(void)
//{
//#if (BLINK_ACTIVE_LOW)
//  HAL_GPIO_WritePin(BLINK_GPIOx(BLINK_PORT_NUMBER),
//    BLINK_PIN_MASK(BLINK_PIN_NUMBER), GPIO_PIN_RESET);
//#else
//  HAL_GPIO_WritePin(BLINK_GPIOx(BLINK_PORT_NUMBER),
//    BLINK_PIN_MASK(BLINK_PIN_NUMBER), GPIO_PIN_SET);
//#endif
//}
//
//void
//blink_led_off(void)
//{
//#if (BLINK_ACTIVE_LOW)
//  HAL_GPIO_WritePin(BLINK_GPIOx(BLINK_PORT_NUMBER),
//    BLINK_PIN_MASK(BLINK_PIN_NUMBER), GPIO_PIN_SET);
//#else
//  HAL_GPIO_WritePin(BLINK_GPIOx(BLINK_PORT_NUMBER),
//    BLINK_PIN_MASK(BLINK_PIN_NUMBER), GPIO_PIN_RESET);
//#endif
//}

// ----------------------------------------------------------------------------

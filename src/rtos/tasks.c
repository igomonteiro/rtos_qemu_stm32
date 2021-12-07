#include "os.h"
#include "led.h"

sem_t semaf1;
sem_t semaf2;

/*
 * A ideia das tarefas criadas abaixo é a seguinte:
 * Os leds podem estar todos ligados ou desligados ao mesmo tempo
 * Os leds verde e laranja sempre estarão ligados ou desligados juntos
 * Os leds azul e vermelho sempre estarão ligados ou desligados juntos
 * Mas nunca vai ocorrer:
 * led verde ligado e led laranja desligado e vice-versa
 * led vermelho ligado e led azul desligado e vice-versa
 *
 *
 * Ao final do arquivo tem o código anterior que eu havia feito, com apenas um semáforo,
 * nele a ideia é que ao ligar o led verde na tarefa 3, os outros leds ligam na tarefa 4,
 * após um tempo todos os leds desligam, mas sempre que o verde ligar, os outros leds ligam.
 * */

void task1(void) {
  (void)sem_init(&semaf1);
  for(;;){
    #if with_scheduler == 1

    delay(30);
    // Ligando LED verde
    blink_led_on(BLINK_PIN_NUMBER_GREEN);
    (void)sem_post(&semaf1);

    delay(100);
    // Desligando todos os LEDS
    blink_led_off(BLINK_PIN_NUMBER_ORANGE);
    blink_led_off(BLINK_PIN_NUMBER_GREEN);

    #else
    yield();
    #endif
  }
}


void task2(void) {
  for(;;){
    (void)sem_pend(&semaf1, 200);
    // Ligando LED laranja
    blink_led_on(BLINK_PIN_NUMBER_ORANGE);
  }
}

void task3(void) {
  (void)sem_init(&semaf2);
  for(;;){
    #if with_scheduler == 1

    delay(60);
    // Ligando LED azul
    blink_led_on(BLINK_PIN_NUMBER_BLUE);
    (void)sem_post(&semaf2);

    delay(140);
    // Desligando todos os LEDS
    blink_led_off(BLINK_PIN_NUMBER_BLUE);
    blink_led_off(BLINK_PIN_NUMBER_RED);

    #else
    yield();
    #endif
  }
}


void task4(void) {
  for(;;){
    (void)sem_pend(&semaf2, 400);
    // Ligando LED vermelho
    blink_led_on(BLINK_PIN_NUMBER_RED);
  }
}

//-----------------------------VERSÃO ANTERIOR--------------------------------

//void task1(void) {
//  int i = 0;
//  for(;;){
//    i++;
//    #if with_scheduler == 1
//    delay(10);
//    #else
//    yield();
//    #endif
//  }
//}
//
//void task2(void) {
//  int i = 0;
//  for(;;){
//    i++;
//    #if with_scheduler == 1
//    delay(20);
//    #else
//    yield();
//    #endif
//  }
//}
//
//sem_t semaf;
//void task3(void) {
//  (void)sem_init(&semaf);
//  for(;;){
//    #if with_scheduler == 1
//
//    delay(30);
//    // Ligando LED verde
//    blink_led_on(BLINK_PIN_NUMBER_GREEN);
//    (void)sem_post(&semaf);
//
//    delay(100);
//    // Desligando todos os LEDS
//    blink_led_off(BLINK_PIN_NUMBER_ORANGE);
//    blink_led_off(BLINK_PIN_NUMBER_RED);
//    blink_led_off(BLINK_PIN_NUMBER_BLUE);
//    blink_led_off(BLINK_PIN_NUMBER_GREEN);
//
//    #else
//    yield();
//    #endif
//  }
//}
//
//
//void task4(void) {
//  for(;;){
//    (void)sem_pend(&semaf, 200);
//
//    // Ligando LED laranja
//    blink_led_on(BLINK_PIN_NUMBER_ORANGE);
//    // Ligando LED vermelho
//    blink_led_on(BLINK_PIN_NUMBER_RED);
//    // Ligando LED azul
//    blink_led_on(BLINK_PIN_NUMBER_BLUE);
//  }
//}


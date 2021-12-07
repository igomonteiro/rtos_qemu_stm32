#include "os.h"
#include <unistd.h>

cpu_t *stk_tmp;

cpu_t *PrepareStack(void *task, cpu_t *stk, int stk_size){
  stk = (cpu_t*)((int)stk + stk_size);

  *--stk = (cpu_t)0x01000000; // xPSR
  *--stk = (cpu_t)task; // Tarefa
  *--stk = 0;
  *--stk = (cpu_t)0x12121212u;
  *--stk = (cpu_t)0x03030303u;
  *--stk = (cpu_t)0x02020202u;
  *--stk = (cpu_t)0x01010101u;
  *--stk = (cpu_t)0;
  //*--stk = (cpu_t)0xfffffffdu; // Registrador de ponto flutuante
  *--stk = (cpu_t)0x11111111u;
  *--stk = (cpu_t)0x10101010u;
  *--stk = (cpu_t)0x09090909u;
  *--stk = (cpu_t)0x08080808u;
  *--stk = (cpu_t)0x07070707u;
  *--stk = (cpu_t)0x06060606u;
  *--stk = (cpu_t)0x05050505u;
  *--stk = (cpu_t)0x04040404u;

  return stk;
}


__attribute__ ((naked)) void SwitchContext(void){
  SAVE_CONTEXT();
  SAVE_SP();

  Clear_PendSV();

  current_task->stk=stk_tmp;
  stk_tmp = scheduler();
  
  RESTORE_SP();
  RESTORE_CONTEXT();
}

__attribute__ ((naked)) void SVCHandler(void){
  *(NVIC_SYSPRI3) |= NVIC_PENDSV_PRI;
  *(NVIC_SYSPRI3) |= NVIC_SYSTICK_PRI;
  RESTORE_SP();
  RESTORE_CONTEXT();
}


void init_os_timer(void){
  uint32_t module = configCPU_CLOCK_HZ / (uint32_t)configTICK_RATE_HZ;

  *(NVIC_SYSTICK_CTRL) = 0;
  *(NVIC_SYSTICK_LOAD) = module - 1u;
  *(NVIC_SYSTICK_CTRL) = NVIC_SYSTICK_CLK_SOURCE | NVIC_SYSTICK_INT | NVIC_SYSTICK_ENABLE;
}                                     


void TickTimer(void){
  if(os_inc_and_compare()){
      yield();
//    SAVE_CONTEXT();
//    SAVE_SP();
//
//    current_task->stk=stk_tmp;
//    stk_tmp = scheduler();
//
//    RESTORE_SP();
//    RESTORE_CONTEXT();
  }
}

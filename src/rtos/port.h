#include <stdint.h>

// ARM Cortex-Mx registers
#define NVIC_SYSTICK_CTRL 		(( volatile unsigned long *) 0xe000e010)
#define NVIC_SYSTICK_LOAD 		(( volatile unsigned long *) 0xe000e014)
#define NVIC_INT_CTRL     		(( volatile unsigned long *) 0xe000ed04)

// Interrupt Control and State Register
#define NVIC_PENDSVSET  		0x10000000
#define NVIC_PENDSVCLR  		0x08000000
#define NVIC_SYSTICK_CLK_SOURCE 	0x00000004
#define NVIC_SYSTICK_INT  		0x00000002
#define NVIC_SYSTICK_ENABLE  		0x00000001

// PRIO
#define NVIC_SYSPRI3      		((volatile unsigned long *) 0xe000ed20)
#define PRIO_BITS                       4
#define LOWEST_INTERRUPT_PRIORITY       0xF
#define KERNEL_INTERRUPT_PRIORITY       (LOWEST_INTERRUPT_PRIORITY << (8 - PRIO_BITS) )

#define NVIC_PENDSV_PRI                 ((( unsigned long ) KERNEL_INTERRUPT_PRIORITY ) << 16 )
#define NVIC_SYSTICK_PRI                ((( unsigned long ) KERNEL_INTERRUPT_PRIORITY ) << 24 )

// Tick Timer
#define configCPU_CLOCK_HZ      	160000000
#define configTICK_RATE_HZ		1000
typedef unsigned long cpu_t;

extern cpu_t *stk_tmp;

void init_os_timer(void);
cpu_t *PrepareStack(void *task, cpu_t *stk, int stk_size);

#define dispatcher() __asm( "cpsie i			\n"	\
			    "svc 0			\n"	\
			  )

// a.k.a yield()
#define yield()	*(NVIC_INT_CTRL) = NVIC_PENDSVSET;

#define Clear_PendSV(void) *(NVIC_INT_CTRL) = NVIC_PENDSVCLR;

#define OS_INT_EXIT_EXT() *(NVIC_INT_CTRL) = NVIC_PENDSVSET;

#define SAVE_CONTEXT() __asm(                                   \
			       "MRS R0, PSP             \n"     \
			       "SUBS R0, R0, #0x20      \n"     \
			       "STM R0, {R4-R11}        \n"     \
                            )

#define RESTORE_CONTEXT() __asm(                                \
        "LDM     R0, {R4-R11}       			\n"     \
	"ADDS    R0, R0, #0x20                          \n"     \
	"MSR     PSP, R0                                \n"     \
	"LDR     LR,=0xFFFFFFFD                         \n"     \
	"CPSIE   I                                      \n"     \
	"BX     LR                                      \n"     \
			       )

        
#define SAVE_SP() __asm( "LDR R1, =stk_tmp      	\n"     \
                         "STR R0, [R1]          	\n"	\
		       )

#define RESTORE_SP() __asm("LDR R1, =stk_tmp    	\n"     \
                           "LDR R0, [R1]        	\n"	\
			  )

#define ENTER_CRITICAL() __asm("CPSID I")

#define EXIT_CRITICAL() __asm("CPSIE I")

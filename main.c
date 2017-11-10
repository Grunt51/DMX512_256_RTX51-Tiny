#include "interrupt.h"
#include <rtx51tny.h>
#include <STC15.H>
#include <string.h>
#include "UART.H"
void uart_init_1(void) // 115200bps@24.000MHz
{
  SCON = 0xD0;  // 9位数据,可变波特率
  AUXR |= 0x40; //定时器1时钟为Fosc,即1T
  AUXR &= 0xFE; //串口1选择定时器1为波特率发生器
  TMOD &= 0x0F; //设定定时器1为16位自动重装方式
  TL1 = 0xCC;   //设定定时初值
  TH1 = 0xFF;   //设定定时初值
  ET1 = 0;      //禁止定时器1中断
  TR1 = 1;      //启动定时器1
}
void job_0() _task_ 0
{
	ES = 1;
//	PS = 1;
	uart_init_1();
	os_create_task (1);
	os_create_task (2);
	os_delete_task (0);
}
void job_1() _task_ 1
{
	while(1)
	{
		os_wait1(K_SIG);
		uart_send_str(g_command);
	}
}
void job_2() _task_ 2
{
	while(1)
	{
		os_wait(K_SIG, 0, 0);
		
	}
}
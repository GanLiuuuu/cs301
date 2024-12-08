#ifndef __MOTOR_H_
#define __MOTOR_H_
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，计算机软件管理规定，个人可以学习研究24小时，24小时后请删除，不得用于其它任何用途
//使用SysTick的普通计数模式对延迟进行管理（适合STM32F10x系列）
//包括delay_us,delay_ms
//********************************************************************************
//////////////////////////////////////////////////////////////////////////////////  
#include "stm32f10x.h"

void TIM4_PWM_Init(unsigned short arr,unsigned short psc);
void SetMotorSpeed(unsigned char ucChannel,signed char cSpeed);

void HJduino_run(signed char speed,int time);       //前进函数
void HJduino_brake(int time);                       //刹车函数
void HJduino_Left(signed char speed,int time);      //左转函数
void HJduino_Spin_Left(signed char speed,int time); //左旋转函数
void HJduino_Right(signed char speed,int time);     //右转函数
void HJduino_Spin_Right(signed char speed,int time);//右旋转函数
void HJduino_back(signed char speed,int time);      //后退函数


//电机驱动IO口定义 
/* 
LEFT_MOTOR_GO	  PB12  左1电机方向控制
LEFT_MOTOR_PWM	PB6	左1电机PWM

RIGHT_MOTOR_GO	PB14     右1电机方向控制
RIGHT_MOTOR_PWM	PB8	  右1电机电机PWM


LEFT2_MOTOR_GO	  PB13  左2电机方向控制
LEFT2_MOTOR_PWM	PB7	左2电机PWM

RIGHT2_MOTOR_GO	PB15     右2电机方向控制
RIGHT2_MOTOR_PWM	PB9	  右2电机电机PWM
 */
// 左前1 方向控制
#define LEFT_MOTOR_GO             GPIO_Pin_12
#define LEFT_MOTOR_GO_GPIO        GPIOB
#define LEFT_MOTOR_GO_SET         GPIO_SetBits(LEFT_MOTOR_GO_GPIO,LEFT_MOTOR_GO)
#define LEFT_MOTOR_GO_RESET       GPIO_ResetBits(LEFT_MOTOR_GO_GPIO,LEFT_MOTOR_GO)
// 左前1 PWM速度控制
#define LEFT_MOTOR_PWM            GPIO_Pin_6
#define LEFT_MOTOR_PWM_GPIO       GPIOB
#define LEFT_MOTOR_PWM_SET        GPIO_SetBits(LEFT_MOTOR_PWM_GPIO,LEFT_MOTOR_PWM)
#define LEFT_MOTOR_PWM_RESET      GPIO_ResetBits(LEFT_MOTOR_PWM_GPIO,LEFT_MOTOR_PWM)
//右1 方向控制
#define RIGHT_MOTOR_GO             GPIO_Pin_14
#define RIGHT_MOTOR_GPIO           GPIOB
#define RIGHT_MOTOR_GO_SET         GPIO_SetBits(RIGHT_MOTOR_GPIO,RIGHT_MOTOR_GO)
#define RIGHT_MOTOR_GO_RESET       GPIO_ResetBits(RIGHT_MOTOR_GPIO,RIGHT_MOTOR_GO)
//右1 PWM速度控制
#define RIGHT_MOTOR_PWM            GPIO_Pin_8
#define RIGHT_MOTOR_PWM_GPIO       GPIOB
#define RIGHT_MOTOR_PWM_SET        GPIO_SetBits(RIGHT_MOTOR_PWM_GPIO,RIGHT_MOTOR_PWM)
#define RIGHT_MOTOR_PWM_RESET      GPIO_ResetBits(RIGHT_MOTOR_PWM_GPIO,RIGHT_MOTOR_PWM)

//左2 方向控制
#define LEFT2_MOTOR_GO             GPIO_Pin_13
#define LEFT2_MOTOR_GO_GPIO        GPIOB
#define LEFT2_MOTOR_GO_SET         GPIO_SetBits(LEFT2_MOTOR_GO_GPIO,LEFT2_MOTOR_GO)
#define LEFT2_MOTOR_GO_RESET       GPIO_ResetBits(LEFT2_MOTOR_GO_GPIO,LEFT2_MOTOR_GO)
//左2 PWM速度控制
#define LEFT2_MOTOR_PWM            GPIO_Pin_7
#define LEFT2_MOTOR_PWM_GPIO       GPIOB
#define LEFT2_MOTOR_PWM_SET        GPIO_SetBits(LEFT2_MOTOR_PWM_GPIO,LEFT2_MOTOR_PWM)
#define LEFT2_MOTOR_PWM_RESET      GPIO_ResetBits(LEFT2_MOTOR_PWM_GPIO,LEFT2_MOTOR_PWM)
// 右2 方向控制
#define RIGHT2_MOTOR_GO             GPIO_Pin_15
#define RIGHT2_MOTOR_GPIO           GPIOB
#define RIGHT2_MOTOR_GO_SET         GPIO_SetBits(RIGHT2_MOTOR_GPIO,RIGHT2_MOTOR_GO)
#define RIGHT2_MOTOR_GO_RESET       GPIO_ResetBits(RIGHT2_MOTOR_GPIO,RIGHT2_MOTOR_GO)
//右2 PWM速度控制
#define RIGHT2_MOTOR_PWM            GPIO_Pin_9
#define RIGHT2_MOTOR_PWM_GPIO       GPIOB
#define RIGHT2_MOTOR_PWM_SET        GPIO_SetBits(RIGHT2_MOTOR_PWM_GPIO,RIGHT2_MOTOR_PWM)
#define RIGHT2_MOTOR_PWM_RESET      GPIO_ResetBits(RIGHT2_MOTOR_PWM_GPIO,RIGHT2_MOTOR_PWM)

#endif

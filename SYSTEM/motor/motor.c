//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，计算机软件管理规定，个人可以学习研究24小时，24小时后请删除，不得用于其它任何用途
//使用SysTick的普通计数模式对延迟进行管理（适合STM32F10x系列）
//包括delay_us,delay_ms
//********************************************************************************
//////////////////////////////////////////////////////////////////////////////////  
#include "motor.h"
#include "Math.h"
#include "delay.h"
#include "stm32f10x.h"                  // Device header
//采用定时器4配置PWM
void TIM4_PWM_Init(unsigned short arr,unsigned short psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);// 
 	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB , ENABLE);  //使能GPIO外设时钟使能 可以自己改成A口控制方向   
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);  //使能GPIO外设时钟使能  
	//前电机
  GPIO_InitStructure.GPIO_Pin = LEFT_MOTOR_GO;         //左1电机方向控制 PB12
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_Init(LEFT_MOTOR_GO_GPIO, &GPIO_InitStructure);  
	
	GPIO_InitStructure.GPIO_Pin = LEFT_MOTOR_PWM;         //左1电机PWM控制 PB6
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	   //复用推挽输出
	GPIO_Init(LEFT_MOTOR_PWM_GPIO, &GPIO_InitStructure);  
		
	
  GPIO_InitStructure.GPIO_Pin = RIGHT_MOTOR_GO;       //右1电机方向控制  PB14
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
	GPIO_Init(RIGHT_MOTOR_GPIO, &GPIO_InitStructure); 
	
	
	GPIO_InitStructure.GPIO_Pin = RIGHT_MOTOR_PWM;       //右1电机PWM控制  PB8
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	   //复用推挽输出
	GPIO_Init(RIGHT_MOTOR_PWM_GPIO, &GPIO_InitStructure);  
	
	
	//后电机
	  GPIO_InitStructure.GPIO_Pin = LEFT2_MOTOR_GO;         //左2电机方向控制 PB13
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_Init(LEFT2_MOTOR_GO_GPIO, &GPIO_InitStructure);  
	
	GPIO_InitStructure.GPIO_Pin = LEFT2_MOTOR_PWM;         //左2电机PWM控制 PB7
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	   //复用推挽输出
	GPIO_Init(LEFT2_MOTOR_PWM_GPIO, &GPIO_InitStructure);  
		
	
  GPIO_InitStructure.GPIO_Pin = RIGHT2_MOTOR_GO;       //右2电机方向控制  PB15
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
	GPIO_Init(RIGHT2_MOTOR_GPIO, &GPIO_InitStructure); 
	
	
	GPIO_InitStructure.GPIO_Pin = RIGHT2_MOTOR_PWM;       //右2电机PWM控制  PB9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	   //复用推挽输出
	GPIO_Init(RIGHT2_MOTOR_PWM_GPIO, &GPIO_InitStructure);  
	
	
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx 右1电机CH3
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx 左1电机CH1
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx 右2电机CH2
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx 左2电机CH4
	
	TIM_CtrlPWMOutputs(TIM4,ENABLE);	//MOE 主输出使能	
  
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //CH3预装载使能	 
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //CH1预装载使能
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);  //CH2预装载使能	 
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  //CH4预装载使能
	
  TIM_ARRPreloadConfig(TIM4, ENABLE); //使能TIMx在ARR上的预装载寄存器
 	TIM_Cmd(TIM4, ENABLE);  //使能TIM1   
}
//左1右1前轮PWM控制函数
void SetMotorSpeed(unsigned char ucChannel,signed char cSpeed) 
{
//		static short sMotorSpeed = 0;
		short sPWM;//设置变量
//	  float fDir = 1;
	
		if (cSpeed>=100) cSpeed = 100;
	  if (cSpeed<=-100) cSpeed = -100;
	
   	sPWM = 7201 - fabs(cSpeed)*72;  //附一个值给变量
	switch(ucChannel)
	{
		case 0://右1轮 用CH3
			TIM_SetCompare3(TIM4,sPWM);
			if (cSpeed>0) 
				RIGHT_MOTOR_GO_RESET;		
			else if(cSpeed<0) 
				RIGHT_MOTOR_GO_SET;
			break;
				
		case 1://左1轮 用CH1
		  TIM_SetCompare1(TIM4,sPWM); 
			if (cSpeed>0) 
				LEFT_MOTOR_GO_SET;
			else if (cSpeed<0)
				LEFT_MOTOR_GO_RESET;
			break;	

	}
}

//左2右2后轮PWM控制
void SetMotorSpeed2(unsigned char ucChannel,signed char cSpeed) 
{
//		static short sMotorSpeed = 0;
		short sPWM;
//	  float fDir = 1;
	
		if (cSpeed>=100) cSpeed = 100;
	  if (cSpeed<=-100) cSpeed = -100;
	
   	sPWM = 7201 - fabs(cSpeed)*72;
	switch(ucChannel)
	{
      case 0://右2轮
			TIM_SetCompare4(TIM4,sPWM);
			if (cSpeed>0) 
				RIGHT2_MOTOR_GO_RESET;
			else if(cSpeed<0) 
				RIGHT2_MOTOR_GO_SET;		
			break;		
			
			case 1://左2轮
		  TIM_SetCompare2(TIM4,sPWM); 
			if (cSpeed>0) 
				LEFT2_MOTOR_GO_SET;
			else if (cSpeed<0)
				LEFT2_MOTOR_GO_RESET;
			break;
	}
}
//----------------------------------运动函数--------------------------------
void HJduino_run(signed char speed,int time)  //前进函数
{
		  signed char f_speed = - speed;
	    SetMotorSpeed(1,f_speed);//左1轮  //为负数
			SetMotorSpeed(0,speed);//右1轮   //为正数
	
		  SetMotorSpeed2(1,f_speed);//左2轮  //为负数
			SetMotorSpeed2(0,speed);//右2轮   //为正数
			delay_ms(time);                 //时间为毫秒

}

void HJduino_brake(int time) //刹车函数
{
	  SetMotorSpeed(1,0);//左1轮   //为0
	  SetMotorSpeed(0,0);//右1轮   //为0
	  RIGHT_MOTOR_GO_RESET;
	  LEFT_MOTOR_GO_RESET;
		SetMotorSpeed2(1,0);//左2轮   //为0
	  SetMotorSpeed2(0,0);//右2轮   //为0
	  RIGHT2_MOTOR_GO_RESET;
	  LEFT2_MOTOR_GO_RESET;
		delay_ms(time);             //时间为毫秒  
}

void HJduino_Left(signed char speed,int time) //左转函数
{
	  SetMotorSpeed(1,0);//左轮     //左轮不动
	  SetMotorSpeed(0,speed);        //右轮为正
	
		SetMotorSpeed2(1,0);//左轮     //左轮不动
	  SetMotorSpeed2(0,speed);        //右轮为正
		delay_ms(time);                 //时间为毫秒  

}
void HJduino_Spin_Left(signed char speed,int time) //左旋转函数
{
	  signed char u_speed = 100 - speed; 
 	  SetMotorSpeed(0,speed);//左轮     //左轮为正
	  SetMotorSpeed(1,u_speed);            //右轮为正
	
	 	SetMotorSpeed2(0,speed);//左轮     //左轮为正
	  SetMotorSpeed2(1,u_speed);            //右轮为正
		delay_ms(time);                    //时间为毫秒  

}
void HJduino_Right(signed char speed,int time)  //右转函数
{
	  signed char f_speed = - speed;
	  SetMotorSpeed(1,f_speed);//左轮     //左轮为负
	  SetMotorSpeed(0,0);                 //右轮为0
		SetMotorSpeed2(1,f_speed);//左轮     //左轮为负
	  SetMotorSpeed2(0,0);                 //右轮为0
		delay_ms(time);                   //时间为毫秒  

}
void HJduino_Spin_Right(signed char speed,int time) //右旋转函数
{
	  signed char u_speed = 100 - speed;
	  signed char f_speed = - speed;
	  SetMotorSpeed(0,-u_speed);//左轮     //左轮为负
	  SetMotorSpeed(1,f_speed);            //右轮为负
		SetMotorSpeed2(0,-u_speed);//左轮     //左轮为负
	  SetMotorSpeed2(1,f_speed);            //右轮为负
		delay_ms(time);                    //时间为毫秒  

}
void HJduino_back(signed char speed,int time) //后退函数
{
	  signed char u_speed = 100- speed;
	  signed char f_speed = - u_speed;
	  SetMotorSpeed(1,u_speed);//左1轮   //为正数
	  SetMotorSpeed(0,f_speed);//右1轮 //为负数
	
		SetMotorSpeed2(1,u_speed);//左2轮   //为正数
	  SetMotorSpeed2(0,f_speed);//右2轮 //为负数
		delay_ms(time);                 //时间为毫秒  


}


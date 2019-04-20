#define F_CPU 16000000UL
#include "LotL.h"

int main(void)
{	
	
	InitPorts();
	InitPWM();
	// Uncomment/Comment according to the Background and line
	//CalcError(); 	// White background and black line 
	CalcErrorb(); // black background and white line
	sbi(PORTB,PB2);
	
	while(true)
	{	CalcErrorb();
		if(bit_is_clear(PINA, PA7) && bit_is_clear(PINA, PA6) && bit_is_clear(PINA, PA5) && bit_is_clear(PINA, PA4) && bit_is_clear(PINA, PA3) && bit_is_clear(PINA, PA2) && bit_is_clear(PINA, PA1) && bit_is_clear(PINA, PA0))		//robot has overshot
		{				
			
				while(bit_is_clear(PINA, PA7) && bit_is_clear(PINA, PA6) && bit_is_clear(PINA, PA5) && bit_is_clear(PINA, PA4) && bit_is_clear(PINA, PA3) && bit_is_clear(PINA, PA2) && bit_is_clear(PINA, PA1) && bit_is_clear(PINA, PA0))		//robot has overshot
				{
					if(lastreading == 'l')			//checks if the last sensor to the activated was right
					{	//turn left at full speed
					
						OCR1A = overshoot;
						OCR1B = overshoot;
						RightMF();						
						LeftMB();
						
					}	
					else if(lastreading == 'r')		//checks if the last sensor to the activated was left
					{    //turn right at full speed
						
						OCR1A =overshoot;
						OCR1B = overshoot;					
						RightMB();
						LeftMF();
						
					}
					else if(lastreading == 's')		//checks if the last sensor to the activated was left
					{    //turn right at full speed
								
						OCR1A =overshoot;
						OCR1B = overshoot;					
						RightMF();
						LeftMF();
						
					}
				}
				flag=1;
				
		}
		else if(s2+s3+s4+s5+s6+s7==6)
		{
			cbi(PORTB,PB2);
			//_delay_ms(60);
			
			for(int i=basespeed;i>5;i--)
			{	CalcErrorb();			
				OCR1A =i;
				OCR1B = i;					
				RightMF();
				LeftMF();
			}
			
			sbi(PORTB,PB2);
			
			CalcErrorb();	
			while(s1+s2+s3+s4+s5+s6+s7+s8>=6)
			{
						OCR1A = 255;
						OCR1B = 255;
						RightMS();						
						LeftMS();
						CalcErrorb();
						
			}

			
		}
		/*else if(s5+s6+s7+s8==4)
		{			OCR1A = overshoot;
						OCR1B = overshoot;
						RightMB();						
						LeftMF();
						_delay_ms(150);
		}
		else if(s1+s2+s3+s4==4)
		{			OCR1A = overshoot;
						OCR1B = overshoot;
						RightMF();						
						LeftMB();
						_delay_ms(100);
		}
		
		*/else if(s>=4 && s!=8)
		{	
			
			for(int i=basespeed;i>10;i--)
			{	CalcErrorb();			
				OCR1A =i;
				OCR1B = i;					
				RightMF();
				LeftMF();
			}
			
		}
		
		else  //robot on line
		{
			if(s3+s4+s5+s6>=1)
				flag=0;
			P = (error * kp)/10;
			I=I+error;
			D = (error - perror);
			correction = P +(I*ki)+(D*kd);
					
					perror = error;
					rightpulse =  basespeed + correction;
					leftpulse = basespeed - correction;				
						
					if(leftpulse > 255)
						leftpulse = 255;
					if(leftpulse < 0)
						leftpulse = 0;
					
					if(rightpulse > 255)
						rightpulse = 255;
					if(rightpulse < 0)
						rightpulse = 0;
					
					//OCR1A = leftpulse;
					//OCR1B = rightpulse;
					OCR1A =  rightpulse;
					OCR1B =leftpulse;
					
					LeftMF();
					RightMF();
		}
			
			prev=s1+s2+s3+s4+s5+s6+s7+s8;
			_delay_ms(20);
	}

}

//Interface GPS with LPC1768 and receive the frame in GPRMC format and transmit valid latitude and longitude value to the serial window of personal computer.

#include<LPC17xx.H>
void gps_send(void);
void uart0_init(void);
void uart3_init(void);
unsigned char rxval;
unsigned char val;
unsigned char gpsdata[200];
unsigned char lat[]="LATTITUDE:";
unsigned char lon[]="LONGITUDE:";
unsigned long int i;
int main()
{
	SystemInit();
	uart0_init();
	uart3_init();
	while(1)
	{
		while((LPC_UART3->LSR&0X01)!=0X01)
		{}
		rxdval= LPC_UART3->RBR;
		LPC_UART0->THR=rxval;
    while((LPC_UART0->LSR&0X20)!=0X20);
		gps_send();
	}
}
void gps_send(void)
{
    do
		{
      while((LPC_UART3->LSR&0X01)!=0X01);
      val=LPC_UART3->RBR;
		}while(val!='$');

		for(i=0;i<100;i++)
		{
			while((LPC_UART3->LSR&0X01)!=0X01)
    	gpsdata[i]=	LPC_UART3->RBR;
		}
		if(gpsdata[2]=='R')
		{
			if(gpsdata[17]=='A')
			{
				for(i=19;i<29;i++) //
				{ for(i=0;lat[i]!='\0';i++)
	           {
		           LPC_UART0->THR=lat[i];
		           while((LPC_UART0->LSR&0X20)!=0X20);
	           }
					LPC_UART0->THR=gpsdata[i];
					while((LPC_UART0->LSR&0X20)!=0X20);
				}
				for(i=31;i<42;i++) // To get the longitude and send the value to pc
				{
					for(i=0;lon[i]!='\0';i++)
	           {
		           LPC_UART0->THR=lon[i];
		           while((LPC_UART0->LSR&0X20)!=0X20);
	           }
					LPC_UART0->THR=gpsdata[i];
					while((LPC_UART0->LSR&0X20)!=0X20);
				}

			}
			else;
		}
		else;
	}
void uart0_init(void)
{
	LPC_SC->PCONP=0x00000000;
	LPC_PINCON->PINSEL0=0X00000050;
	LPC_UART0->LCR=0X83;
	LPC_UART0->DLM=0X00;
	LPC_UART0->DLL=0X75; // found using the baud rate =9600
	LPC_UART0->FDR=0X00000010;
	LPC_UART0->LCR=0x83;
}
void uart3_init(void)
{
	LPC_SC->PCONP=0x02000000;
	LPC_PINCON->PINSEL9=0X0f000000;
	LPC_UART0->LCR=0X83;
	LPC_UART0->DLM=0X00;
	LPC_UART0->DLL=0X75;
}

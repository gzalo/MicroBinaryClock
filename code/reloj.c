#include <pic16F628A.h>
#include <xc.h>
#include <stdint.h>
#include <stdio.h>

#pragma config FOSC=INTOSCIO, WDTE=OFF, PWRTE=OFF, BOREN=OFF, LVP=OFF, MCLRE=ON, CP=OFF
#define _XTAL_FREQ 4000000

uint8_t horas = 0, minutos = 0, segundos = 0;
uint24_t contador = 0;

//Escribir Horas+Minutos en LEDs
void escribir(){
	unsigned char h3 = (horas&8) != 0;
	unsigned char h2 = (horas&4) != 0;
	unsigned char h1 = (horas&2) != 0;
	unsigned char h0 = (horas&1) != 0;
	unsigned char m5 = (minutos&32) != 0;
	unsigned char m4 = (minutos&16) != 0;
	unsigned char m3 = (minutos&8) != 0;
	unsigned char m2 = (minutos&4) != 0;
	unsigned char m1 = (minutos&2) != 0;
	unsigned char m0 = (minutos&1) != 0;
	
	/*
	PA1 PA0 PA7 PA6
	PB2 PB7 PB6 PB5 PB4 PB3 
	h3 h2 h1 h0
	m5 m4 m3 m2 m1 m0
	*/
	PORTA = ~((h3<<1)|h2|(h1<<7)|(h0<<6));
	PORTB = ~((m5<<2)|(m4<<7)|(m3<<6)|(m2<<5)|(m1<<4)|(m0<<3));
}

volatile uint8_t oldVal = 0, tiempoBoton = 0;

//Interrupción del timer0, cada 32.768ms
void t0isr() __interrupt 1{
	TMR0IF = 0;
	contador += 32768;
	
	if(RB0 == 0) tiempoBoton++;
	if(oldVal==1 && RB0){	//Soltado boton
		if(tiempoBoton < 15) //480 ms
			minutos++;
		else
			horas++;
		
		horas%=12;
		minutos%=60;
		
		escribir();
		tiempoBoton = 0;
	}
	oldVal = !RB0;
	
	if(contador >= 1000000){
		//RA2 = !RA2;
		contador -= 1000000;
		
		segundos++;
		if(segundos==60){
			segundos=0;
			minutos++;
			if(minutos==60){
				minutos=0;
				horas++;
				if(horas==12){
					horas=0;
				}
			}
		}		
		escribir();
	}
}

void main(){
	PS0 = 0; PS1 = PS2 = 1; //1:128
	PSA = 0;
	T0CS = 0;
	TMR0IE = 1;
	PEIE = 1;
	GIE = 1;
	
	//Config puertos
	TRISB = 0b00000001;
	TRISA = 0x00;
	PORTA = 0x00;
	PORTB = 0x00;
	nRBPU = 0; //Habilitar Pullups Puerto B
	
	while(1);
}


#include "sam.h"
#include "SAMD21G18A_H.h"
 
#define PINCFG_CONFIG_VALUE 0b00000000

int main(void) {

	SystemInit();	

   //PORT configuration
	PORT->Group[0].PINCFG[14].reg = PINCFG_CONFIG_VALUE;
   	PORT->Group[0].DIRSET.reg = PORT_PA14;

   //TIMER configuration
	//Power Manager
	PM->APBCMASK.reg |= 0x00000800;
	//Generic Clock Control
	GCLK->GENDIV.reg = 0x00;
	GCLK->GENCTRL.reg = 0x10600;
	GCLK->CLKCTRL.reg = 0x401B;

	//Initial Count
	TC3->COUNT16.COUNT.reg = 65307;

	//Configure TC3 Peripheral
	TC3->COUNT16.CTRLA.reg = 0;
	TC3->COUNT16.CTRLBSET.reg = 0;
	TC3->COUNT16.INTFLAG.reg = 0x1;

	//Enabling TC3 Peripheral
	TC3->COUNT16.CTRLA.reg |= 0x2;

	//Loop
	while(!TC3->COUNT16.STATUS.bit.SYNCBUSY);

	//Loop
	while(1){
		while(!TC3->COUNT16.INTFLAG.bit.OVF);
		PORT->Group[0].OUTTGL.reg = 0x01;
		TC3->COUNT16.INTFLAG.reg = 0x01;
		TC3->COUNT16.COUNT.reg = 65307;
	}
}

#include "Arduino.h"
#include "CAP1298.h"

CAP1298::CAP1298() {
}

boolean CAP1298::begin(uint8_t i2caddr) {
    Wire.begin();
    _i2caddr = i2caddr;
	

	if ((readRegister(CAP1298_PRODID) != 0x71) || (readRegister(CAP1298_MANUID) != 0x5D)) {
		Serial.println("Device ID does not match");
		return false;
	}else{
		Serial.println("Setup OK");
		//configure for use here
		writeRegister(CAP1298_MTCONFIG, 0);		//allow multiple touches
		writeRegister(CAP1298_SENSITIVITY, 0x5F);   //reduce sensitivity to 8x (from default 32x)
		writeRegister(CAP1298_RPTRATEENABLE, 0x00);   //disable repeat interrupts on all pins (this happens when you hold the pin, useful for volume/skipping)
		//writeRegister(CAP1298_CONFIG2, readRegister(CAP1298_CONFIG2) & ~CAP1298_CONFIG2_BCOUTRECAL);		//disable base count out-of-limit function
		writeRegister(CAP1298_CALIBRATE, 0xFF);  //force calibration
		return true;
	}
}

boolean CAP1298::touchStatusChanged(void){
	boolean result=readRegister(CAP1298_MAIN) & CAP1298_MAIN_INT;
	writeRegister(CAP1298_MAIN, readRegister(CAP1298_MAIN) & ~CAP1298_MAIN_INT); //clear main interrupt
	return result;
}

void CAP1298::updateTouchData(){
	uint8_t touchData=readRegister(CAP1298_SENSTATUS);
	_newTouches=  (_touchData ^ touchData) & touchData;
	_newReleases= (_touchData ^ touchData) & _touchData;
	_touchData=touchData;
}

boolean CAP1298::isNewTouch(uint8_t cs){
	return (1<<(cs))&_newTouches;
}

boolean CAP1298::isNewRelease(uint8_t cs){
	return (1<<(cs))&_newReleases;
}

uint8_t CAP1298::getTouchData(void){
	return _touchData;
}
uint8_t CAP1298::getNewTouches(void){
	return _newTouches;
}
uint8_t CAP1298::getNewReleases(void){
	return _newReleases;
}

void CAP1298::setSensitivity(uint8_t value){
	
}

uint8_t CAP1298::readRegister(uint8_t reg){
	Wire.beginTransmission(_i2caddr);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom(_i2caddr, 1);
    return Wire.read();
}

void CAP1298::writeRegister(uint8_t reg,uint8_t value){
	Wire.beginTransmission(_i2caddr);
    Wire.write((uint8_t) reg);
    Wire.write((uint8_t) value);
    Wire.endTransmission();
}
  
 

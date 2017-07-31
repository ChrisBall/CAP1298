/*
*Not intended to be a full implementation, just one suitable for general purpose and for my exact application
*May work for other CAP1XXX chips with I2C only, no LED support
*/

#ifndef CAP1298_h
#define CAP1298_h
#include "Arduino.h"
#include <Wire.h>

#define CAP1298_ADDR 				0x28 		//this is the default address for all cap1298 chips

#define CAP1298_MAIN 				0x00      	//main control register (MCR)
#define CAP1298_MAIN_INT 				0x01  		//Interrupt bit (default 0)
#define CAP1298_MAIN_COMBO 				0x02		//Combo mode bit  (default 0)
#define CAP1298_MAIN_CGAIN0 			0x04		//Combo mode gain setting bit 1 (default 0)
#define CAP1298_MAIN_CGAIN1 			0x08		//Combo mode gain setting bit 2 (default 0)
#define CAP1298_MAIN_DSLEEP				0x10		//Deep sleep mode bit (default 0)
#define CAP1298_MAIN_STBY				0x20		//Standby mode bit
#define CAP1298_MAIN_GAIN0 				0x40		//Active mode gain setting bit 1 (default 0)
#define CAP1298_MAIN_GAIN1 				0x80		//Active mode gain setting bit 2 (default 0)
#define CAP1298_GENSTAT 			0x02		//General status register
#define CAP1298_GENSTAT_ACALFAIL 		0x20		//Calibration failure bit
#define CAP1298_SENSTATUS 			0x03		//Sensor statuses register (where touches on the 8 inputs are stored)
#define CAP1298_NOISEFLAG 			0x0A		//Noise flag status register
#define CAP1298_SENSITIVITY			0x1F		//Sensitivity control register
#define CAP1298_CONFIG1 			0x20		//Configuration register 1 (Configuration register 2 is 0x44)
#define CAP1298_CONFIG1_TIMEOUT			0x80		//Timeout config bit (default 0)
#define CAP1298_CONFIG1_DISDIGNOISE		0x20		//Disable digital noise threshold (default 1 (disabled))
#define CAP1298_CONFIG1_DISANANOISE		0x10		//Disable analog noise threshold (default 0 (enabled))
#define CAP1298_CONFIG1_MAXDUREN 		0x08		//Enable Max duration recalibration
#define CAP1298_SENSINPUTENABLE		0x21		//Sensor input enable register (default 0xFF)
#define CAP1298_SENSINPUTCONFIG1	0x22		//Sensor input configuration register 1 (default 0xA4)
#define CAP1298_SENSINPUTCONFIG2	0x23		//Sensor input configuration register 1 (default 0x07)
#define CAP1298_AVGSAMPCONFIG		0x24		//Averaging and sampling configuration register (default 0x39)
#define CAP1298_CALIBRATE 			0x26		//Calibration activate and status register
#define CAP1298_INTENABLE 			0x27		//Interrupt enable register
#define CAP1298_RPTRATEENABLE 		0x28		//Repeat rate enable register
#define CAP1298_SGENABLE 			0x29		//Signal guard (CS5) enable register
#define CAP1298_MTCONFIG 			0x2A		//Multi-touch configuration register
#define CAP1298_MTPATTERNCONFIG		0x2B		//Multi-touch pattern configuration
#define CAP1298_MTPATTERN			0x2B		//Multi-touch pattern register
#define CAP1238_SENSINPUTNOISTHRES	0x38		//Sensor input noise threshold register
#define CAP1298_STANDBYCFG 			0x41		//Standby configuration register
#define CAP1298_CONFIG2 			0x44		//Configuration register 2 (Configuration register 1 is 0x20)	
#define CAP1298_CONFIG2_BCOUTRECAL 		0x40		//Base count out-of-limit recalibration bit (default 1)			I THINK I SHOULD TURN THIS OFF FOR MOST USERS (BARE CONTACTS CAUSE OOL)
#define CAP1298_CONFIG2_BLKPWRCONT 		0x20		//Disable power control while sensing (default 0)
#define CAP1298_PRODID 				0xFD		//Product ID register
#define CAP1298_MANUID 				0xFE		//Manufacturer ID register
#define CAP1298_REV 				0xFF		//Chip revision number register

class CAP1298 {
    
  public:
	CAP1298(void);
	boolean begin(uint8_t i2caddr = CAP1298_ADDR);
	boolean touchStatusChanged(void);
	void updateTouchData(void);
	boolean isNewTouch(uint8_t cs);
	boolean isNewRelease(uint8_t cs);
	uint8_t getTouchData(void);
	uint8_t getNewTouches(void);
	uint8_t getNewReleases(void);
	void setSensitivity(uint8_t value);
	uint8_t readRegister(uint8_t reg);
	void writeRegister(uint8_t reg, uint8_t value);
	
  private:
	int8_t _i2caddr;
	uint8_t _touchData,_newTouches,_newReleases;
};

#endif

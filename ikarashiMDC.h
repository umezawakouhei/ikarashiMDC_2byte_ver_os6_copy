#ifndef IKARASHIMDC_H
#define IKARASHIMDC_H

#include "mbed.h"
#include "algorithm"

#define LAP 0
#define SM 1
/**
 * @file   ikarashiMDC.h
 * @Author Wataru Nakata
 * @date   August, 2017
 * @brief  ikarashi MDC class header file.
 *
 * MDC control libraly. creates object for each motors.
 */
  
/** Ikarashi MDC class
*   MDC libraly
*Example :
*@code
#include "mbed.h"
#include "ikarashiMDC.h"
Serial serial(PC_10,PC_11);
DigitalOut serialcontrol(D2);
*
ikarashiMDC ikarashi[]{
*    ikarashiMDC(&serialcontrol,2,2,SM,&serial),
*    ikarashiMDC(&serialcontrol,2,3,LAP,&serial),
};
PwmOut pwm(LED1);
*
int main() {
*    serial.baud(38400);
*    float i = -1;
*    while(1) {
*        ikarashi[0].setSpeed(i);
*        ikarashi[1].setSpeed(i);
*        i += 0.01;
*        pwm = fabs(i);
*        wait_ms(20);
*        if(i >= 1) i = -1;
*    }
}
*@endcode    
**/
class ikarashiMDC
{        
public:
    /** Create ikarashiMDC inctance
    * @param address of cs pin for rs485
    * @param addr for MDC
    * @param ch for motor
    * @param mdc mode (LAP or SM)
    * @param  address of serial object
    **/
    ikarashiMDC(uint8_t taddr,uint8_t tmotorNum,bool tmode, BufferedSerial *tserial);
    
    /** drive motor
    * @param speed of motor -1 to 1
    **/
    int setSpeed(const double& speed);
    bool braking;

protected:   
    uint8_t addr;
    uint8_t motorNum;
    bool mode;
    BufferedSerial* serial;
    
};
void estop(BufferedSerial *serial);
    
#endif
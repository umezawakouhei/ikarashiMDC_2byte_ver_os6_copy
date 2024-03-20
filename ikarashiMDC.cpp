#include "ikarashiMDC.h"


ikarashiMDC::ikarashiMDC(uint8_t taddr,uint8_t tmotorNum,bool tmode, BufferedSerial *tserial)
{
    serial = tserial;
    addr = taddr;
    motorNum = tmotorNum;
    mode = tmode;
    braking = true;
}

int ikarashiMDC::setSpeed(const double& speed)
{
    uint8_t data[6];
    //Limiter
    const double cropped_speed = std::min(1.0,std::max(-1.0,speed));
    uint16_t dataSpeed = ((cropped_speed+1.0)/2.0)*0xffff;
    //set sending data
    data[0] = 255; //header
    data[1] = 254;
    data[2] = (addr<<5) + motorNum + (mode<<4)+(braking<<3); //address
    data[3] = dataSpeed & 0xff;
    data[4] = dataSpeed >> 8;
    data[5] = data[2]^data[3]^data[4];
    if((data[3]==255)&&(data[4]==254))data[4]=255;
    //send data
    for(int i=0; i<6; i++) {
        serial->write(&data[i], 1);
    }
    return 0;
}


void estop(BufferedSerial *serial)
{
    uint8_t data = 255;
    for(int i = 0; i<3; i++) {
        serial->write(&data, 1);
    }

}

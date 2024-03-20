# サンプルコード
```C
#include <mbed.h>
#include <ikarashiMDC.h>
#define PI 3.14159265359
BufferedSerial serial(PC_10, PC_11, 115200);
DigitalOut es(D2);

ikarashiMDC ikarashi[]{
    ikarashiMDC(1, 0, SM, &serial),
    ikarashiMDC(1, 1, SM, &serial),
    ikarashiMDC(1, 2, SM, &serial),
    ikarashiMDC(1, 3, SM, &serial),
};

int main()
{
    float speed = 0.5;
    while (1)
    {
        for(int i=0; i<4; i++)
        {
            ikarashi[i].setSpeed(speed);
        }
    }
}
```
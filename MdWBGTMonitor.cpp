#include "MdWBGTMonitor.h"
#include "DrTHSensor.h"
#include "M5All-In-One-Gadget.h"

DrTHSensor drthsensor;
void MdWBGTMonitor::init()
{
    drthsensor.init();
}

void MdWBGTMonitor::getWBGT(double *temperature, double *humidity, WbgtIndex *index)
{
    drthsensor.getTempHumi(temperature, humidity);
    int calc_index = (int)(0.68 * *temperature + 0.12 * *humidity);

    if (calc_index < 15)
    {
        *index = SAFE;
    }
    else if (calc_index < 24)
    {
        *index = ATTENTION;
    }
    else if (calc_index < 27)
    {
        *index = ALERT;
    }
    else if (calc_index < 30)
    {
        *index = HIGH_ALERT;
    }
    else if (calc_index > 31)
    {
        *index = DANGER;
    }
}
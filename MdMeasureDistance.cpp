#include "MdMeasureDistance.h"
#include "DrUltraSonic.h"
#include <M5Stack.h>
#include "M5All-In-One-Gadget.h"

DrUltraSonic drultrasonic = DrUltraSonic(ECHO_PIN, TRIG_PIN);

double MdMeasureDistance::getDistance()
{

  double t = drultrasonic.measureReturnTime();

  distance = (double)t * 340 * (0.000001) * 0.5 * 100;
  return distance;
}

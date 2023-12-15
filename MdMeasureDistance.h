/* インクルードガード */
#include "DrUltraSonic.h"
#include <M5Stack.h>
#pragma once

class MdMeasureDistance // classの定義
{
private: // privateはクラス内からしかアクセスできない
public:  // publicはどこからでもアクセス可能
    double getDistance();
    double measureReturnTime();
    double distance;
     double t;
};

/* インクルードガード */
#pragma once
#include <M5Stack.h>
class DrUltraSonic // classの定義
{
private:
    int m_echo_pin;
    int m_trig_pin; // privateはクラス内からしかアクセスできない
    
public:
    DrUltraSonic(int echo_pin, int trig_pin); // publicはどこからでもアクセス可能
    double measureReturnTime();
};

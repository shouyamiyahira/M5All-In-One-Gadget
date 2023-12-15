#include "AppControl.h"
#include <Arduino.h>
#include <M5Stack.h>
#include "MdWBGTMonitor.h"

MdLcd mlcd;
MdWBGTMonitor mwbgt;
MdMusicPlayer mmplay;
MdMeasureDistance mmdist;
MdDateTime mdtime;

const char *g_str_orange[] = {
    COMMON_ORANGE0_IMG_PATH,
    COMMON_ORANGE1_IMG_PATH,
    COMMON_ORANGE2_IMG_PATH,
    COMMON_ORANGE3_IMG_PATH,
    COMMON_ORANGE4_IMG_PATH,
    COMMON_ORANGE5_IMG_PATH,
    COMMON_ORANGE6_IMG_PATH,
    COMMON_ORANGE7_IMG_PATH,
    COMMON_ORANGE8_IMG_PATH,
    COMMON_ORANGE9_IMG_PATH,
};

const char *g_str_blue[] = {
    COMMON_BLUE0_IMG_PATH,
    COMMON_BLUE1_IMG_PATH,
    COMMON_BLUE2_IMG_PATH,
    COMMON_BLUE3_IMG_PATH,
    COMMON_BLUE4_IMG_PATH,
    COMMON_BLUE5_IMG_PATH,
    COMMON_BLUE6_IMG_PATH,
    COMMON_BLUE7_IMG_PATH,
    COMMON_BLUE8_IMG_PATH,
    COMMON_BLUE9_IMG_PATH,
};

void AppControl::setBtnAFlg(bool flg)
{
    m_flag_btnA_is_pressed = flg;
}

void AppControl::setBtnBFlg(bool flg)
{
    m_flag_btnB_is_pressed = flg;
}

void AppControl::setBtnCFlg(bool flg)
{
    m_flag_btnC_is_pressed = flg;
}

void AppControl::setBtnAllFlgFalse()
{
    m_flag_btnA_is_pressed = false;
    m_flag_btnB_is_pressed = false;
    m_flag_btnC_is_pressed = false;
}

State AppControl::getState()
{
    return m_state;
}

void AppControl::setState(State state)
{
    m_state = state;
}

Action AppControl::getAction()
{
    return m_action;
}

void AppControl::setAction(Action action)
{
    m_action = action;
}

void AppControl::setStateMachine(State state, Action action)
{
    setState(state);
    setAction(action);
}

FocusState AppControl::getFocusState()
{
    return m_focus_state;
}

void AppControl::setFocusState(FocusState fs)
{
    m_focus_state = fs;
}

void AppControl::displayTitleInit()
{
    mlcd.displayJpgImageCoordinate(TITLE_IMG_PATH, TITLE_X_CRD, TITLE_Y_CRD);
}

void AppControl::displayMenuInit()
{
    // 画面をクリア
    mlcd.clearDisplay();

    // 背景を白にする
    mlcd.fillBackgroundWhite();

    // WBGTにフォーカス表示
    mlcd.displayJpgImageCoordinate(MENU_WBGT_FOCUS_IMG_PATH, MENU_WBGT_FOCUS_IMG_PATH_X_CRD, MENU_WBGT_FOCUS_IMG_PATH_Y_CRD);

    // MUSIC表示
    mlcd.displayJpgImageCoordinate(MENU_MUSIC_IMG_PATH, MENU_MUSIC_IMG_PATH_X_CRD, MENU_MUSIC_IMG_PATH_Y_CRD);

    // MEASURE表示
    mlcd.displayJpgImageCoordinate(MENU_MEASURE_IMG_PATH, MENU_MEASURE_IMG_PATH_X_CRD, MENU_MEASURE_IMG_PATH_Y_CRD);

    // DATE表示
    mlcd.displayJpgImageCoordinate(MENU_DATE_IMG_PATH, MENU_DATE_IMG_PATH_X_CRD, MENU_DATE_IMG_PATH_Y_CRD);

    // ↑表示
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_UP_IMG_PATH, COMMON_BUTTON_UP_IMG_PATH_X_CRD, COMMON_BUTTON_UP_IMG_PATH_Y_CRD);

    // ↓表示
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_DOWN_IMG_PATH, COMMON_BUTTON_DOWN_IMG_PATH_X_CRD, COMMON_BUTTON_DOWN_IMG_PATH_Y_CRD);

    // 決定表示
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_DECIDE_IMG_PATH, COMMON_BUTTON_DECIDE_IMG_PATH_X_CRD, COMMON_BUTTON_DECIDE_IMG_PATH_Y_CRD);
}

void AppControl::focusChangeImg(FocusState current_state, FocusState next_state)
{
    switch (current_state)
    {
    case MENU_WBGT:
        // WBGT表示
        mlcd.displayJpgImageCoordinate(MENU_WBGT_IMG_PATH, MENU_WBGT_IMG_PATH_X_CRD, MENU_WBGT_IMG_PATH_Y_CRD);
        break;

    case MENU_MUSIC:
        // WBGT表示
        mlcd.displayJpgImageCoordinate(MENU_WBGT_IMG_PATH, MENU_WBGT_IMG_PATH_X_CRD, MENU_WBGT_IMG_PATH_Y_CRD);

        // MUSIC表示
        mlcd.displayJpgImageCoordinate(MENU_MUSIC_IMG_PATH, MENU_MUSIC_IMG_PATH_X_CRD, MENU_MUSIC_IMG_PATH_Y_CRD);
        break;

    case MENU_MEASURE:
        // WBGT表示
        mlcd.displayJpgImageCoordinate(MENU_WBGT_IMG_PATH, MENU_WBGT_IMG_PATH_X_CRD, MENU_WBGT_IMG_PATH_Y_CRD);

        // MEASURE表示
        mlcd.displayJpgImageCoordinate(MENU_MEASURE_IMG_PATH, MENU_MEASURE_IMG_PATH_X_CRD, MENU_MEASURE_IMG_PATH_Y_CRD);
        break;

    case MENU_DATE:
        // WBGT表示
        mlcd.displayJpgImageCoordinate(MENU_WBGT_IMG_PATH, MENU_WBGT_IMG_PATH_X_CRD, MENU_WBGT_IMG_PATH_Y_CRD);

        // DATE表示
        mlcd.displayJpgImageCoordinate(MENU_DATE_IMG_PATH, MENU_DATE_IMG_PATH_X_CRD, MENU_DATE_IMG_PATH_Y_CRD);
        break;
    }
    switch (next_state)
    {
    case MENU_WBGT:
        // WBGTにフォーカス表示
        mlcd.displayJpgImageCoordinate(MENU_WBGT_FOCUS_IMG_PATH, MENU_WBGT_FOCUS_IMG_PATH_X_CRD, MENU_WBGT_IMG_PATH_Y_CRD);

        break;

    case MENU_MUSIC:
        // MUSICにフォーカス表示
        mlcd.displayJpgImageCoordinate(MENU_MUSIC_FOCUS_IMG_PATH, MENU_MUSIC_FOCUS_IMG_PATH_X_CRD, MENU_MUSIC_FOCUS_IMG_PATH_Y_CRD);
        break;

    case MENU_MEASURE:
        // MEASUREにフォーカス表示
        mlcd.displayJpgImageCoordinate(MENU_MEASURE_FOCUS_IMG_PATH, MENU_MEASURE_FOCUS_IMG_PATH_X_CRD, MENU_MEASURE_FOCUS_IMG_PATH_Y_CRD);
        break;

    case MENU_DATE:
        // DATEにフォーカス表示
        mlcd.displayJpgImageCoordinate(MENU_DATE_FOCUS_IMG_PATH, MENU_DATE_FOCUS_IMG_PATH_X_CRD, MENU_DATE_FOCUS_IMG_PATH_Y_CRD);
        break;
    }
}

void AppControl::displayWBGTInit()
{
    // 画面をクリア化
    mlcd.clearDisplay();

    // 背景を白くする
    mlcd.fillBackgroundWhite();

    // 温度画像
    mlcd.displayJpgImageCoordinate(WBGT_TEMPERATURE_IMG_PATH, WBGT_TEMPERATURE_IMG_PATH_X_CRD, WBGT_TEMPERATURE_IMG_PATH_Y_CRD);

    // 戻るの画面表示
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH, COMMON_BUTTON_BACK_IMG_PATH_X_CRD, COMMON_BUTTON_BACK_IMG_PATH_Y_CRD);
}

void AppControl::displayTempHumiIndex()
{
    mwbgt.init();
    double temperature;
    double humidity;
    WbgtIndex index;
    mwbgt.getWBGT(&temperature, &humidity, &index);
    double temperaturebox = temperature;
    double humiditybox = humidity;
    Serial.println(humidity);
    temperaturebox = temperaturebox * 10;
    humiditybox = humiditybox * 10;
    int temperaturehundred = (int)(temperaturebox / 100);
    int b = (int)temperaturebox % 100;
    int temperatureten = b / 10;
    int d = b % 10;
    int temperatureone = d;

    int humidityhundred = (int)(humiditybox / 100);
    int c = (int)humiditybox % 100;
    int humidityten = c / 10;
    int e = c % 10;
    int humidityone = e;
    if (temperaturebox > 0 && temperaturebox < 600)
    {
        if (temperaturebox > 100 && humiditybox > 100)
        {
            // 温度の画面表示
            mlcd.displayJpgImageCoordinate(WBGT_TEMPERATURE_IMG_PATH, WBGT_TEMPERATURE_IMG_PATH_X_CRD, WBGT_TEMPERATURE_IMG_PATH_Y_CRD);

            // 温度の10の位
            mlcd.displayJpgImageCoordinate(g_str_orange[temperaturehundred], WBGT_T2DIGIT_X_CRD, WBGT_T2DIGIT_Y_CRD);

            // 温度の1の位
            mlcd.displayJpgImageCoordinate(g_str_orange[temperatureten], WBGT_T1DIGIT_X_CRD, WBGT_T1DIGIT_Y_CRD);

            // 温度の.
            mlcd.displayJpgImageCoordinate(COMMON_BLUEDOT_IMG_PATH, WBGT_HDOT_X_CRD, WBGT_HDOT_Y_CRD);

            // 温度の小数第一
            mlcd.displayJpgImageCoordinate(g_str_orange[temperatureone], WBGT_T1DECIMAL_X_CRD, WBGT_T1DECIMAL_Y_CRD);

            // ℃
            mlcd.displayJpgImageCoordinate(WBGT_DEGREE_IMG_PATH, WBGT_DEGREE_IMG_PATH_X_CRD, WBGT_DEGREE_IMG_PATH_Y_CRD);

            // 湿度の画面表示
            mlcd.displayJpgImageCoordinate(WBGT_HUMIDITY_IMG_PATH, WBGT_HUMIDITY_IMG_PATH_X_CRD, WBGT_HUMIDITY_IMG_PATH_Y_CRD);

            // 湿度の10の位
            mlcd.displayJpgImageCoordinate(g_str_blue[humidityhundred], WBGT_H2DIGIT_X_CRD, WBGT_H2DIGIT_Y_CRD);

            // 湿度の1の位
            mlcd.displayJpgImageCoordinate(g_str_blue[humidityten], WBGT_H1DIGIT_X_CRD, WBGT_H1DIGIT_Y_CRD);

            // 湿度の.
            mlcd.displayJpgImageCoordinate(COMMON_ORANGEDOT_IMG_PATH, WBGT_TDOT_X_CRD, WBGT_TDOT_Y_CRD);

            // 小数第一
            mlcd.displayJpgImageCoordinate(g_str_blue[humidityone], WBGT_H1DECIMAL_X_CRD, WBGT_H1DECIMAL_Y_CRD);

            //%
            mlcd.displayJpgImageCoordinate(WBGT_PERCENT_IMG_PATH, WBGT_PERCENT_IMG_PATH_X_CRD, WBGT_PERCENT_IMG_PATH_Y_CRD);

            // 戻る
            mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH, COMMON_BUTTON_BACK_IMG_PATH_X_CRD, COMMON_BUTTON_BACK_IMG_PATH_Y_CRD);
        }
        else if (temperaturebox < 100 && humiditybox > 100)
        {
            // 温度の画像
            mlcd.displayJpgImageCoordinate(WBGT_TEMPERATURE_IMG_PATH, WBGT_TEMPERATURE_IMG_PATH_X_CRD, WBGT_TEMPERATURE_IMG_PATH_Y_CRD);

            // 温度の10の位
            mlcd.displayJpgImageCoordinate(g_str_orange[temperaturehundred], WBGT_T2DIGIT_X_CRD, WBGT_T2DIGIT_Y_CRD);

            // 温度の10の位を隠す
            mlcd.displayJpgImageCoordinate(COMMON_ORANGEFILLWHITE_IMG_PATH, WBGT_T2DIGIT_X_CRD, WBGT_T2DIGIT_Y_CRD);

            // 温度の1の位
            mlcd.displayJpgImageCoordinate(g_str_orange[temperatureten], WBGT_T1DIGIT_X_CRD, WBGT_T1DIGIT_Y_CRD);

            // 温度の.
            mlcd.displayJpgImageCoordinate(COMMON_BLUEDOT_IMG_PATH, WBGT_HDOT_X_CRD, WBGT_HDOT_Y_CRD);

            // 温度の小数第一
            mlcd.displayJpgImageCoordinate(g_str_orange[temperatureone], WBGT_T1DECIMAL_X_CRD, WBGT_T1DECIMAL_Y_CRD);

            // ℃
            mlcd.displayJpgImageCoordinate(WBGT_DEGREE_IMG_PATH, WBGT_DEGREE_IMG_PATH_X_CRD, WBGT_DEGREE_IMG_PATH_Y_CRD);

            // 湿度の画面表示
            mlcd.displayJpgImageCoordinate(WBGT_HUMIDITY_IMG_PATH, WBGT_HUMIDITY_IMG_PATH_X_CRD, WBGT_HUMIDITY_IMG_PATH_Y_CRD);

            // 湿度の10の位
            mlcd.displayJpgImageCoordinate(g_str_blue[humidityhundred], WBGT_H2DIGIT_X_CRD, WBGT_H2DIGIT_Y_CRD);

            // 湿度の1の位
            mlcd.displayJpgImageCoordinate(g_str_blue[humidityten], WBGT_H1DIGIT_X_CRD, WBGT_H1DIGIT_Y_CRD);

            // 湿度の.
            mlcd.displayJpgImageCoordinate(COMMON_ORANGEDOT_IMG_PATH, WBGT_TDOT_X_CRD, WBGT_TDOT_Y_CRD);

            // 小数第一
            mlcd.displayJpgImageCoordinate(g_str_blue[humidityone], WBGT_H1DECIMAL_X_CRD, WBGT_H1DECIMAL_Y_CRD);

            //%
            mlcd.displayJpgImageCoordinate(WBGT_PERCENT_IMG_PATH, WBGT_PERCENT_IMG_PATH_X_CRD, WBGT_PERCENT_IMG_PATH_Y_CRD);

            // 戻る
            mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH, COMMON_BUTTON_BACK_IMG_PATH_X_CRD, COMMON_BUTTON_BACK_IMG_PATH_Y_CRD);
        }
        else if (temperaturebox > 100 && humiditybox < 100)
        {
            // 温度の画面表示
            mlcd.displayJpgImageCoordinate(WBGT_TEMPERATURE_IMG_PATH, WBGT_TEMPERATURE_IMG_PATH_X_CRD, WBGT_TEMPERATURE_IMG_PATH_Y_CRD);

            // 温度の10の位
            mlcd.displayJpgImageCoordinate(g_str_orange[temperaturehundred], WBGT_T2DIGIT_X_CRD, WBGT_T2DIGIT_Y_CRD);

            // 湿度の10の位を隠す
            mlcd.displayJpgImageCoordinate(COMMON_BLUEFILLWHITE_IMG_PATH, WBGT_H2DIGIT_X_CRD, WBGT_H2DIGIT_Y_CRD);

            // 温度の1の位
            mlcd.displayJpgImageCoordinate(g_str_orange[temperatureten], WBGT_T1DIGIT_X_CRD, WBGT_T1DIGIT_Y_CRD);

            // 温度の.
            mlcd.displayJpgImageCoordinate(COMMON_BLUEDOT_IMG_PATH, WBGT_HDOT_X_CRD, WBGT_HDOT_Y_CRD);

            // 温度の小数第一
            mlcd.displayJpgImageCoordinate(g_str_orange[temperatureone], WBGT_T1DECIMAL_X_CRD, WBGT_T1DECIMAL_Y_CRD);

            // ℃
            mlcd.displayJpgImageCoordinate(WBGT_DEGREE_IMG_PATH, WBGT_DEGREE_IMG_PATH_X_CRD, WBGT_DEGREE_IMG_PATH_Y_CRD);

            // 湿度の画面表示
            mlcd.displayJpgImageCoordinate(WBGT_HUMIDITY_IMG_PATH, WBGT_HUMIDITY_IMG_PATH_X_CRD, WBGT_HUMIDITY_IMG_PATH_Y_CRD);

            // 湿度の10の位
            mlcd.displayJpgImageCoordinate(g_str_blue[humidityhundred], WBGT_H2DIGIT_X_CRD, WBGT_H2DIGIT_Y_CRD);

            // 湿度の1の位
            mlcd.displayJpgImageCoordinate(g_str_blue[humidityten], WBGT_H1DIGIT_X_CRD, WBGT_H1DIGIT_Y_CRD);

            // 湿度の.
            mlcd.displayJpgImageCoordinate(COMMON_ORANGEDOT_IMG_PATH, WBGT_TDOT_X_CRD, WBGT_TDOT_Y_CRD);

            // 小数第一
            mlcd.displayJpgImageCoordinate(g_str_blue[humidityone], WBGT_H1DECIMAL_X_CRD, WBGT_H1DECIMAL_Y_CRD);

            //%
            mlcd.displayJpgImageCoordinate(WBGT_PERCENT_IMG_PATH, WBGT_PERCENT_IMG_PATH_X_CRD, WBGT_PERCENT_IMG_PATH_Y_CRD);

            // 戻る
            mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH, COMMON_BUTTON_BACK_IMG_PATH_X_CRD, COMMON_BUTTON_BACK_IMG_PATH_Y_CRD);
        }
        else if (temperaturebox < 100 && humiditybox < 100)
        {
            // 温度画像の表示
            mlcd.displayJpgImageCoordinate(WBGT_TEMPERATURE_IMG_PATH, WBGT_TEMPERATURE_IMG_PATH_X_CRD, WBGT_TEMPERATURE_IMG_PATH_Y_CRD);

            // 温度の10の位
            mlcd.displayJpgImageCoordinate(g_str_orange[temperaturehundred], WBGT_T2DIGIT_X_CRD, WBGT_T2DIGIT_Y_CRD);

            // 温度の.
            mlcd.displayJpgImageCoordinate(COMMON_ORANGEFILLWHITE_IMG_PATH, WBGT_T2DIGIT_X_CRD, WBGT_T2DIGIT_Y_CRD);

            // 温度の1の位
            mlcd.displayJpgImageCoordinate(g_str_orange[temperatureten], WBGT_T1DIGIT_X_CRD, WBGT_T1DIGIT_Y_CRD);

            // 温度の.
            mlcd.displayJpgImageCoordinate(COMMON_BLUEDOT_IMG_PATH, WBGT_HDOT_X_CRD, WBGT_HDOT_Y_CRD);

            // 温度の小数第一
            mlcd.displayJpgImageCoordinate(g_str_orange[temperatureone], WBGT_T1DECIMAL_X_CRD, WBGT_T1DECIMAL_Y_CRD);

            // ℃
            mlcd.displayJpgImageCoordinate(WBGT_DEGREE_IMG_PATH, WBGT_DEGREE_IMG_PATH_X_CRD, WBGT_DEGREE_IMG_PATH_Y_CRD);

            // 湿度の画面表示
            mlcd.displayJpgImageCoordinate(WBGT_HUMIDITY_IMG_PATH, WBGT_HUMIDITY_IMG_PATH_X_CRD, WBGT_HUMIDITY_IMG_PATH_Y_CRD);

            // 湿度の10の位を隠す
            mlcd.displayJpgImageCoordinate(COMMON_BLUEFILLWHITE_IMG_PATH, WBGT_H2DIGIT_X_CRD, WBGT_H2DIGIT_Y_CRD);

            // 湿度の10の位
            mlcd.displayJpgImageCoordinate(g_str_blue[humidityhundred], WBGT_H2DIGIT_X_CRD, WBGT_H2DIGIT_Y_CRD);

            // 湿度の1の位
            mlcd.displayJpgImageCoordinate(g_str_blue[humidityten], WBGT_H1DIGIT_X_CRD, WBGT_H1DIGIT_Y_CRD);

            // 湿度の.
            mlcd.displayJpgImageCoordinate(COMMON_ORANGEDOT_IMG_PATH, WBGT_TDOT_X_CRD, WBGT_TDOT_Y_CRD);

            // 小数第一
            mlcd.displayJpgImageCoordinate(g_str_blue[humidityone], WBGT_H1DECIMAL_X_CRD, WBGT_H1DECIMAL_Y_CRD);

            //%
            mlcd.displayJpgImageCoordinate(WBGT_PERCENT_IMG_PATH, WBGT_PERCENT_IMG_PATH_X_CRD, WBGT_PERCENT_IMG_PATH_Y_CRD);

            // 戻る
            mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH, COMMON_BUTTON_BACK_IMG_PATH_X_CRD, COMMON_BUTTON_BACK_IMG_PATH_Y_CRD);
        }
    }

    switch (index)
    {
        // 熱中症アラートの画像
    case SAFE:
        // 安全の表示
        mlcd.displayJpgImageCoordinate(WBGT_SAFE_IMG_PATH, WBGT_SAFE_IMG_PATH_X_CRD, WBGT_SAFE_IMG_PATH_Y_CRD);
        break;

    case ATTENTION:
        // 注意の表示
        mlcd.displayJpgImageCoordinate(WBGT_ATTENTION_IMG_PATH, WBGT_ATTENTION_IMG_PATH_X_CRD, WBGT_ATTENTION_IMG_PATH_Y_CRD);
        break;

    case ALERT:
        // 警戒の表示
        mlcd.displayJpgImageCoordinate(WBGT_ALERT_IMG_PATH, WBGT_ALERT_IMG_PATH_X_CRD, WBGT_ALERT_IMG_PATH_Y_CRD);
        break;

    case HIGH_ALERT:
        // 厳重警戒の表示
        mlcd.displayJpgImageCoordinate(WBGT_HIGH_ALERT_IMG_PATH, WBGT_HIGH_ALERT_IMG_PATH_X_CRD, WBGT_HIGH_ALERT_IMG_PATH_Y_CRD);
        break;

    case DANGER:
        // 危険の表示
        mlcd.displayJpgImageCoordinate(WBGT_DANGER_IMG_PATH, WBGT_DANGER_IMG_PATH_X_CRD, WBGT_DANGER_IMG_PATH_Y_CRD);
        break;

    default:
        break;
    }
}

void AppControl::displayMusicInit()
{
    // クリア化する
    mlcd.clearDisplay();

    // 背景白
    mlcd.fillBackgroundWhite();

    // タイトル関数
    displayMusicTitle();
}

void AppControl::displayMusicStop()
{
    displayMusicInit();

    // STOP
    mlcd.displayJpgImageCoordinate(MUSIC_NOWSTOPPING_IMG_PATH, MUSIC_NOWSTOPPING_IMG_PATH_X_CRD, MUSIC_NOWSTOPPING_IMG_PATH_Y_CRD);

    // 再生
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_PLAY_IMG_PATH, COMMON_BUTTON_PLAY_IMG_PATH_X_CRD, COMMON_BUTTON_PLAY_IMG_PATH_Y_CRD);

    // 戻る
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH, COMMON_BUTTON_BACK_IMG_PATH_X_CRD, COMMON_BUTTON_BACK_IMG_PATH_Y_CRD);

    // 次の曲
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_NEXT_IMG_PATH, COMMON_BUTTON_NEXT_IMG_PATH_X_CRD, COMMON_BUTTON_NEXT_IMG_PATH_Y_CRD);
}

void AppControl::displayMusicTitle()
{
    mlcd.displayText(mmplay.getTitle(), MUSIC_TITLE_X_CRD, MUSIC_TITLE_Y_CRD);
}

void AppControl::displayNextMusic()
{
    mmplay.selectNextMusic();

    displayMusicTitle();
}

void AppControl::displayMusicPlay()
{
    displayMusicInit();

    // 音楽再生中
    mlcd.displayJpgImageCoordinate(MUSIC_NOWPLAYING_IMG_PATH, MUSIC_NOWPLAYING_IMG_PATH_X_CRD, MUSIC_NOWPLAYING_IMG_PATH_Y_CRD);

    // 停止ボタン表示
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_STOP_IMG_PATH, COMMON_BUTTON_STOP_IMG_PATH_X_CRD, COMMON_BUTTON_STOP_IMG_PATH_Y_CRD);
}

void AppControl::displayMeasureInit()
{
    // クリア化する
    mlcd.clearDisplay();

    // 背景を白にする
    mlcd.fillBackgroundWhite();

    // 距離測定中画面
    mlcd.displayJpgImageCoordinate(MEASURE_NOTICE_IMG_PATH, MEASURE_NOTICE_IMG_PATH_X_CRD, MEASURE_NOTICE_IMG_PATH_Y_CRD);

    // 戻る
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH, COMMON_BUTTON_BACK_IMG_PATH_X_CRD, COMMON_BUTTON_BACK_IMG_PATH_Y_CRD);
}

void AppControl::displayMeasureDistance()
{
    double distance = mmdist.getDistance();

    distance = distance * 10;
    Serial.println(distance);
    int hundred = (int)distance / 1000;
    int b = (int)distance % 1000;
    int ten = b / 100;
    int d = b % 100;
    int one = d / 10;
    int Few = d % 10;

    // cm表示
    mlcd.displayJpgImageCoordinate(MEASURE_CM_IMG_PATH, MEASURE_CM_IMG_PATH_IMG_PATH_X_CRD, MEASURE_CM_IMG_PATH_IMG_PATH_Y_CRD);

    // 湿度の.
    mlcd.displayJpgImageCoordinate(COMMON_BLUEDOT_IMG_PATH, MEASURE_DOT_X_CRD, MEASURE_DOT_Y_CRD);

    if (distance > 20 && distance < 4500)
    {
        Serial.println("2cm以上,450cm未満");
        if (distance < 100)
        {
            Serial.println("10cm未満");
            // 少数第一の位の数字の画面表示
            mlcd.displayJpgImageCoordinate(g_str_blue[Few], MEASURE_DECIMAL_X_CRD, MEASURE_DECIMAL_Y_CRD);

            // 1の位の画面表示
            mlcd.displayJpgImageCoordinate(g_str_blue[one], MEASURE_DIGIT1_X_CRD, MEASURE_DIGIT1_Y_CRD);

            // 10の位を白で隠す
            mlcd.displayJpgImageCoordinate(COMMON_BLUEFILLWHITE_IMG_PATH, 53, 100);

            // 100の位を白で隠す
            mlcd.displayJpgImageCoordinate(COMMON_BLUEFILLWHITE_IMG_PATH, 10, 100);
        }
        else if (distance >= 100 && distance < 1000)
        {
            Serial.println("10cm以上,100cm未満");
            //.表示
            mlcd.displayJpgImageCoordinate(COMMON_BLUEDOT_IMG_PATH, MEASURE_DOT_X_CRD, MEASURE_DOT_Y_CRD);

            // 少数第一の位の数字の画面表示
            mlcd.displayJpgImageCoordinate(g_str_blue[Few], MEASURE_DECIMAL_X_CRD, MEASURE_DECIMAL_Y_CRD);

            // 1の位の画面表示
            mlcd.displayJpgImageCoordinate(g_str_blue[one], MEASURE_DIGIT1_X_CRD, MEASURE_DIGIT1_Y_CRD);

            // 10の位の画面表示
            mlcd.displayJpgImageCoordinate(g_str_blue[ten], MEASURE_DIGIT2_X_CRD, MEASURE_DIGIT2_Y_CRD);

            // 100の位を白で隠す
            mlcd.displayJpgImageCoordinate(COMMON_BLUEFILLWHITE_IMG_PATH, 10, 100);
        }
        else if (distance >= 1000)
        {
            Serial.println("100cm以上");

            //.表示
            mlcd.displayJpgImageCoordinate(COMMON_BLUEDOT_IMG_PATH, MEASURE_DOT_X_CRD, MEASURE_DOT_Y_CRD);

            // 少数第一の位の数字の画面表示
            mlcd.displayJpgImageCoordinate(g_str_blue[Few], MEASURE_DECIMAL_X_CRD, MEASURE_DECIMAL_Y_CRD);

            // 1の位の画面表示
            mlcd.displayJpgImageCoordinate(g_str_blue[one], MEASURE_DIGIT1_X_CRD, MEASURE_DIGIT1_Y_CRD);

            // 10の位の画面表示
            mlcd.displayJpgImageCoordinate(g_str_blue[ten], MEASURE_DIGIT2_X_CRD, MEASURE_DIGIT2_Y_CRD);

            // 100の位の画面表示
            mlcd.displayJpgImageCoordinate(g_str_blue[hundred], MEASURE_DIGIT3_X_CRD, MEASURE_DIGIT3_Y_CRD);
        }
    }
}
void AppControl::displayDateInit()
{
    // クリア化
    mlcd.clearDisplay();

    // 背景白
    mlcd.fillBackgroundWhite();

    // 時刻表示の画像
    mlcd.displayJpgImageCoordinate(DATE_NOTICE_IMG_PATH, DATE_NOTICE_IMG_PATH_X_CRD, DATE_NOTICE_IMG_PATH_Y_CRD);

    // 日付
    mlcd.displayDateText(mdtime.readDate(), DATE_YYYYMMDD_X_CRD, DATE_YYYYMMDD_Y_CRD);

    // 時刻
    mlcd.displayDateText(mdtime.readTime(), DATE_HHmmSS_X_CRD, DATE_HHmmSS_Y_CRD);

    // 戻る
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH, COMMON_BUTTON_BACK_IMG_PATH_X_CRD, COMMON_BUTTON_BACK_IMG_PATH_Y_CRD);
}

void AppControl::displayDateUpdate()
{
    // 日付
    mlcd.displayDateText(mdtime.readDate(), DATE_YYYYMMDD_X_CRD, DATE_YYYYMMDD_Y_CRD);

    // 時刻
    mlcd.displayDateText(mdtime.readTime(), DATE_HHmmSS_X_CRD, DATE_HHmmSS_Y_CRD);
}

void AppControl::controlApplication()
{

    mmplay.init();
    mmplay.prepareMP3();
    int num = 0;
    while (1)
    {

        switch (getState())
        {
        case TITLE:
            switch (getAction())
            {
            case ENTRY:
                /*
                ** まずはここにタイトル画面の表示処理を呼び出してみよう。
                ** タイトル画面表示の関数はdisplayTitleInit()である。
                ** この関数の中身はまだ何もないので、この関数にタイトル画面表示処理を書いてみよう。*/
                displayTitleInit();
                setStateMachine(TITLE, DO);

                break;

            case DO:

                if (m_flag_btnA_is_pressed || m_flag_btnB_is_pressed || m_flag_btnC_is_pressed)
                {
                    setStateMachine(TITLE, EXIT);
                    setBtnAllFlgFalse();
                }
                break;

            case EXIT:

                setStateMachine(MENU, ENTRY);
                break;
            default:
                break;
            }

            break;

        case MENU:
            switch (getAction())
            {
            case ENTRY:

                displayMenuInit();
                setStateMachine(MENU, DO);
                break;

            case DO:
                if (m_flag_btnC_is_pressed)
                {
                    switch (getFocusState())
                    {
                    case MENU_WBGT:
                        setFocusState(MENU_MUSIC);
                        focusChangeImg(MENU_WBGT, MENU_MUSIC);
                        setBtnAllFlgFalse();
                        break;
                    case MENU_MUSIC:
                        setFocusState(MENU_MEASURE);
                        focusChangeImg(MENU_MUSIC, MENU_MEASURE);
                        setBtnAllFlgFalse();
                        break;
                    case MENU_MEASURE:
                        setFocusState(MENU_DATE);
                        focusChangeImg(MENU_MEASURE, MENU_DATE);
                        setBtnAllFlgFalse();
                        break;
                    case MENU_DATE:
                        setFocusState(MENU_WBGT);
                        focusChangeImg(MENU_DATE, MENU_WBGT);
                        setBtnAllFlgFalse();
                        break;
                    default:
                        break;
                    }
                }
                else if (m_flag_btnA_is_pressed)
                {

                    switch (getFocusState())
                    {
                    case MENU_WBGT:
                        setFocusState(MENU_DATE);
                        focusChangeImg(MENU_WBGT, MENU_DATE);
                        setBtnAllFlgFalse();
                        break;
                    case MENU_MUSIC:
                        setFocusState(MENU_WBGT);
                        focusChangeImg(MENU_MUSIC, MENU_WBGT);
                        setBtnAllFlgFalse();
                        break;
                    case MENU_MEASURE:
                        setFocusState(MENU_MUSIC);
                        focusChangeImg(MENU_MEASURE, MENU_MUSIC);
                        setBtnAllFlgFalse();
                        break;
                    case MENU_DATE:
                        setFocusState(MENU_MEASURE);
                        focusChangeImg(MENU_DATE, MENU_MEASURE);
                        setBtnAllFlgFalse();
                        break;
                    default:
                        break;
                    }
                }
                else if (m_flag_btnB_is_pressed)
                {

                    switch (getFocusState())
                    {
                    case MENU_WBGT:
                        setStateMachine(MENU, EXIT);
                        break;
                    case MENU_MUSIC:

                        setStateMachine(MENU, EXIT);

                        break;
                    case MENU_MEASURE:
                        setStateMachine(MENU, EXIT);
                        break;
                    case MENU_DATE:
                        setStateMachine(MENU, EXIT);
                        break;
                    default:
                        break;
                    }
                }
                break;

            case EXIT:

                switch (getFocusState())
                {
                case MENU_WBGT:
                    setStateMachine(WBGT, ENTRY);
                    setBtnAllFlgFalse();
                    setFocusState(MENU_WBGT);
                    break;
                case MENU_MUSIC:
                    setStateMachine(MUSIC_STOP, ENTRY);
                    Serial.println("! MUSIC");
                    setBtnAllFlgFalse();
                    setFocusState(MENU_WBGT);
                    break;
                case MENU_MEASURE:
                    setStateMachine(MEASURE, ENTRY);
                    setBtnAllFlgFalse();
                    setFocusState(MENU_WBGT);
                    break;
                case MENU_DATE:
                    setStateMachine(DATE, ENTRY);
                    setBtnAllFlgFalse();
                    setFocusState(MENU_WBGT);
                    break;
                default:
                    break;
                }

                break;
            default:
                break;
            }
            break;

        case WBGT:

            switch (getAction())
            {
            case ENTRY:
                displayWBGTInit();
                setStateMachine(WBGT, DO);
                break;
            case DO:
                displayTempHumiIndex();
                delay(100);
                if (m_flag_btnB_is_pressed)
                {
                    setStateMachine(WBGT, EXIT);
                }
                break;

            case EXIT:
                setStateMachine(MENU, ENTRY);
                setBtnAllFlgFalse();
                break;

            default:
                break;
            }

            break;

        case MUSIC_STOP:
            switch (getAction())
            {
            case ENTRY:
                displayMusicStop();
                setStateMachine(MUSIC_STOP, DO);
                break;

            case DO:
                if (m_flag_btnA_is_pressed)
                {
                    setStateMachine(MUSIC_STOP, EXIT);
                }
                else if (m_flag_btnB_is_pressed)
                {
                    setStateMachine(MUSIC_STOP, EXIT);
                }
                else if (m_flag_btnC_is_pressed)
                {

                    setStateMachine(MUSIC_STOP, EXIT);
                }
                break;

            case EXIT:
                if (m_flag_btnA_is_pressed)
                {
                    setStateMachine(MUSIC_PLAY, ENTRY);
                }
                else if (m_flag_btnB_is_pressed)
                {
                    setStateMachine(MENU, ENTRY);
                }
                else if (m_flag_btnC_is_pressed)
                {
                    displayNextMusic();
                }

                setBtnAllFlgFalse();
                break;

            default:
                break;
            }

            break;

        case MUSIC_PLAY:

            switch (getAction())
            {
            case ENTRY:
                mmplay.prepareMP3();
                displayMusicPlay();
                setStateMachine(MUSIC_PLAY, DO);
                break;

            case DO:

                if (m_flag_btnA_is_pressed || !mmplay.playMP3())
                {

                    setStateMachine(MUSIC_PLAY, EXIT);
                }

                break;

            case EXIT:

                setStateMachine(MUSIC_STOP, ENTRY);
                mmplay.stopMP3();
                setBtnAllFlgFalse();
                break;

            default:
                break;
            }

            break;

        case MEASURE:

            switch (getAction())
            {
            case ENTRY:

                displayMeasureInit();

                setStateMachine(MEASURE, DO);

                break;

            case DO:
                displayMeasureDistance();
                delay(250);
                if (m_flag_btnB_is_pressed)
                {
                    setStateMachine(MEASURE, EXIT);
                }

                break;

            case EXIT:
                setStateMachine(MENU, ENTRY);
                setBtnAllFlgFalse();
                break;

            default:
                break;
            }

            break;

        case DATE:

            switch (getAction())
            {
            case ENTRY:
                displayDateInit();
                setStateMachine(DATE, DO);
                break;

            case DO:

                displayDateUpdate();
                delay(100);
                if (m_flag_btnB_is_pressed)
                {
                    setStateMachine(DATE, EXIT);
                }
                break;

            case EXIT:
                setStateMachine(MENU, ENTRY);
                setBtnAllFlgFalse();
                break;

            default:
                break;
            }

        default:
            break;
        }
    }
}

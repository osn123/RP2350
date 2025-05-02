#include "StateMachine.h"  // ヘッダーファイルのインクルード

// コンストラクタ：LEDの初期設定とステートマシンの初期化
StateMachine::StateMachine(int* pins, int numPins, unsigned long intervalMs, uint8_t repeat)  // コンストラクタの定義
    : pins(pins), numPins(numPins), interval(intervalMs), colorRepeat(repeat), repeatCount(0), state(ST_INIT), prevMillis(0)  // メンバ変数の初期化
{
    leds1 = new CRGB[NUM_LEDS];
    leds2 = new CRGB[NUM_LEDS];
    FastLED.addLeds<WS2812B, LED_PIN1, GRB>(leds1, NUM_LEDS);
    FastLED.addLeds<WS2812B, LED_PIN2, GRB>(leds2, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);  // LEDの明るさを設定
}

StateMachine::~StateMachine() {
  delete[] leds;
}

// メインの状態更新関数：各状態に応じたLED制御を実行
void StateMachine::update()  // 状態更新関数の定義
{
    unsigned long now = millis();  // 現在時刻を取得

    switch (state)  // 現在の状態に応じて処理を分岐
    {
    case ST_INIT:  // 初期状態の場合
        FastLED.clear();  // LEDをクリア
        FastLED.show();  // LEDの状態を更新
        state = ST_RED;  // 赤色状態へ移行
        prevMillis = now;  // 前回の更新時刻を記録
        break;
    case ST_RED:  // 赤色状態の場合
        if (checkInterval(now))  // 指定時間が経過したかチェック
        {
            setColorAndUpdateState(CRGB(255, 0, 0), CRGB(0, 255, 0), ST_GREEN);  // 赤色を設定して緑色状態へ移行
        }
        break;
    case ST_GREEN:  // 緑色状態の場合
        if (checkInterval(now))  // 指定時間が経過したかチェック
        {
            setColorAndUpdateState(CRGB(0, 255, 0), CRGB(0, 0, 255), ST_BLUE);  // 緑色を設定して青色状態へ移行
        }
        break;
    case ST_BLUE:  // 青色状態の場合
        if (checkInterval(now))  // 指定時間が経過したかチェック
        {
            setColorAndUpdateState(CRGB(0, 0, 255), CRGB(255, 255, 0), ST_WHITE);  // 青色を設定して白色状態へ移行
        }
        break;
    case ST_WHITE:  // 白色状態の場合
        if (checkInterval(now))  // 指定時間が経過したかチェック
        {
            setColorAndUpdateState(CRGB(255, 255, 255), CRGB(255, 0, 255), ST_RED);  // 白色を設定して赤色状態へ移行
            repeatCount++;  // 繰り返しカウントを増加
            if (repeatCount >= colorRepeat)  // 指定回数に達したかチェック
            {
                repeatCount = 0;  // カウントをリセット
            }
            else
            {
                state = ST_INIT;  // 初期状態へ戻る
            }
        }
        break;
    }
}

// LEDの色を設定し、次の状態へ移行する補助関数
void StateMachine::setColorAndUpdateState(CRGB color1, CRGB color2, State nextState)  // 色設定と状態更新関数の定義
{
    leds1[0] = color1;
    leds2[0] = color2;
    FastLED.show();  // LEDの状態を更新
    state = nextState;  // 次の状態へ移行
    prevMillis = millis();  // 前回の更新時刻を記録
}

// 指定された時間間隔が経過したかチェックする関数
bool StateMachine::checkInterval(unsigned long now) {  // 時間間隔チェック関数の定義
    return (now - prevMillis >= interval);  // 指定時間が経過したかどうかを返す
}
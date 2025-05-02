#include "StateMachine.h"  // ヘッダーファイルのインクルード

// コンストラクタ：LEDの初期設定とステートマシンの初期化
StateMachine::StateMachine(int* pins, int numPins, unsigned long intervalMs, uint8_t repeat, uint8_t brightness)  // コンストラクタの定義
    : pins(pins), numPins(numPins), interval(intervalMs), colorRepeat(repeat), repeatCount(0), state(ST_INIT), prevMillis(0), brightness(brightness)  // メンバ変数の初期化
{
    leds = new CRGB[NUM_LEDS];  // LED配列のメモリを動的に確保
    if (pins[0] == LED_PIN1) {  // LED1の場合
        FastLED.addLeds<WS2812B, LED_PIN1, GRB>(leds, NUM_LEDS);  // LED1の設定
    } else {  // LED2の場合
        FastLED.addLeds<WS2812B, LED_PIN2, GRB>(leds, NUM_LEDS);  // LED2の設定
    }
    FastLED.setBrightness(brightness);  // LEDの明るさを設定
}

// デストラクタ：メモリの解放
StateMachine::~StateMachine()  // デストラクタの定義
{
    delete[] leds;  // 動的に確保したメモリを解放
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
            setColorAndUpdateState(CRGB(255, 0, 0), ST_ORANGE);  // 赤色を設定してオレンジ色状態へ移行
        }
        break;
    case ST_ORANGE:  // オレンジ色状態の場合
        if (checkInterval(now))
        {
            setColorAndUpdateState(CRGB(255, 128, 0), ST_YELLOW);  // オレンジ色を設定して黄色状態へ移行
        }
        break;
    case ST_YELLOW:  // 黄色状態の場合
        if (checkInterval(now))
        {
            setColorAndUpdateState(CRGB(255, 255, 0), ST_LIME);  // 黄色を設定してライム色状態へ移行
        }
        break;
    case ST_LIME:  // ライム色状態の場合
        if (checkInterval(now))
        {
            setColorAndUpdateState(CRGB(128, 255, 0), ST_GREEN);  // ライム色を設定して緑色状態へ移行
        }
        break;
    case ST_GREEN:  // 緑色状態の場合
        if (checkInterval(now))
        {
            setColorAndUpdateState(CRGB(0, 255, 0), ST_TURQUOISE);  // 緑色を設定してターコイズ色状態へ移行
        }
        break;
    case ST_TURQUOISE:  // ターコイズ色状態の場合
        if (checkInterval(now))
        {
            setColorAndUpdateState(CRGB(0, 255, 128), ST_CYAN);  // ターコイズ色を設定してシアン色状態へ移行
        }
        break;
    case ST_CYAN:  // シアン色状態の場合
        if (checkInterval(now))
        {
            setColorAndUpdateState(CRGB(0, 255, 255), ST_BLUE);  // シアン色を設定して青色状態へ移行
        }
        break;
    case ST_BLUE:  // 青色状態の場合
        if (checkInterval(now))
        {
            setColorAndUpdateState(CRGB(0, 0, 255), ST_PURPLE);  // 青色を設定して紫色状態へ移行
        }
        break;
    case ST_PURPLE:  // 紫色状態の場合
        if (checkInterval(now))
        {
            setColorAndUpdateState(CRGB(128, 0, 255), ST_MAGENTA);  // 紫色を設定してマゼンタ色状態へ移行
        }
        break;
    case ST_MAGENTA:  // マゼンタ色状態の場合
        if (checkInterval(now))
        {
            setColorAndUpdateState(CRGB(255, 0, 255), ST_PINK);  // マゼンタ色を設定してピンク色状態へ移行
        }
        break;
    case ST_PINK:  // ピンク色状態の場合
        if (checkInterval(now))
        {
            setColorAndUpdateState(CRGB(255, 0, 128), ST_WHITE);  // ピンク色を設定して白色状態へ移行
        }
        break;
    case ST_WHITE:  // 白色状態の場合
        if (checkInterval(now))
        {
            setColorAndUpdateState(CRGB(255, 255, 255), ST_RED);  // 白色を設定して赤色状態へ移行
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
void StateMachine::setColorAndUpdateState(CRGB color, State nextState)  // 色設定と状態更新関数の定義
{
    leds[0] = color;  // LEDの色を設定
    FastLED.show();  // LEDの状態を更新
    state = nextState;  // 次の状態へ移行
    prevMillis = millis();  // 前回の更新時刻を記録
}

// 指定された時間間隔が経過したかチェックする関数
bool StateMachine::checkInterval(unsigned long now) {  // 時間間隔チェック関数の定義
    return (now - prevMillis >= interval);  // 指定時間が経過したかどうかを返す
}

void StateMachine::setBrightness(uint8_t newBrightness) {  // 明るさ設定関数の定義
    brightness = newBrightness;  // 新しい明るさを設定
    FastLED.setBrightness(brightness);  // LEDの明るさを更新
}
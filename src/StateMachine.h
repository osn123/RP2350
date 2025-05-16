#ifndef STATE_MACHINE_H    // ヘッダーガード開始
#define STATE_MACHINE_H

#include <Arduino.h>       // Arduino基本ライブラリ
#include <FastLED.h>       // FastLEDライブラリ

// --- 定数定義 ---
#define LED_POWER 23   // LED電源制御ピン
#define LED_PIN1  22   // LEDデータピン1
#define LED_PIN2  3    // LEDデータピン2

#define NUM_LEDS 1     // LEDの数

// --- ステートマシンクラス定義 ---
class StateMachine {
    // --- 状態を表す列挙型 ---
    enum State {
        ST_INIT,      // 初期状態
        ST_RED,       // 赤
        ST_ORANGE,    // オレンジ
        ST_YELLOW,    // 黄
        ST_LIME,      // ライム
        ST_GREEN,     // 緑
        ST_TURQUOISE, // ターコイズ
        ST_CYAN,      // シアン
        ST_BLUE,      // 青
        ST_PURPLE,    // 紫
        ST_MAGENTA,   // マゼンタ
        ST_PINK,      // ピンク
        ST_WHITE      // 白
    };

    // --- メンバ変数 ---
    CRGB *leds;         // LED色情報配列
    int *pins;          // LEDピン配列
    int numPins;        // ピン数
    State state;        // 現在の状態

    u32_t interval;         // 状態遷移間隔（ms）
    u32_t lastMs;           // 前回遷移時刻
    uint8_t colorRepeat;    // 色繰り返し回数
    uint8_t repeatCount;    // 現在の繰り返しカウント
    uint8_t brightness;     // LED明るさ

    // --- 内部関数 ---
    bool checkInterval(unsigned long now); // 遷移タイミング判定
    void setColorNext(CRGB color, State nextState); // 色設定＆状態遷移

  public:
    // --- パブリック関数 ---
    StateMachine(int *pins, int numPins, unsigned long intervalMs,
                 uint8_t repeat = 2, uint8_t brightness = 2); // コンストラクタ
    void update();                             // 状態更新
    void setBrightness(uint8_t newBrightness); // 明るさ設定
    ~StateMachine();                           // デストラクタ
};

#endif // STATE_MACHINE_H

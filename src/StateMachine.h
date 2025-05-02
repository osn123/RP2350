#ifndef STATE_MACHINE_H  // ヘッダーガードの開始
#define STATE_MACHINE_H  // ヘッダーガードの定義

#include <Arduino.h>     // Arduinoの基本ライブラリをインクルード
#include <FastLED.h>    // FastLEDライブラリをインクルード

// 定数定義
#define LED_POWER 23    // LEDの電源制御ピン
#define LED_PIN1 22     // LEDのデータピン1
#define LED_PIN2 3      // LEDのデータピン2

#define NUM_LEDS 1      // LEDの数を定義

class StateMachine {    // ステートマシンクラスの定義
  enum State {          // 状態を表す列挙型
    ST_INIT,           // 初期状態
    ST_RED,            // 赤色状態
    ST_ORANGE,         // オレンジ色状態
    ST_YELLOW,         // 黄色状態
    ST_LIME,           // ライム色状態
    ST_GREEN,          // 緑色状態
    ST_TURQUOISE,      // ターコイズ色状態
    ST_CYAN,           // シアン色状態
    ST_BLUE,           // 青色状態
    ST_PURPLE,         // 紫色状態
    ST_MAGENTA,        // マゼンタ色状態
    ST_PINK,           // ピンク色状態
    ST_WHITE           // 白色状態
  };

  CRGB* leds;          // LEDの色情報を格納するポインタ
  int* pins;           // LEDピンの配列
  int numPins;         // ピンの数
  State state;         // 現在の状態
  
  unsigned long interval;    // 状態遷移の間隔（ミリ秒）
  unsigned long prevMillis;  // 前回の状態遷移時刻
  uint8_t colorRepeat;       // 色の繰り返し回数
  uint8_t repeatCount;       // 現在の繰り返しカウント
  uint8_t brightness;        // LEDの明るさ

  bool checkInterval(unsigned long now);            // 状態遷移のタイミングをチェックする関数
  void setColorAndUpdateState(CRGB color, State nextState);  // 色を設定して状態を更新する関数

public:
  StateMachine(int* pins, int numPins, unsigned long intervalMs, uint8_t repeat = 2, uint8_t brightness = 2);  // コンストラクタ
  void update();        // 状態マシンの更新関数
  void setBrightness(uint8_t newBrightness);  // 明るさを設定する関数
  ~StateMachine();      // デストラクタ
};

#endif  // ヘッダーガードの終了


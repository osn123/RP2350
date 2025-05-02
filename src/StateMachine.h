#ifndef STATE_MACHINE_H  // ヘッダーガードの開始
#define STATE_MACHINE_H  // ヘッダーガードの定義

#include <Arduino.h>     // Arduinoの基本ライブラリをインクルード
#include <FastLED.h>    // FastLEDライブラリをインクルード

// 定数定義
#define LED_POWER 23    // LEDの電源制御ピン
#define LED_PIN1 22      // LEDのデータピン1
#define LED_PIN2 3     // LEDのデータピン2

#define NUM_LEDS 1      // LEDの数を定義
#define BRIGHTNESS 2    // LEDの明るさを定義

class StateMachine {    // ステートマシンクラスの定義
  enum State {          // 状態を表す列挙型
    ST_INIT,           // 初期状態
    ST_RAINBOW_HSL,    // レインボーとHSLの状態
    ST_RED,            // 赤色状態
    ST_GREEN,          // 緑色状態
    ST_BLUE,           // 青色状態
    ST_WHITE           // 白色状態
  };

  CRGB* leds1;          // LED1の色情報を格納するポインタ
  CRGB* leds2;          // LED2の色情報を格納するポインタ
  int* pins;
  int numPins;
  State state;         // 現在の状態
  
  unsigned long interval;    // 状態遷移の間隔（ミリ秒）
  unsigned long prevMillis;  // 前回の状態遷移時刻
  uint8_t hue1;        // レインボー用の色相
  uint8_t hue2;        // HSL用の色相
  uint8_t saturation;  // HSL用の彩度
  uint8_t lightness;   // HSL用の明度
  uint8_t colorRepeat;       // 色の繰り返し回数
  uint8_t repeatCount;       // 現在の繰り返しカウント

  void setRainbowColor(uint8_t hue);  // レインボーカラーを設定
  void setHSLColor(uint8_t hue);      // HSLカラーを設定
  void setColor(uint8_t r, uint8_t g, uint8_t b, bool isLed1);  // LEDの色を設定する関数
  bool checkInterval(unsigned long now);            // 状態遷移のタイミングをチェックする関数
  void setColorAndUpdateState(CRGB color1, CRGB color2, State nextState);  // 色を設定して状態を更新する関数

public:
  StateMachine(int* pins, int numPins, unsigned long intervalMs, uint8_t repeat = 2);  // コンストラクタ
  void update();        // 状態マシンの更新関数
  ~StateMachine();      // デストラクタ
};

#endif  // ヘッダーガードの終了


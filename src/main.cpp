#include <Arduino.h>     // Arduinoの基本ライブラリをインクルード
#include "StateMachine.h"  // ステートマシンのヘッダーファイルをインクルード

// グローバル変数
int ledPins[] = {LED_PIN1, LED_PIN2};  // LEDピンの配列
StateMachine rgb(ledPins, 2, 1000, 2);  // 2つのLEDピン、1秒周期、2回繰り返しのステートマシンインスタンスを作成

// メイン関数
void setup() {          // 初期化関数
  pinMode(LED_POWER, OUTPUT);  // LED_POWERピンを出力モードに設定
  digitalWrite(LED_POWER, HIGH);  // LEDの電源をON
}

void loop() {           // メインループ関数
  rgb.update();         // ステートマシンの状態を更新
}
#include <Arduino.h>     // Arduinoの基本ライブラリをインクルード
#include "StateMachine.h"  // ステートマシンのヘッダーファイルをインクルード

// グローバル変数
int ledPins1[] = {LED_PIN1};  // LED1のピン配列
int ledPins2[] = {LED_PIN2};  // LED2のピン配列
StateMachine rgb1(ledPins1, 1, 1000, 2, 2);  // LED1用のステートマシン（1秒間隔、2回繰り返し、明るさ2）
StateMachine rgb2(ledPins2, 1, 1500, 3, 3);  // LED2用のステートマシン（1.5秒間隔、3回繰り返し、明るさ3）

// メイン関数
void setup() {          // 初期化関数
  pinMode(LED_POWER, OUTPUT);  // LED_POWERピンを出力モードに設定
  digitalWrite(LED_POWER, HIGH);  // LEDの電源をON
}

void loop() {           // メインループ関数
  rgb1.update();        // LED1のステートマシンを更新
  rgb2.update();        // LED2のステートマシンを更新
}
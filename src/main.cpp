#include "StateMachine.h" // ステートマシン制御用ヘッダ
#include <Arduino.h>      // Arduino基本ライブラリ

// --- グローバル変数定義 ---
int ledPins1[] = {LED_PIN1}; // LED1のピン番号
int ledPins2[] = {LED_PIN2}; // LED2のピン番号

// LED1用ステートマシン（1秒間隔、2回繰り返し、明るさ2）
StateMachine rgb1(ledPins1, 1, 1000, 2, 2);
// LED2用ステートマシン（1.5秒間隔、3回繰り返し、明るさ3）
StateMachine rgb2(ledPins2, 1, 1500, 3, 3);

u32_t preMillis = 0; // 前回のミリ秒記録用

// --- 初期化処理 ---
void setup() {
    pinMode(LED_POWER, OUTPUT);    // LED電源ピンを出力に設定
    digitalWrite(LED_POWER, HIGH); // LED電源ON
    pinMode(4, OUTPUT);            // GPIO4を出力に設定
    digitalWrite(4, HIGH);         // GPIO4をHIGHに
}

// --- メインループ ---
void loop() {
    delay(1);            // 負荷軽減のための短い待機
    rgb1.update();       // LED1の状態更新
    rgb2.update();       // LED2の状態更新

    // 1秒ごとにGPIO4の状態を反転
    if (millis() - preMillis > 1000) {
        digitalWrite(4, !digitalRead(4));
        preMillis = millis();
    }
}
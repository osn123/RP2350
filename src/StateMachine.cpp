#include "StateMachine.h" // ヘッダーファイルのインクルード

// ==============================
// コンストラクタ：LEDの初期設定とステートマシンの初期化
// ==============================
StateMachine::StateMachine(int *pins, int numPins, unsigned long intervalMs,
                           uint8_t repeat,
                           uint8_t brightness)
    : pins(pins), numPins(numPins), interval(intervalMs), colorRepeat(repeat),
      repeatCount(0), state(ST_INIT), lastMs(0),
      brightness(brightness)
{
    leds = new CRGB[NUM_LEDS]; // LED配列のメモリを動的に確保

    // LEDピンに応じてFastLEDを初期化
    if (pins[0] == LED_PIN1) {
        FastLED.addLeds<WS2812B, LED_PIN1, GRB>(leds, NUM_LEDS); // LED1の設定
    } else {
        FastLED.addLeds<WS2812B, LED_PIN2, GRB>(leds, NUM_LEDS); // LED2の設定
    }
    FastLED.setBrightness(brightness); // LEDの明るさを設定
}

// ==============================
// デストラクタ：メモリの解放
// ==============================
StateMachine::~StateMachine()
{
    delete[] leds; // 動的に確保したメモリを解放
}

// ==============================
// メインの状態更新関数：各状態に応じたLED制御を実行
// ==============================
void StateMachine::update()
{
    unsigned long now = millis(); // 現在時刻を取得

    switch (state)
    {
    case ST_INIT: // 初期状態
        FastLED.clear();  // LEDをクリア
        FastLED.show();   // LEDの状態を更新
        state = ST_RED;   // 赤色状態へ移行
        lastMs = now;     // 前回の更新時刻を記録
        break;

    case ST_RED: // 赤色状態
        if (checkInterval(now)) {
            setColorNext(CRGB(255, 0, 0), ST_ORANGE); // 赤→オレンジ
        }
        break;

    case ST_ORANGE: // オレンジ色状態
        if (checkInterval(now)) {
            setColorNext(CRGB(255, 128, 0), ST_YELLOW); // オレンジ→黄色
        }
        break;

    case ST_YELLOW: // 黄色状態
        if (checkInterval(now)) {
            setColorNext(CRGB(255, 255, 0), ST_LIME); // 黄色→ライム
        }
        break;

    case ST_LIME: // ライム色状態
        if (checkInterval(now)) {
            setColorNext(CRGB(128, 255, 0), ST_GREEN); // ライム→緑
        }
        break;

    case ST_GREEN: // 緑色状態
        if (checkInterval(now)) {
            setColorNext(CRGB(0, 255, 0), ST_TURQUOISE); // 緑→ターコイズ
        }
        break;

    case ST_TURQUOISE: // ターコイズ色状態
        if (checkInterval(now)) {
            setColorNext(CRGB(0, 255, 128), ST_CYAN); // ターコイズ→シアン
        }
        break;

    case ST_CYAN: // シアン色状態
        if (checkInterval(now)) {
            setColorNext(CRGB(0, 255, 255), ST_BLUE); // シアン→青
        }
        break;

    case ST_BLUE: // 青色状態
        if (checkInterval(now)) {
            setColorNext(CRGB(0, 0, 255), ST_PURPLE); // 青→紫
        }
        break;

    case ST_PURPLE: // 紫色状態
        if (checkInterval(now)) {
            setColorNext(CRGB(128, 0, 255), ST_MAGENTA); // 紫→マゼンタ
        }
        break;

    case ST_MAGENTA: // マゼンタ色状態
        if (checkInterval(now)) {
            setColorNext(CRGB(255, 0, 255), ST_PINK); // マゼンタ→ピンク
        }
        break;

    case ST_PINK: // ピンク色状態
        if (checkInterval(now)) {
            setColorNext(CRGB(255, 0, 128), ST_WHITE); // ピンク→白
        }
        break;

    case ST_WHITE: // 白色状態
        if (checkInterval(now)) {
            setColorNext(CRGB(255, 255, 255), ST_RED); // 白→赤
            repeatCount++; // 繰り返しカウントを増加

            // 指定回数に達したらリセット、それ以外は初期化
            if (repeatCount >= colorRepeat) {
                repeatCount = 0;
            } else {
                state = ST_INIT;
            }
        }
        break;
    }
}

// ==============================
// LEDの色を設定し、次の状態へ移行する補助関数
// ==============================
void StateMachine::setColorNext(CRGB color, State nextState)
{
    leds[0] = color;       // LEDの色を設定
    FastLED.show();        // LEDの状態を更新
    state = nextState;     // 次の状態へ移行
    lastMs = millis();     // 前回の更新時刻を記録
}

// ==============================
// 指定された時間間隔が経過したかチェックする関数
// ==============================
bool StateMachine::checkInterval(unsigned long now)
{
    return (now - lastMs >= interval); // 指定時間が経過したかどうかを返す
}

// ==============================
// 明るさを設定する関数
// ==============================
void StateMachine::setBrightness(uint8_t newBrightness)
{
    brightness = newBrightness;        // 新しい明るさを設定
    FastLED.setBrightness(brightness); // LEDの明るさを更新
}
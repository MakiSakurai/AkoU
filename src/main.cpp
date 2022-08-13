#include <Adafruit_MCP23X17.h>
#include <Adafruit_NeoPixel.h>  //ライブラリの読み込み
#include <Arduino.h>
#define MAX_VAL 64  // 最大輝度の設定をする(暗い←0 ～ 255→明い)
#define INT_PIN 14

Adafruit_MCP23X17 mcp;
// Adafruit_NeoPixel(LEDの使用個数、Arduinoのピン番号、色の並び+データの転送速度)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(4, 12, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();  //インスタンスの使用を開始、この時全てのLEDの状態を「0」とする。
  strip.show();  // Arduinoから全てのLEDへオフ信号「0」を転送し初期化する。
  Serial.begin(9600);
  Serial.println("MCP23x17 Test");

  if (!mcp.begin_I2C(0x27)) {
    Serial.println("I2C connection Error.");
    while (1)
      ;
  }

  pinMode(INT_PIN, INPUT);

  mcp.setupInterrupts(true, false, LOW);

  mcp.pinMode(0, INPUT);
  mcp.pinMode(8, INPUT);

  mcp.setupInterruptPin(0, LOW);
  mcp.setupInterruptPin(8, LOW);
  Serial.println("Looping...");
}

void loop() {
  if (!digitalRead(INT_PIN)) {
    Serial.print("Interrupt detected on pin: ");
    Serial.println(mcp.getLastInterruptPin());
    uint16_t n = strip.numPixels();  // 接続されたLEDの数を取得します
    Serial.print("kosuu");
    Serial.println(n);

    strip.setPixelColor(3,strip.Color(255, 0,255));  // LED番号を指定して色をセットできます．一括して色を変更したい場合はfor文でLEDの数分だけ
    // strip.setPixelColor(n, red, green, blue);

    strip.setBrightness(64);  // 0-255の範囲で輝度（実際には電流量？）を調整できます
    strip.show();
    delay(50);
  }
}

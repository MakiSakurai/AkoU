#include <Adafruit_MCP23X17.h>
#include <Adafruit_NeoPixel.h>  //ライブラリの読み込み
#include <Arduino.h>
#define MAX_VAL 64  // 最大輝度の設定をする(暗い←0 ～ 255→明い)
#define INT_PIN GPIO_NUM_14

Adafruit_MCP23X17 mcp;
// Adafruit_NeoPixel(LEDの使用個数、Arduinoのピン番号、色の並び+データの転送速度)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(4, 12, NEO_GRB + NEO_KHZ800);

volatile byte state = LOW;

void IRAM_ATTR itr_1() {
  state = !state;
  digitalWrite(LED_BUILTIN,state);
  Serial.print("Interrupt detected on pin: ");
  Serial.println(mcp.getLastInterruptPin());
}

void setup() {
  strip.begin();
  strip.show(); 
  Serial.begin(9600);
  Serial.println("MCP23x17 Test");
  pinMode(INT_PIN, INPUT);
  pinMode(LED_BUILTIN,OUTPUT);
  attachInterrupt(INT_PIN, itr_1, CHANGE);

  if (!mcp.begin_I2C(0x27)) {
    Serial.println("I2C connection Error.");
    while (1);
  }

  mcp.setupInterrupts(true, false, LOW);

  mcp.pinMode(0, INPUT);
  mcp.pinMode(8, INPUT);

  mcp.setupInterruptPin(0, LOW);
  mcp.setupInterruptPin(8, LOW);
  Serial.println("Looping...");
}

void loop() {
  delay(100);
  Serial.print(".");
}

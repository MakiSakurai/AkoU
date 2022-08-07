#include <Adafruit_MCP23X17.h>
#include <Arduino.h>
Adafruit_MCP23X17 mcp;
void setup() {
  mcp.begin_I2C(0x27);
  mcp.pinMode(8, INPUT);
  mcp.pinMode(0, OUTPUT);
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);  // pinmodeはGPIOのピンを認識させるモード
}

void loop() {
  // put your main code here, to run repeatedly:
  if (mcp.digitalRead(8) == LOW) {
    digitalWrite(LED_BUILTIN, LOW);
    mcp.digitalWrite(0, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
    mcp.digitalWrite(0, LOW);
  }
}

#include <Adafruit_MCP23X17.h>
#include <Arduino.h>
#define INT_PIN 14

Adafruit_MCP23X17 mcp;
void setup() {
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
    delay(1000);
  }
}

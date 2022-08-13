#include <Adafruit_MCP23X17.h>
#include <Adafruit_NeoPixel.h>  //ライブラリの読み込み
#include <Arduino.h>
#define MAX_VAL 64  // 最大輝度の設定をする(暗い←0 ～ 255→明い)


Adafruit_MCP23X17 mcp1;
// Adafruit_NeoPixel(LEDの使用個数、Arduinoのピン番号、色の並び+データの転送速度)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(4, 26, NEO_GRB + NEO_KHZ800);

volatile byte state = LOW;
volatile bool sensor[8]={false,false,false,false,false,false,false,false};
void IRAM_ATTR itr_1() {
  state = !state;
  digitalWrite(LED_BUILTIN,state);
  sensor[0]=true;
  Serial.println("ITTR1!");
}
void IRAM_ATTR itr_2() {
  state = !state;
  digitalWrite(LED_BUILTIN,state);
  sensor[1]=true;
  Serial.println("ITTR2!");
}
void IRAM_ATTR itr_3() {
  state = !state;
  digitalWrite(LED_BUILTIN,state);
  sensor[2]=true;
  Serial.println("ITTR3!");
}
void IRAM_ATTR itr_4() {
  state = !state;
  digitalWrite(LED_BUILTIN,state);
  sensor[3]=true;
  Serial.println("ITTR4!");
}
void IRAM_ATTR itr_5() {
  state = !state;
  digitalWrite(LED_BUILTIN,state);
  sensor[4]=true;
  Serial.println("ITTR5!");
}
void IRAM_ATTR itr_6() {
  state = !state;
  digitalWrite(LED_BUILTIN,state);
  sensor[5]=true;
  Serial.println("ITTR6!");
}

void IRAM_ATTR itr_7() {
  state = !state;
  digitalWrite(LED_BUILTIN,state);
  sensor[6]=true;
  Serial.println("ITTR7!");
}

void IRAM_ATTR itr_8() {
  state = !state;
  digitalWrite(LED_BUILTIN,state);
  sensor[7]=true;
  Serial.println("ITTR8!");
}

void setup() {
  strip.begin();
  strip.show(); 
  Serial.begin(9600);
  Serial.println("MCP23x17 Test");
  pinMode(14, INPUT);
  pinMode(32, INPUT);
  pinMode(34, INPUT);
  pinMode(33, INPUT);
  pinMode(27, INPUT);
  pinMode(25, INPUT);
  pinMode(39, INPUT);
  pinMode(21, INPUT);            
  pinMode(LED_BUILTIN,OUTPUT);
  attachInterrupt(14, itr_1, FALLING);
  attachInterrupt(32, itr_2, FALLING);
  attachInterrupt(34, itr_3, FALLING);  
  attachInterrupt(33, itr_4, FALLING);
  attachInterrupt(27, itr_5, FALLING);
  attachInterrupt(25, itr_6, FALLING);
  attachInterrupt(39, itr_7, FALLING);
  attachInterrupt(21, itr_8, FALLING);

  if (!mcp1.begin_I2C(0x27)) {
    Serial.println("I2C connection Error.");
    while (1);
  }
  mcp1.readGPIOAB();
  mcp1.setupInterrupts(true, false, LOW);

  mcp1.pinMode(0, INPUT);
  mcp1.pinMode(8, INPUT);

  mcp1.setupInterruptPin(0, LOW);
  mcp1.setupInterruptPin(8, LOW);
  Serial.println("Looping...");
}

void loop() {
  delay(100);
  Serial.print(".");
  if(sensor[0]==true){
    Serial.println("intr ch:1"); 
    Serial.print("intr pin:");
    Serial.println(mcp1.getLastInterruptPin());
    sensor[0]=false;
  }
  if(sensor[1]==true){
    Serial.println("intr ch:2"); 
    Serial.print("intr pin:");
    //Serial.println(mcp2.getLastInterruptPin());
    sensor[1]=false;
  }
  if(sensor[2]==true){
    Serial.println("intr ch:3"); 
    Serial.print("intr pin:");
    //Serial.println(mcp3.getLastInterruptPin());
    sensor[2]=false;
  }
  if(sensor[3]==true){
    Serial.println("intr ch:4"); 
    Serial.print("intr pin:");
    //Serial.println(mcp4.getLastInterruptPin());
    sensor[3]=false;
  }
  if(sensor[4]==true){
    Serial.println("intr ch:5"); 
    Serial.print("intr pin:");
    //Serial.println(mcp5.getLastInterruptPin());
    sensor[4]=false;
  }
  if(sensor[5]==true){
    Serial.println("intr ch:6"); 
    Serial.print("intr pin:");
    //Serial.println(mcp6.getLastInterruptPin());
    sensor[5]=false;
  }
  if(sensor[6]==true){
    Serial.println("intr ch:7"); 
    Serial.print("intr pin:");
    //Serial.println(mcp7.getLastInterruptPin());
    sensor[6]=false;
  }
  if(sensor[7]==true){
    Serial.println("intr ch:8"); 
    Serial.print("intr pin:");
    //Serial.println(mcp8.getLastInterruptPin());
    sensor[7]=false;
  }  
  mcp1.readGPIOAB();
  
}

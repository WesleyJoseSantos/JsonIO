#include <Arduino.h>
#include <Json.hpp>

#define JSON_ITEMS_COUNT 5
#define JSON_DOC_SIZE 128

Json json = Json(JSON_ITEMS_COUNT, JSON_DOC_SIZE);
int integer = 0;
bool state = false;
float real = 0;
unsigned long timer = 0;
char text[] = "hello world!!!";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(74400);

  json.addObject(integer);
  json.addObject(state);
  json.addObject(real);
  json.addObject(timer);
  json.addObject(text);
}

void loop() {
  // put your main code here, to run repeatedly:
  integer++;
  state = !state;
  real += 0.1;
  timer = millis();
  Serial.println(json.toString());
  delay(10);
}
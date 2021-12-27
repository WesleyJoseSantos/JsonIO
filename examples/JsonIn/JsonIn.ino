#include <Arduino.h>
#include <Json.hpp>

#define JSON_ITEMS_COUNT 5
#define JSON_DOC_SIZE 128

String jsonStr = "{\"integer\":332,\"state\":false,\"real\":33.20,\"timer\":3722,\"text\":\"bye bye world!!!\"}";

Json json = Json(JSON_ITEMS_COUNT, JSON_DOC_SIZE);
int integer = 0;
bool state = false;
float real = 0.0;
unsigned long timer = 0;
String text = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(74400);

  json.addObject(integer);
  json.addObject(state);
  json.addObject(real);
  json.addObject(timer);
  json.addObject(text);

  json.fromString(jsonStr);

  Serial.printf("integer = %d\n", integer);
  Serial.printf("state = %d\n", state);
  Serial.printf("real = %f\n", real);
  Serial.printf("timer = %lu\n", timer);
  Serial.printf("text = %s\n\n", text);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
}
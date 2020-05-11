#include <Arduino.h>
#include "Variant.h"

Variant var;

void setup() {
  Serial.begin(115200);

  var = true;
  var.toStream(Serial);
  Serial.println();
  var = -128;
  var.toStream(Serial);
  Serial.println();
  var = 255;
  var.toStream(Serial);
  Serial.println();
  var = -32768;
  var.toStream(Serial);
  Serial.println();
  var = 65535;
  var.toStream(Serial);
  Serial.println();
  var = (int32_t)-2147483648;
  var.toStream(Serial);
  Serial.println();
  var = (uint32_t)4294967295;
  var.toStream(Serial);
  Serial.println();
  var = (float)3.14;
  var.toStream(Serial);
  Serial.println();
  var = '*';
  var.toStream(Serial);
  Serial.println();
  var = "String in RAM";
  var.toStream(Serial);
  Serial.println();
  var = F("String in FLASH");
  var.toStream(Serial);
  Serial.println();
  {
    char str[16];

    if (var.get(str)) {
      Serial.print(F("GET: "));
      Serial.println(str);
    }
  }
  var.clear();
  {
    Variant var2(var);
    char str[16];

    var = false;
    var2 = var;
    Serial.println(var2.toStr(str, sizeof(str)));
    var = -128;
    var2 = var;
    Serial.println(var2.toStr(str, sizeof(str)));
    var = 255;
    var2 = var;
    Serial.println(var2.toStr(str, sizeof(str)));
    var = -32768;
    var2 = var;
    Serial.println(var2.toStr(str, sizeof(str)));
    var = 65535;
    var2 = var;
    Serial.println(var2.toStr(str, sizeof(str)));
    var = (int32_t)-2147483648;
    var2 = var;
    Serial.println(var2.toStr(str, sizeof(str)));
    var = (uint32_t)4294967295;
    var2 = var;
    Serial.println(var2.toStr(str, sizeof(str)));
    var = (float)3.14;
    var2 = var;
    Serial.println(var2.toStr(str, sizeof(str)));
    var = '*';
    var2 = var;
    Serial.println(var2.toStr(str, sizeof(str)));
    var = "String in RAM";
    var2 = var;
    Serial.println(var2.toStr(str, sizeof(str)));
    var = F("String in FLASH");
    var2 = var;
    Serial.println(var2.toStr(str, sizeof(str)));
  }
}

void loop() {}

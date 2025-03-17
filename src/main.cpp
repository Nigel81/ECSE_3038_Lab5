
#include <LiquidCrystal.h>
#include <Arduino.h>
#include <WiFi.h>
#include "env.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>


LiquidCrystal lcd(4, 5, 18, 19, 21, 22);

void setup() {

  Serial.begin(115200);
  Serial.println("Hello, ESP32!");

  lcd.begin(16, 2); 
  lcd.setCursor(0, 0);
  lcd.print("Hello, ESP32!");
  
  if (IS_WOKWI) 
  WiFi.begin(SSID, PASS, CHANNEL);
  else 
  WiFi.begin(SSID, PASS);

  while(WiFi.status() != WL_CONNECTED){

    delay(500);
    Serial.print(".");
  }
  Serial.print("Wifi connect. IP address is: ");
  Serial.println(WiFi.localIP());

}

void loop() {

  if (WiFi.status()==WL_CONNECTED){

    HTTPClient http;
    http.begin(ENDPOINT);
    http.addHeader("api-key",(apiKey));
    int responseCode = http.GET();

    Serial.print("HTTP Response: ");
    Serial.println(responseCode);

    if (responseCode == HTTP_CODE_OK){
      String response = http.getString();
      Serial.print("HTTP Response: ");
      Serial.println(response);

      JsonDocument object;
      DeserializationError error = deserializeJson(object, response);

      if(error){
        Serial.print("Deserialization failed: ");
        Serial.println(error.c_str());
      }else {
        const char* line_1 = object["line_1"];
        const char* line_2 = object["line_2"];

        lcd.setCursor(0, 0);
        lcd.print("Line1: ");
        lcd.print(line_1);
        lcd.setCursor(0, 1);
        lcd.print("Line2: ");
        lcd.print(line_2);

        Serial.print("Line 1: ");
        Serial.println(line_1);
        Serial.print("Line 2: ");
        Serial.println(line_2);
      }
    } else {
      Serial.print("HTTP Request Failed: ");
      Serial.println(responseCode);
    }

    http.end();
  } else {
    Serial.println("Wifi Connection Lost");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Wifi Lost");
  }
  delay(1000);

}
// #include <Arduino.h>
// #include <HTTPClient.h>
// #include "env.h"
// #include <WiFi.h>
// #include <ArduinoJson.h>
// #include <LiquidCrystal.h>
// // #include <Wire.h>

// LiquidCrystal lcd(4, 5, 18, 19, 21, 22);;
// void setup(){
   
//     Serial.begin(115200);
//     lcd.begin(16,2);  // Initialize the LCD
//     lcd.print("Hello");
//     if (IS_WOKWI) 
//     WiFi.begin(SSID, PASS, CHANNEL);
//     else 
//     WiFi.begin(SSID, PASS);

//     while (WiFi.status()!= WL_CONNECTED)
//     {
//         delay(500);
//         Serial.print("."); //waits for wifi connection to then jump out the while loop
//     }

//     Serial.println("Connected to the WiFi Network with IP address: ");
//     Serial.println(WiFi.localIP());

    
    
// }

// void loop(){
//     if(WiFi.status() == WL_CONNECTED) {
//         HTTPClient http;

//         http.begin(ENDPOINT); //just like localhost8000 used previously
//         http.addHeader("api-key", apiKey);


//         // http.GET(); 

//         int responseCode = http.GET(); // -1 if request was unsuccessful 

//         if (responseCode <= 0){
//             Serial.print("An error occurred with this code: ");
//             Serial.println(responseCode);
//             http.end(); //close open connections 
//             return;
//         }
//         Serial.print("HTTP Response Code: ");
//         Serial.println(responseCode);

//         String response = http.getString();
//         Serial.println(response);
//         http.end();

//         JsonDocument object;
//         DeserializationError error = deserializeJson(object, response);  //response  string to object json 

//         if(error){  //error occured
//             Serial.print("Deserialization failed: ");
//             Serial.println(error.c_str());
//             return;
//         }

//         const char* line_1 = object["line1"];
//         const char* line_2 = object["line2"];
        
//         lcd.setCursor(0, 0);
//         lcd.print("Line1: ");
//         lcd.print(line_1);
//         lcd.setCursor(0, 1);
//         lcd.print("Line2: ");
//         lcd.print(line_2);
//     }
//     else {
//         Serial.println("Wifi Connection Lost");
//         lcd.clear();
//         lcd.setCursor(0,0);
//         lcd.print("Wifi Lost");
//       }
//       delay(1000);
// }
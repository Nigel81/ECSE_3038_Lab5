#include <Arduino.h>
#include <HTTPClient.h>
#include "env.h"
#include <WiFi.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup(){
   
    Serial.begin(115200);
    lcd.begin(16,2);  // Initialize the LCD
    lcd.backlight();
    lcd.print("Hello");
    if (IS_WOKWI) 
    WiFi.begin(SSID, PASS, CHANNEL);
    else 
    WiFi.begin(SSID, PASS);

    // while (WiFi.status()!= WL_CONNECTED)
    // {
    //     delay(500);
    //     Serial.print("."); //waits for wifi connection to then jump out the while loop
    // }

    // Serial.println("Connected to the WiFi Network with IP address: ");
    // Serial.println(WiFi.localIP());

    
    
}

void loop(){
    if(WiFi.status() == WL_CONNECTED) {
        HTTPClient http;

        http.begin(ENDPOINT); //just like localhost8000 used previously
        http.addHeader("api-key", apiKey);

        JsonDocument object;
        String request_body;
    
        object["line_1"] = "message1";  
        object["line_2"] = "message2";
            
        serializeJson(object, request_body);

        // http.GET(); 

        int responseCode = http.GET(); // -1 if request was unsuccessful 

        if (responseCode <= 0){
            Serial.print("An error occurred with this code: ");
            Serial.println(responseCode);
            http.end(); //close open connections 
            return;
        }
        Serial.print("HTTP Response Code: ");
        Serial.println(responseCode);

        String response = http.getString();
        Serial.println(response);
        http.end();

        DeserializationError error = deserializeJson(object, response);  //response  string to object json 

        if(error){  //error occured
            Serial.print("Deserialization failed: ");
            Serial.println(error.c_str());
            return;
        }

        String line_1 = object["line1"];
        String line_2 = object["line2"];
        
        lcd.setCursor(0, 0);
        lcd.print("Line1: ");
        lcd.print(line_1);
        lcd.setCursor(0, 1);
        lcd.print("Line2: ");
        lcd.print(line_2);


    }
}
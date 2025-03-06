#include <SoftwareSerial.h>

SoftwareSerial Frontend(2, 3); // RX, TX

String message;
String receivedMessage;
int co2Value = 0;
int temperatureValue = 0;

void setup(void) {
    Serial.begin(9600);
    Frontend.begin(9600);

    delay(500);
    Serial.println(F("TFT LCD test"));

}

void sendToFrontend(String message) {
    Serial.println(message);
}


void loop() {
    while (Frontend.available()>0) {
        char receivedChar = Frontend.read();
        if (receivedChar == '\n') {
            Serial.println(message);
            receivedMessage = "";
        }else{
            receivedMessage += receivedChar;
        }
    }

    // send random co2Value and temperatureValue to frontend
    co2Value = random(0, 1000);
    temperatureValue = random(0, 100);
    message = "CO2:" + String(co2Value) + "Temperature:" + String(temperatureValue);
    sendToFrontend(message);
    delay(1000);
    
    
}

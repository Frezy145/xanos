#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif

// import packages
#include <Adafruit_GFX.h> 
#include <Adafruit_TFTLCD.h>
#include <TouchScreen.h>
#include <SoftwareSerial.h>
#include "Button.h"
#include "Text.h"
#include <MCUFRIEND_kbv.h>

// Define variables
#define YP A2
#define XM A3
#define YM 8
#define XP 9

#define TS_MINX 130
#define TS_MAXX 905

#define TS_MINY 75
#define TS_MAXY 930

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define BOXSIZE 40
#define PENRADIUS 2

#define MINPRESSURE 10
#define MAXPRESSURE 1000

int oldcolor, currentcolor;
int co2Value = 0;
int temperatureValue = 0;
String message;
String receivedMessage;
String co2Label = "CO2: ";
String temperatureLabel = "Temperature: ";
int loopTime = 0;

MCUFRIEND_kbv tft;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

void eraseScreen(int x=5, int y=5, int width=tft.width()-10, int height=tft.height()-10) {
    tft.fillRect(x, y, width, height, BLACK);
}

void sendToBackend(String message) {
    Serial.println(message);
}

void parseReceivedMessage(String receivedMessage) {
    int co2Index = receivedMessage.indexOf("CO2:") + 4;
    int tempIndex = receivedMessage.indexOf("Temperature:") + 12;

    co2Value = receivedMessage.substring(co2Index, receivedMessage.indexOf(",", co2Index)).toInt();
    temperatureValue = receivedMessage.substring(tempIndex).toInt();
}

void readFromBackend() {
    tft.print("Calling readFromBackend");
    tft.setCursor(50, 360);

    if (Serial.available() > 0) {
        eraseScreen(45, 360, 100, 10);
        tft.print("available");
    } else {
        eraseScreen(45, 360, 100, 10);
        tft.print("Not available");
    }

    while (Serial.available()) {
      char receivedChar = Serial.read();
        if (receivedChar == '\n') {
            parseReceivedMessage(receivedMessage);
            receivedMessage = "";
        } else {
            receivedMessage += receivedChar;
        }
    }
}

Button button1 = Button(10, 10, "Menu", WHITE, 2, 8, true, BLUE, 5, true, BLUE, true, eraseScreen);
Button button2 = Button(10, 70, "Home", WHITE, 2, 8, true, WHITE, 0, true, YELLOW, true, eraseScreen);

Text text1 = Text(100, 200, "Hello world !", WHITE, 2, 10, true);
Text text2 = Text(100, 150, "Here is XanOS !", BLACK, 1, 10, true, BLUE, 5, true, YELLOW);


// screen 1
Text screen1Texts[2] = {text1, text2};
Button scren1Buttons[2] = {button1, button2};

// Text xWelcome = Text("Welcome to XanOS", 2, 0, WHITE, 50, 50);

void setup(void) {
    Serial.begin(9600);

    tft.reset();
    uint16_t identifier = tft.readID();
    tft.begin(identifier);
    tft.setRotation(0);

    tft.fillScreen(BLACK);
    tft.drawRoundRect(2, 2, tft.width()-4, tft.height()-4, 10, WHITE);

    // xWelcome.render();

    // delay(3000);

    eraseScreen();
}

void loop() {
    loopTime++;
    digitalWrite(13, HIGH);
    TSPoint p = ts.getPoint();
    digitalWrite(13, LOW);

    // if sharing pins, you'll need to fix the directions of the touchscreen pins
    //pinMode(XP, OUTPUT);
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    //pinMode(YM, OUTPUT);

    for (int i=0; i<2; i++){
        scren1Buttons[i].render();
    }
    for (int i=0; i<2; i++){
        screen1Texts[i].render();
    }

    delay(1000);

    if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {

        p.x = p.x + p.y;       
        p.y = p.x - p.y;            
        p.x = p.x - p.y;   
        
        p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);

        p.y = tft.height()-(map(p.y, TS_MINY, TS_MAXY, tft.height(), 0));
        //p.y = map(p.y, TS_MINY, TS_MAXY, tft.height(), 0);
        
        if (p.y < BOXSIZE) {
            oldcolor = currentcolor;

            // Click a button 
            if (p.x < BOXSIZE) { 
                String msg = "Red";
                sendToBackend(msg);
                currentcolor = RED; 
                tft.drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
            } else if (p.x < BOXSIZE*2) {
                String msg = "Yellow";
                sendToBackend(msg);
                currentcolor = YELLOW;
                tft.drawRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, WHITE);
            } else if (p.x < BOXSIZE*3) {
                currentcolor = GREEN;
                tft.drawRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, WHITE);
            } else if (p.x < BOXSIZE*4) {
                currentcolor = CYAN;
                tft.drawRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, WHITE);
            } else if (p.x < BOXSIZE*5) {
                currentcolor = BLUE;
                tft.drawRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, WHITE);
            } else if (p.x < BOXSIZE*6) {
                currentcolor = MAGENTA;
                tft.drawRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, WHITE);
            }

        }
    }
}


// Paint example specifically for the TFTLCD breakout board.
// If using the Arduino shield, use the tftpaint_shield.pde sketch instead!
// DOES NOT CURRENTLY WORK ON ARDUINO LEONARDO
//Technical support:goodtft@163.com

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>
#include <SoftwareSerial.h>


#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif

// When using the BREAKOUT BOARD only, use these 8 data lines to the LCD:
// For the Arduino Uno, Duemilanove, Diecimila, etc.:
//   D0 connects to digital pin 8  (Notice these are
//   D1 connects to digital pin 9   NOT in order!)
//   D2 connects to digital pin 2
//   D3 connects to digital pin 3
//   D4 connects to digital pin 4
//   D5 connects to digital pin 5
//   D6 connects to digital pin 6
//   D7 connects to digital pin 7

// For the Arduino Mega, use digital pins 22 through 29
// (on the 2-row header at the end of the board).
//   D0 connects to digital pin 22
//   D1 connects to digital pin 23
//   D2 connects to digital pin 24
//   D3 connects to digital pin 25
//   D4 connects to digital pin 26
//   D5 connects to digital pin 27
//   D6 connects to digital pin 28
//   D7 connects to digital pin 29

// For the Arduino Due, use digital pins 33 through 40
// (on the 2-row header at the end of the board).
//   D0 connects to digital pin 33
//   D1 connects to digital pin 34
//   D2 connects to digital pin 35
//   D3 connects to digital pin 36
//   D4 connects to digital pin 37
//   D5 connects to digital pin 38
//   D6 connects to digital pin 39
//   D7 connects to digital pin 40
/*
#define YP 9  // must be an analog pin, use "An" notation!
#define XM 8  // must be an analog pin, use "An" notation!
#define YM A2   // can be a digital pin
#define XP A3   // can be a digital pin
*/

#define YP A2  // must be an analog pin, use "An" notation!
#define XM A3  // must be an analog pin, use "An" notation!
#define YM 8   // can be a digital pin
#define XP 9   // can be a digital pin

#define TS_MINX 130
#define TS_MAXX 905

#define TS_MINY 75
#define TS_MAXY 930
/*
#define TS_MINX 125
#define TS_MAXX 913

#define TS_MINY 118
#define TS_MAXY 833*/
// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
// optional
#define LCD_RESET A4

// Assign human-readable names to some common 16-bit color values:
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

int oldcolor, currentcolor;
int co2Value = 0;
int temperatureValue = 0;
String message;
String receivedMessage;
String co2Label = "CO2: ";
String temperatureLabel = "Temperature: ";


#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
// Adafruit_TFTLCD tft;

// function to erase the screen
void eraseScreen(int x=5, int y=5, int width=tft.width()-10, int height=tft.height()-10) {
    tft.fillRect(x, y, width, height, BLACK);
}


void setup(void) {
    Serial.begin(9600);

    tft.reset();
    uint16_t identifier = tft.readID();
    tft.begin(identifier);
    tft.setRotation(0);

    tft.fillScreen(BLACK);
    tft.drawRoundRect(2, 2, tft.width()-4, tft.height()-4, 10, WHITE);

    // Write "Wellcome to Xanos" in the middle of the screen
    tft.setCursor(50, 50);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.println("Welcome to XanOS");

    delay(3000);

    // Erase the fillScreen
    eraseScreen();
}

#define MINPRESSURE 10
#define MAXPRESSURE 1000

// function to communicate with the backend
void sendToBackend(String message) {
    Serial.println(message);
}

// received message should be in the format "CO2:1000,Temperature:30"
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

// loop time 
int loopTime = 0;

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

    // print co2Value and temperatureValue with labels in the middle of the screen
    eraseScreen(co2Label.length()*2*6 + 45, 100, 50, 15);
    tft.setCursor(50, 100);
    tft.setTextColor(WHITE);   
    tft.setTextSize(2);
    tft.print("CO2: ");
    tft.print(co2Value);

    eraseScreen(temperatureLabel.length()*2*6 + 45, 130, 50, 15);
    tft.setCursor(50, 130);
    tft.print("Temperature: ");
    tft.print(temperatureValue);

    tft.setCursor(50, 300);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print("DEBUG:");
    // erase the loopTime
    eraseScreen(120, 300, 100, 15);
    tft.print(String(loopTime));
    tft.setTextSize(1);
    tft.setCursor(50, 330);
    readFromBackend();

    delay(1000);

    // CLICKING
    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {

        p.x = p.x + p.y;       
        p.y = p.x - p.y;            
        p.x = p.x - p.y;   
        // scale from 0->1023 to tft.width
        //p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
        p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
        //p.y = (tft.height()-map(p.y, TS_MINY, TS_MAXY, tft.height(), 0));
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


            // Draw color buttons
            // if (oldcolor != currentcolor) {
            //     if (oldcolor == RED) {
            //         tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
            //     } 
            //     if (oldcolor == YELLOW) tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
            //     if (oldcolor == GREEN) tft.fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, GREEN);
            //     if (oldcolor == CYAN) tft.fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, CYAN);
            //     if (oldcolor == BLUE) tft.fillRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, BLUE);
            //     if (oldcolor == MAGENTA) tft.fillRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, MAGENTA);
            // }
        }
    }
}


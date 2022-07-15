#include <Arduino.h>
#include "ESP8266QRCode.h"
#include "qrencode.h"

int offsetsX = 42;
int offsetsY = 10;
int screenwidth = 128;
int screenheight = 64;
bool QRDEBUG = false;

ESP8266QRCode::ESP8266QRCode(Adafruit_SSD1306 *display){
	this->display = display;
}

void ESP8266QRCode::init(){
	if(QRDEBUG)
		Serial.println("QRcode init");

	// display->init();
  	// display->flipScreenVertically();
	// display->setColor(WHITE);
}

void ESP8266QRCode::debug(){
	QRDEBUG = true;
}

void ESP8266QRCode::render(int x, int y, int color){
  x=x+offsetsX;
  y=y+offsetsY;
  if(color==1) {
	display->drawPixel(x, y, SSD1306_BLACK);
  }
  else {
	display->drawPixel(x, y, SSD1306_WHITE);
  }
}

void ESP8266QRCode::screenwhite(){
	display->clearDisplay();
	display->fillRect(0, 0, screenwidth, screenheight, SSD1306_WHITE);
}

void ESP8266QRCode::create(String message) {

  // create QR code
  message.toCharArray((char *)strinbuf,260);
  qrencode();
  screenwhite();

  if(QRDEBUG){
	Serial.println("QRcode render");
	Serial.println();
  }
  // print QR Code
  for (byte x = 0; x < WD; x+=2) {
    for (byte y = 0; y < WD; y++) {
      if ( QRBIT(x,y) &&  QRBIT((x+1),y)) {
        // black square on top of black square
        if(QRDEBUG)
			Serial.print("@");
        render(x, y, 1);
        render((x+1), y, 1);
      }
      if (!QRBIT(x,y) &&  QRBIT((x+1),y)) {
        // white square on top of black square
        if(QRDEBUG)
			Serial.print(" ");
        render(x, y, 0);
        render((x+1), y, 1);
      }
      if ( QRBIT(x,y) && !QRBIT((x+1),y)) {
        // black square on top of white square
        if(QRDEBUG)
			Serial.print("@");
        render(x, y, 1);
        render((x+1), y, 0);
      }
      if (!QRBIT(x,y) && !QRBIT((x+1),y)) {
        // white square on top of white square
        if(QRDEBUG)
			Serial.print(" ");
        render(x, y, 0);
        render((x+1), y, 0);
      }
    }
    Serial.println();
  }
  Serial.println();
  display->display();
}

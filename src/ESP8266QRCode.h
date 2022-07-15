#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class ESP8266QRCode
{
	private:
		Adafruit_SSD1306 *display;
		void render(int x, int y, int color);

	public:
		ESP8266QRCode(Adafruit_SSD1306 *display);

		void init();
		void debug();
		void screenwhite();
		void create(String message);
};

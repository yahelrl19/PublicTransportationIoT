#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

void setup() {
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Error al iniciar SSD1306 OLED");
    for (;;);
  }
  display.clearDisplay();
}

void loop() {

  // clear the display and set some font properties
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);

  // display the message on the OLED
  display.println("¡Hola mundo!");
  display.display();

  // wait for some time before updating the display again
  delay(1000);
}

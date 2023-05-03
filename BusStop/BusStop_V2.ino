// Libreria LoRa
#include <RadioLib.h>

//Libreria OLED
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// SX1272 
//arduino uno
// NSS pin:   10
// DIO0 pin:  2
// RESET pin: 14
// DIO1 pin:  3
SX1272 radio = new Module(10, 2, 14, 3);

//Modulo OLED 
//VCC: 5V
//SCL: A5
//SDA: A4
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

void setup() {
  Serial.begin(9600);

  //Inicializando OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Error al iniciar SSD1306 OLED");
    for (;;);
  }
  display.clearDisplay();
  
  // Inicializando SX1272
  Serial.print(F("[SX1272] Initializing ... "));
  int state = radio.begin(898.0,125.0,9,7,0x14,10,8,0); 
  radio.setCRC(0);

  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
  }
}

void loop() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);

  Serial.print(F("[SX1272] Waiting for incoming transmission ... "));

  String str;
  int state = radio.receive(str);

  if (state == RADIOLIB_ERR_NONE) {
    // packet was successfully received
    Serial.println(F("success!"));
    // print the data of the packet
    Serial.print(F("[SX1272] Data:\t\t\t"));
    Serial.println(str);
    // print the RSSI (Received Signal Strength Indicator)
    // of the last received packet
    Serial.print(F("[SX1272] RSSI:\t\t\t"));
    Serial.print(radio.getRSSI());
    Serial.println(F(" dBm"));
    // print the SNR (Signal-to-Noise Ratio)
    // of the last received packet
    Serial.print(F("[SX1272] SNR:\t\t\t"));
    Serial.print(radio.getSNR());
    Serial.println(F(" dB"));
    // print frequency error
    // of the last received packet
    Serial.print(F("[SX1272] Frequency error:\t"));
    Serial.print(radio.getFrequencyError());
    Serial.println(F(" Hz"));
  } else if (state == RADIOLIB_ERR_RX_TIMEOUT) {
    // timeout occurred while waiting for a packet
    Serial.println(F("timeout!"));
  } else if (state == RADIOLIB_ERR_CRC_MISMATCH) {
    // packet was received, but is malformed
    Serial.println(F("CRC error!"));
  } else {
    // some other error occurred
    Serial.print(F("failed, code "));
    Serial.println(state);
  }
}

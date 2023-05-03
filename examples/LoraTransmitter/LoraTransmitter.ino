// SX1272 TRANSMITTER EXAMPLE
// include the library
#include <RadioLib.h>

// SX1272 has the following connections:
//arduino uno
// NSS pin:   10
// DIO0 pin:  2
// RESET pin: 14
// DIO1 pin:  3
SX1272 radio = new Module(10, 2, 14, 3); //arduino uno


void setup() {
  Serial.begin(9600);

  // initialize SX1272
  Serial.print(F("[SX1272] Initializing ... "));
  int state = radio.begin(898.0,125.0,9,7,0x14,10,8,0); 
  //radio.begin(frequency(860.0-1020.0 MHz), bandwidth(125,250,500 kHz), spreading factor(6-12), coding rate denominater(5-8), sync word, output power(1-20 dBm),preamble length(6-65535), gain(0-6 , 0 automatic,  6 the lowest, max:1))
  
  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
  }
}

int counter = 0;

void loop() {
  Serial.print(F("[SX1272] Transmitting packet ... "));

  // you can transmit C-string or Arduino string up to
  // 256 characters long
  // NOTE: transmit() is a blocking method!
  //       See example SX127x_Transmit_Interrupt for details
  //       on non-blocking transmission method.
  int state = radio.transmit("Num: " + String(counter));
  counter ++;

  // you can also transmit byte array up to 256 bytes long
  /*
    byte byteArr[] = {0x01, 0x23, 0x45, 0x67, 0x89, 200, 0x15, 0x77};
    int state = radio.transmit(byteArr, 8);
 */ 

  if (state == RADIOLIB_ERR_NONE) {
    // the packet was successfully transmitted
    Serial.println(F(" success!"));

    // print measured data rate
    Serial.print(F("[SX1272] Datarate:\t"));
    Serial.print(radio.getDataRate());
    Serial.println(F(" bps"));

  } else if (state == RADIOLIB_ERR_PACKET_TOO_LONG) {
    // the supplied packet was longer than 256 bytes
    Serial.println(F("too long!"));

  } else if (state == RADIOLIB_ERR_TX_TIMEOUT) {
    // timeout occurred while transmitting packet
    Serial.println(F("timeout!"));

  } else {
    // some other error occurred
    Serial.print(F("failed, code "));
    Serial.println(state);

  }

  // wait for a second before transmitting again
  delay(10000);
}

//SX 1272 RECEIVER EXAMPLE
// include the library
#include <RadioLib.h>

// SX1272 has the following connections:
//arduino uno
// NSS pin:   10
// DIO0 pin:  2
// RESET pin: 14
// DIO1 pin:  3
SX1272 radio = new Module(10, 2, 14, 3);

void setup() {
  Serial.begin(9600);

  // initialize SX1272 with default settings
  Serial.print(F("[SX1272] Initializing ... "));
  int state = radio.begin(898.0,125.0,9,7,0x14,10,8,0); 
    //radio.begin(frequency(860.0-1020.0 MHz), bandwidth(125,250,500 kHz), spreading factor(6-12), coding rate denominater(5-8), sync word, output power(1-20 dBm),preamble length(6-65535), gain(0-6 , 0 automatic,  6 the lowest, max:1))
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
  Serial.print(F("[SX1272] Waiting for incoming transmission ... "));

  // you can receive data as an Arduino String
  // NOTE: receive() is a blocking method!
  //       See example ReceiveInterrupt for details
  //       on non-blocking reception method.
  String str;
  int state = radio.receive(str);

  // you can also receive data as byte array
  /*
    byte byteArr[8];
    int state = radio.receive(byteArr, 8);
  */

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

// Libreria LoRa
#include <RadioLib.h>
// Libreria GPS
#include <TinyGPS++.h>

// SX1272 has the following connections:
//arduino uno
// NSS pin:   10
// DIO0 pin:  2
// RESET pin: 14
// DIO1 pin:  3
SX1272 radio = new Module(10, 2, 14, 3); //arduino uno

TinyGPSPlus gps;

int minutos;
int pasajeros=0;

const int PIRDelante=18;
const int PIRTrasero=19;

int ETA();
int capacidad();
void setup() {
  Serial.begin(9600);

  pinMode(PIRDelante,INPUT);
  pinMode(PIRTrasero,INPUT);
  // initialize SX1272
  Serial.print(F("[SX1272] Initializing ... "));
  int state = radio.begin(898.0,125.0,9,7,0x14,10,8,0); 
  
  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
  }
}

void loop() {
  Serial.print(F("[SX1272] Transmitting packet ... "));

  int state = radio.transmit("Tiempo estimado de llegada: " + String(ETA()) + " minutos" + "\n Pasajeros en la unidad: " + String(capacidad()));

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

  delay(10000);
}

int ETA(){
  double lat=gps.location.lat();
  double lng=gps.location.lng();
  
  double eta;
  
  if(gps.encode(Serial.read())){
    if(gps.location.isValid()){
      eta=gps.distanceBetween(lat,lng,20.36,-103.22)/3600; //Localización random y 3600 para que sea por minutos
    }
  }
  return eta;
}

int capacidad(){
  int entrada=digitalRead(PIRDelante);
  int salida=digitalRead(PIRTrasero);

  if(entrada==true){
   pasajeros+=1;
  }else if(salida==true){
    pasajeros-=1;
  }
  return pasajeros;
}

#include <TinyGPS++.h>

// Initialize the GPS module with the serial port connected to it
TinyGPSPlus gps;

void setup()
{
  // Start the serial communication with the computer
  Serial.begin(9600);

}

void loop()
{
  // Check if there's data available from the GPS module
  while (Serial.available() > 0)
  {
    // Read the incoming data from the GPS module
    if (gps.encode(Serial.read()))
    {
      // Check if the GPS module has a valid location fix
      if (gps.location.isValid())
      {
        // Get the current location coordinates
        double lat = gps.location.lat();
        double lng = gps.location.lng();
        
        // Calculate the estimated time of arrival (ETA)
        // You can use any algorithm you prefer here
        // This is just a simple example that assumes a constant speed of 60 km/h
        double eta = gps.distanceBetween(lat, lng, 37.7749, -122.4194) / 60;
        
        // Print the ETA to the serial port
        Serial.print("ETA: ");
        Serial.print(eta);
        Serial.println(" hours");
      }
    }
  }
}

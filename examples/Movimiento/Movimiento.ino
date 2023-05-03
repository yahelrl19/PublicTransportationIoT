const int PIRPin= 13;

void setup()
{
  Serial.begin(9600);
  pinMode(PIRPin, INPUT);
}

void loop()
{
  int value= digitalRead(PIRPin);
 
  if (value == HIGH)
  {
    Serial.println("Hay alguien!");
  }
  else
  {
    Serial.println("No hay nadie");
  }
}

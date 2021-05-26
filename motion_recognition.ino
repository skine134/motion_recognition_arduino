#include <SoftwareSerial.h>


#define TX_PIN 2
#define RX_PIN 3
SoftwareSerial mySerial(TX_PIN, RX_PIN);

void setup()
{
  Serial.begin(9600);
  mySerial.begin(115200);
  mySerial.print("Hello! \n");
}
void loop()
{
  if(mySerial.available())
  Serial.println((char)mySerial.read());
}

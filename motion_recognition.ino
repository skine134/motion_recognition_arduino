#include <SoftwareSerial.h>
SoftwareSerial mySerial(14,15);

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

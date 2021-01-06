#include <WiFi.h>

void setup()
{
  Serial.begin(9600);
  delay(10);
  Serial.println();
  WiFi.begin("kladee_home2G", "2011948483");
  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");

  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}
void loop() {}

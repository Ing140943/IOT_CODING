// this code is for test to measure the distance and send notify to line apllication with line notify.
#include <TridentTD_LineNotify.h>
#define SSID "kladee_home2G"
#define PASSWORD "2011948483"
#define LINE_TOKEN "F3pjGonHBTbq6p9mnMiySPIXPROpnk5kOKk4ryh9eLE"
const int pingPin = 19; //D19
int inPin = 18; //D18

bool checksend = false;
void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println(LINE.getVersion());
  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n", SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(400);
  }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());
  LINE.setToken(LINE_TOKEN);
}

void loop()
{
  long duration, cm;

  pinMode(pingPin, OUTPUT);


  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(inPin, INPUT);
  duration = pulseIn(inPin, HIGH);

  cm = microsecondsToCentimeters(duration);
  if ((cm < 30) and (checksend == false))
  {
    checksend = true;
    Serial.print("มีคนเข้ามาใกล้แล้วอยู่หน้าบ้าน : ");
    Serial.println(cm);
    LINE.notify("มีคนเข้ามาใกล้แล้วอยู่หน้าบ้าน ");
    LINE.notify(int(cm));
    LINE.notify("cm");
    LINE.notify("https://drive.google.com/file/d/1gDCtSeigK7NR-K1XXhfJcZiy0M717zf_/view?usp=sharing");
  }
  else {
    checksend = false;
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();
  }
  delay(5000);

}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

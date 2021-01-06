#define LDR 36
#define FAN 5

void setup() 
{ 
  pinMode(FAN,OUTPUT);
  Serial.begin(115200); 
} 
void loop() 
{ 
  // read the input on analog pin 0: 
  int sensorValue = analogRead(LDR); 
  Serial.print("ADC 12 bit = "); 
  Serial.print(sensorValue); // print out the value you read: 
  float volts = 3.30*(float)sensorValue/4095.00; 
  Serial.print(" , Voltage = "); 
  Serial.print(volts,2); 
  Serial.println(" V"); delay(1); // delay for stability 
}

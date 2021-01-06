#define RELAY 19 
#define FAN 5
unsigned long interval=1000; // wait time
unsigned long previousMillis=0; // millis() returns

bool ledState = false; // state variable for the LED
void setup() {
  pinMode(FAN,OUTPUT);
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, ledState);
}

void loop() {
  unsigned long currentMillis = millis(); // grab current time 
  // check if "interval" time has passed (1000 milliseconds)
  if ((unsigned long)(currentMillis - previousMillis) >= interval) 
  {
    ledState = !ledState; // "toggles" the state
    digitalWrite(RELAY, ledState); // sets the LED with ledState
    // save the "current" time
    previousMillis = millis();
  }
}

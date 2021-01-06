#include<WiFi.h>

#define RELAY1 19  
#define LDR 36   
#define SSID_NAME "kladee_home2G" //network-name
#define SSID_PASS "2011948483" //pass-to-network

WiFiServer server(80);

void setup()
{
  pinMode(RELAY1,OUTPUT);
  Serial.begin(115200);
  delay(10);
  Serial.println();

  WiFi.begin(SSID_NAME, SSID_PASS);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK\nContent-type:text/html\n");
            
            client.print("Realy 1 status :");
            client.print(digitalRead(RELAY1));
            client.println("<br>");
            
            client.print("LDR read:");
            client.print(analogRead(LDR));
            client.println("<br>");

            // the content of the HTTP response follows the header:
            client.println("Click <a href=\"/H\">here</a> to turn ON the Realy 1.<br>");
            client.println("Click <a href=\"/L\">here</a> to turn OFF the Realy 1.<br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(RELAY1, HIGH);               // GET /H turns the LED on
          Serial.println("turns the realy1 on");
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(RELAY1, LOW);                // GET /L turns the LED off
          Serial.println("turns the realy1 off");
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}

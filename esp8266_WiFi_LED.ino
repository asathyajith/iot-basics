#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "*******";  // Replace with your Wi-Fi SSID
const char* password = "*****";  // Replace with your Wi-Fi 

ESP8266WebServer server(80);

const int ledPin = 16;  // GPIO16
bool ledState = LOW;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);
  
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to Wi-Fi...");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("Connected to Wi-Fi");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String message;
  
  if (server.hasArg("state")) {
    String state = server.arg("state");
    
    if (state == "on") {
      digitalWrite(ledPin, HIGH);  // Turn the LED on
      ledState = HIGH;
      message = "LED turned ON";
    } else if (state == "off") {
      digitalWrite(ledPin, LOW);  // Turn the LED off
      ledState = LOW;
      message = "LED turned OFF";
    } else {
      message = "Invalid state";
    }
  } else {
    message = "LED is ";
    
    if (ledState == HIGH) {
      message += "ON";
    } else {
      message += "OFF";
    }
  }
  
  server.send(200, "text/plain", message);
}
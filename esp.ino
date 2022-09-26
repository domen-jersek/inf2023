#include <WiFi.h>

const char* ssid = "ime omrezja";
const char* password = "geslo omrezja";

WiFiServer server(80);

void setup() {
    Serial.begin(115200);
    pinMode(2, OUTPUT);

    WiFi.begin(ssid, password);
    Serial.println(WiFi.localIP());

    server.begin();
    
}

void loop() {

}
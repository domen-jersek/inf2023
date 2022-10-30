#include <WiFi.h>

const char* ssid = "Ju57";
const char* password = "dvamuceca";

const int button = 4; 

WiFiServer server(80);

void setup() {
    Serial.begin(115200);
    pinMode(5, OUTPUT);

    pinMode(button, INPUT);

    WiFi.begin(ssid, password);
    Serial.println(WiFi.localIP());

    server.begin();

}

int value = 0;

void loop() {
    WiFiClient client = server.available(); //poslusaj za cliente

    if(client) {
        String currentLine = "";
        while(client.connected()) {
            if(client.available()) {
                char c = client.read();
                Serial.write(c);
                if(c == '\n') {

                    if(currentLine.length() == 0) {
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println();

                        client.print("<a href=\"/H\">ON</a>");
                        client.print("<a href=\"/L\">OFF</a>");

                        client.println();
                        break;

                    } else {
                        currentLine = ""; //izbrisi linijo
                    }


                } else if(c != '\r') { //sprejmi vnos le ce ni kocija
                    currentLine += c;
                }

                if (currentLine.endsWith("GET /H")) {
                    digitalWrite(5, HIGH);
                }

                if (currentLine.endsWith("GET /L")) {
                    digitalWrite(5, LOW);
                }

            }
        }
        client.stop(); //zapri povezavo
    }
    /*buttonState = digitalRead(button);
    if (buttonState == HIGH) {
        digitalWrite(5, HIGH);
    }
    if (buttonState == LOW) {
        digitalWrite(5, LOW);
    }*/

}

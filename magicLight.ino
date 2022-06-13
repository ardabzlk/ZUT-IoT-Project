// Arda Bozlak
// 52863
// Erasmus Exchange student at ZUT Computer Science and Information Technology Faculty

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "ardab";        //  Network ID
const char *password = "8125526A"; //  Network password

ESP8266WebServer server(80); // We created a web server object using port 80

uint8_t LED1pin = D6;
bool LED1status = LOW;

void setup()
{
  Serial.begin(115200);
  delay(100);
  pinMode(LED1pin, OUTPUT);

  Serial.println("Connecting");
  Serial.println(ssid);

  // The function that allows us to connect local network
  WiFi.begin(ssid, password);

  // checking out the conenction
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print("."); // Loading sign
  }
  Serial.println("");
  Serial.println("Connection succesfull..!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.on("/led1on", handle_led1on);
  server.on("/led1off", handle_led1off);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP Server launched");
}
void loop()
{
  server.handleClient();
  if (LED1status)
  {
    digitalWrite(LED1pin, HIGH);
  }
  else
  {
    digitalWrite(LED1pin, LOW);
  }
}
// the function that works on beginning
void handle_OnConnect()
{
  LED1status = LOW;
  Serial.println("GPIO6 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status));
}
// function for turning LED on
void handle_led1on()
{
  LED1status = HIGH;
  Serial.println("GPIO7 Status: ON");
  server.send(200, "text/html", SendHTML(true));
}
// function for turning LED off
void handle_led1off()
{
  LED1status = LOW;
  Serial.println("GPIO7 Status: OFF");
  server.send(200, "text/html", SendHTML(false));
}
// exception for wrong url
void handle_NotFound()
{
  server.send(404, "text/plain", "Page not found");
}
// HTML template =>
String SendHTML(uint8_t led1stat)
{
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<meta http-equiv=\"Content-Type\" content=\"text/html;charset=UTF-8\">";
  ptr += "<title>ESP8266 BA52863</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr += ".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr += ".button-on {background-color: #1abc9c;}\n";
  ptr += ".button-on:active {background-color: #16a085;}\n";
  ptr += ".button-off {background-color: #34495e;}\n";
  ptr += ".button-off:active {background-color: #2c3e50;}\n";
  ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1>ESP8266 Web Server Project</h1>\n";
  ptr += "<h3>Arda Bozlak 52863</h3>\n";
  ptr += "<h3>Introduction to the Internet of Things Final Project</h3>\n";
  ptr += "<h3>ESP Station(STA) MODE</h3>\n";

  if (led1stat)
  {
    ptr += "<p>LED STATUS: ON</p><a class=\"button button-off\" href=\"/led1off\">OFF</a>\n";
  }
  else
  {
    ptr += "<p>LED STATUS: OFF</p><a class=\"button button-on\" href=\"/led1on\">ON</a>\n";
  }

  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}

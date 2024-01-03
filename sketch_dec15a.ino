#include <ESP8266WiFi.h> 
const char* WLAN_SSID = "Fd";
const char* WLAN_PASSWORD = "MarxEngelsss"; 
const char* thingSpeakHost = "api.thingspeak.com";
String writeAPIKey = "35I43KO7ZTTW53DA"; 
int sicaklikSensor= A0;
float sicaklikdegeri;
float olculendeger;
WiFiClient client;
void WiFi_Setup() {
delay (10);
Serial.println(); Serial.print (WLAN_SSID);
Serial.print("Kablosuz Agina Baglaniyor");
WiFi.begin(WLAN_SSID, WLAN_PASSWORD);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println();Serial.print (WLAN_SSID);
Serial.println("Kablosuz Agina Baglandi");
Serial.println("IP adresi: ");
Serial.println(WiFi.localIP());
}

void setup() {
Serial.begin (9600);
WiFi_Setup();
pinMode (A0, INPUT);
}
void loop () {
olculendeger = analogRead (sicaklikSensor);
olculendeger = (olculendeger/1024)*5000;
sicaklikdegeri = olculendeger /12.0;
sicaklikdegeri=sicaklikdegeri + 10;
if (client.connect (thingSpeakHost, 80)){
String postStr = "field1=";
postStr+= String (sicaklikdegeri);
client.print("POST /update HTTP/1.1\n");
client.print("Host: api.thingspeak.com\n");
client.print("Connection: close\n");
client.print ("X-THINGSPEAKAPIKEY: " + writeAPIKey + "\n");
client.print ("Content-Type: application/x-www-form-urlencoded\n");
client.print("Content-Length: ");
client.print (postStr.length());
client.print("\n\n");
client.print (postStr);
client.print("\n\n");
Serial.println(sicaklikdegeri);
Serial.println ("Thingspeak veri gönderildi");
}
client.stop();
delay (2000);
}
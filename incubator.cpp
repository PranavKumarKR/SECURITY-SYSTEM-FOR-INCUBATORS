#include <ESP8266WiFi.h>
const int MO=D2;
const int RO=D4;
int adcPin = A0;
int relayInput = D6;
long randNumber;
// Your WiFi credentials.
// Set password to "" for open networks.
const char *ssid = "IOT";
const char *pass = "password";
const char* host = "gladesoftwaresolution.in";
void setup() 
{
       Serial.begin(115200);
       Serial.println("Connecting to ");      
       Serial.println(ssid);
       WiFi.begin(ssid, pass);
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
           
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
      
      delay(4000);

}
void loop()
{
  String postData;
   
   bMO = digitalRead(MO);
    bRO = digitalRead(RO);
   
  if (bMO == LOW){
      MOData="HIGH";
      //digitalWrite(relayInput, HIGH);
    }
    else if(bMO == HIGH){
      MOData="LOW";
      //digitalWrite(relayInput, LOW);
    }
  if (bRO == LOW){
      ROData="HIGH";
      //digitalWrite(relayInput, HIGH);
    }
    else if(bRO == HIGH){
      ROData="LOW";
      //digitalWrite(relayInput, LOW);
    }
  if(bMO == LOW || bRO == LOW)
  {
    digitalWrite(relayInput, HIGH);
  }
  else
  {
    digitalWrite(relayInput, LOW);
  }
  delay(100);
  HTTPClient http;
  if (connect(host,80))
  {
postData = "?r=" + String(MOData) + ",s=" + String(ROData);
  http.begin("http://cloud.gladeembeddedsystems.in/IOT_Baby.aspx"+ postData);              //Specify request destination
  //http.addHeader("Content-Type", "application/x-www-form-urlencoded"); 
  int httpCode = http.GET();   //Send the request
  String payload = http.getString();    //Get the response payload
  //String payload = http.getString();    //Get the response payload
 Serial.println(postData);   //Print HTTP return code
 // Serial.println(httpCode);
  http.end();
  //Close connection
  Serial.println("Waiting...");
  delay(100000);
  }
}

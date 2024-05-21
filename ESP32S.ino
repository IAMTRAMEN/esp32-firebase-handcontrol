#include <WiFi.h>                                                // esp32 library

#include <IOXhop_FirebaseESP32.h>                                             // firebase library

#define FIREBASE_HOST "https://esp32-e9773-default-rtdb.firebaseio.com/"                         // the project name address from firebase id

#define FIREBASE_AUTH "AIzaSyDbFqtzvVFdNDWWjI9WlSCXHhtTl1km_9M"                    // the secret key generated from firebase

#define WIFI_SSID "TOPNET_BLYT"                                          // input your home or public wifi name

#define WIFI_PASSWORD "hvjzoaqr01"                                    //password of wifi ssid

String fireStatus = "";                                                     // led status received from firebase                                                              

void setup() {

  Serial.begin(115200);

  delay(1000);             

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                      //try to connect with wifi

  Serial.print("Connecting to ");

  Serial.print(WIFI_SSID);

  while (WiFi.status() != WL_CONNECTED) {

    Serial.print(".");

    delay(500);

  }

  Serial.println();

  Serial.print("Connected to ");

  Serial.println(WIFI_SSID);

  Serial.print("IP Address is : ");

  Serial.println(WiFi.localIP());                                                      //print local IP address

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                                       // connect to firebase

  Firebase.setString("led/status", "0");                                          //send initial string of led status
pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

  fireStatus = Firebase.getString("led/status");                     // get led status input from firebase

  if (fireStatus == "1") {                         // compare the input of led status received from firebase

    Serial.println("Led Turned ON");                 
    digitalWrite(LED_BUILTIN, HIGH);                                                        // make output led ON

  }

  else if (fireStatus == "0") {              // compare the input of led status received from firebase

    Serial.println("Led Turned OFF");
   digitalWrite(LED_BUILTIN, LOW);                                                       // make output led OFF

  }

  else {

    Serial.println("Wrong Credential! Please send ON/OFF");

  }

}
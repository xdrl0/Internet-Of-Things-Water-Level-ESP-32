#include <ThingSpeak.h>
#include <WiFi.h>
const int trigPin = 5;
const int echoPin = 18;

// defines variables
long duration;
int distance;
//sambungin ke wifi kita
const char *ssid =  "IRINE X"; //your network SSID (name)
const char *pass =  "minimal90"; //your network password
WiFiClient client;
//thingspeak settings
unsigned long channel = 1757224; //your channel ID number** dari channel thingspeak yg telah kita buat
const char *apiKey = "A3N4QON3GXI3VGF3"; //your channel write API Key

//int lum, i = 0;

void setup() {
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    Serial.begin(115200);
    delay(10);
    
    //connect to WiFi
    Serial.print("Connecting to: "); Serial.println(ssid);
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("\nWiFi connected\n");
    
    ThingSpeak.begin(client); //initialize ThingSpeak
}

void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance cm
distance= duration*0.034/2;

// Prints the distance on the Serial Monitor
Serial.print("Distance (Cm): ");
Serial.println(distance);  
// i++;
 // lum = analogRead(34);
  
  int x = ThingSpeak.writeField(channel, 1, distance, apiKey);
  if (x == 200) {
    Serial.println("Data NEW UPDATE " + String(distance));
    Serial.print("distance: "); Serial.println(distance);
    Serial.println("Update to ThingSpeak Successful.");
  }
  else {
    Serial.println("Data NEW UPDATE " + String(distance));
    Serial.println("Problem updating data. HTTP error code " + String(x));
  }
  
  Serial.println("Waiting...\n");
  //tahan selama 1 detik, program tidak menjalankan yang lain
  delay(1000);
}

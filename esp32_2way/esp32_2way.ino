/************************With kicker and Dribbler data***************check baud rate and Serial.write()************************/
#include <WiFi.h>
#include <WiFiUdp.h>
#define LED 2

/* WiFi network name and password */
const char * ssid = "Xiaomi_D01D";
const char * pwd = "qwerty123456";

// IP address to send UDP data to.
// it can be ip address of the server or
// a network broadcast address
// here is broadcast address
const char * udpAddress = "192.168.31.4";
const int udpPort = 44444;

//create UDP instance
WiFiUDP udp;

void setup(){

  Serial.begin(250000);
  pinMode(LED,OUTPUT);
  //Connect t o the WiFi network
   WiFi.begin(ssid, pwd);
  //Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED, LOW);
    delay(500);
    digitalWrite(LED, HIGH);
  }
  //Serial.println("");
  //Serial.print("Connected to ");
  /*Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());*/
  //This initializes udp and transfer buffer
  udp.begin(udpPort);
}

void loop(){
  
     if(WiFi.status() != WL_CONNECTED)
    {
    digitalWrite(LED, LOW);
    WiFi.begin(ssid, pwd);
    while (WiFi.status() != WL_CONNECTED) 
    {
      digitalWrite(LED, LOW);
      delay(500);
      digitalWrite(LED, HIGH);
    }
  }
  else
  {
    digitalWrite(LED, HIGH);
  }
    char* a;
    int i,d;
  //data will be sent to server
  uint8_t buffer[50] = "abcdefgh";
  //send hello world to server
  udp.beginPacket(udpAddress, udpPort);
  udp.write(buffer, 8);
  udp.endPacket();
  memset(buffer, 0, 50);
  //processing incoming packet, must be called before reading the buffer
  udp.parsePacket();
  //receive response from server, it will be HELLO WORLD
 
      //Serial.print('y');
  if(udp.read(buffer,32) > 0){
    
      //Serial.println('New packet');
    
    a = (char *)buffer;
    Serial.write(255);
    for(i =6 ;i <11; i++)
    {
      d = (int)a[i];
      if(d>127)
      {
       d = 254 -(d+127)%255;
      }
      /*if(d>0&&d<20)
      {
        d= 20;
      }
      else if(d>128&&d<148)
      {
        d = 148;
      }*/
      Serial.write(d);
      //delay(2000);
      //Serial.println();
    }
  }
  //Wait for 1 second
  //delay(1000);
}

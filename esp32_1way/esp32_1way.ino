/************************With kicker and Dribbler data***************check baud rate and Serial.write()************************/
#include <WiFi.h>
#include <WiFiUdp.h>
#define UART_CHECK 255
#define LED 2
/* WiFi network name and password */
const char * ssid = "Xiaomi_D01D";
const char * pwd = "qwerty123456";

/*IP Address of the Server*/
/*Don't use broadcast address - It wont work due to high power required*/
const char * udpAddress = "192.168.31.4";
const int udpPort = 44444;

WiFiUDP udp;

void setup() {

  Serial.begin(250000);
  pinMode(LED, OUTPUT);
  WiFi.begin(ssid, pwd);
  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(LED, LOW);
    delay(500);
    digitalWrite(LED, HIGH);
  }
  /*Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());*/
  //This initializes udp and transfer buffer
  udp.begin(udpPort);
}

void loop()
{
  if (WiFi.status() != WL_CONNECTED)
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
  char* data;
  int i, d;
  /*//data will be sent to server
    uint8_t buffer[50] = "abcdefgh";
    //send hello world to server
    udp.beginPacket(udpAddress, udpPort);
    udp.write(buffer, 8);
    udp.endPacket();*/
  uint8_t buffer[50];
  memset(buffer, 0, 50);
  //processing incoming packet, must be called before reading the buffer
  udp.parsePacket();
  if (udp.read(buffer, 32) > 0)
  {
    data = (char *)buffer;
    Serial.write(UART_CHECK);
    for (i = 6 ; i < 11; i++)
    {
      d = (int)data[i];
      if (d > 127)
      {
        d = 254 - (d + 127) % 255;
      }
      Serial.write(d);
      //delay(2000);
      //Serial.println();
    }
  }
}

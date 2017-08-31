#include <SPI.h> 
#include <Ethernet.h>
#include <EthernetUdp.h>

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

IPAddress broadcastIP(255, 255, 255, 255);
unsigned int broadcastPort = 6555;

unsigned int localPort = 8888;
bool connection = false;

int packetRate = 20;

char packetBuffer[48];
uint8_t _data[48] = {
  /* 0  */ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, //destination MAC
  /* 6  */ 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, //source MAC
  /* 12 */ 0x08, 0x06, //frame type (ARP)
  /* 14 */ 0x00, 0x01, //ethernet
  /* 16 */ 0x08, 0x00, //ipv4
  /* 18 */ 0x06, 0x04, //size, protocol size
  /* 20 */ 0x00, 0x02, //opcode (1:request, 2:reply)
  /* 22 */ 0x01, 0x01, 0x01, 0x01c, 0x01, 0x01, //source MAC
  /* 28 */ 0xc0, 0xa8, 0x02, 0x01, //source IP
  /* 32 */ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, //destination MAC
  /* 38 */ 0xFF, 0xFF, 0xFF, 0xFF, //destination IP (255.255.255.255)
};

EthernetUDP Udp;

void sendARP() {
for (int i = 0; i < packetRate; i++) {
      digitalWrite(LED_BUILTIN, HIGH);

      for (int x = 0; x < 48; x++) {
          packetBuffer[x] = _data[x];
      }

      Udp.beginPacket(broadcastIP, broadcastPort);
      Udp.write(packetBuffer, 48);
      Udp.endPacket();
      delay(1000 / packetRate);
      digitalWrite(LED_BUILTIN, LOW);
  } 
  
}
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  if (Ethernet.begin(mac) == 0) {
      connection = false;
      digitalWrite(LED_BUILTIN, LOW);  
  } else {
      connection = true;
      Udp.begin(localPort);  
  }

  while (!connection) {
    setup();
 }
}

void loop() {
  if (connection) {
      sendARP();
      delay(100);
  }
}

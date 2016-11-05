#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const uint16_t NTP_PACKET_SIZE = 48;
// Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
const unsigned long seventyYears = 2208988800UL;

class NtpClient {
private:
  uint16_t localPort;      // local port to listen for UDP packets

  IPAddress ntpIpAdress;

  byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets

  // A UDP instance to let us send and receive packets over UDP
  WiFiUDP udp;
public:
  NtpClient();
  void init();
  unsigned long getNtpTime();
};

#include <ESP8266WiFi.h>
//#include <ArduinoJson.h>
#include <JsonStreamingParser.h>
#include "WeatherListener.h"

#include "icons.h"
#include "constants.h"

// TODO spin while connecting to WiFi
// const char spinner[] = {'/', '-', 0b11111011, 0b11111110};

void load_icon(const uint8_t icon[]) {
  for (uint8_t c = 0; c < 8; c++) {
    Serial.printf("\031");
    Serial.printf("%c", c);
    for (uint8_t d = 0; d < 8; d++) {
      Serial.printf("%c", icon[(c * 8) + d]);
    }
  }
}
void print_icon_pt1() {
  // Position cursor to upper left of screen
  Serial.printf("\014");
  Serial.printf("\200\201\202\203");
}
void print_icon_pt2() {
  Serial.printf("\204\205\206\207            ");
}

void scroll_string(String str) {
  unsigned long start_time = millis();
  int len = str.length();
  int pos = 0;
  while (true) {
    // Position cursor to start of scroll area
    Serial.printf("\021\004\001");
    Serial.print(str.substring(pos, pos+12));
    if (pos == 0) {
      // Beginning of string
      ++pos;
      delay(2000);
    } else if (pos == len - 12) {
      // End of string
      // Break after scrolling for 1 hour
      // TODO handle millis() overflow (70 days)
      if (millis() - start_time > 3600000) {
        break;
      }
      pos = 0;
      delay(2000);
    } else {
      // In the middle
      ++pos;
      delay(200);
    }
  }
}

void setup() {
  // TODO spin while connecting to WiFi
  // uint8_t spinner_index = 0;

  // Initialize Crystalfontz display
  Serial.begin(19200, SERIAL_8N1);
  delay(1000);
  // Reset display  
  Serial.printf("\032\032");
  delay(2000);
  // Set display contrast
  Serial.printf("\017F");
  // Hide cursor
  Serial.printf("\004");
  // Scroll off
  Serial.printf("\024");
  // Wrap off
  Serial.printf("\030");

  delay(1000);

  // Associate with wifi
  Serial.printf("Connecting to\r\n%s... ", ssid);
  WiFi.mode(WIFI_STA);
  // FIXME -- WiFi.begin is buggy. Work around: https://github.com/esp8266/Arduino/issues/2186
  WiFi.begin(ssid, password);
  Serial.printf("\014Connected! IP:\r\n");
  IPAddress ip = WiFi.localIP();
  Serial.printf("%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
  delay(2000);
}

void loop() {
  JsonStreamingParser parser;
  WeatherListener listener;
  
  Serial.printf("\014Fetching url\r\n");
  WiFiClientSecure client;
  client.connect("api.darksky.net", 443);
  client.printf("GET /forecast/%s/%s?exclude=currently,hourly,minutely,alerts,flags HTTP/1.1\r\n", api_key, latlong);
  client.printf("Host: api.darksky.net\r\n");
  client.printf("Connection: close\r\n");
  client.printf("\r\n");
  delay(10);
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
  }
  Serial.printf("Parsing response\r\n");

  parser.setListener(&listener);
  while (client.connected()) {
    parser.parse(client.read());
  }

  if (listener.icon == "snow") {
    load_icon(snow);
  } else if (listener.icon == "clear-day" || listener.icon == "clear-night") {
    load_icon(clear_day);  // TODO make icon for night
  } else if (listener.icon == "party-cloudy-day" || listener.icon == "party-cloudy-night") {
    load_icon(partly_cloudy_day);  // TODO make icon for night
  } else if (listener.icon == "fog") {
    load_icon(cloudy);  // TODO make icon for fog
  } else if (listener.icon == "cloudy") {
    load_icon(cloudy);
  } else if (listener.icon == "wind") {
    load_icon(wind);
  } else if (listener.icon == "rain") {
    load_icon(rain);
  } else if (listener.icon == "sleet") {
    load_icon(snow);  // TODO make icon for sleet
  } else {
    load_icon(clear_day);
  }

  print_icon_pt1();
  Serial.printf("%c %d\036\001\200 ", 0b11011110, listener.temperatureMax);
  Serial.printf("%c %d\036\001\200\r\n", 0b11100000, listener.temperatureMin);
  print_icon_pt2();

  // Replace unicode degree symbol with blank. TODO handle multibyte degree symbol
  // ("\036\001\200") while scrolling
  listener.summary.replace("°", "");
  scroll_string(listener.summary);
}

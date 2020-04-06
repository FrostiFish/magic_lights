#include <Arduino.h>
#include <OOCSI.h>
#include <FastLED.h>

OOCSI oocsi = OOCSI();
const String ssid  = "";
const String password = "";

const int ledPin = 22;
const int numLeds = 10;
const int brightness = 100;
CRGB leds[numLeds];
int8_t hue = 40;
int8_t saturation = 100;
int8_t value = 230;

void processOOCSI() {
  Serial.println("Received message!");
}

void setup() {
  oocsi.connect("group1_lamps", "oocsi.id.tue.nl", ssid, password, processOOCSI);
  Serial.begin(115200);
  Serial.println("subscribing to channel: group1_mirror");
  oocsi.subscribe("group1_mirror");
  pinMode(ledPin, OUTPUT);
  FastLED.addLeds<WS2813, ledPin, GRB>(leds, numLeds);
  FastLED.setBrightness(brightness);
}

void loop() {
  CRGB rgb;
  hsv2rgb_spectrum(CHSV(hue, saturation, value), rgb);
  FastLED.show();

  //OOCSI
  int hsv[] = {hue, saturation, value};
  oocsi.newMessage("magic_lights");
  oocsi.addIntArray("lamp1", hsv, 3);
  oocsi.sendMessage();
}

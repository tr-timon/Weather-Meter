#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#include <Fonts/FreeSans9pt7b.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define BLUE_LED   4
#define GREEN_LED  5
#define YELLOW_LED 6
#define RED_LED    7



void setup() {
  pinMode(BLUE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  dht.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for (;;); // Loop forever if OLED fails
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  display.clearDisplay();
  display.setFont();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("- Weather Station -");

  // Turn all LEDs off every cycle
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);

  if (isnan(temp) || isnan(hum)) {
    display.setCursor(0, 15);
    display.println("Sensor error!");
    display.display();
    delay(2000);
    return;
  }

  const char* label;
  if (temp <= 20) {
    label = "Cold";
    digitalWrite(BLUE_LED, HIGH);
  } else if (temp <= 27) {
    label = "Normal";
    digitalWrite(GREEN_LED, HIGH);
  } else if (temp <= 32) {
    label = "Warm";
    digitalWrite(YELLOW_LED, HIGH);
  } else {
    label = "Hot";
    digitalWrite(RED_LED, HIGH);
  }
  display.setFont(&FreeSans9pt7b);
  display.setCursor(0, 25);
  display.print("Temp: "); display.print(temp, 1); display.print(" C");
  display.setCursor(0, 40);
  display.print("Hum: "); display.print(hum, 0); display.print(" %");
  display.setCursor(0, 55);
  display.print(label);
  display.display();

  delay(2000);
}

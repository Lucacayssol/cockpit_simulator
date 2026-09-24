#include <Joystick.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIN_WS2812B 16
#define NUM_PIXELS 8

Joystick_ Joystick;

int time_appui = 0;
int pressed = false;
int throttle;

const int pin_x = A0;
const int pin_y = A2;
const int pin_throttle = A3;
const int alim_joystick = 14;
const int alim_led = 9;
int xcentre = 0;
int ycentre = 0;
int button0;
int mode = 0; // 0 --> MSFS, 1 --> FS

Adafruit_NeoPixel WS2812B(NUM_PIXELS, PIN_WS2812B, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(alim_led, OUTPUT);
  digitalWrite(alim_led, HIGH);
  WS2812B.begin();
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {           // for each pixel
    WS2812B.setPixelColor(pixel, WS2812B.Color(255, 0, 0));  // it only takes effect if pixels.show() is called
  }
  WS2812B.show();
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {
    WS2812B.setPixelColor(pixel, WS2812B.Color(0, 0, 255));  //Bleu
  }
  delay(1000);
  Serial.begin(9600);
  pinMode(10,INPUT_PULLUP);
  pinMode(pin_x, INPUT);
  pinMode(pin_y, INPUT);
  pinMode(pin_throttle, INPUT);
  //pinMode(pin_flaps, INPUT);
  pinMode(alim_joystick, OUTPUT);
  digitalWrite(alim_joystick, HIGH);
  Joystick.begin();
  Joystick.setXAxisRange(-512, 512);
  Joystick.setYAxisRange(-512, 512);
  //Initialisation
  Serial.println("Initialisation, ne touchez pas au joystick");
  int count = 0;
  xcentre = 0;
  ycentre = 0;
  unsigned long time = millis();
  while (count < 20) {
    xcentre = xcentre + analogRead(pin_x);
    ycentre = ycentre + analogRead(pin_y);
    count = count + 1;
  }
  xcentre = xcentre/count;
  ycentre = ycentre/count;
  Serial.println(xcentre);
  Serial.println(ycentre);
}

void loop() {
  WS2812B.show();
  Joystick.setButton(0,digitalRead(10));
  //Axe X
  int x = analogRead(pin_x);
  int x_mapped = (x - xcentre) * (512/9.5);
  x_mapped = constrain(x_mapped, -512, 512);
  //Axe Y
  int y = analogRead(pin_y);
  int y_mapped = (y - ycentre) * (512/30);
  y_mapped = constrain(y_mapped, -512, 512);
  //Volets
  //int flaps = (analogRead(pin_flaps));
  //Joystick.setZAxis(flaps);
  //Serial.println(flaps);
  //Throttle
  throttle = analogRead(pin_throttle);
  throttle = map(throttle,100,1023,0,1023);
  throttle = constrain(throttle, 0, 1023);

  Joystick.setXAxis(x_mapped);
  //Serial.println(x_mapped);

  Joystick.setYAxis(y_mapped);
  //Serial.println(y_mapped);
  
  if (throttle < 341) {
    Joystick.setButton(1,1);
    Joystick.setButton(2,0);
  }
  else if (throttle > 853) {
    Joystick.setButton(1,0);
    Joystick.setButton(2,1);
  }
  else {
    Joystick.setButton(1,0);
    Joystick.setButton(2,0);
  }
  //Joystick.setThrottle(throttle);
  Serial.println(throttle);

  Joystick.sendState();
  //Serial.println(" ");
  delay(10);
}

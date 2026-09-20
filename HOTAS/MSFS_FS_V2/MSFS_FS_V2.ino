#include <Joystick.h>
#include <ezButton.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIN_WS2812B 16
#define NUM_PIXELS 8

Joystick_ Joystick;

ezButton button(10);
const int SHORT_PRESS_TIME = 1000; // 1000 milliseconds
const int LONG_PRESS_TIME  = 1000; // 1000 milliseconds
unsigned long pressedTime  = 0;
unsigned long releasedTime = 0;
bool isPressing = false;
bool isLongDetected = false;
int time_appui = 0;
int pressed = false;

const int pin_x = A0;
const int pin_y = A2;
const int pin_throttle = A3;
const int alim_joystick = 14;
const int alim_led = 9;
int xcentre = 0;
int ycentre = 0;
int etat_butt1;
int mode = 1; // 0 --> MSFS, 1 --> FS

Adafruit_NeoPixel WS2812B(NUM_PIXELS, PIN_WS2812B, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(alim_led, OUTPUT);
  digitalWrite(alim_led, HIGH);
  WS2812B.begin();
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {           // for each pixel
    WS2812B.setPixelColor(pixel, WS2812B.Color(255, 0, 0));  // it only takes effect if pixels.show() is called
  }
  WS2812B.show();
  delay(1000);
  Serial.begin(9600);
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
  button.setDebounceTime(50);
}

void loop() {
  button.loop();
  WS2812B.show();
  if (pressed == true && time_appui + 100 < millis()) {
    Joystick.setButton(0, 0);
    pressed = false;
  }
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
  int throttle = map(analogRead(pin_throttle),0,700,1023,0);
  throttle = constrain(throttle, 0, 1023);

  if(button.isPressed())
    pressedTime = millis();

  if(button.isReleased()) {
    releasedTime = millis();

    long pressDuration = releasedTime - pressedTime;

    if( pressDuration < SHORT_PRESS_TIME ) {
      Serial.println("A short press is detected");
      Joystick.setButton(0, 1);
      time_appui = millis();
      pressed = true;
    }

    if( pressDuration > LONG_PRESS_TIME ) {
      Serial.println("A long press is detected");
      mode = mode + 1;
    }
  }

  if (mode >= 2) {
    mode = 0;
  }
  else if (mode == 0) {
    for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {           // for each pixel
      WS2812B.setPixelColor(pixel, WS2812B.Color(0, 0, 255));  //Bleu
    }
    Joystick.setThrottle(throttle);
    //Serial.println(throttle);
  }
  else if (mode == 1) {
    for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {
      WS2812B.setPixelColor(pixel, WS2812B.Color(0, 255, 0));  //Vert
    }
    if (x_mapped < 150 && x_mapped > -150 ){
      x_mapped = 0;
    }
    if (y_mapped < 150 && y_mapped > -150 ){
      y_mapped = 0;
    }
  }
  Joystick.setXAxis(x_mapped);
  //Serial.println(x_mapped);

  Joystick.setYAxis(y_mapped);
  //Serial.println(y_mapped);

  Joystick.sendState();
  //Serial.println(" ");
  delay(10);
}

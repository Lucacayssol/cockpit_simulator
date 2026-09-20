 #include <Joystick.h>

// Crée une manette USB avec un axe X
Joystick_ Joystick(
  JOYSTICK_DEFAULT_REPORT_ID,
  JOYSTICK_TYPE_JOYSTICK,
  0,     // boutons
  0,     // hats
  true,  // Axe X
  false, false,
  false, false, false,
  false, false, false, false, false
);

const int potPin = A0;

void setup() {
  pinMode(potPin, INPUT);

  // Valeur de l'axe : 0 à 1023
  Joystick.setXAxisRange(0, 1023);

  Joystick.begin();
}

void loop() {
  int valeur = analogRead(potPin);
  Serial.println(valeur);
  valeur = map(valeur,410,605,0,1023);
  valeur = 1023 - valeur;
  valeur = constrain(valeur,0,1023);
  if (valeur > 462 and valeur < 562) {
    valeur = 512;
  }
  Joystick.setXAxis(valeur);
  Serial.println(valeur);
  Serial.println(" ");
  delay(5);
}

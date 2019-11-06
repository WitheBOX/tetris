/////////////////////////////////////////////////////////////////////////////////////
// Naam: Michiel de Jong, Quinn Hermans                         //
// Klas: 5IW // Project: Tetris //
// devversion: 16*2 lcd 1 dimentie random blokjes L n R //
/////////////////////////////////////////////////////////////////////////////////////

// include the library code:
#include <Arduino.h>
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int xSize = 0;      // momentele waarde van dimentie van een blokje
int tikspeed = 500; // bewegingssnelheid

// lijst van mogelijke soorten blokjesvormen
const bool tetromino1[4] = {1, 0, 0, 0};
const bool tetromino2[4] = {1, 1, 0, 0};
const bool tetromino3[4] = {1, 1, 1, 0};
const bool tetromino4[4] = {1, 1, 1, 1};

bool blokjePositie[16]; // bijhouden waar het blokje zich bevindt
bool tetromino[4];

// nieuw aangemaakte karakter die volledig zwart is
const byte customChar[] = {
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111
};

// kiest willekeurig een blokjesvorm uit
void randomTetromino() {

  for (int i = 0; i < 4; i++) {
    tetromino[i] = false;
  }

  int randNumber = 0;
  randNumber = (int)random(
      1, 5); // random functie: inclusief 1ste argument, exclusief 2de

  Serial.print("Random number: ");
  Serial.println(randNumber);

  switch (randNumber) {
  case 1:
    for (int i = 0; i < 4; i++) {
      if (tetromino1[i] == true) {
        tetromino[i] = true;
      }
    }
    break;

  case 2:
    for (int i = 0; i < 4; i++) {
      if (tetromino2[i] == true) {
        tetromino[i] = true;
      }
    }
    break;

  case 3:
    for (int i = 0; i < 4; i++) {
      if (tetromino3[i] == true) {
        tetromino[i] = true;
      }
    }
    break;

  case 4:
    for (int i = 0; i < 4; i++) {
      if (tetromino4[i] == true) {
        tetromino[i] = true;
      }
    }
    break;
  }
}

// Vult de array die de blokjespositie bijhoud met de beginpositie van een
// tetromino
void vulPositie(bool tetromino[]) {
  for (int i = 0; i < 4; i++) {
    if (tetromino[i] == true) {
      blokjePositie[i] = true;
    }
  }
}

// bepaalt de max dimentie van een tetromino
void bepaalGrootte(bool tetromino[]) {
  for (int i = 0; i < 4; i++) {
    if (tetromino[i] == true) {
      xSize = xSize + 1;
    }
  }
  Serial.print("xSize: ");
  Serial.println(xSize);
}

// tekent het blokje op de lcd
void draw(bool positieBijhouden[]) {
  for (int i = 0; i <= 16; i++) {
    if (positieBijhouden[i] == true) {
      lcd.setCursor(i, 0);
      lcd.write(byte(0));
    } else {
      lcd.setCursor(i, 0);
      lcd.print(" ");
    }
  }
}

void setup() {
  // Zorgt er voor dat de willekeurige getallen niet altijd de zelfde zijn bij
  // opstarten A0 pin mag niet verbonden zijn moet een flaoting point zijn!
  randomSeed(analogRead(A0));
  lcd.begin(16, 2);
  lcd.createChar(0, customChar);
  lcd.home();
  Serial.begin(9600);
}

void loop() {
  xSize = 0;
  randomTetromino();
  bepaalGrootte(tetromino);
  vulPositie(tetromino);
  draw(blokjePositie);

  for (int i = 0; i <= 16; i++) {

    if (blokjePositie[i] == true) {
      blokjePositie[i] = false;
      blokjePositie[i + xSize] = true;
      delay(tikspeed);
      draw(blokjePositie);
    }

    else {
      blokjePositie[i] = false;
    }
  }
}

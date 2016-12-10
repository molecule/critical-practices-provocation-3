const int BUTTON_PIN = 8;

//******** Neopixel ***********//
#include <Adafruit_NeoPixel.h>

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
#define NEOPIXEL_PIN 3
#define NUM_LEDS 14
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

uint32_t green         = strip.Color(0, 255, 25);
uint32_t red           = strip.Color(255, 0, 0);
uint32_t yellowOrange  = strip.Color(255, 173, 0);

uint32_t numberZero     = 0b11110110000000;
uint32_t numberOne      = 0b11000000000000;
uint32_t numberTwo      = 0b01101110000000;
uint32_t numberThree    = 0b11101010000000;
uint32_t numberFour     = 0b11011000000000;
uint32_t numberFive     = 0b10111010000000;
uint32_t numberSix      = 0b10111110000000;
uint32_t numberSeven    = 0b11100000000000;
uint32_t numberEight    = 0b11111110000000;
uint32_t numberNine     = 0b01111100000000;
uint32_t numberTen      = 0b11000001111011;
uint32_t numberTwenty   = 0b00000000110111;
uint32_t numberThirty   = 0b00000001110101;


uint32_t singlesDigitMap[10] = {
  numberZero,
  numberOne,
  numberTwo,
  numberThree,
  numberFour,
  numberFive,
  numberSix,
  numberSeven,
  numberEight,
  numberNine
};

uint32_t tensDigitMap[4] = {
  0,
  numberTen,
  numberTwenty,
  numberThirty
};

void setup() {
  Serial.begin(9600);
  
  pinMode(NEOPIXEL_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  // Neopixel setup
  strip.begin();
}

void loop() {
  for (int i = 0; i < 30; i++) {
    Serial.print("I: ");
    Serial.println(i);
    buildNumber(i);
    delay(100);
  }
  
  
  int buttonPress = digitalRead(BUTTON_PIN);
  if (buttonPress == HIGH) {
    timerCountdown();
  }
}

void timerCountdown() {
  uint32_t color;
  for (int i = 30; i >= 0; i--) {
    color = green;
    if (i < 20 && i >= 16) {
      color = yellowOrange;
    }
    if (i < 16 && i > 6) {
      color = red;
    }
    displayNumber(buildNumber(i), color);
    delay(1000);
  }
  //displayNumber(1, green);
  //delay(1000);
  //displayNumber(numberSix, red);
  //delay(1000);
}

uint32_t buildNumber(int numberToBuild) {
  Serial.print("Number to build: " );
  Serial.println(numberToBuild);
  int tensDigit = numberToBuild/10;
  Serial.print("tens: " );
  Serial.println(tensDigit);
  int singlesDigit = numberToBuild - (tensDigit*10);
   Serial.print("singles: " );
  Serial.println(singlesDigit);

  Serial.print("singlesDigitMap: ");
  Serial.println(singlesDigitMap[singlesDigit], BIN);

  Serial.print("tensDigitMap: ");
  Serial.println(tensDigitMap[tensDigit], BIN);

  uint32_t representationOfNumber;
  if (numberToBuild < 10) {
    representationOfNumber = singlesDigitMap[singlesDigit];
  } else {
    representationOfNumber = singlesDigitMap[singlesDigit] | tensDigitMap[tensDigit];
  }
  Serial.println(representationOfNumber, BIN);

}

// Takes in the number to be displayed, and the color to display.
void displayNumber(int numArray[], uint32_t color) { 

  for (int i = 0; i < NUM_LEDS; i++) {
    // If the value at the index is set to 1, turn that LED on, otherwise turn it off.
    if (numArray[i] == 1) {
      strip.setPixelColor(i, color);
    } else {
      strip.setPixelColor(i, 0);
    }
  }
  strip.show();
}

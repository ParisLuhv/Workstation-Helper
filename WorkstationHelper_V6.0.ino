//Include Smoothing library
  #include <AnalogSmooth.h>
//Include Button library
  #include <Button.h>
//Include Adafruit library
  #include <Adafruit_NeoPixel.h>
  #ifdef __AVR__
  #include <avr/power.h>
  #endif
//
//Start define 
  #define LIGHT_1 13
  #define LIGHT_2 2
  #define POT_1 A0
  #define PEZIO_1 3
  #define BUTT_1 A1
  #define BUTTLIGHT_1 5
  void(* resetFunc) (void) = 0;
//End definitions
//
//Set each LIGHT to its corresponding pin. (,variable, name, pin#);
  const int light_1 = 13;
  const int light_2 = 2;
//Set each POTENTIOMETER to its corresponding pin. (,variable, name, pin#);
  const int pot_1 = A0; 
// define where the piezoelectric  SPEAKER is connected
  const int piezo_1 = 3; 
//
// define where the BUTTON is connected
  const int butt_1 = A1; 
  const int buttLight_1 = 5;
//
  AnalogSmooth knobSmooth = AnalogSmooth(100);
//
  Button button1(butt_1);
//neopixel constructor
  Adafruit_NeoPixel strip_1 = Adafruit_NeoPixel(8, LIGHT_1, NEO_GRB + NEO_KHZ800);
  Adafruit_NeoPixel strip_2 = Adafruit_NeoPixel(5, LIGHT_2, NEO_GRB + NEO_KHZ800);
//
//VARIABLES
  int currentKnobValue;
  int previousKnobValue;
  int currentButtValue;
  int previousButtValue;
  int brightnessPercentage;
  float knobValue;
  float knobSmoothValue;
 //
//COLOR ANIMATION FUNTIONS
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip_2.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip_2.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip_2.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
//LIGHT 1 ANIMATION
//simple animation to Fill the dots one after the other with a color
//this allowes us to set 1 color to all dots at once, persistently.
  void colorWipe1(uint32_t c, uint8_t wait) {
    for(uint16_t i=0; i<strip_1.numPixels(); i++) {
      strip_1.setPixelColor(i, c);
      strip_1.show();
      delay(wait);
    }
  }
//LIGHT 2 ANIMATION
// Fill the dots one after the other with a color
void colorWipe2(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip_2.numPixels(); i++) {
    strip_2.setPixelColor(i, c);
    strip_2.show();
    delay(wait);
  }
}
//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip_2.numPixels(); i=i+3) {
        strip_2.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip_2.show();

      delay(wait);

      for (uint16_t i=0; i < strip_2.numPixels(); i=i+3) {
        strip_2.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}
//END OF PRE PROGRAM
//SETUP CLASS.
void setup() { 
//Initialize serial connection on port 9600;
  while (!Serial) {};
    Serial.begin(9600);
//
//
  Serial.println("Lighting System Software V1.0. Created by Paris Luhv");
  delay(1000);
    Serial.println("Starting program in:");
    Serial.println("5"); delay(1000);
    Serial.println("4"); delay(1000);
    Serial.println("3"); delay(1000);
    Serial.println("2"); delay(1000);
    Serial.println("1"); delay(1000);
    Serial.println("0");
    currentKnobValue = knobSmoothValue;
    currentKnobValue = map(currentKnobValue, 0, 1023, 0, 250);
    pinMode (BUTTLIGHT_1, OUTPUT);
    digitalWrite (buttLight_1, HIGH);
    Serial.println("STARTED!");
    Serial.println("**********");
//
//Initialize on-board Speaker
   Serial.println("Initializing Speaker");
  pinMode (piezo_1, OUTPUT);
  digitalWrite(piezo_1, HIGH);
  delayMicroseconds(1000);
  digitalWrite(piezo_1, LOW);
  delayMicroseconds(1000);
  Serial.println("Speaker Initialized");
//
//
//Initialize System Button
  Serial.println("Initializing System Button");
  button1.begin();
  delay(1000);
  Serial.println("Webcam knob successfuly initialized.");
//Initialize webcam knob
  Serial.println("Initializing Webcam Knob");
  currentKnobValue = analogRead(POT_1);
  //currentKnobValue = map(currentKnobValue, 0, 1024, 0, 250);
  Serial.print("current RAW knob value is ");
  Serial.println(currentKnobValue);
  delay(1000);
  Serial.println("Webcam knob successfuly initialized.");
//
//Initialize Cam light (light_1.
   Serial.println("Initializing Webcam lights.");
   strip_1.begin(); //Initialize Light 1
   colorWipe1(strip_1.Color(200, 50, 50), 500); //Set light color to RED
   strip_1.show(); //Show changes on light
  digitalWrite(piezo_1, HIGH);
  delayMicroseconds(1000);
  digitalWrite(piezo_1, LOW);
  digitalWrite(piezo_1, HIGH);
  delay(1000);
   colorWipe1(strip_1.Color(50, 50, 200), 500); //Set light color to BLUE
   strip_1.show(); //Show changes on light
  digitalWrite(piezo_1, HIGH);
  delayMicroseconds(1000);
  digitalWrite(piezo_1, LOW);
  digitalWrite(piezo_1, HIGH);
   colorWipe1(strip_1.Color(50, 200, 50), 500); //Set light color to GREEN
   strip_1.show(); //Show changes on light
  digitalWrite(piezo_1, HIGH);
  delayMicroseconds(1000);
  digitalWrite(piezo_1, LOW);
  digitalWrite(piezo_1, HIGH);
  Serial.println("Webcam light successfuly initialized.");
  delay(1000);
//
//Initialize Ambient Light (light_2.
   Serial.println("Initializing Ambient lights.");
   strip_2.begin(); //Initialize Light 2
   theaterChase(strip_2.Color(  0,   0, 100), 50); // Blue
   strip_2.show(); //Show changes on light
   delay(1000);
//
//
  Serial.println("SUCCESS.");
  Serial.println("System is currently 100% functional");
} //END OF SETUP CLASS.
//
//
//
//LOOP CLASS.
 void loop() { 
//Knob smoothing
  float knobValue = analogRead(POT_1);
  float knobSmoothValue = knobSmooth.smooth(knobValue);
//
//previousButtValue = currentButtValue;
   colorWipe2(strip_2.Color(  0,   0, 250), 0); // Blue
   strip_2.setBrightness(currentKnobValue);
   strip_2.show(); //Show changes on light
//WEBCAM LIGHT
//Set light brightness
  currentKnobValue = knobSmoothValue;
  currentKnobValue = map(currentKnobValue, 1024, 0, 0, 250);
  colorWipe1(strip_1.Color(currentKnobValue, currentKnobValue, currentKnobValue), 0); 
  strip_1.show(); //show changes on light
//calculate current brightness percentage
  brightnessPercentage = map(currentKnobValue, 0, 249, 0, 100);
  if (currentKnobValue != previousKnobValue) {
    Serial.print(brightnessPercentage);
    Serial.print("% ");
    Serial.println("Brightness");
    //SPEAKER
  digitalWrite( piezo_1, HIGH);
  delayMicroseconds(1432);
  digitalWrite( piezo_1, LOW);
  delayMicroseconds(1276);
  digitalWrite( piezo_1, HIGH);
  delayMicroseconds(1012);
  }
  previousKnobValue = currentKnobValue;
//
// BUTTON1
  digitalWrite (buttLight_1, LOW);
  currentButtValue = (button1.read());
  if (button1.toggled()) {
  if (button1.read() == Button::PRESSED) {
        //SPEAKER
  digitalWrite( piezo_1, HIGH);
  delayMicroseconds(1432);
  digitalWrite( piezo_1, LOW);
  delayMicroseconds(1276);
  digitalWrite( piezo_1, HIGH);
  delayMicroseconds(1012);
  digitalWrite (buttLight_1, LOW);
    Serial.println("Button 1 pressed");
    Serial.println("SYSTEM RESTARTING");
    delay(5000);
    Serial.println("GOODBYE"); 
    resetFunc();
  } 
  else
      Serial.println("Button 1 has been released");
      digitalWrite (buttLight_1, HIGH);
  }

}

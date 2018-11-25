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
//simple animation to Fill the dots one after the other with a color
//this allowes us to set 1 color to all dots at once, persistently.
  void colorWipe2(uint32_t c, uint8_t wait) {
    for(uint16_t i=0; i<strip_2.numPixels(); i++) {
      strip_2.setPixelColor(i, c);
      strip_2.show();
      delay(wait);
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
   colorWipe1(strip_1.Color(200, 50, 50), 1000); //Set light color to RED
   strip_1.show(); //Show changes on light
  digitalWrite(piezo_1, HIGH);
  delayMicroseconds(1000);
  digitalWrite(piezo_1, LOW);
  delayMicroseconds(1000);
  digitalWrite(piezo_1, HIGH);
  delay(1000);
   colorWipe1(strip_1.Color(50, 50, 200), 1000); //Set light color to BLUE
   strip_1.show(); //Show changes on light
  digitalWrite(piezo_1, HIGH);
  delayMicroseconds(1000);
  digitalWrite(piezo_1, LOW);
  delayMicroseconds(1000);
  digitalWrite(piezo_1, HIGH);
  delay(1000);
   colorWipe1(strip_1.Color(50, 200, 50), 1000); //Set light color to GREEN
   strip_1.show(); //Show changes on light
  digitalWrite(piezo_1, HIGH);
  delayMicroseconds(1000);
  digitalWrite(piezo_1, LOW);
  delayMicroseconds(1000);
  digitalWrite(piezo_1, HIGH);
  delay(1000);
  Serial.println("Webcam light successfuly initialized.");
  delay(1000);
//
//Initialize Ambient Light (light_2.
   Serial.println("Initializing Webcam lights.");
   strip_2.begin(); //Initialize Light 2
   colorWipe2(strip_2.Color(50, 50, 200), 1000); //Set light color to RED
   strip_2.show(); //Show changes on light
  digitalWrite(piezo_1, HIGH);
  delayMicroseconds(1000);
  digitalWrite(piezo_1, LOW);
  delayMicroseconds(1000);
  digitalWrite(piezo_1, HIGH);
  delay(1000);
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
//WEBCAM LIGHT
//Set light brightness
  currentKnobValue = knobSmoothValue;
  currentKnobValue = map(currentKnobValue, 1023, 0, 0, 250);
  colorWipe1(strip_1.Color(currentKnobValue, currentKnobValue, currentKnobValue), 0); 
  strip_1.show(); //show changes on light
//calculate current brightness percentage
  brightnessPercentage = map(currentKnobValue, 0, 250, 0, 100);
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
  digitalWrite (buttLight_1, HIGH);
    Serial.println("Button 1 pressed");
    Serial.println("SYSTEM RESTARTING");
    //delay(5000);
    Serial.println("GOODBYE"); 
    //resetFunc();
  } 
  else
      Serial.println("Button 1 has been released");
      digitalWrite (buttLight_1, LOW);
  }
 //previousButtValue = currentButtValue;

}

//Include Smoothing library
  #include <AnalogSmooth.h>
//Include Adafruit library
  #include <Adafruit_NeoPixel.h>
  #ifdef __AVR__
  #include <avr/power.h>
  #endif
//
//Start define 
  #define LIGHT_1 13
  #define POT_1 A0
//End definitions
//
//Set each LIGHT to its corresponding pin. (,variable, name, pin#);
  const int light_1 = 13;
//Set each POTENTIOMETER to its corresponding pin. (,variable, name, pin#);
  const int pot_1 = A0; 
//
  AnalogSmooth knobSmooth = AnalogSmooth(100);
//neopixel constructor
  Adafruit_NeoPixel strip_1 = Adafruit_NeoPixel(8, LIGHT_1, NEO_GRB + NEO_KHZ800);
//
//VARIABLES
  int currentKnobValue;
  int previousKnobValue;
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
    Serial.println("5"); delay(100);
    Serial.println("4"); delay(100);
    Serial.println("3"); delay(10);
    Serial.println("2"); delay(100);
    Serial.println("1"); delay(100);
    Serial.println("0");
    Serial.println("STARTED!");
    Serial.println("**********");
//
//Initialize webcam knob (knob_1_
   Serial.println("Initializing Webcam Knob");
   currentKnobValue = analogRead(POT_1);
   currentKnobValue = map(currentKnobValue, 0, 1024, 0, 250);
   Serial.print("current knob value is ");
   Serial.println(currentKnobValue);
  delay(100);
   Serial.println("Webcam knob successfuly initialized.");
//
//Initialize Cam light (light_1.
   Serial.println("Initializing Webcam lights.");
   strip_1.begin(); //Initialize Light 1
   colorWipe1(strip_1.Color(200, 50, 50), 60); //Set light color to RED
   strip_1.show(); //Show changes on light
  delay(100);
   colorWipe1(strip_1.Color(50, 50, 200), 60); //Set light color to BLUE
   strip_1.show(); //Show changes on light
  delay(100);
   colorWipe1(strip_1.Color(50, 200, 50), 60); //Set light color to GREEN
   strip_1.show(); //Show changes on light
  delay(100);
  Serial.println("Webcam light successfuly initialized.");
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
//WEBCAM LIGHT
//Set light brightness
  currentKnobValue = knobSmoothValue;
  currentKnobValue = map(currentKnobValue, 0, 1023, 0, 250);
  colorWipe1(strip_1.Color(currentKnobValue, currentKnobValue, currentKnobValue), 0); 
  strip_1.show(); //show changes on light
//calculate current brightness percentage
  brightnessPercentage = map(currentKnobValue, 0, 250, 0, 100);
  if (currentKnobValue != previousKnobValue) {
    Serial.print(brightnessPercentage);
    Serial.print("% ");
    Serial.println("Brightness");
  }
  previousKnobValue = currentKnobValue;
}   

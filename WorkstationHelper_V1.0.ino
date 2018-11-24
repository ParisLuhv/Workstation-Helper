//Include Adafruit library
  #include <Adafruit_NeoPixel.h>
  #ifdef __AVR__
  #include <avr/power.h>
  #endif
//
//Start define 
    #define LIGHT_1 13
//End definitions
//
//Set each light to its corresponding pin. (,variable, name, pin#);
    const int light1 = 13;
//
//neopixel constructor
  Adafruit_NeoPixel strip_1 = Adafruit_NeoPixel(8, LIGHT_1, NEO_GRB + NEO_KHZ800);
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
//
//END OF PRE PROGRAM
//
//BEGGENING OF PROGRAM
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
    Serial.println("STARTED!");
//
//Initialize each light.
   Serial.println("Initializing lights.");
//Initialize Light 1
    strip_1.begin();
//Set light color to white
    colorWipe1(strip_1.Color(100, 250, 250), 0); //white
//Show changes on light
    strip_1.show();
} //END OF SETUP CLASS.
//
//
//
//LOOP CLASS.
 void loop() { 
//LIGHT ONE 
//Set light color to white
    colorWipe1(strip_1.Color(100, 100, 100), 0); //white
//Show changes on light
    strip_1.show();
}   

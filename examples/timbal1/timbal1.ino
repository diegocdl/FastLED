#include <FastLED.h>


#define LED_PIN     11
#define MIC_PIN     A0
#define NUM_LEDS    65
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
uint8_t COLOR       = 100;
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100
int averageSound;
void setup() {
   delay( 3000 ); // power-up safety delay
   FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
   FastLED.setBrightness(  BRIGHTNESS );
   averageSound = analogRead(MIC_PIN);

   for(int i = 0; i < 300; i++){
     averageSound += analogRead(MIC_PIN);
   }
   averageSound /= 300;
   Serial.begin(9600);
   Serial.print("Sonido promedio ");
   Serial.println(averageSound);
}

void loop(){
  Serial.print("Average sound: ");
  Serial.print(averageSound);
  int mic = analogRead(MIC_PIN);
  Serial.print("  Microphone: ");
  Serial.println(mic);
  //static uint8_t COLOR = 100;

  if(mic > 650) {
    COLOR = (COLOR + 128)%255;
  }

  for(int i = 0; i < NUM_LEDS/2; i++) {
    leds[i] = CHSV(COLOR, 255, 255);
  }
  for(int i = NUM_LEDS/2; i < NUM_LEDS; i++) {
    leds[i] = CHSV((COLOR + 128)%255, 255, 255);
  }

  FastLED.show();
  delay(100);
}

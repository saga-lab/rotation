#include <Gaussian.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN        6
#define NUMPIXELS 144 //24 //60+24+144

Gaussian G[3];

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 20

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  for(int k=0;k<3; k++){
    G[k] = Gaussian(60, 5);
  }
    
  pixels.begin();
}

void loop() {
  static int j=0;
  int k;

  pixels.clear();
  for(k=0;k<3; k++){
    //G[k].setVariance(int(NUMPIXELS/3));
  }
  if(j<=NUMPIXELS){j++;}else{j=0;};
  if(j<=NUMPIXELS){
    for(k=0;k<3; k++){
      G[k].setMean(j+int(NUMPIXELS/10)*k);
      G[k].setVariance(j+int(NUMPIXELS/3)*k);
    }
  }
  for(int i=0; i<NUMPIXELS; i++) {
    if(G[2].plot(i)<0.001){
      pixels.setPixelColor(i, pixels.Color(255*G[0].plot(i+NUMPIXELS),255*G[1].plot(i+NUMPIXELS),255*G[2].plot(i+NUMPIXELS)));
    }else{
      pixels.setPixelColor(i, pixels.Color(255*G[0].plot(i),255*G[1].plot(i),255*G[2].plot(i)));
    }
  }
  pixels.show();
  //delay(DELAYVAL);
}

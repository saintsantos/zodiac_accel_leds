#include <Adafruit_CircuitPlayground.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <SPI.h>

#define greenScale 0
#define redScale 10
#define blueScale 12.75

#define brightness_white 200
#define delay_white 150

#define brightness_color 200
#define delay_color 150

/*
 * Number of times the leds pulse
 */
#define pulse_number 2
#define offset 0.50

uint8_t pixeln = 0;

float x_prev = 0;
float y_prev = 0;
float z_prev = 0;


/*
 * These arrays store the color values that are to be randomly
 * assigned to the LEDs. This allows for them all to be indexeds individually,
 * and lit with a different color.
 */
int red[10];
int green[10];
int blue[10];

/*
 * This is the function to make an individual LED in a string of LEDs
 * twinkle. The color is set to a dim white color.
 */
void twinkle_twinkle( ){
  int q = 0;
  int led_to_light_1 = random(0, 10);
  //Serial.println(led_to_light);
  for(int i =0; i < brightness_white; i++) {
    CircuitPlayground.setBrightness(i);
    CircuitPlayground.setPixelColor(led_to_light_1, 10, 10, 10);
    delayMicroseconds(delay_white);
  }

  for(int i = brightness_white; i > -1; i--) {
    CircuitPlayground.setBrightness(i);
    CircuitPlayground.setPixelColor(led_to_light_1, 10, 10, 10);
    delayMicroseconds(delay_white);
  }
}


/*
 * This function will pulse each LED a different color with a breathing effect.
 */
void pulse() {
  int q = 0;
  for (; q <pulse_number; q++) {
    int r = 0;
  for(; r < 10; r++) {
    red[r] = random(0, 20);
    green[r] = random(0, 20);
    blue[r] = random(0, 20);
  }

  /*
   * Increase brightness to the value defined by brightness_color
   */
  for (int j=0; j<brightness_color; j++) {
    CircuitPlayground.setBrightness(j);
    for(int i=0; i<10;i++) {
      CircuitPlayground.setPixelColor(i, red[i], green[i], blue[i]);
      //CircuitPlayground.setPixelColor(i + 1, red[i], green[i], blue[i]);  
      }
      delayMicroseconds(delay_color);
    }

    /*
     * Decrease brightness to zero
     */
    for (int j=brightness_color; j>0; j--) {
     CircuitPlayground.setBrightness(j);
     for(int i=0; i<10;i++) {
      CircuitPlayground.setPixelColor(i, red[i], green[i], blue[i]);  
      }
      delayMicroseconds(delay_color);
    }
  }
}


void setup() {

  /*
   * Initialize Serial, CircuitPlayground, and accelerometer
   */
  Serial.begin(9600);
  CircuitPlayground.begin();
  CircuitPlayground.setAccelRange(LIS3DH_RANGE_2_G);   // 2, 4, 8 or 16 G!
  

}

void loop() {
  CircuitPlayground.clearPixels();
  float x = CircuitPlayground.motionX();
  float y = CircuitPlayground.motionY();
  float z = CircuitPlayground.motionZ();
  
  CircuitPlayground.setBrightness(0);

  if( (((x - x_prev) <= offset) && ((y - y_prev) <=offset) && ((z - z_prev) <=offset))) {
    twinkle_twinkle();
  } else {
    pulse();
  }
  
  x_prev = x;
  y_prev = y;
  z_prev = z;
  
  
  delay(5);
}

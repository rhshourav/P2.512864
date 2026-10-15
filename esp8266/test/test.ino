#define PxMATRIX_COLOR_DEPTH 4 // Low color depth saves ESP8266 RAM
#include <PxMatrix.h>

// Define ESP8266 to HUB75 Pins
#define P_LAT 15 // D8
#define P_A 16   // D0
#define P_B 5    // D1
#define P_C 4    // D2
#define P_D 0    // D3
#define P_E -1   // Not used, tied to GND physically
#define P_OE 3   // RX pin

// Define display size (Test mode trick: 128x32 pseudo-driving)
PxMATRIX display(128, 32, P_LAT, P_OE, P_A, P_B, P_C, P_D);

// Flash timer for the ESP8266 screen refresh
#include <Ticker.h>
Ticker display_ticker;
void display_updater() {
  display.display(20); // Refresh rate factor
}

void setup() {
  // Initialize display geometry and multiplex pattern
  display.begin(16); // 1/16 scan rate
  
  // Start the background refresh interrupt
  display_ticker.attach_slot(0.002, display_updater); 
  
  display.clearDisplay();
}

void loop() {
  // Color definitions (565 Format)
  uint16_t red = display.color565(255, 0, 0);
  uint16_t green = display.color565(0, 255, 0);
  uint16_t blue = display.color565(0, 0, 255);
  uint16_t white = display.color565(255, 255, 255);

  display.clearDisplay();

  // Test 1: Light up the 4 corners of the top half matrix
  display.drawPixel(0, 0, red);        // Top-Left
  display.drawPixel(127, 0, green);    // Top-Right
  display.drawPixel(0, 31, blue);      // Bottom-Left (of top half)
  display.drawPixel(127, 31, white);   // Bottom-Right (of top half)

  // Test 2: Draw a simple test shape in the center
  display.drawRect(44, 8, 40, 16, white);
  
  delay(5000); 
}

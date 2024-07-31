#include <Adafruit_MAX31865.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define Read_time 100

// Define pins for MAX31865 PT100 sensor
#define CS_PIN 5
#define DI_PIN 23
#define DO_PIN 19
#define CLK_PIN 18

// Define the Rref resistor for the PT100 sensor
#define RREF 430.0

// Define pins and constants for pressure sensor
#define Crnt_Sensor 34
#define MAX_BAR 16.0  // Maximum pressure in bar (for 4-20 mA)
#define Min_Crnt 4.0  // Min Current of 4-20mA
#define Max_Crnt 20.0 // Max Current of 4-20mA
#define Max_Volt 3.3  // Maximum volts reading in the MCU (change to 5 for 5V ADC)

// Define pins and constants for flow meter sensor
#define Crnt_Flow_Sensor 35
#define MAX_FLOW_RATE 100.0  // Maximum flow rate (units depend on your flow meter)
#define Min_Flow_Crnt 4.0    // Min Current of 4-20mA
#define Max_Flow_Crnt 20.0   // Max Current of 4-20mA

// OLED display parameters
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1  // Reset pin # (or -1 if sharing Arduino reset pin)

// Initialize the MAX31865 PT100 sensor with software SPI
Adafruit_MAX31865 max31865 = Adafruit_MAX31865(CS_PIN, DI_PIN, DO_PIN, CLK_PIN);
// Initialize the OLED display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);  // Initialize serial communication
  max31865.begin(MAX31865_3WIRE);  // Set to 3WIRE for 3-wire PT100
  analogReadResolution(12);  // Set the ADC resolution to 12 bits

  // Initialize the OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);  // Don't proceed, loop forever
  }
  display.display();  // Show initial display buffer contents on the screen
  delay(2000);  // Pause for 2 seconds

  display.clearDisplay();  // Clear the buffer
  display.setTextSize(1);  // Set text size to 1
  display.setTextColor(SSD1306_WHITE);  // Set text color to white
}

void loop() {
  // Read sensor data
  float temperature = readPT100Sensor();
  float pressure = readPressureSensor();
  float flowRate = readFlowSensor();

  // Print data in CSV format
  Serial.print(temperature);        Serial.print(",");
  Serial.print(pressure);           Serial.print(",");
  Serial.print(flowRate);           Serial.println();

  // Display sensor values on the OLED
  display.clearDisplay();

  display.setCursor(0, 0);  // Start at top-left corner
  display.print("Temperature: "); display.print(temperature); display.println(" C");
  display.print("Pressure: "); display.print(pressure); display.println(" bar");
  display.print("Flow Rate: "); display.print(flowRate); display.println(" units");

  display.display();  // Update the display with new data

  delay(Read_time);  // Do reading every (Read_time)
}

float readPT100Sensor() {
  uint16_t rtd = max31865.readRTD();
  float ratio = rtd;
  ratio /= 32768;
  float resistance = RREF * ratio;
  return max31865.temperature(100, RREF);
}

float readPressureSensor() {
  int RawVolt = analogRead(Crnt_Sensor);  // Read the raw ADC value
  float Volt = (RawVolt / 4095.0) * Max_Volt;  // Convert ADC value to voltage
  float Crnt = ((Volt / Max_Volt) * (Max_Crnt - Min_Crnt)) + Min_Crnt;  // Convert voltage to current in mA
  return (Crnt - Min_Crnt) * (MAX_BAR / (Max_Crnt - Min_Crnt));  // Convert current to pressure
}

float readFlowSensor() {
  int RawVolt = analogRead(Crnt_Flow_Sensor);  // Read the raw ADC value
  float Volt = (RawVolt / 4095.0) * Max_Volt;  // Convert ADC value to voltage
  float Crnt = ((Volt / Max_Volt) * (Max_Flow_Crnt - Min_Flow_Crnt)) + Min_Flow_Crnt;  // Convert voltage to current in mA
  return (Crnt - Min_Flow_Crnt) * (MAX_FLOW_RATE / (Max_Flow_Crnt - Min_Flow_Crnt));  // Convert current to flow rate
}

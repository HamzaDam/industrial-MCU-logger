ESP32 Sensor Data Logger
This project demonstrates how to use an ESP32 microcontroller to read data from multiple sensors and send the data to a Python script for logging and analysis. The system is designed to handle three types of sensors:

  1- PT100 Temperature Sensor - Measures temperature using the Adafruit MAX31865 sensor.
  2- Pressure Sensor (4-20 mA) - Measures pressure and converts current signals to pressure readings.
  3- Flow Meter (4-20 mA) - Measures flow rate and converts current signals to flow readings.

Features
  *ESP32 Microcontroller: Reads sensor data and formats it for serial transmission.
  *Temperature Measurement: Utilizes the MAX31865 module to read PT100 sensor data and calculate temperature.
  *Pressure Measurement: Converts 4-20 mA current signals to pressure values in bars.
  *Flow Measurement: Converts 4-20 mA current signals to flow rates.
  *Python Data Logging: A Python script receives the sensor data via serial communication, parses it, and logs it into an Excel spreadsheet with timestamps.

Components
  1-ESP32 microcontroller
  2-Adafruit MAX31865 PT100 sensor interface
  3-Pressure sensor (4-20 mA)
  4-Flow meter (4-20 mA)
  5-Excel file for data storage

Setup
Hardware: Connect the PT100 sensor, pressure sensor, and flow meter to the ESP32 according to the pin definitions in the code.
ESP32 Code: Upload the provided Arduino code to the ESP32 to handle sensor readings and send data over serial.
Python Script: Run the provided Python script to read data from the ESP32 and save it to an Excel file.

Usage
Modify the pin definitions and sensor parameters as needed to match your hardware setup.
Ensure that the COM port and baud rate in the Python script match those used by the ESP32.
Check the Excel file to view logged data with timestamps.

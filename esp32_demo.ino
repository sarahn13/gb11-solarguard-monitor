/* GB11 SolarGuard ESP32 starter firmware
 * IMPORTANT: This is a starter for bench testing, not a safety-certified controller.
 * Confirm sensor modules, pinout, ADC scaling, battery chemistry and isolation first.
 * Never connect a battery directly to an ESP32 ADC. Use a correctly designed divider
 * or compatible sensor module, common reference only where the sensor design permits,
 * fusing and suitable protection. This sketch prints JSON-like readings to Serial;
 * it does not yet connect to the web dashboard or actuate a real load.
 */
#include <Arduino.h>

// Example analog inputs ONLY; adapt to your actual board and sensor interfaces.
const int BATTERY_VOLTAGE_PIN = 34;
const int BATTERY_CURRENT_PIN = 35;
const int TEMP_PIN = 32;
const int LAMP_BRANCH_CURRENT_PIN = 33;

// CALIBRATE these values against reference instruments before use.
const float ADC_REF_V = 3.3f;
const float ADC_MAX = 4095.0f;
const float VOLTAGE_DIVIDER_RATIO = 5.0f; // Example only; calculate for your circuit.
const float CURRENT_ZERO_V = 1.65f;       // Example for a compatible analog sensor.
const float CURRENT_A_PER_V = 10.0f;      // Example only; set to sensor datasheet value.
const float TEMP_C_PER_V = 100.0f;        // Placeholder; replace with sensor-specific conversion.
const float LAMP_ZERO_V = 1.65f;
const float LAMP_A_PER_V = 10.0f;

float readPinVoltage(int pin) {
  // Average samples to reduce noise; calibration and filtering still required.
  uint32_t total = 0;
  for (int i = 0; i < 16; i++) { total += analogRead(pin); delay(2); }
  float raw = total / 16.0f;
  return raw * ADC_REF_V / ADC_MAX;
}
float readCurrentA(int pin, float zeroV, float ampPerV) {
  return (readPinVoltage(pin) - zeroV) * ampPerV;
}

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  Serial.println("GB11 SolarGuard ESP32 starter - calibrate before use");
}
void loop() {
  float batteryV = readPinVoltage(BATTERY_VOLTAGE_PIN) * VOLTAGE_DIVIDER_RATIO;
  float batteryA = readCurrentA(BATTERY_CURRENT_PIN, CURRENT_ZERO_V, CURRENT_A_PER_V);
  float temperatureC = readPinVoltage(TEMP_PIN) * TEMP_C_PER_V; // Replace conversion.
  float lampBranchA = readCurrentA(LAMP_BRANCH_CURRENT_PIN, LAMP_ZERO_V, LAMP_A_PER_V);

  // JSON line for serial logging. These are raw prototype estimates, not calibrated results.
  Serial.printf("{\"battery_voltage_V\":%.3f,\"battery_current_A\":%.3f,\"temperature_C\":%.2f,\"lamp_branch_current_A\":%.4f}\n",
                batteryV, batteryA, temperatureC, lampBranchA);
  delay(2000);
}

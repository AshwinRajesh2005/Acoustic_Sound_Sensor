#define SENSOR_PIN A0

void setup() {
    Serial.begin(9600);
    pinMode(SENSOR_PIN, INPUT);
    Serial.println("=== Initialized ===");
}

void loop() {
    int sensorValue = analogRead(SENSOR_PIN);
    float voltage = sensorValue * (5.0 / 1023.0); // Convert analog value to voltage
    float ppm = map(voltage, 0.4, 2.0, 300, 10000); // Map voltage to CO2 concentration range

    Serial.print("CO2 concentration: ");
    Serial.print(ppm);
    Serial.println(" ppm.");

    delay(1000);
}

#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

unsigned long previousTime = 0;
float velocityX = 0;
float velocityY = 0;
float velocityZ = 0;
float alpha = 0.98; // Complementary filter constant

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed");
    while (1);
  }
}

void loop() {
  unsigned long currentTime = millis();
  float deltaTime = (currentTime - previousTime) / 1000.0; // Convert to seconds
  previousTime = currentTime;

  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  // Convert raw values to 'g'
  float accelX = ax / 16384.0;
  float accelY = ay / 16384.0;
  float accelZ = az / 16384.0;

  // Integrate acceleration to get velocity
  velocityX = alpha * (velocityX + accelX * deltaTime);
  velocityY = alpha * (velocityY + accelY * deltaTime);
  velocityZ = alpha * (velocityZ + accelZ * deltaTime);

  Serial.print("Velocity X: "); Serial.print(velocityX); Serial.print(" m/s, ");
  Serial.print("Velocity Y: "); Serial.print(velocityY); Serial.print(" m/s, ");
  Serial.print("Velocity Z: "); Serial.println(velocityZ); Serial.print(" m/s");

  delay(100); // Adjust delay as needed
}

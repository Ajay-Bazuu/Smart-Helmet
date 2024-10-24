#include <Wire.h>
#include <MadgwickAHRS.h>
#include <MPU6050.h>

Madgwick filter;
MPU6050 mpu;


// Variables to store the initial roll and pitch
float initialRoll = 0;
float initialPitch = 0;

void setup() {
  Serial.begin(115200);  // Initialize Serial communication
  Wire.begin();
  mpu.initialize();
  filter.begin(100);  // Filter update rate in Hz
  Serial.println("MPU6050 Mouse Control Ready");

  // Wait for the sensor to stabilize
  delay(1000);

  // Variables to accumulate multiple readings
  float totalRoll = 0;
  float totalPitch = 0;
  const int numReadings = 10;  // Number of readings to average

  for (int i = 0; i < numReadings; i++) {
    int16_t ax, ay, az, gx, gy, gz;
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    float gyroX = gx / 131.0;
    float gyroY = gy / 131.0;
    float gyroZ = gz / 131.0;
    float accelX = ax / 16384.0;
    float accelY = ay / 16384.0;
    float accelZ = az / 16384.0;

    filter.updateIMU(gyroX, gyroY, gyroZ, accelX, accelY, accelZ);

    // Accumulate roll and pitch values
    totalRoll += filter.getRoll();
    totalPitch += filter.getPitch();

    // Delay between readings (optional, to allow for stabilization)
    delay(100);
  }

  // Calculate the average roll and pitch
  initialRoll = totalRoll / numReadings;
  initialPitch = totalPitch / numReadings;
  Serial.println(initialRoll);
  Serial.println(initialPitch);
  delay(2000);

  Serial.println("Initial roll and pitch set based on average of readings.");
}

void loop() {
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Convert raw values to degrees/s and g's
  float gyroX = gx / 131.0;
  float gyroY = gy / 131.0;
  float gyroZ = gz / 131.0;
  float accelX = ax / 16384.0;
  float accelY = ay / 16384.0;
  float accelZ = az / 16384.0;

  // Update the Madgwick filter with gyroscope and accelerometer data
  filter.updateIMU(gyroX, gyroY, gyroZ, accelX, accelY, accelZ);

  // Get orientation angles (in radians)
  float roll = filter.getRoll();
  float pitch = filter.getPitch();

  // Subtract the initial roll and pitch to make the current position relative to the start
  float relativePitch=0;
  float relativeRoll=0;
  if (pitch>0){
    relativePitch = (pitch - abs(initialPitch))*10; //*10 for making it more sensitive
  }else{
    relativePitch = (pitch - initialPitch)*10;
  }
    if (roll>0){
    relativeRoll = (roll - abs(initialRoll))*10;
  }else{
    relativeRoll = (roll - initialRoll)*10;
  }
    Serial.print("IniPitch: ");  // Print X movement data
    Serial.print(initialPitch);
    Serial.print(", IniRoll: ");  // Print Y movement data
    Serial.println(initialRoll);
    Serial.print("Pitch: ");  // Print X movement data
    Serial.print(relativePitch);
    Serial.print(", Roll: ");  // Print Y movement data
    Serial.println(relativeRoll);
    Serial.println();
  
  delay(110);  // Adjust delay as needed
}

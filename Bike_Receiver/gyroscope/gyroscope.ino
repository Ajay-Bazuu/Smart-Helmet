#include <Wire.h>
#include <MadgwickAHRS.h>
#include <MPU6050.h>

Madgwick filter;
MPU6050 mpu;

// Calibration offsets obtained from your previous readings
const int16_t accelXOffset = -3;  // XAccel offset
const int16_t accelYOffset = -15;   // YAccel offset
const int16_t accelZOffset = 16380; // ZAccel offset (adjust if necessary)
const int16_t gyroXOffset = 0;     // XGyro offset
const int16_t gyroYOffset = -1;     // YGyro offset
const int16_t gyroZOffset = -1;     // ZGyro offset

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

        // Apply calibration offsets
        float gyroX = (gx - gyroXOffset) / 131.0;
        float gyroY = (gy - gyroYOffset) / 131.0;
        float gyroZ = (gz - gyroZOffset) / 131.0;
        float accelX = (ax - accelXOffset) / 16384.0;
        float accelY = (ay - accelYOffset) / 16384.0;
        float accelZ = (az - accelZOffset) / 16384.0;

        // Update the Madgwick filter with calibrated values
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

    Serial.print("Initial Roll: ");
    Serial.println(initialRoll);
    Serial.print("Initial Pitch: ");
    Serial.println(initialPitch);
    delay(2000);
    Serial.println("Initial roll and pitch set based on average of readings.");
}

void loop() {
    int16_t ax, ay, az, gx, gy, gz;
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    // Apply calibration offsets
    float gyroX = (gx - gyroXOffset) / 131.0;
    float gyroY = (gy - gyroYOffset) / 131.0;
    float gyroZ = (gz - gyroZOffset) / 131.0;
    float accelX = (ax - accelXOffset) / 16384.0;
    float accelY = (ay - accelYOffset) / 16384.0;
    float accelZ = (az - accelZOffset) / 16384.0;

    // Update the Madgwick filter with gyroscope and accelerometer data
    filter.updateIMU(gyroX, gyroY, gyroZ, accelX, accelY, accelZ);

    // Get orientation angles (in radians)
    float roll = filter.getRoll();
    float pitch = filter.getPitch();

    // Subtract the initial roll and pitch to make the current position relative to the start
    float relativePitch = (pitch - initialPitch);  // Make it more sensitive
    float relativeRoll = (roll - initialRoll);      // Make it more sensitive

    Serial.print("IniPitch: ");
    Serial.print(initialPitch);
    Serial.print(", IniRoll: ");
    Serial.print(initialRoll);
    Serial.print("Pitch: ");
    Serial.print(relativePitch);
    Serial.print(", Roll: ");
    Serial.println(relativeRoll);
    Serial.println();

    delay(110);  // Adjust delay as needed
}

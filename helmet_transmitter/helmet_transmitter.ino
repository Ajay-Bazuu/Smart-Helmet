int FSRPin1=32; // pin for getting reading from Force Sensitive Resistor 1
int FSRPin2=33; // pin for getting reading from Force Sensitive Resistor 2

int FSRValue1=0;
int FSRValue2=0;
void setup() {
  pinMode(FSRPin1,INPUT);
  pinMode(FSRPin2,INPUT);
  Serial.begin(115200);

}

// Function to read the Force Sensitive Resistor value
void FSRReadValue(){
  // Read the values
  FSRValue1=analogRead(FSRPin1);
  FSRValue2=analogRead(FSRPin2);
  // Print the values
  Serial.println(FSRValue1);
  Serial.println(FSRValue2);
  Serial.println();


}

void loop() {
  FSRReadValue(); // calling the function to read the values from FSR
  delay(100); //wait for 1 second

}

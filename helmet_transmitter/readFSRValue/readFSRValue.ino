int const fsrPin1=32; // pin for getting reading from Force Sensitive Resistor 1
int const fsrPin2=33; // pin for getting reading from Force Sensitive Resistor 2
int totalValue=0;

int fsrValue1=0; // variable to store FSR sensor 1
int fsrValue2=0; //variable to store FSR sensor 2

void setup() {
  pinMode(fsrPin1,INPUT);
  pinMode(fsrPin2,INPUT);
  Serial.begin(115200);

}

// Function to read the Force Sensitive Resistor value
void fsrReadValue(){
  // Read the values
  fsrValue1=analogRead(fsrPin1);
  fsrValue2=analogRead(fsrPin2);
  // Print the values
  Serial.print("FSR Value1: ");
  Serial.println(fsrValue1);
  Serial.print("FSR Value2: ");
  Serial.println(fsrValue2);
  totalValue=fsrValue1+fsrValue2;
  Serial.println();

  if (totalValue>3000){
    Serial.println("Helmet Worn ");
  }else{
    Serial.println("Helmet Not Worn ");
  }
}

void loop() {
  fsrReadValue(); // calling the function to read the values from FSR
  delay(500); //wait for 1 second

}

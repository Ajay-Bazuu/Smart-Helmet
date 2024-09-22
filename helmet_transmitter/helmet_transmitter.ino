int const fsrPin1=32; // pin for getting reading from Force Sensitive Resistor 1
int const fsrPin2=33; // pin for getting reading from Force Sensitive Resistor 2
int const mq3Pin=35; // pin for reading value of alcohol from MQ3 sensor


String command1="NT"; //command to send the signal which determine whether the helmet is worn or not
//NT for not worn helmet and W for the worn

int fsrValue1=0; // variable to store FSR sensor 1
int fsrValue2=0; //variable to store FSR sensor 2
int alcoholValue=0; // variable to store alcohol value

void setup() {
  pinMode(fsrPin1,INPUT);
  pinMode(fsrPin2,INPUT);
  pinMode(mq3Pin,INPUT);
  Serial.begin(115200);

}

// Function to read the Force Sensitive Resistor value
void fsrReadValue(){
  // Read the values
  fsrValue1=analogRead(fsrPin1);
  fsrValue2=analogRead(fsrPin2);
  // Print the values
  Serial.println(fsrValue1);
  Serial.println(fsrValue2);
  Serial.println();

  if (fsrValue1>2045 || fsrValue2>2045){
        command1="W"; //  Helmet Worn
        Serial.println("Helmet Worn ");
  }else{
    command1="NT"; // Helmet not Worn
    Serial.println("Helmet Not Worn ");
  }
}



void alcoholReadValue(){
  alcoholValue=analogRead(mq3Pin);
  Serial.println(alcoholValue);
}


void loop() {
  fsrReadValue(); // calling the function to read the values from FSR
  alcoholReadValue(); // calling the function to read the values 
  delay(100); //wait for 1 second

}

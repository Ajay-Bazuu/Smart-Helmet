int const mq3Pin=35; // pin for reading value of alcohol from MQ3 sensor
int alcoholValue=0; // variable to store alcohol value

void setup() {
  // put your setup code here, to run once:
  pinMode(mq3Pin,INPUT);
  Serial.begin(115200);
  delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  alcoholValue=analogRead(mq3Pin);
  Serial.print("ALcohol Value ");
  Serial.println(alcoholValue);
  Serial.println();
  delay(500);
}

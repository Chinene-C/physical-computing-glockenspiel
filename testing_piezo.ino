const int threshold = 100;  // threshold value to decide when the detected sound is a knock or not
int sensorReading = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), sense_hit, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(0);
  delay(500);
}

int piezo[] = {A1,A2};

void sense_hit(){
  // read the sensor and store it in the variable sensorReading:
  Serial.println("touch");
  for (int keys = 0; keys<2; keys++){
    int pin = piezo[keys];
    sensorReading = analogRead(pin);
    if (sensorReading >= threshold){
      //user_hit = piezo_hit;
      Serial.print("hit");
      Serial.println(piezo[keys]);
    }
  }
  delay(1000);
  //sensorReading = analogRead(1);
  //if (sensorReading >= threshold){
    //user_hit = piezo_hit;
    //Serial.println("hit");
 //}
}

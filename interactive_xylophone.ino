//SIMON THE MOVING XYLOPHONE
//simon says game,assists musical creativity
//teaches you how to play songs

//HOW IT WORKS:
//1. proximity sensor senses hand to start
//2. step motor activates & lcd shows hello
//3. simon plays a sequence
//4. player repeats sequence
//4a. if correct happy face & happy shake
//4b. if incorrect then gameover & when all lives lost jiggles then flatlines, skull shown

int time_to_sense = true;
int time_to_move = true;

//button
// constants won't change. They're used here to set pin numbers:
const int LEVEL_buttonPin = 22;     // the number of the pushbutton pin
const int GAMEOVER_buttonPin = 23;
int LEVEL_buttonState = 0;
int GAMEOVER_buttonState = 0;


//motion sensor
int pirPin = 2; // Input for HC-S501
int pirStat = 0;
  
//define game
const int START = 0;
const int PLAY = 1;
const int GAMEOVER = 2;
int gameState;
int user_hit;

//xylophone keys
//int keys[] = {1,2,3,4,5,6,7};
int song[28] = {5,5,6,5,1,7,0,5,5,6,5,2,1,0,5,5,5,3,1,7,6,4,4,3,1,2,1,0};
int level = 2;

//nema17 step motor
const int stepPin = 10; //step
const int dirPin = 11; //direction
const int STEPS_PER_REV = 200; //steps per rotation

//stepper motor
#include <Stepper.h>
const int stepsPerRevolution = 200;  // big motor, change this to fit the number of steps per revolution
const int SMALLstepsPerRevolution = 2048; //small motor
const int rolePerMinute = 15;         // Adjustable range of 28BYJ-48 stepper is 0~17 rpm
Stepper myStepper(stepsPerRevolution, 47, 49, 51, 53);

//ultrasonic sensor
const int trigPin = 12;
const int echoPin = 13;
long duration;
int distance;

//servo
#include <Servo.h>
Servo myservo;

//LCD Screen
#include <LiquidCrystal.h>
const int rs = 35, en = 37, d4 = 39, d5 = 41, d6 = 43, d7 = 45;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.print(1);
  
  //button
  pinMode(LEVEL_buttonPin, INPUT);
  pinMode(GAMEOVER_buttonPin, INPUT);
  
  //motion sensor
  pinMode(pirPin, INPUT);
  
  //servo
  myservo.attach(25);//connect pin 9 with the control line(the middle line of Servo) 
  myservo.write(0);// move servos to center position -> 90°
  
  //nema 17 step motor
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  //ultrasonic sensor
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input    
  
  //lcd screen
  lcd.begin(16, 2);
  lcd.home();
  
  //stepper motor
  myStepper.setSpeed(60); // set the speed at 60 rpm: 

  gameState = START; // Start the game with the start.
  delay(60000);
  randomSeed(analogRead(40));
  Serial.begin(9600);
}


void waitToStart(){
  pirStat = digitalRead(pirPin);  
  if (gameState == START && pirStat == HIGH) {        
    Serial.println("Motion Sensed ");
        
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(":D Hello ");
    lcd.setCursor(0, 1);
    lcd.print("Let's play.");

    gameState = PLAY;
   
    // steps 2 revolutions in one direction:
    /*digitalWrite(dirPin, HIGH);
     for(int i = 0; i < (STEPS_PER_REV *2); i++){
     Serial.println("NEMA clockwise");
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(1000);
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(1000);
      }*/
    }
    else{
      gameState = GAMEOVER;
    }
}

void showSequence(){
  time_to_sense = false;
  int time_to_move = true;
  Serial.println("NOT time to sense");

  if(time_to_move == true){
  
  for (int hits = 0; hits < 8; hits++){
    Serial.println("showing sequence");
    //motor hits relevant key
    //song[hits] = key_to_hit;
    if (song[hits] == 0){
      delay(1000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Pause");   
    }
    else if (song[hits] == 1){
      //keys move
      Serial.println("M rotate");
      myStepper.step(3*(stepsPerRevolution/4));
      delay(500);
      Serial.print("m hit");
      Serial.println(hits);
      myservo.write(90);// move servos to center position -> 90°
         
      //return to centre
      myservo.write(0);
      Serial.println("m return");
      delay(500);
      myStepper.step(-3*(stepsPerRevolution/4));
      Serial.println("M return");
      delay(1000);
      }       
      else if(song[hits] == 2){
      //keys move
      Serial.println("M rotate");
      myStepper.step(2*(stepsPerRevolution/4));
      delay(500);
      Serial.print("m hit");
      Serial.println(hits);
      myservo.write(90);// move servos to center position -> 90°
         
      //return to centre
      myservo.write(0);
      Serial.println("m return");
      delay(500);
      myStepper.step(-2*(stepsPerRevolution/4));
      Serial.println("M return");
      delay(1000);
      }      
      else if(song[hits] == 3){
      //keys move
      Serial.println("M rotate");
      myStepper.step(stepsPerRevolution/4);
      delay(500);
      Serial.print("m hit");
      Serial.println(hits);
      myservo.write(90);// move servos to center position -> 90°
         
      //return to centre
      myservo.write(0);
      Serial.println("m return");
      delay(500);
      myStepper.step(-stepsPerRevolution/4);
      Serial.println("M return");
      delay(1000);
      }      
      else if(song[hits] == 4){
      //keys move
      Serial.println("M rotate");
      //myStepper.step(stepsPerRevolution/4);
      delay(500);
      Serial.print("m hit");
      Serial.println(hits);
      myservo.write(90);// move servos to center position -> 90°
         
      //return to centre
      myservo.write(0);
      Serial.println("m return");
      delay(500);
      //myStepper.step(-stepsPerRevolution/4);
      Serial.println("M return");
      delay(1000);
      }      
      else if(song[hits] == 5){
      //keys move
      Serial.println("M rotate");
      myStepper.step(-stepsPerRevolution/4);
      delay(500);
      Serial.print("m hit");
      Serial.println(hits);
      myservo.write(90);// move servos to center position -> 90°
         
      //return to centre
      myservo.write(0);
      Serial.println("m return");
      delay(500);
      myStepper.step(stepsPerRevolution/4);
      Serial.println("M return");
      delay(1000);
      }      
      else if(song[hits] == 6){
      //keys move
      Serial.println("M rotate");
      myStepper.step(-stepsPerRevolution/4);
      delay(500);
      Serial.print("m hit");
      Serial.println(hits);
      myservo.write(90);// move servos to center position -> 90°
         
      //return to centre
      myservo.write(0);
      Serial.println("m return");
      delay(500);
      myStepper.step(stepsPerRevolution/4);
      Serial.println("M return");
      delay(1000);
      }
      else{
      //keys move
      Serial.println("M rotate");
      myStepper.step(-stepsPerRevolution/4);
      delay(500);
      Serial.print("m hit");
      Serial.println(hits);
      myservo.write(90);// move servos to center position -> 90°
         
      //return to centre
      myservo.write(0);
      Serial.println("m return");
      delay(500);
      myStepper.step(stepsPerRevolution/4);
      Serial.println("M return");
      delay(1000);
    }
    Serial.println("Sequence shown");
    time_to_sense = true;
    Serial.println("Time to sense");
    time_to_move = false;
  }}
  else{}
}

void game(){
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
  
  if((time_to_sense  = true) || (distance > 23)){
    distance = 0;
    }
    else{
      for (int hits = 0; hits < level; hits++){
        if(song[hits] == 1 && distance > 4){
           lcd.clear();
           lcd.setCursor(0, 0);
           lcd.print("Are you sure?");
           }
         else if(song[hits] == 2 && (6 > distance || distance < 4)){
           lcd.clear();
           lcd.setCursor(0, 0);
           lcd.print("Are you sure?");
           }
         else if(song[hits] == 3 && (12 > distance || distance < 8)){
           lcd.clear();
           lcd.setCursor(0, 0);
           lcd.print("Are you sure?");
           }
         else if(song[hits] == 4 && (14 > distance || distance < 10)){
           lcd.clear();
           lcd.setCursor(0, 0);
           lcd.print("Are you sure?");
           }
           else if(song[hits] == 5 && (16 > distance || distance < 12)){
           lcd.clear();
           lcd.setCursor(0, 0);
           lcd.print("Are you sure?");
           }
           else if(song[hits] == 6 && (18 > distance || distance < 14)){
           lcd.clear();
           lcd.setCursor(0, 0);
           lcd.print("Are you sure?");
           }
           else if(song[hits] == 7 && (20 > distance || distance < 16)){
           lcd.clear();
           lcd.setCursor(0, 0);
           lcd.print("Are you sure?");
           }
        else{
           lcd.clear();
           lcd.setCursor(0, 0);
           lcd.print(":) You might be right!");
        }
      }
    }
}


void increase_level(){
  LEVEL_buttonState = digitalRead(LEVEL_buttonPin);
  GAMEOVER_buttonState = digitalRead(GAMEOVER_buttonPin);
  if (gameState == PLAY && LEVEL_buttonState == HIGH){
  level += random(0,3);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("LEVEL UP!");
  }
  else if (GAMEOVER_buttonState == HIGH){
    gameState = GAMEOVER;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(":c GAMEOVER");
  }
}


void loop(){
 Serial.print(0);
 
 if(gameState == START)
  {
    Serial.println("START"); 
    waitToStart();
  }
  else if(gameState == PLAY)
  {
    Serial.println("PLAY"); 
    showSequence();
    game();
    increase_level();
  }
  else if(gameState == GAMEOVER)
  {
    Serial.println("GAMEOVER");
    gameState = START;
  }
}  

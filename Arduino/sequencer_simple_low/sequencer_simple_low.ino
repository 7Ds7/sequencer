#define ARRAYSIZE(x) (sizeof(x)/sizeof(*x))

const int ledStep1 = 2;
const int ledStep2 = 3;
const int ledStep3 = 4;
const int ledStep4 = 5;

const int ledStep5 = 6;
const int ledStep6 = 7;
const int ledStep7 = 8;
const int ledStep8 = 9;

const int gate = 13;

const int button1 = 11;
const int button2 = 12;
const int pot1 = A5;

int stepArray[] = {ledStep1, ledStep2, ledStep3, ledStep4, ledStep5, ledStep6, ledStep7, ledStep8};
int randArray[8];
//int stepArray[5] = {ledStep1, ledStep2, ledStep3, ledStep4};


int beat = 120;
int curvalue = -1;

int stepCounter = 0;

int mode = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledStep1, OUTPUT);
  pinMode(ledStep2, OUTPUT);
  pinMode(ledStep3, OUTPUT);
  pinMode(ledStep4, OUTPUT);
  pinMode(ledStep5, OUTPUT);
  pinMode(ledStep6, OUTPUT);
  pinMode(ledStep7, OUTPUT);
  pinMode(ledStep8, OUTPUT);

  digitalWrite(ledStep1, LOW);
  digitalWrite(ledStep2, LOW);
  digitalWrite(ledStep3, LOW);
  digitalWrite(ledStep4, LOW);
  digitalWrite(ledStep5, LOW);
  digitalWrite(ledStep6, LOW);
  digitalWrite(ledStep7, LOW);
  digitalWrite(ledStep8, LOW);
  
  pinMode(gate, OUTPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(pot1, INPUT);

  Serial.begin(9600);
}

void turnAllOff() {
  for ( int i= 0; i <= 7; i++ ) {
    //digitalWrite(stepArray[i], LOW);
  }
  digitalWrite(gate, LOW);
}

void regularPlay() {
  Serial.println("regularPlay");
  turnAllOff();
  //digitalWrite(stepArray[stepCounter], HIGH);
  digitalWrite(gate, HIGH);

  stepCounter++;
  if ( stepCounter >= 8 ) {
    stepCounter = 0;
  }
}

void reversePlay() {
  Serial.println("reversePlay");
  turnAllOff();
  //digitalWrite(stepArray[stepCounter], HIGH);
  digitalWrite(gate, HIGH);

  stepCounter--;
  if ( stepCounter <= -1 ) {
    stepCounter = 7;
  } 
}

void doublePlay() {
  Serial.println("doublePlay");
  turnAllOff();

  digitalWrite(stepArray[stepCounter], HIGH);      
  digitalWrite(stepArray[stepCounter+4], HIGH);
  digitalWrite(gate, HIGH);

  stepCounter++;
  if ( stepCounter >= 4 ) {
    stepCounter = 0;
  } 
}

void randomPlay() {
  Serial.println("randomPlay");
  turnAllOff();
  if ( stepCounter == 0 ) {
     for( int i = 0 ; i < 8 ; ++i ){
      randArray[ i ] = stepArray[ i ];
    }  
  }
  for( int i = 0 ; i < 8 ; ++i ){
    Serial.println(randArray[i]);
  }
  Serial.println("--------");
  Serial.println(ARRAYSIZE(randArray) );
  int arr_access = randArray[random(0, 8)];
  digitalWrite( arr_access, HIGH);
  digitalWrite(gate, HIGH);
  //remove_element(arr_access
  stepCounter++;
  if ( stepCounter >= 8 ) {
    stepCounter = 0;
  }
}


int modeSelect() {
  boolean b1 = digitalRead(button1);
  boolean b2 = digitalRead(button2);
  int md = 0;
  Serial.println(b1);
  Serial.println(b2);
  if ( true ) {
    md = 0;
  }
  else if ( b1 == 0 && b2 == 0 ) {
    //Serial.println("regularPlay");
    md = 0;
  } else if ( b1 == 1 && b2 == 0 ) {
    //Serial.println("reversePlay");
    md = 1;
  } else if ( b1 == 0 && b2 == 1 ) {
    //Serial.println("doublePlay");
    md = 2;
  } else if ( b1 == 1 && b2 == 1 ) {
    md = 3;
  }
  
  return md;
  
}

void loop() {
  //beat = 30 + 220*(analogRead(pot1)/256);
  mode = modeSelect();
//  mode = 0;
  //Serial.println(stepCounter);
  //Serial.println(mode);
  //Serial.println(analogRead(pot1));
//  Serial.print("\n");
   //Serial.println(beat);
  if ( mode == 0) {
    //Serial.println("Regular play");
    regularPlay();
  } else if ( mode == 1 ) {
    //Serial.println("Alternate play");
    reversePlay();
  } else if ( mode == 2 ) {
    doublePlay();
  } else if ( mode == 3 ) {
    randomPlay(); 
  }
//  Serial.println(digitalRead(button1));
//  Serial.println(digitalRead(button2));
//  Serial.println(mode);
  //Serial.println(stepArray[stepCounter]);
  delay(beat);
}

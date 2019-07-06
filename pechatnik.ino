
//вертикальные шаговики
//swither, pul, dir
int motor1[] = {A2, 10 , 11};
int motor2[] = {A3, 10 , 11};
int motor3[] = {A4, 10 , 11};
int motor4[] = {A5, 12, 13};


int horiz_motor7 = 7;
int horiz_motor8 = 8;
int solenoid = 2;

int optocoupler1 = A0;

int button2=A1;

void initialization(int mot[]){
   pinMode(mot[0], INPUT);
   pinMode(mot[1], OUTPUT);
   pinMode(mot[2], OUTPUT);

}


void step(int pin){
  digitalWrite(pin, HIGH);   
  delay(2);                   
  digitalWrite(pin, LOW);    
  delay(2);
  Serial.println(pin);
    
  }


void speedstep(int pin){
  digitalWrite(pin, HIGH);   
  delayMicroseconds(100);                   
  digitalWrite(pin, LOW);    
  delayMicroseconds(100);
  //Serial.println(pin);
    
  }
void parkovka(int motorA[], int motorB[]){
  int back_motorA=200,
  back_motorB=200,
  amountA=0,
  amountB=0;
  while(back_motorA>0 | back_motorB>0){
    if(back_motorA>0){speedstep(motorA[1]);}
    if(back_motorB>0){speedstep(motorB[1]);}
    
    if(digitalRead(motorA[0])==LOW){
        Serial.println("LOW A");
        digitalWrite(motorA[2], HIGH);
        amountA=-1;
      }
    if(digitalRead(motorB[0])==LOW){
        Serial.println("LOW B");
        digitalWrite(motorB[2], HIGH);
        amountB=-1;
      }
      back_motorA = back_motorA+amountA;
      back_motorB = back_motorB+amountB;
    }
  }

void pechat(int motorA[], int motorB[]){
    int i=0;
    digitalWrite(motorA[2], HIGH);
    digitalWrite(motorB[2], HIGH);
    while(i<7000){
    i++;
    step(motorA[1]);
    step(motorB[1]);    
    Serial.println(i);
    }  
  
  }  







void setup() {
  initialization(motor3); 
  initialization(motor4);
  
  pinMode(horiz_motor7, OUTPUT);
  pinMode(horiz_motor8, OUTPUT);
  pinMode(solenoid, OUTPUT);
    
  Serial.begin(57600);


  while(digitalRead(button2)==LOW){
    delay(100);
    Serial.println("stop");
    }
    Serial.println("start");
    
  parkovka(motor3,motor4);

  delay(2000);
Serial.println("start zahvat stranitci");
    
  digitalWrite(solenoid, HIGH);
  for(int i=0;i<50;i++){
      step(motor3[1]);
      step(motor4[1]);
    }
  digitalWrite(solenoid, LOW);
   Serial.println("dovod do optopari");
    
  while(digitalRead(optocoupler1)==HIGH){
      step(horiz_motor7);
      step(horiz_motor8);
    }
   Serial.println("pechat");
    pechat(motor3, motor4);

}



void loop() {

  while(1){};  
}

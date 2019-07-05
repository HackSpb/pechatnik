

//swither, pul, dir
int motor3[] = {A5, 12, 13};
int motor4[] = {A4, 10 , 11};

void initialization(int mot[]){
   pinMode(mot[0], INPUT);
   pinMode(mot[1], OUTPUT);
   pinMode(mot[2], OUTPUT);

}


void step(int pin){
  digitalWrite(pin, HIGH);   
  delay(1);                   
  digitalWrite(pin, LOW);    
  delay(1);
  }
  
void parkovka(int motorA[], int motorB[]){
  int back_motorA=200,
  back_motorB=200,
  amountA=0,
  amountB=0;
  while(back_motorA>0 | back_motorB>0){
    if(back_motorA>0)step(motorA[1]);
    if(back_motorB>0)step(motorB[1]);
    
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





int i=0;

void setup() {
  initialization(motor3); 
  initialization(motor4);  
  Serial.begin(57600);
  
  parkovka(motor3,motor4);

delay(2000);
  digitalWrite(motor3[2], HIGH);
  digitalWrite(motor4[2], HIGH);
  while(i<11000){
    i++;
    step(motor3[1]);
    step(motor4[1]);    
    //Serial.println(i);
    }  
}



void loop() {

  while(1){};  
}

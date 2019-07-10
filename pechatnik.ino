
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display




//вертикальные шаговики
//pul, dir, swither, 
int motor1[] = {10, 11, 12};
int motor2[] = {23, 24, 25};
int motor3[] = {30, 31, 32};
int motor4[] = {40, 41, 42};


int horiz_motor5 = 5;
int horiz_motor6 = 6;
int horiz_motor7 = 7;
int horiz_motor8 = 8;
int solenoid = 9;

int optocoupler1 = A1;
int optocoupler2 = A0;//перепутали при пайке

int button1=17;
int button2=18;
int button3=19;

void initialization(int mot[]){
   pinMode(mot[0], OUTPUT);
   pinMode(mot[1], OUTPUT);
   pinMode(mot[2], INPUT);

}


void step(int pin){
  digitalWrite(pin, HIGH);   
   delayMicroseconds(1800);                    
  digitalWrite(pin, LOW);    
  //delay(2);
  //Serial.println(pin);
    
  }


void speedstep(int pin){
  digitalWrite(pin, HIGH);   
  delayMicroseconds(75);                   
  digitalWrite(pin, LOW);    
 // delayMicroseconds(75);
 // Serial.println(pin);
    
  }
void parkovka(int motorA[], int motorB[]){
  int back_motorA=200,
  back_motorB=200,
  amountA=0,
  amountB=0;
  while(back_motorA>0 | back_motorB>0){
    if(back_motorA>0){speedstep(motorA[0]);}
    if(back_motorB>0){speedstep(motorB[0]);}
    
    if(digitalRead(motorA[2])==LOW){
      Serial.print(motorA[2]);
        Serial.println("LOW A");
        digitalWrite(motorA[1], HIGH);
        amountA=-1;
      }
    if(digitalRead(motorB[2])==LOW){
      Serial.print(motorB[2]);
        Serial.println("LOW B");
        digitalWrite(motorB[1], HIGH);
        amountB=-1;
      }
      back_motorA = back_motorA+amountA;
      back_motorB = back_motorB+amountB;
    }
  }

void Parralel_parkovka(int motorA[], int motorB[]){
  int back_motorA=200,
  back_motorB=200,
  amountA=0,
  amountB=0;
  while(back_motorA>0 | back_motorB>0){
    if(back_motorA>0){speedstep(motorA[0]);}
    if(back_motorB>0){speedstep(motorB[0]);}
    
    if(digitalRead(motorA[2])==LOW){
      Serial.print(motorA[2]);
        Serial.println("LOW A");
        digitalWrite(motorA[1], HIGH);
        amountA=-1;
      }
    if(digitalRead(motorB[2])==LOW){
      Serial.print(motorB[2]);
        Serial.println("LOW B");
        digitalWrite(motorB[1], HIGH);
        amountB=-1;
      }
      back_motorA = back_motorA+amountA;
      back_motorB = back_motorB+amountB;
    }
  }


void pechat(int motorA[], int motorB[]){
    int i=0;
    digitalWrite(motorA[1], HIGH);
    digitalWrite(motorB[1], HIGH);
    while(i<7000){
    i++;
    speedstep(motorA[0]);
    speedstep(motorB[0]);    
    //Serial.println(i);
    }  
    digitalWrite(motorA[1], LOW);
    digitalWrite(motorB[1], LOW);
    delay(2);
     lcd.setCursor(3,0);
  lcd.print("BACK              ");
    i=0;
    while(i<2000){
      i++;
      speedstep(motorA[0]);
      speedstep(motorB[0]);    
    //Serial.println(i);
    }  
    
}  



void interruptMenu(){
  int state = digitalRead(button3); 
    lcd.setCursor(3,0);
  lcd.print("STOP!              ");
  while(digitalRead(button3)==state){
    1;
    }
  
  }




void setup() {
  lcd.init();    
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("starting!");
 // attachInterrupt(digitalPinToInterrupt(button3), interruptMenu, CHANGE);
  initialization(motor1);
  initialization(motor2);
  initialization(motor3); 
  initialization(motor4);
  
  pinMode(horiz_motor5, OUTPUT);
  pinMode(horiz_motor6, OUTPUT);
  pinMode(horiz_motor7, OUTPUT);
  pinMode(horiz_motor8, OUTPUT);
  pinMode(solenoid, OUTPUT);
    
  Serial.begin(9600);


  while(digitalRead(button1)==LOW){
    delay(100);
    Serial.println("stop");
    }

        lcd.setCursor(0,0);
      lcd.print("start       ");
    Serial.println("start");
    
  //parkovka(motor1,motor2);
/*
  //delay(2000);
  Serial.println("give paper");
    lcd.setCursor(0,0);
      lcd.print("give paper      ");
  digitalWrite(solenoid, HIGH);
  for(int i=0;i<75;i++){
      step(horiz_motor7);
      step(horiz_motor8);
    }
  digitalWrite(solenoid, LOW);

   
   
   Serial.println("dovod do optopari 1");
        lcd.setCursor(0,0);
      lcd.print("go to 1 pos.       ");
  
            int back_motor1=200, back_motor2=200, back_motor3=200, back_motor4=200,
                amount1=0, amount2=0, amount3=0, amount4=0;
   
  while(digitalRead(optocoupler1)==HIGH){
      step(horiz_motor6);
      step(horiz_motor7);
      step(horiz_motor8);
                
                if(back_motor1>0){speedstep(motor1[0]);}
                if(back_motor2>0){speedstep(motor2[0]);}
                if(back_motor3>0){speedstep(motor3[0]);}
                if(back_motor4>0){speedstep(motor4[0]);}
                
                if(digitalRead(motor1[2])==LOW){
                  Serial.print(motor1[2]);
                    Serial.println("LOW A");
                    digitalWrite(motor1[1], HIGH);
                    amount1=-1;
                  }
                if(digitalRead(motor2[2])==LOW){
                  Serial.print(motor2[2]);
                    Serial.println("LOW B");
                    digitalWrite(motor2[1], HIGH);
                    amount2=-1;
                  }                
                if(digitalRead(motor3[2])==LOW){
                  Serial.print(motor3[2]);
                    Serial.println("LOW C");
                    digitalWrite(motor3[1], HIGH);
                    amount3=-1;
                  }
                if(digitalRead(motor4[2])==LOW){
                  Serial.print(motor4[2]);
                    Serial.println("LOW D");
                    digitalWrite(motor4[1], HIGH);
                    amount4=-1;
                  }
                  back_motor1 = back_motor2+amount2;
                  back_motor2 = back_motor2+amount2;  
                  back_motor3 = back_motor3+amount3;
                  back_motor4 = back_motor4+amount4;  
                }
   Serial.println("pechat 1");
       lcd.setCursor(0,0);
      lcd.print("pechat 1      ");
    pechat(motor3, motor4);

   Serial.println("dovod do optopari 2");
        lcd.setCursor(0,0);
      lcd.print("go to 2 pos.       ");

          
  while(digitalRead(optocoupler2)==HIGH){
      step(horiz_motor5);
      step(horiz_motor6);
      step(horiz_motor7);
  }

   Serial.println("pechat 2");
       lcd.setCursor(0,0);
      lcd.print("pechat 2      ");
    pechat(motor1, motor2);
    */
  
}



   int back_motor1=200, back_motor2=200, back_motor3=200, back_motor4=200,
                amount1=0, amount2=0, amount3=0, amount4=0, povtor;
void loop() {

 
  Serial.println("give paper");
    lcd.setCursor(0,0);
      lcd.print("give paper      ");
  digitalWrite(solenoid, HIGH);
  for(int i=0;i<75;i++){
      step(horiz_motor7);
      step(horiz_motor8);
    }
  digitalWrite(solenoid, LOW);

   
   
   Serial.println("dovod do optopari 1");
        lcd.setCursor(0,0);
      lcd.print("go to 1 pos.       ");
  
      back_motor1=200, back_motor2=200, back_motor3=200, back_motor4=200,
      amount1=0, amount2=0, amount3=0, amount4=0,
      povtor=11500; //повтор захвата 3300 для первого?
                
   digitalWrite(motor1[1], LOW);
   digitalWrite(motor2[1], LOW);
   digitalWrite(motor3[1], LOW);
   digitalWrite(motor4[1], LOW);
  while(digitalRead(optocoupler1)==HIGH || (digitalRead(optocoupler1)==LOW  && digitalRead(optocoupler2)==LOW ) || (back_motor1>0 || back_motor2>0 || back_motor3>0 || back_motor4>0)  ){
      if( digitalRead(optocoupler2)==LOW ) {
        step(horiz_motor5);
      }  
      if(digitalRead(optocoupler1)==LOW  && digitalRead(optocoupler2)==LOW ) {
        step(horiz_motor6);
      }

       if( digitalRead(optocoupler1)==HIGH ){
        step(horiz_motor6);
        step(horiz_motor7);
        step(horiz_motor8);
        povtor--;
        }
      if(povtor<0){
              povtor=11500;
              digitalWrite(solenoid, HIGH);
              for(int i=0;i<75;i++){
                  step(horiz_motor7);
                  step(horiz_motor8);
                }
              digitalWrite(solenoid, LOW);
        }
                
                if(back_motor1>0){speedstep(motor1[0]);speedstep(motor1[0]);}
                if(back_motor2>0){speedstep(motor2[0]);speedstep(motor2[0]);}
                if(back_motor3>0){speedstep(motor3[0]);speedstep(motor3[0]);}
                if(back_motor4>0){speedstep(motor4[0]);speedstep(motor4[0]);}
                
                if(digitalRead(motor1[2])==LOW){
                  
                    //Serial.println("LOW 2");
                    digitalWrite(motor1[1], HIGH);
                    amount1=-1;
                  }
                if(digitalRead(motor2[2])==LOW){
                  
                    ///Serial.println("LOW 2");
                    digitalWrite(motor2[1], HIGH);
                    amount2=-1;
                  }                
                if(digitalRead(motor3[2])==LOW){
                 
                    Serial.println("LOW 3");
                    digitalWrite(motor3[1], HIGH);
                    amount3=-1;
                  }
                if(digitalRead(motor4[2])==LOW){
                  
                    Serial.println("LOW 4");
                    digitalWrite(motor4[1], HIGH);
                    amount4=-1;
                  }
                  back_motor1 = back_motor1+amount1;
                  back_motor2 = back_motor2+amount2;  
                  back_motor3 = back_motor3+amount3;
                  back_motor4 = back_motor4+amount4;  
                }
   Serial.println("pechat 1");
       lcd.setCursor(0,0);
      lcd.print("pechat 1      ");
    pechat(motor3, motor4);

   Serial.println("dovod do optopari 2");
        lcd.setCursor(0,0);
      lcd.print("go to 2 pos.       ");

          
  while(digitalRead(optocoupler2)==HIGH){
      step(horiz_motor5);
      step(horiz_motor6);
      step(horiz_motor7);
  }

   Serial.println("pechat 2");
       lcd.setCursor(0,0);
      lcd.print("pechat 2      ");
    pechat(motor1, motor2);

}

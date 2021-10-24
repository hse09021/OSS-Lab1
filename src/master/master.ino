 #include <Wire.h>
#include <SoftwareSerial.h>
 int blueTx=2;   //Tx (보내는핀 설정)at
int blueRx=3;
SoftwareSerial mySerial(blueTx, blueRx);

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
   pinMode(6, OUTPUT);       // Motor A 방향설정1

  pinMode(7, OUTPUT);       // Motor A 방향설정2

  pinMode(8, OUTPUT);       // Motor B 방향설정1

  pinMode(9, OUTPUT);
  Wire.begin();
  Serial.begin(9600); 
  mySerial.begin(9600);
}

byte count = 0;

void loop() {
  
  Wire.beginTransmission(1);                        
     
   //슬레이브(1)에 4byte 요청
  Wire.endTransmission();   
  delay(500);
  
  
  Wire.requestFrom(1, 7);
  while (Wire.available()) {
    Serial.print("MQ135 : ");
    int MQ135 = Wire.read(); 
    Serial.println(MQ135);
    Serial.print("MQ7_1 : ");
    int MQ7_1 = Wire.read(); 
    Serial.println(MQ7_1);
    Serial.print("MQ7_2 : ");
    int MQ7_2 = Wire.read(); 
    Serial.println(MQ7_2);
    Serial.print("MQ7_3 : ");
    int MQ7_3 = Wire.read(); 
    Serial.println(MQ7_3);
    Serial.print("MQ7_4 : ");
    int MQ7_4 = Wire.read(); 
    Serial.println(MQ7_4);
    Serial.print("MQ7_5 : ");
    int MQ7_5 = Wire.read(); 
    Serial.println(MQ7_5);
    Serial.print("Message: ");
    char read_moter = Wire.read();
    if(read_moter == 'v'){
      analogWrite(8, LOW);
      Serial.println("moter1 down");
    }
    else if(read_moter == 'm'){
      analogWrite(4, LOW);
      Serial.println("moter2 down");
    }
    else if(read_moter == 'q'){
      analogWrite(7, LOW);
      Serial.println("moter3 down");
    }
    else if(read_moter == 'w'){
      
      analogWrite(3, LOW);
      Serial.println("moter4 down");
    }
    else if(read_moter == 'N'){
      Serial.println("Undetected");
      digitalWrite(3, LOW);     
    analogWrite(2, 255);      // Motor A 속도조절 (0~255)   /*모터B설정*/
    digitalWrite(4, LOW);     // Motor B 방향설정2
    analogWrite(5, 255);
    digitalWrite(7, LOW);      // Motor A 방향설정
    analogWrite(6, 255);      // Motor A 속도조절 (0~255)/*모터B설정*/
    digitalWrite(8,LOW);    // Motor B 방향설정
    analogWrite(9, 255); 
    
  }
  else if(read_moter == 's'){
    Serial.println("Motor Works Fine");
    help_a();   
  }
  float avg;
  avg = (MQ7_1 + MQ7_2 + MQ7_3 + MQ7_4 + MQ7_5)/5;
  Serial.print("AVG: ");
  Serial.println(avg);
  
  count++;
  if(count==6)count=0;
  
}
}
void help_a(){
  if (Serial.available()) {         
    mySerial.write("화재가 발생했습니다");  //시리얼 모니터 내용을 블루추스 측에 WRITE
  }
        digitalWrite(3, HIGH);     
    analogWrite(2, 255);      // Motor A 속도조절 (0~255)   /*모터B설정*/
    digitalWrite(4, HIGH);     // Motor B 방향설정2
    analogWrite(5, 255);
    digitalWrite(7, HIGH);      // Motor A 방향설정
    analogWrite(6, 255);      // Motor A 속도조절 (0~255)/*모터B설정*/
    digitalWrite(8, HIGH);    // Motor B 방향설정
    analogWrite(9, 255); 
  }

//Learn ins and outs of demultiplexer
//By: Jerry Elmore
//Date: 23-Dec-2013

//Set pins for each address input on the 74HC138AN
const int ADDRESS_A0 = 3;
const int ADDRESS_A1 = 4;
const int ADDRESS_A2 = 5;

//Set pins for each enable input on the 74HC138AN
const int ENABLE_E1 = 6;
const int ENABLE_E2 = 7;
const int ENABLE_E3 = 8;

//Initialize bits for DEBUG
int r1 = 0;
int r2 = 0;
int r3 = 0;
int r4 = 0;


int r5 = 0;
int r6 = 0;


void setup() {
  pinMode(ADDRESS_A0,OUTPUT);
  pinMode(ADDRESS_A1,OUTPUT);
  pinMode(ADDRESS_A2,OUTPUT);
  pinMode(ENABLE_E1,OUTPUT);
  pinMode(ENABLE_E2,OUTPUT);
  pinMode(ENABLE_E3,OUTPUT);
  
  //DEBUG
  Serial.begin(9600);
}

void loop() {
  //All on - E1 high
  digitalWrite(ADDRESS_A0,LOW);
  digitalWrite(ADDRESS_A1,LOW);
  digitalWrite(ADDRESS_A2,LOW);
  digitalWrite(ENABLE_E1,HIGH);
  digitalWrite(ENABLE_E2,LOW);
  digitalWrite(ENABLE_E3,LOW);
  delay(100);
  
  //DEBUG
  readPinState();
 
  //All on - E2 high  
  digitalWrite(ADDRESS_A0,LOW);
  digitalWrite(ADDRESS_A1,LOW);
  digitalWrite(ADDRESS_A2,LOW);
  digitalWrite(ENABLE_E1,LOW);
  digitalWrite(ENABLE_E2,HIGH);
  digitalWrite(ENABLE_E3,LOW);
  delay(100);
  
  //DEBUG
  readPinState();
  
  //All on - E3 low
  digitalWrite(ADDRESS_A0,LOW);
  digitalWrite(ADDRESS_A1,LOW);
  digitalWrite(ADDRESS_A2,LOW);
  digitalWrite(ENABLE_E1,LOW);
  digitalWrite(ENABLE_E2,LOW);
  digitalWrite(ENABLE_E3,LOW);
  delay(100);

  //DEBUG
  readPinState();
  
  //Y0 off
  digitalWrite(ADDRESS_A0,LOW);
  digitalWrite(ADDRESS_A1,LOW);
  digitalWrite(ADDRESS_A2,LOW);
  digitalWrite(ENABLE_E1,LOW);
  digitalWrite(ENABLE_E2,LOW);
  digitalWrite(ENABLE_E3,HIGH);
  delay(100);

  //DEBUG
  readPinState();

  //Y1 off
  digitalWrite(ADDRESS_A0,HIGH);
  digitalWrite(ADDRESS_A1,LOW);
  digitalWrite(ADDRESS_A2,LOW);
  digitalWrite(ENABLE_E1,LOW);
  digitalWrite(ENABLE_E2,LOW);
  digitalWrite(ENABLE_E3,HIGH);
  delay(100);

  //DEBUG
  readPinState();

  //Y2 off
  digitalWrite(ADDRESS_A0,LOW);
  digitalWrite(ADDRESS_A1,HIGH);
  digitalWrite(ADDRESS_A2,LOW);
  digitalWrite(ENABLE_E1,LOW);
  digitalWrite(ENABLE_E2,LOW);
  digitalWrite(ENABLE_E3,HIGH);
  delay(100);

  //DEBUG
  readPinState();

  //Y3 off
  digitalWrite(ADDRESS_A0,HIGH);
  digitalWrite(ADDRESS_A1,HIGH);
  digitalWrite(ADDRESS_A2,LOW);
  digitalWrite(ENABLE_E1,LOW);
  digitalWrite(ENABLE_E2,LOW);
  digitalWrite(ENABLE_E3,HIGH);
  delay(100);

  //DEBUG
  readPinState();

  //Y4 off
  digitalWrite(ADDRESS_A0,LOW);
  digitalWrite(ADDRESS_A1,LOW);
  digitalWrite(ADDRESS_A2,HIGH);
  digitalWrite(ENABLE_E1,LOW);
  digitalWrite(ENABLE_E2,LOW);
  digitalWrite(ENABLE_E3,HIGH);
  delay(100);

  //DEBUG
  readPinState();

  //Y5 off
  digitalWrite(ADDRESS_A0,HIGH);
  digitalWrite(ADDRESS_A1,LOW);
  digitalWrite(ADDRESS_A2,HIGH);
  digitalWrite(ENABLE_E1,LOW);
  digitalWrite(ENABLE_E2,LOW);
  digitalWrite(ENABLE_E3,HIGH);
  delay(100);
 
  //DEBUG
  readPinState();

  //Y6 off
  digitalWrite(ADDRESS_A0,LOW);
  digitalWrite(ADDRESS_A1,HIGH);
  digitalWrite(ADDRESS_A2,HIGH);
  digitalWrite(ENABLE_E1,LOW);
  
  digitalWrite(ENABLE_E2,LOW);
  digitalWrite(ENABLE_E3,HIGH);
  delay(100);

  //DEBUG
  readPinState();

  //Y7 off
  digitalWrite(ADDRESS_A0,HIGH);
  digitalWrite(ADDRESS_A1,HIGH);
  digitalWrite(ADDRESS_A2,HIGH);
  digitalWrite(ENABLE_E1,LOW);
  digitalWrite(ENABLE_E2,LOW);
  digitalWrite(ENABLE_E3,HIGH);
  delay(100); 

  //DEBUG
  readPinState();  
}

void readPinState() {
  
  //DEBUG
  r1 = digitalRead(ADDRESS_A0);
  r2 = digitalRead(ADDRESS_A1);
  r3 = digitalRead(ADDRESS_A2);
  r4 = digitalRead(ENABLE_E1);
  r5 = digitalRead(ENABLE_E2);
  r6 = digitalRead(ENABLE_E3);
  
  Serial.print("A0 = ");
  Serial.print(r1);
  Serial.print("\t");

  Serial.print("A1 = ");
  Serial.print(r2);
  Serial.print("\t");

  Serial.print("A2 = ");
  Serial.print(r3);
  Serial.print("\t");

  Serial.print("E1 = ");
  Serial.print(r4);
  Serial.print("\t");

  Serial.print("E2 = ");
  Serial.print(r5);
  Serial.print("\t");

  Serial.print("E3 = ");
  Serial.print(r6
  );
  Serial.println("\n");
 
}

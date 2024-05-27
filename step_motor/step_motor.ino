int PUL=4;
int DIR=3;
int ENA=2;
  
void setup() {
  pinMode (PUL, OUTPUT);
  pinMode (DIR, OUTPUT);
  pinMode (ENA, OUTPUT);
 
}
 
void loop() {
  for (int i=0; i<6400*2; i++)
  {
    digitalWrite(DIR,LOW);
    digitalWrite(ENA,HIGH);
    digitalWrite(PUL,HIGH);
    delayMicroseconds(50*4);
    digitalWrite(PUL,LOW);
    delayMicroseconds(50);
  }
  delay(4000);
    //delayMicroseconds(50);

}

#include <Keyboard.h>
#include <Mouse.h>

int enc=0; 
char estat=0;
char testat=0;  
char key=0;
char tkey=0;
unsigned char kchat=254;
char ledmat[12]={1,5,9,2,6,10,3,7,11,4,8,12};

char keypad()
{
  char i,j,res=0,k=0;
  for(i=2;i<=5;i++)
  {
    digitalWrite(i,LOW);
    for(j=6;j<=8;j++)
    {
      k++;
      if(!digitalRead(j))
        res=k;
    }
    digitalWrite(i,HIGH);
  }
  return res;
}
void setup() {
  Serial.begin(9600);

  pinMode(0,INPUT);
  pinMode(1,INPUT);
  char i;
  for(i=2;i<=5;i++)
  {
    pinMode(i,OUTPUT);
    digitalWrite(i,HIGH);
  }
  for(i=6;i<=8;i++) pinMode(i,INPUT);
  for(i=9;i<=22;i++)
  {
    pinMode(i,OUTPUT);
    digitalWrite(i,LOW);
  }
  pinMode(23,INPUT);
  testat=digitalRead(1);
  //Keyboard.begin();
  //Mouse.begin();
}

void loop() {
  // enc
  estat=digitalRead(1);
  if(estat!=testat)
  {
    if(digitalRead(0)!=estat)
    {
      digitalWrite(21,HIGH);
      digitalWrite(22,LOW);
    }
    else
    {
      enc--;
      digitalWrite(22,HIGH);
      digitalWrite(21,LOW);
    }
    Serial.print("Enc : ");
    Serial.println(enc);
  }
  testat=estat;
  
  // button
  if(!kchat) key=keypad();
  if(key!=tkey)
  {
    if(key)
    {
      Serial.print("Key : ");
      Serial.println((int)key);
      digitalWrite(ledmat[key-1]+8,HIGH);
    }
    kchat=254;
    if(!key) digitalWrite(ledmat[tkey-1]+8,LOW);
    tkey=key;
  }
  if(kchat && keypad()!=key) kchat--;
}

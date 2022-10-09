#include <Keyboard.h>
#include <Mouse.h>

int enc=0; 
char estat=0;
char testat=0;  
char key=0;
char tkey=0;
char mode=0;
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

  digitalWrite(22,HIGH);
  Keyboard.begin();
  Mouse.begin();
}

void loop() {
  // enc
  estat=digitalRead(1);
  if(estat!=testat)
  {
    if(digitalRead(0)!=estat)
    {
      enc++;
      mode=1;
      digitalWrite(21,HIGH);
      digitalWrite(22,LOW);
    }
    else
    {
      enc--;
      mode=0;
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

      if(mode==0)
      {
        if(key!=3 && key!=0)
        {
          Keyboard.press('/');
          Keyboard.releaseAll();
          delay(150);
        }

        switch(key){
          case 1: Keyboard.println("c"); 
                  break;
          case 2: Keyboard.println("dc");
                  break;
          case 3: Keyboard.press('t');
                  Keyboard.releaseAll();
                  delay(150);
                  Keyboard.println("cotal");
                  break;
          case 4: Keyboard.print("w ");
                  break;               
          case 5: Keyboard.print("r ");
                  break;
          case 6: Keyboard.println("jukebox");
                  break;
          case 7: Keyboard.println("event");
                  break;
          case 8: Keyboard.println("fish bag");
                  break;
          case 9: Keyboard.println("fishshop");
                  break;
          case 10: Keyboard.println("vote");
                  break;
          case 11: Keyboard.println("map");
                  break;
          case 12: Keyboard.println("gift");
                  break;
        }
        
      }
      else if(mode==1)
      {
        switch(key)
        {
          case 1: Keyboard.press('/');
                  Keyboard.releaseAll();
                  delay(150);
                  Keyboard.println("c"); 
                  break;
          case 2: Keyboard.press('t');
                  Keyboard.releaseAll();
                  delay(150);
                  Keyboard.println("dkssudgktpdy!");
                  break;
          case 3: Keyboard.press('t');
                  Keyboard.releaseAll();
                  delay(150);
                  Keyboard.println("cotal");
                  break;
          case 4: Keyboard.press('t');
                  Keyboard.releaseAll();
                  delay(150);
                  Keyboard.println("djtjdhtpdy!");
                  break;
          case 5: Keyboard.press('t');
                  Keyboard.releaseAll();
                  delay(150);
                  Keyboard.println("gjrjr...");
                  break;
          case 6: Keyboard.print("t");
                   Keyboard.releaseAll();
                   delay(200);
                  Keyboard.println("tkffuwntpdy!");
                  break;
          case 7: Keyboard.press('t');
                  Keyboard.releaseAll();
                  delay(150);
                  Keyboard.println("rhakdnjdy!");
                  break;
          case 8: Keyboard.press('t');
                  Keyboard.releaseAll();
                  delay(150);
                  Keyboard.println("aldksgody");
                  break;
          case 9: Keyboard.press('t');
                  Keyboard.releaseAll();
                  delay(150);
                  Keyboard.println("rhoscksgdkdy?");
                  break;
          case 10: Keyboard.print("t");
                   Keyboard.releaseAll();
                   delay(200);
                   Keyboard.println(" tjsanf~");
                  break;
          case 11: Keyboard.press('t');
                  Keyboard.releaseAll();
                  delay(150);
                  Keyboard.println("skan tkqslek~~");
                  break;
          case 12: Keyboard.press('t');
                  Keyboard.releaseAll();
                  delay(150);
                  Keyboard.println("anssla... wnantuTskdy??");
                  break;
        }
      }

    }
    kchat=254;
    if(!key) digitalWrite(ledmat[tkey-1]+8,LOW);
    tkey=key;
  }
  if(kchat && keypad()!=key) kchat--;
}

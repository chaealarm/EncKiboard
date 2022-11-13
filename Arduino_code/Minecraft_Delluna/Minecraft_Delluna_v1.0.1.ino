#include <Keyboard.h>
#include <Mouse.h>

int enc=0; // 엔코더 값 
char estat=0; // 엔코더 현재위치
char testat=0;  // 엔코더 과거위치
char key=0; // 눌려진 키(0~12)
char tkey=0; // 과거 눌려진 키(0~12)
char mode=0; // 모드
unsigned char kchat=254; // 키 채터링 방지용
unsigned char ekchat=0;
char ledmat[12]={1,5,9,2,6,10,3,7,11,4,8,12}; // LED 포트 순서를 키 순서에 따라 매핑
char koflag=0; // /r /w 시 자동 한영변환을 위한 플래그

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
  int i;
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

      if(koflag && key)
      {
          Keyboard.press(KEY_RIGHT_ALT);
          koflag=0;
          delay(50);
          Keyboard.releaseAll();
          delay(50);
      }

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
                  Keyboard.press(KEY_RIGHT_ALT);
                  koflag=1;
                  delay(50);
                  Keyboard.releaseAll();
                  delay(50);
                  break;               
          case 5: Keyboard.print("r ");
                  Keyboard.press(KEY_RIGHT_ALT);
                  koflag=1;
                  delay(50);
                  Keyboard.releaseAll();
                  delay(50);
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
                  Keyboard.println("dkssudgktpdy!"); //안녕하세요!
                  break;
          case 3: Keyboard.press('t');
                  Keyboard.releaseAll();
                  delay(150);
                  Keyboard.println("cotal"); //챗미
                  break;
          case 4: Keyboard.press('t');
                  Keyboard.releaseAll();
                  delay(150);
                  Keyboard.println("djtjdhtpdy!"); //어서오세요!
                  break;
          case 5: Keyboard.press('t');
                  Keyboard.releaseAll();
                  delay(150);
                  Keyboard.println("emfdjrktpdy~"); //들어가세요~
                  break;
          case 6: Keyboard.print("t");
                   Keyboard.releaseAll();
                   delay(200);
                  Keyboard.println("rhoscksgdkdy?"); //괜찮아요?
                  break;
          case 7: Keyboard.press('t');
                  Keyboard.releaseAll();
                  delay(150);
                  Keyboard.println("rhakdnjdy!"); //고마워요!
                  break;
          case 8: Keyboard.press('t');
                  Keyboard.releaseAll();
                  delay(150);
                  Keyboard.println("aldksgody"); //미안해요
                  break;
          case 9: Keyboard.press('t');
                  Keyboard.releaseAll();
                  delay(150);
                  Keyboard.println("skan tkqslek~~"); //나무 삽니다~~
                  break;
          case 10: Keyboard.print("t");
                   Keyboard.releaseAll();
                   delay(200);
                   Keyboard.println("cnrgkemfudy!"); // 축하드려요!
                  break;
          case 11: Keyboard.press('t');
                  Keyboard.releaseAll();
                  delay(150);
                  Keyboard.println("dnfl, thxhdgody!"); //우리, 소통해요!
                  break;
          case 12: Keyboard.press('t');
                  Keyboard.releaseAll();
                  delay(150);
                  Keyboard.println("anssla... wnantuTskdy??"); //문님... 주무셨나요?
                  break;
        }
      }
      else if(mode==3 && key)
      {
        switch(key)
        {
          case 1: Keyboard.press('7'); 
                  break;
          case 2: Keyboard.press('8'); 
                  break;
          case 3: Keyboard.press('9'); 
                  break;
          case 4: Keyboard.press('4'); 
                  break;              
          case 5: Keyboard.press('5'); 
                  break;
          case 6: Keyboard.press('6'); 
                  break;
          case 7: Keyboard.press('1'); 
                  break;
          case 8: Keyboard.press('2'); 
                  break;
          case 9: Keyboard.press('3'); 
                  break;
          case 10: Keyboard.press(KEY_BACKSPACE); 
                  break;
          case 11: Keyboard.press('0'); 
                  break;
          case 12: Keyboard.press(KEY_RETURN);
                  break;
        }
      }

    }
    kchat=254;
    if(!key) digitalWrite(ledmat[tkey-1]+8,LOW);
    tkey=key;
    if(!key && mode==3)
    {
      Keyboard.releaseAll();
      for(i=9;i<=20;i++)
      {
        digitalWrite(i,LOW);
      }
    }

  }
  if(kchat && keypad()!=key) kchat--;
  if(!digitalRead(23))
    ekchat=254;
  if(ekchat && digitalRead(23))
  {
    ekchat--;
    if(!ekchat)
    {
      if(mode!=3)
      {
        digitalWrite(21,HIGH);
        digitalWrite(22,HIGH);
        mode=3;
      }
      else
      {
        digitalWrite(21,LOW);
        digitalWrite(22,HIGH);
        mode=0;
      }
    }
  }
}

#include<Servo.h>
#include "IRremote.h"

IRrecv irrecv(2); // указываем вывод, к которому подключен приемник

Servo servoVer; //Vertical Servo
Servo servoHor; //Horizontal Servo
Servo servoBoy;

decode_results results;

int x;
int y;
int prevX;
int prevY;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // запускаем прием
  
  servoVer.attach(8); //Attach Vertical Servo to Pin 5
  servoHor.attach(9); //Attach Horizontal Servo to Pin 6
  servoBoy.attach(7); 
  
  servoVer.write(90);
  servoHor.write(90);
  servoBoy.write(90);
}
void Pos()
{
  if(prevX != x || prevY != y)
  {
    /*int servoX = map(x, 600, 0, 70, 179);
    int servoY = map(y, 450, 0, 179, 95);
    servoX = min(servoX, 179);
    servoX = max(servoX, 70);
    servoY = min(servoY, 179);
    servoY = max(servoY, 95);*/

    int servoX = map(x, 0, 600, 60, 120);
    int servoY = map(y, 0, 450, 150, 60);
    
    servoHor.write(servoX);
    servoVer.write(servoY);
    
    if ( irrecv.decode( &results )) { // если данные пришли
    switch ( results.value ) {
    case 0xFF38C7:
        servoBoy.write(180);
        delay(1000);
        servoBoy.write(90);
        break;
    }    
    irrecv.resume(); // принимаем следующую команду
    }
  }
}
void loop()
{
  if(Serial.available() > 0)
  {
    if(Serial.read() == 'X')
    {
      x = Serial.parseInt();
      if(Serial.read() == 'Y')
      {
        y = Serial.parseInt();
       Pos();
      }
    }

    while(Serial.available() > 0)
    {
      Serial.read();
    }
  }
}

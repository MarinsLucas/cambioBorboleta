#include <AccelStepper.h>
#include "Wire.h"
#define MAX_SPEED 5000 //velocidade máxima do nema17: 5000rpm
#define GEAR_OFFSET 20 //20 passos = 36º (teoricamente)

AccelStepper stepper(2, 10,11); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
short upGearButton = 2; //declarando entradas de botões
short downGearButton = 4;
bool changingGear;

short gear = 0; //Marcha atual: inicialmente em 0 (neutro)

long initialPos;

void writeGear(short gear)
{
  //Essa função vai escrever a marcha atual em um display
  Serial.println(gear);
}

void setup()
{  
  //abrindo o terminal 
  Serial.begin(9600);

  //Botão 1
  pinMode(upGearButton, INPUT); // define o pino do botao como entrada
  //Botão 2
  pinMode(downGearButton, INPUT); // define o pino do botao como entrada
  
  stepper.setMaxSpeed(MAX_SPEED);
  stepper.setSpeed(MAX_SPEED);
  //stepper.setAcceleration(10000.0); //TODO: qual aceleração colocar?

  initialPos = stepper.currentPosition(); 
}

void loop()
{
    //movimenta a marcha pra trás e volta pro centro (tá certo isso)?
    if(gear == 0)
    {
      stepper.runToNewPosition(-GEAR_OFFSET);
      stepper.runToNewPosition(initialPos);
    }
    else //se a moto não estiver no neutro: faz o oposto
    {
      stepper.runToNewPosition(GEAR_OFFSET);
      stepper.runToNewPosition(initialPos);
    }
    
    Serial.println("Up Gear");    
    gear++;

    stepper.runToNewPosition(GEAR_OFFSET);
    stepper.runToNewPosition(initialPos);

    Serial.println("Down Gear");  
    gear--;

  writeGear(gear);

}

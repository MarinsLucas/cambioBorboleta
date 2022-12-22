/* Programa para testes de diferentes velocidades e acelerações */

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
int velocidade=0, acel=0;

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
  initialPos = stepper.currentPosition(); 
}

void loop()
{
  Serial.print("Digite um valor de velocidade: ");
  velocidade = Serial.parseInt();
  Serial.read();

  Serial.print("Digite um valor de aceleração: ");
  acel = Serial.parseInt();
  Serial.read();

  stepper.setMaxSpeed(velocidade);
  stepper.setAcceleration(acel);

  //Velocidade máxima
  Serial.println("Aperte em qualquer manete: ");
  while(digitalRead(upGearButton) == LOW && digitalRead(downGearButton) == LOW)
  {
    stepper.setSpeed(velocidade); 
    stepper.runSpeed();
  }

  stepper.runToNewPosition(stepper.currentPosition() + 200); 
  
  //espera um toque na manete
  Serial.println("Aperte em qualquer manete: ");
  while(digitalRead(upGearButton) == LOW && digitalRead(downGearButton) == LOW);

  stepper.runToNewPosition(stepper.currentPosition() - 200);
  
  
 /*  //UP GEAR
  if(digitalRead(upGearButton) == HIGH && gear < 5)
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
  }

  //DONW GEAR
  if(digitalRead(downGearButton) == HIGH && gear > 0)
  {
    stepper.runToNewPosition(GEAR_OFFSET);
    stepper.runToNewPosition(initialPos);

    Serial.println("Down Gear");  
    gear--;
  }

  writeGear(gear); */

}

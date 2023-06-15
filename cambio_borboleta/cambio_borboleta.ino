#include <AccelStepper.h>
#include "Wire.h"
#define MAX_SPEED 5000 //velocidade máxima do nema17: 5000rpm

AccelStepper stepper(2, 10,11); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
short upGearButton = 5; //declarando entradas de botões
short downGearButton = 4;

short maxPositionButton = 13; 
short minPositionButton = 12; 
bool changingGear;

short gear = 0; //Marcha atual: inicialmente em 0 (neutro)

long initialPos;

long elapsedTime; 

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
  pinMode(LED_BUILTIN, OUTPUT); 

  //Led acende para mostrar a inicialização
  digitalWrite(LED_BUILTIN, HIGH);
  
  //FASE 1 DA INCIALIZAÇÃO: encontrar a posição central do fuso
  initialPos = getInitialPos(); 

  //FASE 2: mover o cambio para a posição inicial
  stepper.runToNewPosition(initialPos);
  delay(2);
  stepper.setCurrentPosition(0);  
  
  digitalWrite(LED_BUILTIN, LOW);
  //Led apaga para mostrar que o sistema começou a funcionar
    
}

long getInitialPos()
{
  long maxPosition;   
  //Colocar o motor para se mover no sentindo negativo
  stepper.setSpeed(-MAX_SPEED);        

  //Motor continua se movendo até apertar o botão
  while(digitalRead(minPositionButton) == LOW)
  {
    stepper.runSpeed();
  }  
  //define a posição 0, como a posição minima
  stepper.setCurrentPosition(0);

  //Coloca o motor para se mover no sentido positivo
  stepper.setSpeed(MAX_SPEED);

  while(digitalRead(maxPositionButton) == LOW)
  {
    stepper.runSpeed();
  } 
  maxPosition = stepper.currentPosition();

  return maxPosition/2; 
}

void changeGear(int direction)
{
  //1 para direção positiva
  if(direction == 1)
  {
    stepper.setSpeed(MAX_SPEED);
    while(digitalRead(maxPositionButton) ==LOW)
    {
      stepper.runSpeed();       
    }
    stepper.runToNewPosition(0);
  }     

  //-1 para direção negativa
  if(direction == -1)  
  {
    stepper.setSpeed(-MAX_SPEED);
    while(digitalRead(minPositionButton) == HIGH)
    {
      stepper.runSpeed(); 
    }    
    stepper.runToNewPosition(0);
  }
}

void loop()
{
  //UP GEAR
  if(digitalRead(upGearButton) == HIGH)
  {
    elapsedTime = millis();
    changeGear(1);
    Serial.println("Up Gear");    
    gear++;
    writeGear(gear);
    elapsedTime = millis() - elapsedTime;
    Serial.println("Troca de marcha em: " + (String)elapsedTime + "ms");     
  }

  //DONW GEAR
  if(digitalRead(downGearButton) == HIGH && gear > 0)
  {
    elapsedTime = millis();
    changeGear(-1);
    Serial.println("Down Gear");  
    gear--;
    writeGear(gear);
    elapsedTime = millis() - elapsedTime;
    Serial.println("Troca de marcha em: " + (String) elapsedTime + "ms");     
  }

  //Comentei por enquanto, pra não ficar spamando 
  //writeGear(gear);

}

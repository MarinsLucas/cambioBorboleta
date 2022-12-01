// ConstantSpeed.pde
// -*- mode: C++ -*-
//
// Shows how to run AccelStepper in the simplest,
// fixed speed mode with no accelerations
/// \author  Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2009 Mike McCauley
// $Id: ConstantSpeed.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $

#include <AccelStepper.h>
#include "Wire.h"

AccelStepper stepper(2, 10,11); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
int pushbutton1 = 2; // declara o push button na porta 2
int pushbutton2 = 3;

void setup()
{  
  //Botão 1
   pinMode(pushbutton1, INPUT); // define o pino do botao como entrada
   pinMode(pushbutton2, INPUT); // define o pino do botao como entrada
   Serial.begin(9600);
   stepper.setMaxSpeed(3000);
   stepper.setSpeed(3000);  
}

void loop()
{ 
  
    

     
  stepper.runSpeed();
}

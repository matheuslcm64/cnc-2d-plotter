#include <AccelStepper.h>

// Pinos a serem usados (para driver de motor bipolar step/direction e corrente constante [A4988])

//Pino para o controle da direção (Sentido horário ou anti-horário)
const int dirPin = 55;
//Pino para o controle do passo do motor(Cada alternancia de 0 para 1 move ao passo definido)
const int stepPin = 54;
const int enablePin = 38;
//Instancia objeto 'AccelStepper' para o driver A4988 (Bipolar, constant current, step/direction driver)
AccelStepper myStepper(AccelStepper::DRIVER, stepPin, dirPin);

void setup()
{  
   //Limita a velocidade de rotação (O valor maximo que 'setSpeed()' pode assumir).
   myStepper.setMaxSpeed(1000);
   //pinMode(dirPin,OUTPUT);
   pinMode(enablePin,OUTPUT);
   digitalWrite(enablePin,LOW);
   pinMode(LED_BUILTIN, OUTPUT);
   //Define velocidade que será utilizada pelo motor ( 'runSpeed()' é o método 
   //responsável pela a execução do motor a velocidade definida pelo 'setSpeed()')*/
   myStepper.setSpeed(500);
}

void loop()
{  
    //digitalWrite(dirPin,0);
    //digitalWrite(stepPin,1);
   //Faz o motor rodar a velocidade definida
   myStepper.runSpeed();
   
}

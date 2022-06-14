#include <AccelStepper.h>
#include <MultiStepper.h>

// Pinos a serem usados (para driver de motor bipolar step/direction e corrente constante [A4988])

//Pino para o controle do passo do motor(Cada alternancia de 0 para 1 move ao passo definido)
const int X_stepPin = 54;
const int Y_stepPin = 60;

//Pino para o controle da direção (Sentido horário ou anti-horário)
const int X_dirPin = 55;
const int Y_dirPin = 61;

//Pino Enable especifico da RAMPS 1.4
const int X_enablePin = 38;
const int Y_enablePin = 56;

//Instancia objeto 'AccelStepper' para o driver A4988 (Bipolar, constant current, step/direction driver)
AccelStepper motorX(AccelStepper::DRIVER, X_stepPin, X_dirPin);
AccelStepper motorY(AccelStepper::DRIVER, Y_stepPin, Y_dirPin);

void setup()
{
   //Definição dos pinos enable
   pinMode(X_enablePin,OUTPUT);
   digitalWrite(X_enablePin,LOW);
   pinMode(Y_enablePin,OUTPUT);
   digitalWrite(Y_enablePin,LOW);

   pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
    quadrado();
    delay(1000);
    triangulo();
    delay(1000);
}

//Função para desenhar quadrado 
void quadrado()
{
    //Limita a velocidade de rotação passos/segundos (a aceleração não passa desse valor)
    motorX.setMaxSpeed(600); 
    motorY.setMaxSpeed(600);
    
    //Define aceleração passos/segundos^2
    motorX.setAcceleration(60);
    motorY.setAcceleration(60);
    
    //Define quantidade de passos a serem percorridos
    motorX.moveTo(1200);
    
    //motorX.runToPosition();
    //Enquanto a quantidade de passos não for alcançada o motor continua girando
    while(motorX.distanceToGo() > 0)
    {
      //Percorre um passo a cada chamada, implementando aceleração
      motorX.run();
    }
    delay(300);
    
    motorY.moveTo(1200);
    motorY.runToPosition();
    delay(300);
    motorX.moveTo(0);
    motorX.runToPosition();
    delay(300);
    motorY.moveTo(0);
    motorY.runToPosition(); 
    delay(300);   
}

//Função para desenhar triângulo 
void triangulo()
{
  //Utilizando MultiStepper para movimento simultaneo dos motores 
  MultiStepper motores;

  motorX.setMaxSpeed(600);
  motorY.setMaxSpeed(600);
  
  motores.addStepper(motorX);
  motores.addStepper(motorY);
  
  //Posições de destino do motorX e motorY respectivamente
  long posicoes[2] = {300, 600};
  
  //Definindo os destinos de cada motor e calcula a velocidade 
  //necessaria para que cada um chegue ao destino ao mesmo tempo
  motores.moveTo(posicoes);

  //Bloqueia o loop até que os motores cheguem ao destino
  motores.runSpeedToPosition();
  
  delay(1000);
  
  //Definindo novos destinos para cada motor percorrer
  posicoes[0] = 600;
  posicoes[1] = 0;
  motores.moveTo(posicoes);
  motores.runSpeedToPosition();

  delay(1000);

  motorX.moveTo(0);
  motorX.runToPosition();
  delay(300);
}

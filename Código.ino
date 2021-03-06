/*******************************************************************************

     Projeto I07 - Controlando motores DC com drive ponte H L298N
     Autor: Angelo Luis Ferreira
     Data: 01/12/20
             http://squids.com.br/arduino

*******************************************************************************/
//motor A
const byte IN1 = 13 ;
const byte IN2 = 12 ;

//motor B
const byte IN3 = 11;
const byte IN4 = 10;

//pinos utilizados para controlar a velocidade de rotacao
const int ENA = 9; // motor A
const int ENB = 3; // motor B

// controle
#define switchPin 2 // Entrada da botão que inverte a rotação
#define turnPin 8 // Entrada do botão liga e desliga o circuito
#define potPin 0 // Potenciômetro no pino analógico 0

//variáveis
int motorSpeed = 0; // armazenar o valor de velocidade atual
boolean stateSwitch = 0; // armazenar o status do switchPin (0 ou 1)
boolean stateTurn = 0; // armazenar rotação (0 ou1)

// leds
const byte ledGreen = 7;
const byte ledYellow = 6;
const byte ledRed = 5;
 
//Inicializa Pinos
void setup(){
 // define os pinos do drive como saída do Arduino
 pinMode(IN1,OUTPUT); // motor A
 pinMode(IN2,OUTPUT); // motor A
 pinMode(IN3,OUTPUT); // motor B
 pinMode(IN4,OUTPUT); // motor B
 pinMode(ENA,OUTPUT); // controle velocidade motor A
 pinMode(ENB,OUTPUT); // controle velocidade motor B
 // define pinos dos leds como saída
 pinMode(ledGreen, OUTPUT);
 pinMode(ledYellow, OUTPUT); 
 pinMode(ledRed, OUTPUT);
 // defini botões como entrada (pullup interno)
 pinMode(switchPin, INPUT_PULLUP);
 pinMode(turnPin, INPUT_PULLUP);

 // inicia com os motores desligados
 digitalWrite(IN1,LOW);
 digitalWrite(IN2,LOW);
 digitalWrite(IN3, LOW);
 digitalWrite(IN4,LOW);
}
 
void loop() {
  turnOnOff();
  if (stateTurn) {
    // velocidade a partir do potenciômetro (0 a 255)
    motorSpeed = analogRead(potPin)/4;
    // verifica se os botões foram acionados--------------------------------------------------------------------------
    turnLed(motorSpeed);
    turnRotation();

    if(stateSwitch) {
      // gira no sentido anti-horário
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4,HIGH);
    } else {
      // gira no sentido horário
      digitalWrite(IN1,HIGH);
      digitalWrite(IN2,LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4,LOW);
    }

    // define a velocidade 
    analogWrite(ENA, motorSpeed);
    analogWrite(ENB, motorSpeed);
        
  } else {    
    // deslig os motores 
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4,LOW);    
  } 
  
}

// controle para ligar e desligar motores
void turnOnOff() {
  if (!digitalRead(turnPin)) { // verifica se o botão foi acionado
    stateTurn = !stateTurn;
    while(!digitalRead(turnPin)) {}
    delay(50);
  }
}

// controle sentido de rotação
void turnRotation() {
  if (!digitalRead(switchPin)) { // verifica se o botão foi acionado
    stateSwitch = !stateSwitch;
    while(!digitalRead(switchPin)) {}
    delay(50);
  }
}

// controle para acender leds de acordo com a velocidade
void turnLed(byte j) {
  turnOffLeds();
  if (j<=+85) {    
    digitalWrite(ledGreen, HIGH);
  } else if ((85< j) && (j<= 170)) {
     digitalWrite(ledYellow, HIGH);
  } else if (j>=170) {
    digitalWrite(ledRed, HIGH);
  }
}

// apaga todos leds
void turnOffLeds() {
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledRed, LOW);
    digitalWrite(ledYellow, LOW);
}

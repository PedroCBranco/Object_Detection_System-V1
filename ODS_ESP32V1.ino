#include <ESP32Servo.h>              //Importar biblioteca do servo ESP32,n confundir com <servo.h> (arduino)

Servo Servo1;
int Sensor_enviado = 25;
int Sensor_ECHO = 32;
int LED_Azul = 5;
int LED_Vermelho= 19;
long tempo_passado=0;
int joystick=34;                                 //Definir o servo e as variaveis globais
int pinoBotao = 33;
bool LEDS_ligado=false;

bool modoManual = false;
bool estadoBotaoAnterior = HIGH;            

void setup() {
  Serial.begin(9600);
  Servo1.attach(13);                                         //Estabelecer o que é input e output e o pino do servo
  pinMode(Sensor_enviado, OUTPUT);
  pinMode(Sensor_ECHO, INPUT);
  pinMode(LED_Azul, OUTPUT);
  pinMode(LED_Vermelho , OUTPUT);
  pinMode(pinoBotao, INPUT_PULLUP);                 //Aqui usamos pullup porque é um botao, pra evitar um estado de "antena" onde o botao capta ruido quando nao pressionado
}

void loop() {
  int leituraBotao = digitalRead(pinoBotao);

  if (leituraBotao == LOW && estadoBotaoAnterior == HIGH) {          //Se nao clicarmos, nao acontece nada(modo automatico)
    modoManual = !modoManual;
    delay(300);
  }
  estadoBotaoAnterior = leituraBotao;

  if (modoManual == true) {
    int valorLido = analogRead(joystick);                           //Se clicarmos no botao lemos o valor do joystick e movemos o servo pra essa posiçao
    int angulo = map(valorLido, 0, 4095, 0, 180);
    Servo1.write(angulo);
    delay(15);
    SinalSensor();                                                 
  } 
  else {
    for(int pos=0; pos<=180; pos+=1){
      if(digitalRead(pinoBotao) == LOW) {                        //Definiçao do modo automatico do servo, modo varredura
        modoManual = true;
        delay(300);
        break;
      }
      Servo1.write(pos);
      delay(15); 
      SinalSensor(); 
    }

    for(int pos=180; pos>=0; pos-=1){
      if(digitalRead(pinoBotao) == LOW) {
        modoManual = true;
        delay(300);
        break;
      }
      Servo1.write(pos);
      delay(15); 
      SinalSensor(); 
    }
  }
}

void SinalSensor() {                                        //Defenir a funçao do sensor, sensor a low, espera 2 micro envia sinal, espera 10 micro, vai a low e repete dentro dos loops
  digitalWrite(Sensor_enviado, LOW);
  delayMicroseconds(2);
  digitalWrite(Sensor_enviado, HIGH);
  delayMicroseconds(10);
  digitalWrite(Sensor_enviado, LOW);

  long duracao=pulseIn(Sensor_ECHO, HIGH, 3000);              //Determina quanto tempo espera pelo sinal q enviou, quanto tempo espera pra "ouvir"

  if (duracao > 0 && duracao < 2000 && LEDS_ligado==false){
    Serial.println("Objeto detetado");
    digitalWrite(LED_Azul, HIGH);                                            //Se as leds tiverem apagadas e a duraçao indicar um objeto a pouca distancia=>ligar as leds
    digitalWrite(LED_Vermelho, HIGH);
    tempo_passado=millis();                                               //Usamos millis() pra começar a contar o tempo em q ligamos as LEDS, e pra evitar 
    LEDS_ligado=true;                                                     //que o servo páre ou seja ruidoso quando deteta algo(como seria no delay())
  }
  if (LEDS_ligado==true){
    if (millis()-tempo_passado>=20){                                        //Se os leds tiverem ligados e a diferenaç entre o tempo passado e a contagem for maior q X, desligar as Leds
      digitalWrite(LED_Azul , LOW);
      digitalWrite(LED_Vermelho, LOW);
      tempo_passado=0;                                                             
      LEDS_ligado=false;
    }
  }
}
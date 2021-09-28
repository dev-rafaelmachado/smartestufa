//Bibliotecas
#include <SPI.h>
#include <Ethernet.h>
#include "DHT.h"
#include "Wire.h"

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 0, 175 };
byte gateway[] = {192, 168, 1, 254};
byte subnet[] = {255, 255, 255, 0};

byte servidor[] = {192, 168, 1, 64};


#define COMMON_ANODE
#define DHTPIN A1
#define DHTTYPE DHT11
#define portaHTTP 80
EthernetClient clienteArduino;
DHT dht(DHTPIN, DHTTYPE);

//Variáveis
int rele1 = 7;
int rele2 = 6;
int rele3 = 5;
int rele4 = 8;
int rele5 = 12;
int SHv;
int SH = A0;
int led1 = 7;
int led2 = 6;
int led3 = 5;
int led4 = 4;
int Bt = 3;
int LuzR = 9;
int LuzB = 10;
int estadoLed = 0;

int TmpLt = 21; //Temperatura Limite para a planta
int TmpMn = 15; //Temperatura Mínima para a planta
int UmiMin = 5; //


void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac, ip, gateway, subnet);

  if (Ethernet.begin(mac) == 0) {
    Serial.println("Falha ao se conctar a rede ");
  } else {
    Serial.print("Conectado a rede ");
  }
  Serial.print(Ethernet.localIP());


  Serial.println("DHTxx test!");

  pinMode(rele1, OUTPUT);
  pinMode(rele2, OUTPUT);
  pinMode(rele3, OUTPUT);
  pinMode(rele4, OUTPUT);
  pinMode(rele5, OUTPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(LuzR, OUTPUT);
  pinMode(LuzB, OUTPUT);
  pinMode(Bt, INPUT_PULLUP);

  dht.begin();
}

void loop() {

  if (clienteArduino.available()) {
    char dadosRetornados = clienteArduino.read();
    Serial.print(dadosRetornados);
  }

  if (!clienteArduino.connected()) {
    clienteArduino.stop();
  }



  //Leitura do sensor de Umidade do Solo e conversão para porcentage,
  SHv = analogRead(SH);
  int UmidS = map(SHv, 1023, 0, 0, 100);

  // Leitura do sensor de temperatura do Ar e Umidade do Ar
  float temp = dht.readTemperature();
  float h = dht.readHumidity();

  //             Monitor Serial             //
  //----------------------------------------//
  Serial.print("UmidadeAr: ");
  Serial.print(h);
  Serial.print("%");
  Serial.print("        Temperatura: ");
  Serial.print(temp);
  Serial.print(" *C      ");
  Serial.print("UmidadeSolo:  ");
  Serial.print(UmidS);
  Serial.println("%");
  //----------------------------------------//


  // Ligar led no Botão
  if (digitalRead(Bt) == LOW) {
    estadoLed = !estadoLed;

    digitalWrite(4, estadoLed);
    while (digitalRead(Bt) == LOW);
    delay(100);
  }


  if (clienteArduino.connect(servidor, portaHTTP)) {
    clienteArduino.print("GET /SmartEstufa/salvar.php?temp=");
    clienteArduino.print(temp);
    clienteArduino.print("&UmidS=");
    clienteArduino.print(UmidS);
    clienteArduino.print("&h=");
    clienteArduino.println(h);

  } else {
    Serial.println("Falha ao se conectar com o Banco");
  }

   //                  Casos                 //
  //----------------------------------------//
  if (temp >= TmpLt) {
    //Ligar Exaustor
      digitalWrite(rele1, LOW);
  } else {
    //Desligar Exaustor
      digitalWrite(rele1, HIGH);
  }
  if (temp <= TmpMn) {
    // Ligar Peltir + Fan 1 e 2
      digitalWrite(rele2, LOW);
      
      digitalWrite(rele3, LOW);
  } else {
    // Desligar Peltier + Fan 1 e 2
      digitalWrite(rele2, HIGH);
      digitalWrite(rele3, HIGH);
  } if (UmidS < UmiMin) { 
    //Abrir a corrente de água
  } else {
    // Fechar a corrente de água
  }

  delay(1000);



}

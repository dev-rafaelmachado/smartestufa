#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 0, 175 }; 
byte gateway[] = {192, 168, 1, 254}; 
byte subnet[] = {255, 255, 255, 0}; 

byte servidor[] = {192, 168, 1, 64};

#define portaHTTP 80
EthernetClient clienteArduino;

void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac, ip, gateway, subnet);

  if (Ethernet.begin(mac) == 0) {
    Serial.println("Falha ao se conctar a rede ");
  } else {
    Serial.print("Conectado a rede ");
  }



  Serial.print(Ethernet.localIP());
}


void loop() {
  if (clienteArduino.available()) {
    char dadosRetornados = clienteArduino.read();
    Serial.print(dadosRetornados);
  }


  if (!clienteArduino.connected()) {
    clienteArduino.stop();
  }

  int Valorteste = 1;

  if (clienteArduino.connect(servidor, portaHTTP)) {
    clienteArduino.print("GET /SmartEstufa/salvar.php?");
    clienteArduino.print("Valorteste=");
    clienteArduino.println(Valorteste);
  } else {
    Serial.println("Falha ao se conectar com o Banco");
  }

  delay(100000);



}

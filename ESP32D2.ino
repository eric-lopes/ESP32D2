//Bibliotecas Utilizadas
#include <WiFi.h>
#include <SD.h>
#include <SPI.h>
#include <ESP32WebServer.h>
#include "AUDIO.h"
#include "REDE.h"
#include "SERVER.h"
//#include "DEV.h"

//Cria as Tasks para usar o dual core
TaskHandle_t server;

//SETUP
void setup() {
  pinMode(R,OUTPUT);
  pinMode(G,OUTPUT);
  pinMode(B,OUTPUT);
  lamp(0);
  delay(1250);
  audio.setPinout(26,25,22);
  dht.begin();
  delay(1250);
  if(SD.begin()){
    for(int i=0;i<3;i++) {
      lamp(2);
      delay(100);
      lamp(0);
      delay(100);
    }
    artoo(SD);
    int aux=0;
    int r=random(0,16);
    aux=musica[r].length()+1;
    char music[aux];
    musica[r].toCharArray(music,aux);
    audio.connecttoSD(music);
    netread(SD);
  }
  else{
    for(int i=0;i<3;i++) {
      lamp(1);
      delay(100);
      lamp(0);
      delay(100);
    }
  }
  netstart();
  //Parâmetros: (Função executada, nome do Task, Tamanho da Pilha, Parâmetros da Tarefa, Prioridade, TaskHandler criado, core)
  xTaskCreatePinnedToCore(servercode, "Server", 10000, NULL, 1, &server, 0);
  //Funções do Servidor
  web.on("/", server_main);
  web.on("/lamp", lamps);
  web.on("/net",  newnet);
  web.begin();

}

//Código para ser usado no Task Player
void servercode( void * pvParameters ) {
  while(true) {
    web.handleClient();
    delay(100);
  }
}

void loop() {
  audio.loop();
  audio.setVolume(volume); 
}

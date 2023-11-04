//Bibliotecas Utilizadas
#include <WiFi.h>
#include <FS.h>
#include <SD.h>
#include <SPI.h>
#include <ESP32WebServer.h>
#include "AUDIO.h"
#include "REDE.h"
#include "SERVER.h"
#include "DEV.h"

//Cria as Tasks para usar o dual core
TaskHandle_t server;

//SETUP
void setup() {
  delay(1000);
  pinMode(R,OUTPUT);
  pinMode(G,OUTPUT);
  pinMode(B,OUTPUT);
  lamp(0);
  delay(1000);
  Serial.begin(115200);
  delay(1000);
  audio.setPinout(26,25,22);
  dht.begin();
  delay(1000);
  if(SD.begin()){
    for(int i=0;i<3;i++) {
      lamp(2);
      delay(100);
      lamp(0);
      delay(100);
    }
    audio.connecttoSD("/R2D2/Processando.mp3");
    netread(SD);
    sdstat=true;
  }
  else{
    Serial.println("CARTÃO AUSENTE");
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
  web.on("/music", lsmusic);
  web.on("/lamp",  lamps);
  web.on("/net",  HTTP_POST,[](){ web.send(200);}, netupload);
  web.begin();
}

//Código para ser usado no Task Player
void servercode( void * pvParameters ) {
  Serial.print("Server no core: ");
  Serial.println(xPortGetCoreID());
  delay(5000);
  pastaread(SD);
  Serial.println("PASTAS");
  for(int j=0;j<numpasta;j++) {
    Serial.println(pasta[j]);
  }
  musicaread(SD,6);
  Serial.println("PLAYLIST");
  for(int l=0;l<nummusica;l++) {
    Serial.println(musica[l]);
  }
  audio_eof_mp3("Playlist");
  while(true) {
    web.handleClient();
    //lamp(8);
    delay(300);
  }
}

void loop() {
  audio.loop();
  audio.setVolume(volume); 
}

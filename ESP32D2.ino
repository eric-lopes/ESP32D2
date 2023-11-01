//Bibliotecas Utilizadas
#include <WiFi.h>
#include <FS.h>
#include <SD.h>
#include <SPI.h>
#include <ESP32WebServer.h>
#include <base64.h>
#include "REDE.h"
#include "AUDIO.h"
#include "SERVER.h"
#include "DEV.h"

//Cria as Tasks para usar o dual core
TaskHandle_t server;
//Pinos para o LED RGB
#define R 12
#define G 14
#define B 27

//SETUP
void setup() {
  pinMode(R,OUTPUT);
  pinMode(G,OUTPUT);
  pinMode(B,OUTPUT);
  digitalWrite(R,LOW);
  digitalWrite(G,LOW);
  digitalWrite(B,LOW);
  delay(500);
  Serial.begin(115200);
  delay(500);
  audio.setPinout(26,25,22);
  audio.setVolume(15);
  //audio.forceMono(true);
  delay(500);
  if(SD.begin()){
    Serial.println("Cartão ok");
    for(int i=0;i<5;i++) {
      digitalWrite(G,HIGH);
      delay(100);
      digitalWrite(G,LOW);
      delay(100);
    }
    audio.connecttoSD("/Music/R2D2/Processando.mp3");
    numrede=netread(SD);
  }
  else{    
    Serial.println("Módulo Fodeu");
    for(int i=0;i<5;i++) {
      digitalWrite(R,HIGH);
      delay(100);
      digitalWrite(R,LOW);
      delay(100);
    }
  }
  WiFi.disconnect();
  delay(500);
  netstart();
  Serial.println(WiFi.localIP()); 
  delay(500);

  web.on("/", server_main);
  //web.on("/upload",   File_Upload);
  //web.on("/fupload",  HTTP_POST,[](){ web.send(200);}, handleFileUpload);
  web.begin();
  //Parâmetros: (Função executada, nome do Task, Tamanho da Pilha, Parâmetros da Tarefa, Prioridade, TaskHandler criado, core)
  xTaskCreatePinnedToCore(servercode, "Server", 10000, NULL, 1, &server, 0); 
  delay(500);
}

//Código para ser usado no Task Player
void servercode( void * pvParameters ) {
  Serial.print("Server no core: ");
  Serial.println(xPortGetCoreID());
  while(true) {
    web.handleClient();
    Serial.println("Server");
    delay(1000); 
  }
}

void loop() {
  audio.loop(); 
}

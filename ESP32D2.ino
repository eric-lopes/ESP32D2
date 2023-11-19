//Bibliotecas Utilizadas
#include <WiFi.h>
#include <SD.h>
#include <SPI.h>
#include <ESP32WebServer.h>
#include "AUDIO.h"
#include "SERVER.h"
//#include "DEV.h"

//Cria as Tasks para usar o dual core
TaskHandle_t server;

void allof() {
  nummusica=0;
  audio.stopSong();
  pisc=false;
  lamp(0);
}

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
  Serial.begin(115200);
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
  web.on("/timer",timeroff);
  web.on("/timeron", HTTP_POST, [](){  
    String argtempo = web.arg("tempo");
    int tempo = argtempo.toInt();
    timer.stop(timerid);
    timerid = timer.after(tempo*1000*60, allof);
    SendHTML_Header();
    webpage += "<h3>Abajur e Música desligarão em " + argtempo +" minuto(s). </h3>";
    SendHTML_Content();
    append_page_footer();
    SendHTML_Content();
    SendHTML_Stop();
  });
  web.on("/net",  newnet);
  web.on("/netnew", HTTP_POST, [](){  
    String ssid = web.arg("ssid");
    String passwd = web.arg("pass");
    SendHTML_Header();
    webpage += "<h3>Você cadastrou a rede: " + ssid + ". </h3>"; 
    webpage += "<h3>Com a senha: " + passwd + ".  </h3>"; 
    SendHTML_Content();
    netwrite(SD,ssid,passwd);
    netread(SD);
    netstart();
    append_page_footer();
    SendHTML_Content();
    SendHTML_Stop();
  });
  web.begin();
}

//Código para ser usado no Task Player
void servercode( void * pvParameters ) {
  while(true) {
    web.handleClient();
    timer.update();
    pisca(pisc);
    endpsc=millis();
    delay(100);
  }
}

void loop() {
  audio.loop();
  audio.setVolume(volume); 
}

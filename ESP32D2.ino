//Bibliotecas Utilizadas
#include <WiFi.h>
#include <SD.h>
#include <SPI.h>
#include <ESP32WebServer.h>
#include "AUDIO.h"
#include "SERVER.h"

//Cria a Task para usar o dual core
TaskHandle_t server;

//Função que desliga o som e o abajur
void allof() {
  nummusica=0;
  audio.stopSong();
  pisc=false;
  lamp(0);
  delay(1000);
  int aux=0;
  int r=random(0,16);
  aux=R2D2[r].length()+1;
  char rtwo[aux];
  R2D2[r].toCharArray(rtwo,aux);
  audio.connecttoSD(rtwo);
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
    aux=R2D2[r].length()+1;
    char music[aux];
    R2D2[r].toCharArray(music,aux);
    audio.connecttoSD(music);
    netread(SD);
    pastaread(SD);
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
  web.on("/", index_html);
  web.on("/abajur", abajur_html);
  web.on("/timer",timer_html);
  web.on("/timeron", HTTP_POST, [](){  
    String argtempo = web.arg("tempo");
    int tempo = argtempo.toInt();
    timer.stop(0);
    timer.after(tempo*1000*60, allof);
    envia_cabeca();
    pagina_web += "<h3>Abajur e Música desligarão em " + argtempo +" minuto(s). </h3>";
    envia_html();
    envia_rodape();
  });
  web.on("/net",  net_html);
  web.on("/addnet", HTTP_POST, [](){  
    String ssid = web.arg("ssid");
    String passwd = web.arg("pass");
    envia_cabeca();
    pagina_web += "<h3>Você cadastrou a rede: " + ssid + ". </h3>"; 
    pagina_web += "<h3>Com a senha: " + passwd + ".  </h3>"; 
    envia_html();
    netwrite(SD,ssid,passwd);
    netread(SD);
    netstart();
    envia_rodape();
  });
  web.begin();
}

//Código para ser usado no Task Server (Core 0)
void servercode( void * pvParameters ) {
  while(true) {
    web.handleClient();
    timer.update();
    pisca(pisc);
    endpsc=millis();
    delay(100);
  }
}
//LOOP (Core 1)
void loop() {
  audio.loop();
  audio.setVolume(volume); 
}

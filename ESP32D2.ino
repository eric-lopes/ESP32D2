//Bibliotecas Utilizadas
//Para usar Wi-Fi
#include <WiFi.h>
//Para fazer usar o cartão micro sd
#include "FS.h"
#include "SD.h"
#include "SPI.h"
/*Conecte os pinos:
CS   = GPIO5
SCK  = GPIO18
MOSI = GPIO23
MISO = GPIO19
VCC  = V5
GND  = GND */

//Variáveis Globais
int sdstat=0;        //Status do Cartão de Memória
int numrede=0;       //Armazena o número de redes e senhas
String redes[10];    //Armazena SSIDs e Senhas das redes (Até o máximo de 5 redes e senhas)
int numpasta=0;      //Armazena o Número de Pastas com Música
String pastas[20];   //Armazena o caminho de cada pasta de música
int numplaylist=0;   //Armazena o número de músicas em uma pasta
String playlist[30]; //Armazena uma lista embaralhada de músicas de uma pasta

String teste[50];

//Funções
//Inicia o Cartão de Memória
int sdstart() {
  if(!SD.begin()){
    return -1; //Retorna -1 se houver erro
  }
  uint64_t cardSize = SD.cardSize() / (1024 * 1024); //Informa o tamanho do cartão.
  return 1;
}

//Lê o arquivo com as redes
int netread(fs::FS &fs){
  int a=0;
  File file = fs.open("/wifi.net");
  if(!file){
    return 0; //Retorna 0 se não houver o arquivo
  }
  while(file.available()){
    redes[a] = file.readStringUntil('\n'); 
    a++;
  }
  file.close();
  return a; //Retorna o número de strings lidas (deve ser par)
}

//Faz a conexão com a internet ou cria um Access Point
void netstart() {
  int stat=2;
  int net=0;
  if(numrede==0) {
    stat=0;
    Serial.println("Sem arquivo, sem rede");
  }
  else{
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(1000);
    Serial.println("Inicio do Wifi");
    int n = WiFi.scanNetworks();
    Serial.println("scan done");
    if (n == 0) {
      Serial.println("no networks found");
      stat=0;
    } 
    else {
      Serial.print(n);
      Serial.println(" networks found");
      for (int i = 0; i < n && stat!=1; ++i) {
        Serial.print("i=");
        Serial.println(i);
        Serial.println(WiFi.SSID(i));
        delay(1000);
        for(int j=0; j<numrede && stat!=1;j+=2) {
          Serial.print("j=");
          Serial.println(j);
          Serial.println(redes[j]);
          delay(500);
          if(WiFi.SSID(i)==redes[j]) {
            net=j;
            stat=1;
            Serial.println("ACHEI");
            Serial.print("stat=");
            Serial.println(stat);
            Serial.print("net=");
            Serial.println(net);
            Serial.print("SSID=");
            Serial.println(WiFi.SSID(i));
            Serial.print("REDE=");
            Serial.println(redes[net]);
          }
            else {
            Serial.println("Procurando");
            stat=0;
          }
        }
      }
    }
  } //Termina o scan da rede
  Serial.println("********************************");
  Serial.print("stat=");
  Serial.println(stat);
  Serial.print("REDE=");
  Serial.println(redes[net]);
  Serial.println(redes[net+1]);

  if(stat==0) {
    Serial.println("Iniciar AP");
  }
  else {
    Serial.println("Iniciar Client");
  }
}
//Lê as pastas na pasta Music
int pastaread(fs::FS &fs){
  int a=0;
  File music = fs.open("/Music");
  if(!music){
    return 0;
  }
  if(!music.isDirectory()){
    return -1;
  }

  File file = music.openNextFile();
  while(file){
    if(file.isDirectory()){
      pastas[a]=file.name();
      a++;
    }  
    file = music.openNextFile();
  }
  return a;
}
//Lê as músicas dentro de uma pasta
int musicaread(fs::FS &fs,int p){
    int a=0;
    File root = fs.open(pastas[p]);
    if(!root){
        return 0;
    }
    if(!root.isDirectory()){
        return -1;
    }

    File file = root.openNextFile();
    while(file){
        if(!file.isDirectory()){
            playlist[a]=file.name();
            a++;
        }
        file = root.openNextFile();
    }
  for(int b=0;b<a;b++) {
    int r=random(b,a);
    String music=playlist[b];
    playlist[b]=playlist[r];
    playlist[r]=music;
  }
  return a;
}


//Criar os dois tasks pra usar os dois núcleos


//Toca Música
void play() {
    numpasta=pastaread(SD);   
}

void websrv () {
//cria um simples web server
//liga led e apaga led
}

//Funções Transitórias

void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("File written");
    } else {
        Serial.println("Write failed");
    }
    file.close();
}

void appendFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Appending to file: %s\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("Failed to open file for appending");
        return;
    }
    if(file.print(message)){
        Serial.println("Message appended");
    } else {
        Serial.println("Append failed");
    }
    file.close();
}

void renameFile(fs::FS &fs, const char * path1, const char * path2){
    Serial.printf("Renaming file %s to %s\n", path1, path2);
    if (fs.rename(path1, path2)) {
        Serial.println("File renamed");
    } else {
        Serial.println("Rename failed");
    }
}

//SETUP
void setup() {
  Serial.begin(115200);
  delay(1000);
  sdstat=sdstart();
  if(sdstat==-1){
    Serial.println("Módulo Fodeu");
    //piscar led vermelho
  } 
  else {
    Serial.println("Cartão ok");
    //piscar led verde
    //tocar som do R2-D2
    numrede=netread(SD);
    netstart();
  }
   
}

void loop() {
  delay(2000);
  Serial.println("Working..."); 
  delay(8000);
}

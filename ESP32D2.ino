//Bibliotecas Utilizadas
//Para usar Wi-Fi
#include <WiFi.h>
//Para usar o cartão micro sd
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
int sdstat=0;               //Status do Cartão de Memória
int numrede=0;              //Armazena o número de redes e senhas
String redes[10];           //Armazena SSIDs e Senhas das redes (Até o máximo de 5 redes e senhas)
int numpasta=0;             //Armazena o Número de Pastas com Música
String pastas[20];          //Armazena o caminho de cada pasta de música
int nummusica=0;            //Armazena o número de músicas em uma pasta
String musicas[30];         //Armazena uma lista embaralhada de músicas de uma pasta
//Cria as Tasks para usar o dual core
TaskHandle_t player, server;

//Funções
//Inicia o Cartão de Memória
int sdstart() {
  if(SD.begin()){return 1;} //Retorna 1 se o cartão iniciar corretamente
  else{return 0;} //Retorna 0 se ocorrer algum erro
}

//Lê o arquivo com as redes
int netread(fs::FS &fs){
  int a=0;
  File file = fs.open("/wifi.net");
  if(!file){return 0;} //Retorna 0 se não houver o arquivo
  while(file.available()){
    redes[a] = file.readStringUntil('\n'); 
    a++;
  }
  file.close();
  return a; //Retorna o número de strings lidas (deve ser par)
}

//Faz a conexão com a internet ou cria um Access Point
void netstart() {
  int stat=0, net=0;
  //Se existir redes cadastradas, scaneia e tenta conectar
  if(numrede!=0) {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(1000);
    int n = WiFi.scanNetworks(); 
    if(n!=0) {
      for (int i = 0; i < n && stat!=1; ++i) {
        for(net=0; net<numrede && stat!=1;net+=2) {
          if(WiFi.SSID(i)==redes[net]) {
            stat=1;
            break;
          }
        }
      }
    }
  }
  if(stat==1) {
    int aux = redes[net].length()+1;
    char rede[aux];
    redes[net].toCharArray(rede,aux);
    aux = redes[net+1].length()+1;
    char senha[aux];
    redes[net+1].toCharArray(senha,aux);
    delay(500);
    WiFi.begin(rede, senha);
    Serial.println("begin");
    delay(5000);
    Serial.println("delay");
    unsigned long milistart=millis();
    unsigned long miliend=millis();
    while (WiFi.status() != WL_CONNECTED) {
      Serial.println(WiFi.status());
      delay(500);
      miliend=millis();
        if(WiFi.status()==6 || miliend-milistart>=30000) {
          stat=0;
          Serial.println("FODEU");
          break;
        }
    }
    Serial.println("CLIENT");
  }
  if(stat==0) {
    Serial.println("AP");
    WiFi.mode(WIFI_AP);
    WiFi.softAP("ESP32D2", "R2D2R2D2");
    delay(200);
    IPAddress Ip(192, 168, 5, 7);
    IPAddress NMask(255, 255, 255, 0);
    WiFi.softAPConfig(Ip, Ip, NMask);
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

//Lê as músicas dentro de uma pasta e gera uma lista embaralhada
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
            musicas[a]=file.name();
            a++;
        }
        file = root.openNextFile();
    }
  for(int b=0;b<a;b++) {
    int r=random(b,a);
    String music=musicas[b];
    musicas[b]=musicas[r];
    musicas[r]=music;
  }
  return a;
}

//Toca Música
void play() {
  int a=0;
  numpasta=pastaread(SD);
  nummusica=musicaread(SD,a);   
}

void websrv () {
//cria um simples web server
//liga led e apaga led
}

//Funções Transitórias

void cria(fs::FS &fs, const char * path){
  Serial.printf("Writing file: %s\n", path);
  File file = fs.open(path, FILE_WRITE);
  if(!file){
    Serial.println("Failed to open file for writing");
    return;
  }
  if(file.print("IOT\n")){
    Serial.println("File written");
  } 
  else {
    Serial.println("Write failed");
  }
  file.close();
  file = fs.open(path, FILE_APPEND);
  file.print("@Xapeleta171171\n");
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

void deleteFile(fs::FS &fs, const char * path){
    Serial.printf("Deleting file: %s\n", path);
    if(fs.remove(path)){
        Serial.println("File deleted");
    } else {
        Serial.println("Delete failed");
    }
}

//SETUP
void setup() {
  delay(500);
  Serial.begin(115200);
  WiFi.disconnect();
  sdstat=sdstart();
  delay(500);
  if(sdstat==0){
    Serial.println("Módulo Fodeu");
    //piscar led vermelho
  } 
  else {
    Serial.println("Cartão ok");
    //piscar led verde
    //tocar som do R2-D2
    numrede=netread(SD);
    delay(500);
    netstart();
  }
  //Parâmetros: (Função executada, nome do Taskm, Tamanho da Pilha, Parâmetros da Tarefa, Prioridade, TaskHandler criado, core)
  xTaskCreatePinnedToCore(playercode, "Player", 10000, NULL, 1, &player, 0); 
  delay(500); 
  xTaskCreatePinnedToCore(servercode, "Server", 10000, NULL, 1, &server, 1); 
  delay(500); 
}

//Código para ser usado no Task Player
void playercode( void * pvParameters ) {
  for(int i=0; i>-1; i++) {
    Serial.print("Player running on core ");
    Serial.println(xPortGetCoreID());
    delay(1000);  
  }
}

//Código para ser usado no Task Server
void servercode( void * pvParameters ){
    for(int i=0;i>-1;i++){
    Serial.print("Server running on core ");
    Serial.println(xPortGetCoreID());
    delay(500);
  }
}

void loop() {
}

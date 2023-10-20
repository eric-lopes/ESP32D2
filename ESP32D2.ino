//Bibliotecas Utilizadas
#include <WiFi.h>

//Variáveis Globais
char* rede[5];
char* senha[5];

#define obled 2

//Funções

void netread() {
//wifi.net  
}

void netsave() {
//só pra tentar escrever algo caso precise
}

void wfcnt() {
//netread
//começa com STA
//tenta conectar
//se não conectar, troca para AP
}


void ligaled() {
  digitalWrite(obled,HIGH);
}

void apagaled() {
  digitalWrite(obled,LOW);
}
void piscaled() {
  delay(1000);
  digitalWrite(obled,HIGH);
  delay(100);
  digitalWrite(obled,LOW);
}

void websrv () {
//cria um simples web server
//liga led e apaga led
}


//Criar os dois tasks pra usar os dois núcleos

//Funções Transitórias
void mkfile() {
  
}

void rmfile() {
  
}

void verifile() {
  
}

void lsdir() {
  
}

void mkdir() {
  
}

void cddir() {
  
}

void rmdir() {
  
}
void opendir() {
  
}

//SETUP
void setup() {

  Serial.begin(115200);
  Serial.setDebugOutput(true);
  WiFi.disconnect();
  delay(1000);
  WiFi.begin(rede[0], senha[0]);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  
pinMode(obled,OUTPUT);

}

void loop() {
  Serial.print("Camera Ready! Use 'http://");
  Serial.println("Iniciando");
  piscaled();
  

}

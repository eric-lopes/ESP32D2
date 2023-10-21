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
char* rede[5];
char* senha[5];
String net[5];
String pass[5];

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


void websrv () {
//cria um simples web server
//liga led e apaga led
}


//Criar os dois tasks pra usar os dois núcleos

//Funções Transitórias
void listDir(fs::FS &fs, const char * dirname){
    int count=0;
    Serial.printf("Listing directory: %s\n", dirname);

    File root = fs.open(dirname);
    if(!root){
        Serial.println("Failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        Serial.println("Not a directory");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("  SIZE: ");
            Serial.println(file.size());
            count++;
        }
        file = root.openNextFile();
    }
    Serial.print(" Arquivos: ");
    Serial.println(count);
}

int lendir(fs::FS &fs, const char * dirname){
  int count=0;
  File root = fs.open(dirname);
  if(!root){
    return 0;
    }
  if(!root.isDirectory()){
    return -1;
    }

  File file = root.openNextFile();
  while(file){
    if(!file.isDirectory()){
      count++;
    }
  file = root.openNextFile();
  }
  return count; 
}

void readFile(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\n", path);

    File file = fs.open(path);
    if(!file){
        Serial.println("Failed to open file for reading");
        return;
    }

    Serial.print("Read from file: ");
    while(file.available()){
        Serial.write(file.read());
    }
    file.close();
}

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

  /*Serial.begin(115200);
  Serial.setDebugOutput(true);
  WiFi.disconnect();
  delay(1000);
  WiFi.begin(rede[0], senha[0]);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }*/

Serial.begin(115200);
    if(!SD.begin()){
        Serial.println("Card Mount Failed");
        return;
    }
    uint8_t cardType = SD.cardType();

    if(cardType == CARD_NONE){
        Serial.println("No SD card attached");
        return;
    }

    Serial.print("SD Card Type: ");
    if(cardType == CARD_MMC){
        Serial.println("MMC");
    } else if(cardType == CARD_SD){
        Serial.println("SDSC");
    } else if(cardType == CARD_SDHC){
        Serial.println("SDHC");
    } else {
        Serial.println("UNKNOWN");
    }

    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    Serial.printf("SD Card Size: %lluMB\n", cardSize);

}

void loop() {
 readFile(SD, "/hello.txt");
 writeFile(SD, "/hello.txt", "Hello ");
 appendFile(SD, "/hello.txt", "World!\n");
 renameFile(SD, "/hello.txt", "/foo.txt");
 Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
 Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));
 readFile(SD,"/teste/numline");
 listDir(SD, "/R2D2");
 delay(3000);
 Serial.println();
 Serial.printf("Arquivos em R2D2: ");
 Serial.println(lendir(SD,"/R2D2")); 
 Serial.println();
 Serial.printf("Arquivos em BB8: ");
 Serial.println(lendir(SD,"/BB8")); 
 Serial.println();
 Serial.printf("Arquivos em foo.txt: ");
 Serial.println(lendir(SD,"/foo.txt"));
 Serial.println();
 Serial.println("*************************");
 Serial.println(); 
 delay(15000);

}

#include "Audio.h"

String pasta[20];          //Armazena o caminho de cada pasta de música
int numpasta=0;             //Armazena o Número de Pastas com Música
String musica[30];         //Armazena uma lista embaralhada de músicas de uma pasta
int nummusica=0;            //Armazena o número de músicas em uma pasta

Audio audio;

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
      pasta[a]=file.name();
      a++;
    }  
    file = music.openNextFile();
  }
  return a;
}

//Lê as músicas dentro de uma pasta e gera uma lista embaralhada
int musicaread(fs::FS &fs,int p){
    int a=0;
    File root = fs.open(pasta[p]);
    if(!root){
        return 0;
    }
    if(!root.isDirectory()){
        return -1;
    }

    File file = root.openNextFile();
    while(file){
        if(!file.isDirectory()){
            musica[a]=file.name();
            a++;
        }
        file = root.openNextFile();
    }
  for(int b=0;b<a;b++) {
    int r=random(b,a);
    String music=musica[b];
    musica[b]=musica[r];
    musica[r]=music;
  }
  return a;
}

void audio_eof_mp3(const char *info){  //end of file
    Serial.print("audio_info: "); Serial.println(info);
    static int i=-1;
    if(i==-1) {
      audio.connecttoSD("/Music/mudo.mp3");
      Serial.println("Música Null");
      i++;
      return;
    }
    if(i<nummusica) {
      delay(1000);
      int aux=0;
      aux=musica[i].length()+1;
      char music[aux];
      musica[i].toCharArray(music,aux);
      Serial.print("Música: ");
      Serial.println(i);
      audio.setVolume(15);
      audio.connecttoSD(music);
      i++;
      
    }
    if(i==nummusica) {
      Serial.println(i);
      audio.stopSong();
      i=0;
      Serial.println(i);
    }
}

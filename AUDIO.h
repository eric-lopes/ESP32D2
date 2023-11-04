#include "Audio.h"

String pasta[20];          //Armazena o caminho de cada pasta de música
int numpasta=0;             //Armazena o Número de Pastas com Música
String musica[50];         //Armazena uma lista embaralhada de músicas de uma pasta
int nummusica=0;            //Armazena o número de músicas em uma pasta

Audio audio;

//Lê as pastas na pasta Music
void pastaread(fs::FS &fs){
  numpasta=0;
  File music = fs.open("/Music");
  File file = music.openNextFile();
  while(file){
    if(file.isDirectory()){
      pasta[numpasta]= "/Music/"; 
      pasta[numpasta].concat(file.name());
      numpasta++;
    }  
    file = music.openNextFile();
  }
}

//Lê as músicas dentro de uma pasta e gera uma lista embaralhada
void musicaread(fs::FS &fs,int p){
  nummusica=0;
  File root = fs.open(pasta[p]);
  File file = root.openNextFile();
  Serial.println("LEITURA DAS MUSICAS");
  while(file){
    if(!file.isDirectory()){
      musica[nummusica]=pasta[p];
      musica[nummusica].concat("/");
      musica[nummusica].concat(file.name());
      Serial.println(musica[nummusica]);
      nummusica++;
    }
    file = root.openNextFile();
  }
  for(int b=0;b<nummusica;b++) {
    int r=random(b,nummusica);
    String music;
    music=musica[b];
    musica[b]=musica[r];
    musica[r]=music;
  }
}

void audio_eof_mp3(const char *info){
    static int i=0;
    if(i==nummusica) {
      Serial.println(i);
      audio.stopSong();
      i=0;
      Serial.println(i);
    }
    if(i<nummusica) {
      Serial.println("Ínicio Player");
      int aux=0;
      aux=musica[i].length()+1;
      char music[aux];
      musica[i].toCharArray(music,aux);
      Serial.println(music);
      Serial.print("Música: ");
      Serial.println(i);
      audio.connecttoSD(music);
      i++;
      
    }

}

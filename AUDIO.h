#include "Audio.h"

String pasta[20];           //Armazena o caminho de cada pasta de música
int numpasta=0;             //Armazena o Número de Pastas com Música
String musica[50];          //Armazena uma lista embaralhada de músicas de uma pasta
String playlist[50];
int nummusica=0;            //Armazena o número de músicas em uma pasta

Audio audio;
int play=0;

//Lê as pastas na pasta Music
void pastaread(fs::FS &fs){
  numpasta=0;
  File music = fs.open("/Music");
  File file = music.openNextFile();
  while(file){
    if(file.isDirectory()){
      pasta[numpasta]=file.name();
      numpasta++;
    }  
    file = music.openNextFile();
  }
}

//Lê as músicas dentro de uma pasta e gera uma lista embaralhada
void musicaread(fs::FS &fs,int p){
  play=0;
  nummusica=0;
  String path="/Music/";
  path.concat(pasta[p]);
  File root = fs.open(path);
  File file = root.openNextFile();
  while(file){
    if(!file.isDirectory()){
      musica[nummusica]=path;
      musica[nummusica].concat("/");
      musica[nummusica].concat(file.name());
      playlist[nummusica]=file.name();
      nummusica++;
    }
    file = root.openNextFile();
  }
  for(int b=0;b<nummusica;b++) {
    int r=random(b,nummusica);
    String music;
    String playlst;
    music=musica[b];
    playlst=playlist[b];
    musica[b]=musica[r];
    playlist[b]=playlist[r];
    musica[r]=music;
    playlist[r]=playlst;
  }
}

void artoo(fs::FS &fs) {
  File root = fs.open("/R2D2");
  File file = root.openNextFile();
  int count=0;
  while(file){
    if(!file.isDirectory()){
      musica[count]="/R2D2/";
      musica[count].concat(file.name());
      count++;
    }
    file = root.openNextFile();
  }
  
}

void audio_eof_mp3(const char *info){
  if(play<nummusica) {
    int aux=0;
    aux=musica[play].length()+1;
    char music[aux];
    musica[play].toCharArray(music,aux);
    audio.connecttoSD(music);
    play++;
    return;
  }
  if(play==nummusica) {
    audio.stopSong();
    play=0;
    return;
  }
}

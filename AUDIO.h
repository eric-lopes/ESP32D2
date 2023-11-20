//Bibliotecas Necessárias
#include <Audio.h>        //Biblioteca que toca áudio no protocolo I2S

//Variáveis Globais
String pasta[40];       //Armazena o caminho de cada pasta de música
int numpasta=0;         //Armazena o Número de Pastas de Música
String musica[60];      //Armazena a lista embaralhada dos caminhos das músicas
String playlist[60];    //Armazena a lista embaralhada dos nomes das músicas
int nummusica=0;        //Armazena o número de músicas em uma pasta
String R2D2[17];        //Armazena o caminho de cada som do Dróide 
int play=0;             //Armazena qual música está sendo tocada no momento

//Inicializa Objetos
Audio audio;

//Lê as pastas na pasta Music
void pastaread(fs::FS &fs){
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
  play=0, nummusica=0;
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
      if(nummusica==60) {return;}
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

//Lê os áudios do Dróide na pasta R2D2
void artoo(fs::FS &fs) {
  File root = fs.open("/R2D2");
  File file = root.openNextFile();
  int count=0;
  while(file){
    if(!file.isDirectory()){
      R2D2[count]="/R2D2/";
      R2D2[count].concat(file.name());
      count++;
    }
    file = root.openNextFile();
  }
}

//Função que é executada ao final de cada mp3
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

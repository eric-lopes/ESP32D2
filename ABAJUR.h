//Define os GPIO Pins do LED
const int R=12;  //Vermelho
const int G=14;  //Verde
const int B=27;  //Azul

//Variáveis Globais
bool pisc=false;					           //Define se irá ou não "piscar" o led
unsigned long startpsc=0,endpsc=0;   //Millis para troca de cor ao "piscar"

//Acende ou apaga o led com uma cor específica
void lamp(int lampstat) {
  switch(lampstat){
  case 0: //Desliga
    digitalWrite(R,LOW);
    digitalWrite(G,LOW);
    digitalWrite(B,LOW);
    break;
  case 1: //Vermelho
    digitalWrite(R,HIGH);
    digitalWrite(G,LOW);
    digitalWrite(B,LOW);
    break;
  case 2: //Verde
    digitalWrite(R,LOW);
    digitalWrite(G,HIGH);
    digitalWrite(B,LOW);
    break;
  case 3: //Azul
    digitalWrite(R,LOW);
    digitalWrite(G,LOW);
    digitalWrite(B,HIGH);
    break;
  case 4: //Amarelo
    digitalWrite(R,HIGH);
    digitalWrite(G,HIGH);
    digitalWrite(B,LOW);
    break;
  case 5: //Ciano
    digitalWrite(R,LOW);
    digitalWrite(G,HIGH);
    digitalWrite(B,HIGH);
    break;
  case 6: //Roxo (Magenta)
    digitalWrite(R,HIGH);
    digitalWrite(G,LOW);
    digitalWrite(B,HIGH);
    break;
  case 7: //Branco
    digitalWrite(R,HIGH);
    digitalWrite(G,HIGH);
    digitalWrite(B,HIGH);
    break;
  }
}

//"Pisca" o led com cores aleatórias
void pisca (bool pisc) {
  if(pisc==true) {
    static int a=6;
    lamp(a);
    if(endpsc-startpsc>400){
      startpsc=endpsc;
      a=random(1,7);
    }
  }
}

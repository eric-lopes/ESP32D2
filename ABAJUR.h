//Controla o LED RGB

const int R=12;
const int G=14;
const int B=27;
bool pisc=false;
unsigned long startpsc=0,endpsc=0;

void lamp(int lampstat) {
  switch(lampstat){
  case 0:
    digitalWrite(R,LOW);
    digitalWrite(G,LOW);
    digitalWrite(B,LOW);
    break;
  case 1:
    digitalWrite(R,HIGH);
    digitalWrite(G,LOW);
    digitalWrite(B,LOW);
    break;
  case 2:
    digitalWrite(R,LOW);
    digitalWrite(G,HIGH);
    digitalWrite(B,LOW);
    break;
  case 3:
    digitalWrite(R,LOW);
    digitalWrite(G,LOW);
    digitalWrite(B,HIGH);
    break;
  case 4:
    digitalWrite(R,HIGH);
    digitalWrite(G,HIGH);
    digitalWrite(B,LOW);
    break;
  case 5:
    digitalWrite(R,HIGH);
    digitalWrite(G,LOW);
    digitalWrite(B,HIGH);
    break;
  case 6:
    digitalWrite(R,LOW);
    digitalWrite(G,HIGH);
    digitalWrite(B,HIGH);
    break;
  case 7:
    digitalWrite(R,HIGH);
    digitalWrite(G,HIGH);
    digitalWrite(B,HIGH);
    break;
  }
}

void pisca (bool pisc) {
  if(pisc==true) {
    static int a=5;
    lamp(a);
    if(endpsc-startpsc>400){
      startpsc=endpsc;
      a=random(1,7);
    }
  }
}

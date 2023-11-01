String redes[10];           //Armazena SSIDs e Senhas das redes (Até o máximo de 5 redes e senhas)
int numrede=0;
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
  WiFi.mode(WIFI_AP_STA);
  //Se existir redes cadastradas, scaneia e tenta conectar
  if(numrede!=0) {
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
    WiFi.begin(rede, senha);
    delay(5000);
    unsigned long milistart=millis(), miliend=millis();
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      miliend=millis();
      if(WiFi.status()==6 || miliend-milistart>=30000) {
        break;
      }
    }
    for(int i=0;i<3;i++) {
      digitalWrite(27,HIGH);
      delay(100);
      digitalWrite(27,LOW);
      delay(100);
    }
  }  
  WiFi.softAP("ESP32D2", "R2D2R2D2");
  delay(200);
  IPAddress Ip(192, 168, 5, 7);
  IPAddress NMask(255, 255, 255, 0);
  WiFi.softAPConfig(Ip, Ip, NMask);
  for(int i=0;i<3;i++) {
    digitalWrite(27,HIGH);
    delay(100);
    digitalWrite(27,LOW);
    delay(100);
  }
}
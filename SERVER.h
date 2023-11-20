//Bibliotecas Necessárias
#include <DHT.h>
#include <Timer.h>
#include "REDE.h"

//Inicializa os objetos
ESP32WebServer web(80);
DHT dht(33, DHT11);
Timer timer;

//Variáveis Globais
int volume=11;
float umi,temp,sens;
String pagina_web,cmd,umid,tempt,senst;

//Função que lê o sensor DHT11
void dht_read() {
  umi = dht.readHumidity();
  umid="";
  umid.concat(umi);
  temp = dht.readTemperature();
  tempt="";
  tempt.concat(temp);
  sens = dht.computeHeatIndex(temp, umi, false);
  senst="";
  senst.concat(sens);
}

//Adiciona o cabeçalho padrão à página HTML
void cabeca_html() {
  //Cabeça com estilo CSS.
  pagina_web  = F("<!DOCTYPE html><html><head>");
  pagina_web += F("<meta charset='utf-8' name='viewport' content='user-scalable=yes,initial-scale=1.0,width=device-width'>    ");
  pagina_web += F("<title>ESP32-D2</title> <style>");
  pagina_web += F("body{max-width:80%;margin:0 auto;font-family:arial;font-size:100%;}  ");
  pagina_web += F("ul{list-style-type:none;padding:0;border-radius:0em;overflow:hidden;background-color:#00008b;font-size:1em;}  ");
  pagina_web += F("li{float:left;border-radius:0em;border-right:0em solid #bbb;}");  
  pagina_web += F("li a{color:white; display: block;border-radius:0.375em;padding:0.44em 0.44em;text-decoration:none;font-size:100%}  ");
  pagina_web += F("li a:hover{background-color:#1b71a8;border-radius:0em;font-size:100%}");  
  pagina_web += F("h1{color:white;text-align:center;border-radius:0em;font-size:1.5em;padding:0.2em 0.2em;background:#00008b;}  ");
  pagina_web += F("h2{color:white;border-radius:0em;font-size:1.0em;padding:0.2em 0.2em;background:#00008b;}");
  pagina_web += F("h3{text-align:center;} ");
  pagina_web += F("table{font-family:arial,sans-serif;font-size:0.9em;border-collapse:collapse;width:94%;}");   
  pagina_web += F("th,td {border:0.06em solid #0552F7;text-align:left;padding:0.3em;border-bottom:0.06em solid 0552F7#;}   ");
  pagina_web += F("tr:nth-child(odd) {background-color:#4E84F7 ;}"); //3572F3
  pagina_web += F(".rcorners_n {border-radius:0.5em;background:#558ED5;padding:0.3em 0.3em;width:20%;color:white;font-size:75%;}  ");
  pagina_web += F(".rcorners_m {border-radius:0.5em;background:#558ED5;padding:0.3em 0.3em;width:50%;color:white;font-size:75%;}");  
  pagina_web += F(".rcorners_w {border-radius:0.5em;background:#558ED5;padding:0.3em 0.3em;width:70%;color:white;font-size:75%;}");  
  pagina_web += F(".column{float:left;width:50%;height:45%;}");  
  pagina_web += F(".row:after{content:'';display:table;clear:both;}  ");
  pagina_web += F("*{box-sizing:border-box;}");  
  pagina_web += F("a{font-size:75%;}p{font-size:75%;}</style></head>");  
  //Corpo padrão do Servidor
  pagina_web += F("<body><h1>ESP32-D2</h1>");
  //Gera o IP
  String IP = WiFi.localIP().toString();
  pagina_web += "<h2 style='text-align: center;'>Endereço IP: " + IP + "</h2>";
  //Lê  os dados do Sensor DHT11
  dht_read();
  pagina_web += "<h2> Temperatura: &ensp;&emsp;&ensp;&emsp;&ensp;" + tempt +"ºC  <br>Umidade: &emsp;&emsp;&emsp;&ensp;&ensp;&ensp;&ensp; " + umid +"% <br>Sensação Térmica:&ensp;&ensp;" + senst + "ºC</h2>";
  //Barra com os links/funções
  pagina_web += F("<hr style='color:#0552F7;'><ul>");
  pagina_web += F("<li><a href='/'>       Início </a></li>    ");  
  pagina_web += F("<li><a href='/abajur'> Abajur </a></li>   ");
  pagina_web += F("<li><a href='/timer'>  Timer  </a></li>   ");
  pagina_web += F("<li><a href='/net'>    Redes  </a></li></ul>"); 
}

//Envia qualquer conteúdo HTML para o servidor
void envia_html(){
  web.sendContent(pagina_web);
  pagina_web = "";
}

//Função para Enviar a Cabeça HTML para o Servidor
void envia_cabeca() {
  web.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate"); 
  web.sendHeader("Pragma", "no-cache"); 
  web.sendHeader("Expires", "-1"); 
  web.setContentLength(CONTENT_LENGTH_UNKNOWN); 
  web.send(200, "text/html", "");
  cabeca_html();
  envia_html();
}

//Adiciona o rodapé padrão à página HTML
void envia_rodape() {
  web.sendContent("</body></html>");
  web.sendContent("");
  pagina_web="";
  web.client().stop();
}

//Função para lidar com o pressionar dos botões no servidor
void opcao(String cmd) {
  for(int a=1;a<=numpasta;a++) {
    if(a==cmd.toInt()) {
      audio.stopSong();
      musicaread(SD,a-1);
      audio_eof_mp3("Playlist");
    }
  }
  if(cmd=="pause") {audio.pauseResume();}
  if(cmd=="stop") {nummusica=0;audio.stopSong();}
  if(cmd=="prev") {
    if(play>=2){
      audio.stopSong();
      play-=2;
      audio_eof_mp3("Playlist");
    }
  } 
  if(cmd=="next") {
    audio.stopSong();
    audio_eof_mp3("Playlist");
  }
  if(cmd=="vol+") {if(volume<21) {volume++;} }
  if(cmd=="vol-") {if(volume>0) {volume--;} }
  if(cmd=="rst") {timer.stop(0);}
  if(cmd=="off") {pisc=false;lamp(0);}
  if(cmd=="vrm") {pisc=false;lamp(1);}
  if(cmd=="vrd") {pisc=false;lamp(2);}
  if(cmd=="azl") {pisc=false;lamp(3);}
  if(cmd=="ama") {pisc=false;lamp(4);}
  if(cmd=="cia") {pisc=false;lamp(5);}
  if(cmd=="rxo") {pisc=false;lamp(6);}
  if(cmd=="bco") {pisc=false;lamp(7);}
  if(cmd=="psc") {startpsc=millis();endpsc=millis();pisc=true;}
  if(cmd=="del") {delwifi(SD);};
}

//Página principal do Servidor e Controla o MP3 Player
void index_html(){
  if(web.args()>0) {cmd = web.arg(0);opcao(cmd);}
  envia_cabeca();
  if(numpasta>0) { 
    pagina_web += F("<table align='center'>");
    pagina_web += F("<tr><th style='font-size:1.25em; width:66%; text-align: center;'>Músicas</th>");
    pagina_web += "<th style='font-size:1.25em; text-align: center;'>Volume: " + String(volume) + "</th></tr>";
    for(int i=0;i<numpasta;i++) {
      if (pagina_web.length() > 1000) {envia_html();}
      pagina_web += "<tr><td>"+pasta[i]+"</td><td>";
      pagina_web += F("<FORM action='/' method='post'>"); 
      pagina_web += F("<button style='float:right; color:#FEE4AF; width:70%; background-color: #011B50;' type='submit' name='play'"); 
      pagina_web += F("' value='"); pagina_web +=String(i+1); pagina_web +=F("'>Tocar &#9658;</button></td></tr>");
    }
    pagina_web += F("</table><hr style='width:94%'>");
  }
  envia_html();
  if(nummusica>0) {
    pagina_web += F("<table align='center'><tr><td>");
    pagina_web += F("<FORM action='/' method='post'>"); 
    pagina_web += F("<button type='submit' style='width:100%; height:50px; background-color: #37B1E7;' name='Previous'"); 
    pagina_web += F("' value='"); pagina_web +="prev"; pagina_web +=F("'>&#9668;&#9668;</button></td><td>");
    pagina_web += F("<FORM action='/' method='post'>"); 
    pagina_web += F("<button type='submit' style='width:100%; height:50px; background-color: #37B1E7;' name='Pause'"); 
    pagina_web += F("' value='"); pagina_web +="pause"; pagina_web +=F("'>&#9658;/&#10074;&#10074;</button></td><td>");
    pagina_web += F("<FORM action='/' method='post'>"); 
    pagina_web += F("<button type='submit' style='width:100%; height:50px; background-color: #37B1E7;' name='Next'"); 
    pagina_web += F("' value='"); pagina_web +="next"; pagina_web +=F("'>&#9658;&#9658;</button></td><td>");
    pagina_web += F("<FORM action='/' method='post'>"); 
    pagina_web += F("<button type='submit' style='width:100%; height:50px; background-color: #37B1E7;' name='Stop'"); 
    pagina_web += F("' value='"); pagina_web +="stop"; pagina_web +=F("'>&#9724;</button></td><td>");
    pagina_web += F("<FORM action='/' method='post'>"); 
    pagina_web += F("<button type='submit' style='width:100%; height:50px; background-color: #37B1E7;' name='Voldown'"); 
    pagina_web += F("' value='"); pagina_web +="vol-"; pagina_web +=F("'> - </button></td><td>");
    pagina_web += F("<FORM action='/' method='post'>"); 
    pagina_web += F("<button type='submit' style='width:100%; height:50px; background-color: #37B1E7;' name='Volup'"); 
    pagina_web += F("' value='"); pagina_web +="vol+"; pagina_web +=F("'> + </button></td></table>");
    pagina_web += F("<hr style='width:92%'>");
    pagina_web += F("<table style='width:90%;' align='center'>");
    pagina_web += F("<tr><th style='font-size:1.25em; text-align: center;'> </th>");
    pagina_web += "<th style='font-size:1.25em; width:98%; text-align: center;'> Playlist</th></tr>";
    envia_html();
    for(int i=0;i<nummusica;i++) {
      if (pagina_web.length() > 1000) {envia_html();}
      if (i==play-1) {pagina_web += "<tr><td style='text-align: right;'> &#8614; </td>";}
      else {pagina_web += "<tr><td> </td>";}
      pagina_web += "<td>"+playlist[i]+"</td></tr>";
    }
    pagina_web += F("</table><hr style='width:90%'>");
    envia_html();
  }  
  envia_rodape();
}

//Cria o controle para o LED RGB
void abajur_html() {
  envia_cabeca();
  pagina_web += F("<tr><td><FORM action='/' method='post'>"); 
  pagina_web += F("<button type='submit' style='color:#00FFFF; width:33%; height:75px; background-color: #FF0000;' name='Vermelho'"); 
  pagina_web += F("' value='"); pagina_web +="vrm"; pagina_web +=F("'>Vermelho</button></td><td>");
  pagina_web += F("<FORM action='/' method='post'>"); 
  pagina_web += F("<button type='submit' style='color:#FF00FF; width:33%; height:75px; background-color: #00FF00;' name='Verde'"); 
  pagina_web += F("' value='"); pagina_web +="vrd"; pagina_web +=F("'>Verde</button></td><td>");
  pagina_web += F("<FORM action='/' method='post'>"); 
  pagina_web += F("<button type='submit' style='color:#FFFF00; width:33%; height:75px; background-color: #0000FF;' name='Azul'"); 
  pagina_web += F("' value='"); pagina_web +="azl"; pagina_web +=F("'>Azul</button></td><td>");
  pagina_web += F("<FORM action='/' method='post'>"); 
  pagina_web += F("<button type='submit' style='color:#0000FF; width:33%; height:75px; background-color: #FFFF00;' name='Amarelo'"); 
  pagina_web += F("' value='"); pagina_web +="ama"; pagina_web +=F("'>Amarelo</button></td><td>");
  pagina_web += F("<FORM action='/' method='post'>"); 
  pagina_web += F("<button type='submit' style='color:#FF0000; width:33%; height:75px; background-color: #00FFFF;' name='Ciano'"); 
  pagina_web += F("' value='"); pagina_web +="cia"; pagina_web +=F("'>Ciano</button></td><td>");
  pagina_web += F("<FORM action='/' method='post'>"); 
  pagina_web += F("<button type='submit' style='color:#00FF00; width:33%; height:75px; background-color: #FF00FF;' name='Roxo'"); 
  pagina_web += F("' value='"); pagina_web +="rxo"; pagina_web +=F("'>Roxo</button></td><td>");
  pagina_web += F("<FORM action='/' method='post'>"); 
  pagina_web += F("<button type='submit' style='color:#000000; width:33%; height:75px; background-color: #FFFFFF;' name='Branco'");
  pagina_web += F("' value='"); pagina_web +="bco"; pagina_web +=F("'>Branco</button></td><td>");
  pagina_web += F("<FORM action='/' method='post'>"); 
  pagina_web += F("<button type='submit' style='color: #666666; width:33%; height:75px; background-color: #999999;' name='Pisca'"); 
  pagina_web += F("' value='"); pagina_web +="psc"; pagina_web +=F("'>Piscar</button></td><td>");
  pagina_web += F("<FORM action='/' method='post'>"); 
  pagina_web += F("<button type='submit' style='color: #FFFFFF; width:33%; height:75px; background-color: #000000;' name='Off'"); 
  pagina_web += F("' value='"); pagina_web +="off"; pagina_web +=F("'>Desliga</button></td></tr><hr>");
  envia_html();
  envia_rodape();
}

//Cria o controle para o Timer
void timer_html() {
  envia_cabeca();
  pagina_web += F("<form align='center' width=250px action='/timeron' method='POST'>");
  pagina_web += F("<label> Desligar após quantos minutos? </label>");
  pagina_web += F("<input type='number' name='tempo'>");
  pagina_web += F("<input type='submit' value='Enviar'></form>");
  pagina_web += F("<h3><FORM action='/' method='post'>"); 
  pagina_web += F("<button style='height:22px; color:#222222; width:100px; background-color: #EEEEEE;' type='submit' name='reset'"); 
  pagina_web += F("value='rst'>Parar o Timer</button></h3>");
  envia_html();
  envia_rodape();
}

//Cria o controle para adicionar uma nova rede
void net_html() {
  envia_cabeca();
  pagina_web += F("<table align='center'>");
  pagina_web += F("<tr><th style='font-size:1.25em; width:50%; text-align: center;'>SSID</th></tr>");
  int n = WiFi.scanNetworks(); 
  for(int i=0;i<n;i++) {
    if (pagina_web.length() > 1000) {envia_html();}
    pagina_web += "<tr><td>"+WiFi.SSID(i)+"</td></tr>";
  }
  pagina_web += F("</table><hr style='width:94%'>");
  pagina_web += F("<form align='center'action='/addnet' method='POST'>");
  pagina_web += F("<label for='ssid'>SSID:&ensp;&ensp;</label>");
  pagina_web += F("<input type='text' id='ssid' name='ssid'><br>");
  pagina_web += F("<label for='pass'>Senha: </label>");
  pagina_web += F("<input type='text' id='pass' name='pass'><br><br>");
  pagina_web += F("<input type='submit' value='Gravar'></form>");

  //APAGAR ESSE TRECHO. APENAS PARA TESTE
  pagina_web += F("<h3><FORM action='/' method='post'>"); 
  pagina_web += F("<button style='height:30px; color:#222222; width:100px; background-color: #AAAAAA;' type='submit' name='delete'"); 
  pagina_web += F("value='del'>Deleta wifi.net</button></h3>");
  //ATÉ AQUI
  envia_html();
  envia_rodape();
}

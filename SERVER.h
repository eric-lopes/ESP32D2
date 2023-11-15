#include <DHT.h>

ESP32WebServer web(80);
DHT dht(33, DHT11);

String webpage = "";
int volume=10;

void append_page_header() {
  webpage  = F("<!DOCTYPE html>");
  webpage += F("<html>");  
  webpage += F("<head>");
  webpage += F("<meta charset='utf-8'>");
  webpage += F("<meta name='viewport' content='user-scalable=yes,initial-scale=1.0,width=device-width'>    ");
  webpage += F("<title>ESP32-D2</title>");
  webpage += F("<style>");
  webpage += F("body{max-width:80%;margin:0 auto;font-family:arial;font-size:100%;}  ");
  webpage += F("ul{list-style-type:none;padding:0;border-radius:0em;overflow:hidden;background-color:#00008b;font-size:1em;}  ");
  webpage += F("li{float:left;border-radius:0em;border-right:0em solid #bbb;}");  
  webpage += F("li a{color:white; display: block;border-radius:0.375em;padding:0.44em 0.44em;text-decoration:none;font-size:100%}  ");
  webpage += F("li a:hover{background-color:#1b71a8;border-radius:0em;font-size:100%}");  
  webpage += F("h1{color:white;text-align:center;border-radius:0em;font-size:1.5em;padding:0.2em 0.2em;background:#00008b;}  ");
  webpage += F("h2{color:white;border-radius:0em;font-size:1.0em;padding:0.2em 0.2em;background:#00008b;}");
  webpage += F("table{font-family:arial,sans-serif;font-size:0.9em;border-collapse:collapse;width:94%;}");   
  webpage += F("th,td {border:0.06em solid #0552F7;text-align:left;padding:0.3em;border-bottom:0.06em solid 0552F7#;}   ");
  webpage += F("tr:nth-child(odd) {background-color:#4E84F7 ;}"); //3572F3
  webpage += F(".rcorners_n {border-radius:0.5em;background:#558ED5;padding:0.3em 0.3em;width:20%;color:white;font-size:75%;}  ");
  webpage += F(".rcorners_m {border-radius:0.5em;background:#558ED5;padding:0.3em 0.3em;width:50%;color:white;font-size:75%;}");  
  webpage += F(".rcorners_w {border-radius:0.5em;background:#558ED5;padding:0.3em 0.3em;width:70%;color:white;font-size:75%;}");  
  webpage += F(".column{float:left;width:50%;height:45%;}");  
  webpage += F(".row:after{content:'';display:table;clear:both;}  ");
  webpage += F("*{box-sizing:border-box;}");  
  webpage += F("a{font-size:75%;}");  
  webpage += F("p{font-size:75%;}");  
  webpage += F("</style></head>");
  webpage += F("<body>");
  webpage += F("<h1>ESP32-D2</h1>");
  char ipString[16];
  WiFi.localIP().toString().toCharArray(ipString, 16);
  webpage += "<h2 style='text-align: center;'>Endereço IP: " + String(ipString) + "</h2>";

  float umi = dht.readHumidity();
  String umid;
  umid.concat(umi);
  float temp = dht.readTemperature();
  String tempt;
  tempt.concat(temp);
  float sens = dht.computeHeatIndex(temp, umi, false);
  String senst;
  senst.concat(sens);
  webpage += "<h2> Umidade: " + umid +"% &emsp; Temperatura: " + tempt +"ºC &emsp; Sensação Térmica: " + senst + "ºC</h2>";
  webpage += F("<hr style='color:#0552F7;'>");
  webpage += F("<ul>");
  webpage += F("<li><a href='/'>Início</a></li>   ");  
  webpage += F("<li><a href='/lamp'>Abajur</a></li>   ");
  webpage += F("<li><a href='/net'>Redes</a></li>");   
  webpage += F("</ul>");
}

void append_page_footer() { 
  webpage += F("</body></html>");
}

void SendHTML_Header() {
  web.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate"); 
  web.sendHeader("Pragma", "no-cache"); 
  web.sendHeader("Expires", "-1"); 
  web.setContentLength(CONTENT_LENGTH_UNKNOWN); 
  web.send(200, "text/html", ""); //Empty content inhibits Content-length header so we have to close the socket ourselves. 
  append_page_header();
  web.sendContent(webpage);
  webpage = "";
}

void SendHTML_Content(){
  web.sendContent(webpage);
  webpage = "";
}

void SendHTML_Stop(){
  web.sendContent("");
  web.client().stop();
}

void server_main(){
  pastaread(SD);
  if(web.args()>0) { 
    String cmd = web.arg(0);
    for(int a=1;a<=numpasta;a++) {
      if(a==cmd.toInt()) {
        audio.stopSong();
        musicaread(SD,a-1);
        audio_eof_mp3("Playlist");
      }
    }
    if(cmd=="pause") {
      audio.pauseResume();
    }
    if(cmd=="stop") {
      nummusica=0;
      audio.stopSong();
    }
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
    if(cmd=="vol+") {
      if(volume<21) {
        volume++;
      }
    }
    if(cmd=="vol-") {
      if(volume>0) {
        volume--;
      }
    }
    if(cmd=="bco") {
      lamp(7);
    }
    if(cmd=="vrm") {
      lamp(1);
    }
    if(cmd=="vrd") {
      lamp(2);
    }
    if(cmd=="azl") {
      lamp(3);
    }
    if(cmd=="ama") {
      lamp(4);
     }
    if(cmd=="rxo") {
      lamp(5);
    }
    if(cmd=="cia") {
      lamp(6);
    }
    if(cmd=="off") {
      lamp(0);
    }
  }
  SendHTML_Header();
  if(numpasta>0) { 
    webpage += F("<table align='center'>");
    webpage += F("<tr><th style='font-size:1.25em; width:66%; text-align: center;'>Músicas</th>");
    webpage += "<th style='font-size:1.25em; text-align: center;'>Volume: " + String(volume) + "</th></tr>";
    for(int i=0;i<numpasta;i++) {
      if (webpage.length() > 1000) {
        SendHTML_Content();
      }
      webpage += "<tr><td>"+pasta[i]+"</td><td>";
      webpage += F("<FORM action='/' method='post'>"); 
      webpage += F("<button style='float:right; color:#FEE4AF; width:70%; background-color: #011B50;' type='submit' name='play'"); 
      webpage += F("' value='"); webpage +=String(i+1); webpage +=F("'>Tocar &#9658;</button></td></tr>");
    }
    webpage += F("</table>");
    webpage += F("<hr style='width:94%'>");
  }
  SendHTML_Content();
  if(nummusica>0) {
    webpage += F("<table align='center'><tr><td>");
    webpage += F("<FORM action='/' method='post'>"); 
    webpage += F("<button type='submit' style='width:100%; height:50px; background-color: #37B1E7;' name='Previous'"); 
    webpage += F("' value='"); webpage +="prev"; webpage +=F("'>&#9668;&#9668;</button></td><td>");
    webpage += F("<FORM action='/' method='post'>"); 
    webpage += F("<button type='submit' style='width:100%; height:50px; background-color: #37B1E7;' name='Pause'"); 
    webpage += F("' value='"); webpage +="pause"; webpage +=F("'>&#9658;/&#10074;&#10074;</button></td><td>");
    webpage += F("<FORM action='/' method='post'>"); 
    webpage += F("<button type='submit' style='width:100%; height:50px; background-color: #37B1E7;' name='Next'"); 
    webpage += F("' value='"); webpage +="next"; webpage +=F("'>&#9658;&#9658;</button></td><td>");
    webpage += F("<FORM action='/' method='post'>"); 
    webpage += F("<button type='submit' style='width:100%; height:50px; background-color: #37B1E7;' name='Stop'"); 
    webpage += F("' value='"); webpage +="stop"; webpage +=F("'>&#9724;</button></td><td>");
    webpage += F("<FORM action='/' method='post'>"); 
    webpage += F("<button type='submit' style='width:100%; height:50px; background-color: #37B1E7;' name='Voldown'"); 
    webpage += F("' value='"); webpage +="vol-"; webpage +=F("'> - </button></td><td>");
    webpage += F("<FORM action='/' method='post'>"); 
    webpage += F("<button type='submit' style='width:100%; height:50px; background-color: #37B1E7;' name='Volup'"); 
    webpage += F("' value='"); webpage +="vol+"; webpage +=F("'> + </button></td></table>");
    webpage += F("<hr style='width:92%'>");
    webpage += F("<table style='width:90%;' align='center'>");
    webpage += F("<tr><th style='font-size:1.25em; text-align: center;'> </th>");
    webpage += "<th style='font-size:1.25em; width:98%; text-align: center;'> Playlist</th></tr>";
    for(int i=0;i<nummusica;i++) {
      if (webpage.length() > 1000) {
        SendHTML_Content();
      }
      if (i==play-1) { 
        webpage += "<tr><td style='text-align: right;'>   &#8614; </td>";
      }
      else {
        webpage += "<tr><td> </td>";
      }
      webpage += "<td>"+playlist[i]+"</td></tr>";
    }
    webpage += F("</table>");
    webpage += F("<hr style='width:90%'>");
    SendHTML_Content();
  }  
  append_page_footer();
  SendHTML_Content();
  SendHTML_Stop();   //Stop is needed because no content length was sent
}

void lamps() {
  SendHTML_Header();
  webpage += "<tr><td>";
  webpage += F("<FORM action='/' method='post'>"); 
  webpage += F("<button type='submit' style='color:#000000; width:25%; height:75px; background-color: #FFFFFF;' name='Branco'"); 
  webpage += F("' value='"); webpage +="bco"; webpage +=F("'>Branco</button></td><td>");
  webpage += F("<FORM action='/' method='post'>"); 
  webpage += F("<button type='submit' style='color:#00FFFF; width:25%; height:75px; background-color: #FF0000;' name='Vermelho'"); 
  webpage += F("' value='"); webpage +="vrm"; webpage +=F("'>Vermelho</button></td><td>");
  webpage += F("<FORM action='/' method='post'>"); 
  webpage += F("<button type='submit' style='color:#FF00FF; width:25%; height:75px; background-color: #00FF00;' name='Verde'"); 
  webpage += F("' value='"); webpage +="vrd"; webpage +=F("'>Verde</button></td><td>");
  webpage += F("<FORM action='/' method='post'>"); 
  webpage += F("<button type='submit' style='color:#FFFF00; width:25%; height:75px; background-color: #0000FF;' name='Azul'"); 
  webpage += F("' value='"); webpage +="azl"; webpage +=F("'>Azul</button></td><td>");
  webpage += F("<FORM action='/' method='post'>"); 
  webpage += F("<button type='submit' style='color:#0000FF; width:25%; height:75px; background-color: #FFFF00;' name='Amarelo'"); 
  webpage += F("' value='"); webpage +="ama"; webpage +=F("'>Amarelo</button></td><td>");
  webpage += F("<FORM action='/' method='post'>"); 
  webpage += F("<button type='submit' style='color:#00FF00; width:25%; height:75px; background-color: #FF00FF;' name='Roxo'"); 
  webpage += F("' value='"); webpage +="rxo"; webpage +=F("'>Roxo</button></td><td>");
  webpage += F("<FORM action='/' method='post'>"); 
  webpage += F("<button type='submit' style='color:#FF0000; width:25%; height:75px; background-color: #00FFFF;' name='Ciano'"); 
  webpage += F("' value='"); webpage +="cia"; webpage +=F("'>Ciano</button></td><td>");
  webpage += F("<FORM action='/' method='post'>"); 
  webpage += F("<button type='submit' style='color: #FFFFFF; width:25%; height:75px; background-color: #000000;' name='Off'"); 
  webpage += F("' value='"); webpage +="off"; webpage +=F("'>Desliga</button></td></tr><hr>");
  SendHTML_Content();
  append_page_footer();
  SendHTML_Content();
  SendHTML_Stop();   
}

void newnet() {
  SendHTML_Header();

  webpage += F("<h1>ADICIONAR REDE</h1>");
  SendHTML_Content();
  
  append_page_footer();
  SendHTML_Content();
  SendHTML_Stop();
}

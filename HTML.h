String webpage = ""; //String to save the html code

void append_page_header() {

  webpage  = F("<!DOCTYPE html>");
  webpage += F("<html>");  
  webpage += F("<head>");
  webpage += F("<meta charset='utf-8'>");
  webpage += F("<meta name='viewport' content='user-scalable=yes,initial-scale=1.0,width=device-width'>    ");
  webpage += F("<title>ESP32-D2</title>");
  webpage += F("<style>");
  webpage += F("body{max-width:66%;margin:0 auto;font-family:arial;font-size:100%;}  ");
  webpage += F("ul{list-style-type:none;padding:0;border-radius:0em;overflow:hidden;background-color:#00008b;font-size:1em;}  ");
  webpage += F("li{float:left;border-radius:0em;border-right:0em solid #bbb;}");  
  webpage += F("li a{color:white; display: block;border-radius:0.375em;padding:0.44em 0.44em;text-decoration:none;font-size:100%}  ");
  webpage += F("li a:hover{background-color:#1b71a8;border-radius:0em;font-size:100%}");  
  webpage += F("h1{color:white;text-align:center;border-radius:0em;font-size:1.5em;padding:0.2em 0.2em;background:#00008b;}  ");
  webpage += F("h2{color:white;border-radius:0em;font-size:1.0em;padding:0.2em 0.2em;background:#00008b;}");
  webpage += F("table{font-family:arial,sans-serif;font-size:0.9em;border-collapse:collapse;width:85%;}");   
  webpage += F("th,td {border:0.06em solid #dddddd;text-align:left;padding:0.3em;border-bottom:0.06em solid #dddddd;}   ");
  webpage += F("tr:nth-child(odd) {background-color:#eeeeee;}");  
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
  //webpage += F("<div style='text-align: center;'>");
  //webpage += F("<img src='/Icon.jpeg' alt='R2-D2'>");
  //webpage += F("</div>");
  
  
  File imageFile = SD.open("/Icon.jpeg", "r");
  if (!imageFile) {
    Serial.println("Falha ao abrir o arquivo de imagem");
    return;
  }

  // Obter o tamanho do arquivo de imagem
  size_t imageSize = imageFile.size();

  // Criar um buffer para armazenar os dados da imagem
  uint8_t* imageBuffer = new uint8_t[imageSize];
  
  // Ler os dados da imagem para o buffer
  imageFile.read(imageBuffer, imageSize);

  // Fechar o arquivo de imagem
  imageFile.close();

  // Converter os dados da imagem em uma string base64
  String base64Image = base64::encode(imageBuffer, imageSize);

  // Adicionar a tag <img> com o atributo src contendo a string base64 da imagem
  webpage += F("<div style='text-align: center;'>");
  webpage += "<img src='data:image/jpeg;base64," + base64Image + "'>";
  webpage += F("</div>");
  // Restante do código para gerar a página inicial

  delete[] imageBuffer;
  
  
  webpage += F("<h1>ESP32-D2</h1>");
  char ipString[16];
  WiFi.localIP().toString().toCharArray(ipString, 16);
  webpage += "<h2 style='text-align: center;'>Endereço IP: " + String(ipString) + "</h2>";
  webpage += F("<h2> Umidade: 123 %<br>Temperatura: 123ºC <br>Sensação Térmica: 123ºC</h2>");
  webpage += F("<hr>");
  webpage += F("<ul>");  
  webpage += F("<li><a href='/'>Músicas</a></li>");
  webpage += F("<li><a href='/upload'>Abajur</a></li>   ");
  webpage += F("<li><a href='/upload'>Redes</a></li>");   
  webpage += F("</ul>");  

}
//Saves repeating many lines of code for HTML page footers
void append_page_footer()
{ 
  webpage += F("</body></html>");
}

#include "HTML.h"

ESP32WebServer web(80);

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
  web.client().stop(); //Stop is needed because no content length was sent
}

void server_main() {
  //Action acording to post, dowload or delete, by MC 2022
  if (web.args() > 0 ){  //Arguments were received, ignored if there are not arguments
    Serial.println(web.arg(0));
    String Order = web.arg(0);
    Serial.println(Order);
      if (Order.indexOf("download_")>=0){
        Order.remove(0,9);
        //SD_file_download(Order);
        Serial.println(Order);
      }
      if ((web.arg(0)).indexOf("delete_")>=0){
        Order.remove(0,7);
        //SD_file_delete(Order);
        Serial.println(Order);
      }
    }
    File root = SD.open("/");
    if (root) {
      root.rewindDirectory();
      SendHTML_Header();
      //webpage += F("<table align='center'>");
      //webpage += F("<tr><th>Name/Type</th><th style='width:20%'>Type File/Dir</th><th>File Size</th></tr>");
      //printDirectory("/",0);
      //webpage += F("</table>");
      SendHTML_Content();
      root.close();
    }
    else {
      SendHTML_Header();
      webpage += F("<h3>No Files Found</h3>");
    }
    append_page_footer();
    SendHTML_Content();
    SendHTML_Stop();   //Stop is needed because no content length was sent
}

void lsmusic() {
  
}

void player() {

}

void lamps() {
  
}

void netupload() {

}

/* Para usar o SD, conecte os pinos:
CS   = GPIO5
SCK  = GPIO18
MOSI = GPIO23
MISO = GPIO19
VCC  = V5
GND  = GND */

/* Pinagem dos Sensores e Leds
BCLK = 26
LRC = 25
DIN = 22

KY037 D0 = 32
DHT11 = 33
*/

//#include <FS.h>

void htmlteste(){
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

//Funções Transitórias
void cria(fs::FS &fs, const char * path){
  Serial.printf("Writing file: %s\n", path);
  File file = fs.open(path, FILE_WRITE);
  if(!file){
    Serial.println("Failed to open file for writing");
    return;
  }
  if(file.print("IOT\n")){
    Serial.println("File written");
  } 
  else {
    Serial.println("Write failed");
  }
  file.close();
  file = fs.open(path, FILE_APPEND);
  file.print("@Xapeleta171171\n");
  file.close();
}

void renameFile(fs::FS &fs, const char * path1, const char * path2){
    Serial.printf("Renaming file %s to %s\n", path1, path2);
    if (fs.rename(path1, path2)) {
        Serial.println("File renamed");
    } else {
        Serial.println("Rename failed");
    }
}

void deleteFile(fs::FS &fs, const char * path){
    Serial.printf("Deleting file: %s\n", path);
    if(fs.remove(path)){
        Serial.println("File deleted");
    } else {
        Serial.println("Delete failed");
    }
}

void ls(fs::FS &fs, const char * dirname, uint8_t levels){
    Serial.printf("Listing directory: %s\n", dirname);

    File root = fs.open(dirname);
    if(!root){
        Serial.println("Failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        Serial.println("Not a directory");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if(levels){
                ls(fs, file.name(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("  SIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}

# ESP32D2

## Versão 0.5 - Atualmente, o código tem acesso ao Cartão Micro SD, lendo um arquivo de texto com dados de SSID e Senha para acessar a internet via Wi-Fi. Também consegue gerar uma lista das pastas que contém música e gera uma playlist embaralhada com as músicas que estão dentro de uma pasta específica. Consegue se conectar na internet Wi-Fi com os dados lidos ou gera um Access Point caso as redes não estejam disponíveis ou demore mais de 30 segundos para conseguir uma conexão. Código está um pouco otimizado desde as últimas versões, mas ainda não está bem documentado. O esboço dos Tasks para usar o processador dual core já está funcionando. O próximo passo é criar o código para gerar o Web Server, condicional a presença do Cartão Micro SD (sem cartão, não haverá um tocados de músicas, apenas a luz RGB do abajur (led) e a leitura da temperatura e umidade). Talvez o Web Server possa adicionar uma nova rede através do Access Point, modificando o arquivo que guarda as redes. Após, será feito o código para o  MAX 98357a tocar músicas, os sensores de palmas, proximidade e temperatura/umidade e o led RGB. 

## Version 0.5 - Currently, the code has access to the Micro SD Card, reading a text file with SSID and Password data to access the internet via Wi-Fi. It can also generate a list of folders that contain music and generate a playlist shuffled with the songs that are inside a specific folder. It can connect to Wi-Fi internet with the data read or generate an Access Point if the networks are not available or it takes more than 30 seconds to get a connection. Code is somewhat optimized since the last versions, but it is still not well documented. The Tasks outline for using the dual core processor is already working. The next step is to create the code to generate the Web Server, conditional on the presence of the Micro SD Card (without a card, there will be no music playing, just the RGB light from the lamp (LED) and the temperature and humidity reading). Perhaps the Web Server can add a new network through the Access Point, modifying the file that stores the networks. Afterwards, the code will be created for the MAX 98357a to play music, the clap, proximity and temperature/humidity sensors and the RGB LED.

### ESP32D2 é um abajur RGB acionado por palmas. Também toca arquivos MP3 acionado por sensor de presença. Possui um sensor de Temperatura e Umidade. Tem um servidor HTTP simples para controle e leitura do sensor de temperatura/umidade. Todo o circuito é montado em um pequeno R2D2 feito em MDF 3mm, cujas fotos serão acrescentadas.

Código está em desenvolvimento. Acompanhe o andamento no anúncio de versão acima. 
Estão sendo usados:
| # | Itens |
| --- | --- |
| 1 | Esp32-Wroover 38 pinos |
| 2 | Módulo de acesso a cartão micro sd |
| 3 | Amplificador MAX98357a com um pequeno auto-falante |
| 4 | Sensor PIR HC-SR501 |
| 5 | LED RGB |
| 6 | Sensor KY-037 |
| 7 | Sensor DHT11 |

### ESP32D2 is a clap-driven RGB table lamp. It also plays MP3 files triggered by a presence sensor. It has a Temperature and Humidity sensor. It has a simple HTTP server for controlling and reading the temperature/humidity sensor. The entire circuit is assembled in a small R2D2 made from 3mm MDF, photos of which will be added.

Code is under development. Follow the progress in the release announcement above.
Are being used:
| # | Items |
| --- | --- |
| 1 | Esp32-Wroover 38 pins |
| 2 | Micro SD Card Access Module |
| 3 | MAX98357a amplifier with a small speaker |
| 4 | PIR sensor HC-SR501 |
| 5 | RGB LED |
| 6 | KY-037 sensor |
| 7 | DHT11 sensor |

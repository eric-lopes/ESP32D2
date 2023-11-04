# ESP32D2

## Versão 0.7 - Atualmente, o código tem acesso ao Cartão Micro SD, lendo um arquivo de texto com dados de SSID e Senha para acessar a internet via Wi-Fi. Também consegue gerar uma lista das pastas que contém música e gera uma playlist embaralhada com as músicas que estão dentro de uma pasta específica. Consegue se conectar na internet Wi-Fi com os dados lidos ou gera um Access Point caso as redes não estejam disponíveis ou demore mais de 30 segundos para conseguir uma conexão. Pisca o led (apenas com as cores verde, vermelho e azul) para sinalizar que o cartão SD está funcionando e que conseguiu conectar no WiFi. Código está um pouco otimizado desde as últimas versões, mas ainda não está bem documentado. O código foi separado em vários arquivos, cada um contendo as funções de um determinado tema. O Task para executar o programa principal já está funcionando, já que o void loop() deve executar apenas o audio.loop(). O Player de música está funcionando, mas faltam testes. O próximo passo é criar o código para gerar o Web Server e fazer os controles de cada função. Talvez o Web Server possa adicionar uma nova rede através do Access Point, modificando o arquivo que guarda as redes. 

## Version 0.7 - Currently, the code has access to the Micro SD Card, reading a text file with SSID and Password data to access the internet via Wi-Fi. It can also generate a list of folders that contain music and generate a playlist shuffled with the songs that are inside a specific folder. It can connect to Wi-Fi internet with the data read or generate an Access Point if the networks are not available or it takes more than 30 seconds to get a connection. The LED flashes (only with green, red and blue colors) to signal that the SD card is working and that it has managed to connect to WiFi. The code has been somewhat optimized since the latest versions, but it is not yet well documented. The code was separated into several files, each containing the functions of a particular theme. The Task to execute the main program is already working, since void loop() should only execute audio.loop(). The Music Player is working, but tests are needed. The next step is to create the code to generate the Web Server and control each function. Perhaps the Web Server can add a new network through the Access Point, modifying the file that stores the networks.

### ESP32D2 é um abajur RGB que toca arquivos MP3. Possui um sensor de Temperatura e Umidade. Tem um servidor HTTP simples para controle do player de música, do abajur e faz a leitura do sensor de temperatura/umidade. Todo o circuito é montado em um pequeno R2D2 feito em MDF 3mm, cujas fotos serão acrescentadas.

Código está em desenvolvimento. Acompanhe o andamento no anúncio de versão acima. 
Estão sendo usados:
| # | Itens |
| --- | --- |
| 1 | Esp32-Wroover 38 pinos |
| 2 | Módulo de acesso a cartão micro sd |
| 3 | Amplificador MAX98357a com um pequeno auto-falante |
| 4 | LED RGB |
| 5 | Sensor DHT11 |

### ESP32D2 is an RGB lamp that plays MP3 files. It has a Temperature and Humidity sensor. It has a simple HTTP server to control the music player, lamp and read the temperature/humidity sensor. The entire circuit is assembled in a small R2D2 made from 3mm MDF, photos of which will be added.

Code is under development. Follow the progress in the release announcement above.
Are being used:
| # | Items |
| --- | --- |
| 1 | Esp32-Wroover 38 pins |
| 2 | Micro SD Card Access Module |
| 3 | MAX98357a amplifier with a small speaker |
| 4 | RGB LED |
| 5 | DHT11 sensor |

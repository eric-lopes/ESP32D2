# ESP32D2

## ESP32D2 é um abajur RGB que toca arquivos MP3. Possui um sensor de Temperatura e Umidade. Tem um servidor HTTP simples para controle do player de música, do abajur e faz a leitura do sensor de temperatura/umidade. Todo o circuito é montado em um pequeno R2D2 feito em MDF 3mm, cujas fotos serão acrescentadas.
| # | Itens |
| --- | --- |
| 1 | Esp32-Wroover 38 pinos |
| 2 | Módulo de acesso a cartão micro sd |
| 3 | Amplificador MAX98357a com um pequeno auto-falante |
| 4 | LED RGB |
| 5 | Sensor DHT11 |

### Versão 0.9 - Código ainda precisa de otimização e ser documentado. Preciso melhorar a função que adiciona redes ao arquivo wifi.net. Fora isso, está perfeitamente funcional. 

### A raiz do cartão SD deve conter: Um arquivo wifi.net com rede e senha de cada rede WiFi a que quiser conectar (SSID numa linha, senha na outra e assim por diante); a pasta R2D2, com os sons do dróide para que toque quando necessário e uma pasta MUSIC onde devem ser coladas as pastas com músicas. Nada mais é necessário ao funcionamento. Aqui neste projeto trago os sons do R2-D2 e exemplos de música.

### O código está separado em 4 bibliotecas, cada uma com seu escopo de funções: Abajur, que traz as funções para manipular o led; Audio, que lida com a leitura das pastas de música e com o player de música; Rede, que lida com as funções de leitura do arquivo de credenciais de Wi-Fi e com a conexão; e Server, que traz todas as funções usadas para gerar o servidor HTML. O projeto usa os dois núcleos da placa: um para o audio, outro para o servidor e demais funções. 

### Ao ligar, verifica a presença do cartão SD e sinaliza via led RGB. Tendo acesso ao cartão SD, conecta na internet lendo um arquivo de texto com SSIDs e senhas. Conseguindo ou não se conectar na rede, gera um Access Point para controlar suas funções através de um Servidor Web, também sinalizando o sucesso via led RGB. O servidor apresenta o IP da ESP32 caso esteja conectada na rede Wi-Fi e os dados de temperatura e umidade vindos do sensor DHT11. Na sequência, gera a lista de pastas de música presentes no cartão SD. Clicando em tocar em um das pastas, apresenta os controles do player e a playlist embaralhada gerada com os arquivos MP3 presentes na pasta. Consegue ir para a próxima música, música anterior, pausar, parar e alterar o volume. Também tem controles para o abajur, ou seja, o led RGB, usando apenas 3 bits de cor e um modo aleatório, onde pisca uma cor diferente a cada 0,4s. Existe um timer definido pelo usuário para desligar a música e o abajur, além de um modo para adicionar novas redes e senhas ao arquivo de texto do cartão de memória e conectar a uma rede Wi-Fi.

# ESP32D2 (English)

## ESP32D2 is an RGB lamp that plays MP3 files. It has a Temperature and Humidity sensor. It has a simple HTTP server to control the music player, lamp and read the temperature/humidity sensor. The entire circuit is assembled in a small R2D2 made from 3mm MDF, photos of which will be added.

Are being used:
| # | Items |
| --- | --- |
| 1 | Esp32-Wroover 38 pins |
| 2 | Micro SD Card Access Module |
| 3 | MAX98357a amplifier with a small speaker |
| 4 | RGB LED |
| 5 | DHT11 sensor |

### Version 0.9 - Code still needs optimization and documentation. I need to improve the function that adds networks to the wifi.net file. Other than that, it's perfectly functional.

### The root of the SD card must contain: A wifi.net file with the network and password for each WiFi network you want to connect to (SSID on one line, password on the other and so on); the R2D2 folder, with the droid's sounds so that it can play when necessary and a MUSIC folder where the folders with music should be pasted. Nothing else is necessary for operation. Here in this project I bring the sounds of R2-D2 and music examples.

### The code is separated into 4 libraries, each with its own scope of functions: Abajur, which contains functions to manipulate the LED; Audio, which handles reading the music folders and the music player; Network, which handles the functions of reading the Wi-Fi credential file and connecting; and Server, which contains all the functions used to generate the HTML server. The project uses the board's two cores: one for audio, the other for the server and other functions.

### When turned on, it checks the presence of the SD card and signals it via RGB LED. Having access to the SD card, it connects to the internet by reading a text file with SSIDs and passwords. Whether or not you can connect to the network, it generates an Access Point to control its functions through a Web Server, also signaling success via RGB LED. The server presents the IP of the ESP32 if it is connected to the Wi-Fi network and the temperature and humidity data coming from the DHT11 sensor. Next, it generates the list of music folders present on the SD card. Clicking on play in one of the folders displays the player controls and the shuffled playlist generated with the MP3 files present in the folder. You can go to the next song, previous song, pause, stop and change the volume. It also has controls for the lamp, that is, the RGB LED, using only 3 color bits and a random mode, where a different color flashes every 0.4s. There is a user-defined timer to turn off the music and lamp, as well as a mode for adding new networks and passwords to the memory card's text file and connecting to a Wi-Fi network.

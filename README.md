# ESP32D2

## Versão 0.8 - Código precisa de otimização e ser documentado. O código está separado em 4 bibliotecas, cada uma com seu escopo de funções: Abajur, que traz as funções para manipular o led; Audio, que lida com a leitura das pastas de música e com o player de música; Rede, que lida com as funções de leitura do arquivo de credenciais de Wi-Fi e com a conexão; e Server, que traz todas as funções do servidor, incluindo as funções para lidar com o sensor DHT11. O projeto já está funcional e usando os dois núcleos da placa: um para o audio, outro para o servidor. Ao ligar, verifica a presença do cartão SD e sinaliza via led RGB. Tendo acesso ao cartão SD, conecta na internet lendo um arquivo de texto com SSIDs e senhas. Conseguindo ou não se conectar na rede, gera um Access Point para controlar suas funções através de um Servidor Web, também sinalizando o sucesso via led RGB. O servidor apresenta o IP da ESP32 caso esteja conectada na rede Wi-Fi e os dados de temperatura e umidade vindos do sensor DHT11. Na sequência, gera a lista de pastas de música presentes no cartão SD. Clicando em tocar em um das pastas, apresenta os controles do player e a playlist embaralhada gerada com os arquivos MP3 presentes na pasta. Consegue ir para a próxima música, música anterior, pausar, parar e alterar o volume. Também tem controles para o abajur, ou seja, o led RGB, usando apenas 3 bits de cor. Próximos passos incluem a otimização e documentação do código, assim como a criação de um timer para parar a música ou desligar o abajur, assim como criar e alterar o arquivo de credenciais através do servidor.


## Version 0.8 - Code needs optimization and documentation. The code is separated into 4 libraries, each with its own scope of functions: Abajur, which contains functions to manipulate the LED; Audio, which handles reading the music folders and the music player; Rede, which handles the functions of reading the Wi-Fi credential file and connecting; and Server, which brings all server functions, including functions to handle the DHT11 sensor. The project is now functional and using the board's two cores: one for the audio, the other for the server. When turned on, it checks the presence of the SD card and signals it via RGB LED. Having access to the SD card, it connects to the internet by reading a text file with SSIDs and passwords. Whether or not you can connect to the network, it generates an Access Point to control its functions through a Web Server, also signaling success via RGB LED. The server presents the IP of the ESP32 if it is connected to the Wi-Fi network and the temperature and humidity data coming from the DHT11 sensor. Next, it generates the list of music folders present on the SD card. Clicking on play in one of the folders displays the player controls and the shuffled playlist generated with the MP3 files present in the folder. You can go to the next song, previous song, pause, stop and change the volume. It also has controls for the lampshade, that is, the RGB LED, using only 3 color bits. Next steps include optimizing and documenting the code, as well as creating a timer to stop the music or turn off the lamp, as well as creating and changing the credentials file via the server.

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

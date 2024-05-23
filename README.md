Projeto de Automação com ESP32 e Sensores de Gases
Descrição
Este projeto foi desenvolvido como conclusão de semestre e tem como objetivo criar um sistema de automação utilizando ESP32 e diversos sensores de detecção de gases, incluindo monóxido de carbono, temperatura, umidade, gás de cozinha e fumaça. Quando os sensores detectam valores acima dos limites estabelecidos, o sistema envia notificações para o usuário.

Funcionalidades
Monitoramento de temperatura, umidade e gases (monóxido de carbono, gás de cozinha e fumaça).
Envio de notificações via CallMeBot quando os valores dos sensores ultrapassam os limites definidos.
Requisitos
ESP32
Sensores (MQ-5, MQ-135, DHT11)
Biblioteca Arduino para ESP32
Conta no CallMeBot
Passo a Passo
1. Configurando o CallMeBot
Adicione o número do bot CallMeBot aos seus contatos: +34 644 97 54 14
Envie uma mensagem para o bot com o texto: "I allow callmebot to send me messages"
O bot responderá com uma ApiKey e confirmará o seu número de telefone.
2. Configurando o Projeto
Clone este repositório ou faça o download dos arquivos.

Instale as bibliotecas necessárias no Arduino IDE:

WiFi.h
HTTPClient.h
DHT.h
Adafruit_GFX.h
Adafruit_SSD1306.h
UrlEncode.h
Conecte os sensores aos pinos apropriados no ESP32:

DHT11 no pino GPIO 5
MQ-5 no pino GPIO 17
MQ-135 no pino GPIO 16
Substitua os valores das constantes no código pelo seu SSID, senha do WiFi, número de telefone e ApiKey fornecidos pelo CallMeBot.

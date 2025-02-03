# Programa de Controle de Padrão de LEDs com Interrupções
Este programa foi desenvolvido para o Raspberry Pi Pico W e utiliza a placa BitDogLab para controlar uma matriz de 25 LEDs (configurada como uma matriz 5x5) do tipo WS2812 (Neopixel). O objetivo é alterar o padrão de acendimento dos LEDs por meio de dois botões, utilizando interrupções para incrementar ou decrementar um índice que seleciona o padrão desejado.

## Funcionalidades
Controle via Botões:
Dois botões conectados aos pinos GPIO 5 e 6 são utilizados para:

Botão A (GPIO 5): Incrementar o valor de a (até o máximo 9), alterando o padrão de LEDs.
Botão B (GPIO 6): Decrementar o valor de a (até o mínimo 0).
Interrupção com Debouncing:
Foi implementado um callback único para interrupções nos dois botões. Um mecanismo de debouncing (200 ms) é utilizado para evitar múltiplos acionamentos indesejados.

## Exibição dos Padrões de LEDs:
São definidos 10 buffers de padrões (de 0 a 9) que configuram quais dos 25 LEDs serão acesos. Ao alterar o valor de a, o padrão correspondente é exibido através do controle do WS2812.

## Feedback Visual:
Um LED vermelho (conectado ao GPIO 13) é alternado no loop principal para indicar que o programa está rodando.

## Hardware Utilizado
Raspberry Pi Pico W
Placa BitDogLab com botões e LEDs WS2812
LED RGB (opcional): Utilizado para feedback visual do funcionamento do programa.
Configuração dos Pinos
WS2812 (Neopixel): GPIO 7
Botão de Incremento: GPIO 5
Botão de Decremento: GPIO 6
LED Vermelho (feedback): GPIO 13
LED Verde: GPIO 11
LED Azul: GPIO 12

## Como Utilizar
1. Preparação do Ambiente:
Certifique-se de ter o Pico SDK devidamente instalado e configurado no seu ambiente de desenvolvimento.

2. Compilação e Upload:
Compile o projeto utilizando o CMake e a toolchain do Pico.
Faça o upload do firmware compilado para o Raspberry Pi Pico.

3. Uso do Programa:
Após o upload, o programa inicia e exibe o padrão inicial de LEDs.
Pressione o botão conectado ao GPIO 5 para incrementar o valor do índice (alterando para o próximo padrão).
Pressione o botão conectado ao GPIO 6 para decrementar o valor do índice (voltando para o padrão anterior).
O LED vermelho pisca continuamente no loop principal, indicando que o sistema está ativo.

4. Depuração:
Mensagens de depuração são enviadas via printf() para o console serial. Verifique o monitor serial para acompanhar as mudanças de estado e o valor atual de a.

## Estrutura dos Arquivos
* ws2812.c:
Contém o código fonte principal, onde estão implementadas a lógica dos padrões de LEDs, o controle dos botões e as funções de interrupção.

* ws2812.pio:
Arquivo com a implementação do programa PIO para controle dos LEDs WS2812.

* README.md:
Este arquivo, com a descrição do programa e instruções de utilização.

* diagram.json:
Arquivo de diagrama utilizado para a simulação com a extensão do Wokwi. Nele são definidas as conexões e posicionamento dos componentes (placa, botões, LEDs, resistores, etc.).

* wokwi.toml:
Arquivo de configuração utilizado pelo simulador Wokwi para definir as opções do projeto e facilitar a simulação online do firmware.

* CMakeLists.txt:
Arquivo de configuração do CMake para compilar o projeto utilizando o Pico SDK. Certifique-se de que o ambiente de desenvolvimento esteja configurado conforme as instruções do Pico SDK para compilar e fazer o upload do firmware para o Raspberry Pi Pico.

## Observações
Verifique se os pinos configurados no código estão de acordo com a fiação da sua placa BitDogLab.
Em caso de problemas com a ativação das interrupções, certifique-se de que os botões estão funcionando corretamente e que não há conflitos de pinos com outros dispositivos conectados.

## Video de demonstração
* Link para o video de demonstração: <https://youtube.com/shorts/R37A8Wue_6I> 

/*
  -     CONECTA E ENVIA SMS SIM800L   -
  =================================================
  ==================================================
*/
#include <SoftwareSerial.h> //Adiciona da biblioteca SoftwareSerial.h

SoftwareSerial mySerial(4, 3); //Cria objeto mySerial passando como parâmetro as portas digitais 3 e 2

void setup(){
  Serial.begin(9600); //Inicializa a comunicação serial

  mySerial.begin(9600); //Inicializa comunicação entre o SIM800L e o Arduino

  delay(1000);  //Intervalo de 1 segundo

  mySerial.println("AT"); //Teste de conexão 
  updateSerial(); //Chamada da função updateSerial()
  
  mySerial.println("AT+CMGF=1"); //Configuração do modo SMS text
  updateSerial(); //Chamada da função updateSerial()
  
  mySerial.println("AT+CMGS=\"+5534999700463\""); //Número de telefone que irá receber a mensagem, “ZZ” corresponde ao código telefônico do pais e “XXXXXXXXXXX” corresponde ao número de telefone com o DDD
  updateSerial(); //Chamada da função updateSerial()
  
  mySerial.print("Enviando dados do leite"); //Texto que será enviado para o usúario
  updateSerial(); //Chamada da função updateSerial()
  
  mySerial.write(26); //confirmação das configurações e envio dos dados para comunicação serial.
}

void loop(){
}

void updateSerial() {
  
  while (mySerial.available()) //Verifica se a comunicação serial está disponível
  {
    Serial.write(mySerial.read()); //Realiza leitura serial dos dados de entrada Arduino
  }
  delay(500); //Intervalo de 0,5 segundos
}
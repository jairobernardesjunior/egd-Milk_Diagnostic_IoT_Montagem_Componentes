// Bibliotecas utilizadas
#include <AdafruitIO_WiFi.h>
#include <ESP8266WiFi.h>
#include <Servo.h>
 
// Credenciais da conta Adafruit IO
#define NOMEUSUARIO_IO     "profsandromesquita"
#define CHAVE_IO          "aio_ZTTg808Tw35vJL4jezK5z8Jktfdg"
 
// Credenciais da rede WiFi
#define NOME_WIFI       "NET_2GED1D16"
#define SENHA_WIFI       "knn1056c"
 
AdafruitIO_WiFi io(NOMEUSUARIO_IO, CHAVE_IO, NOME_WIFI, SENHA_WIFI);
 
// Pino do NodeMCU que o servo está conectado
#define PINO_SERVO D1
 
// Posição 1 da bandeira, em graus
#define POS_INICIAL 90
 
// Posição 2 da bandeira, em graus
#define POS_NOVO_EMAIL 180
 
// Tempo para a bandeira ir da posição 1 para a posição 2, em segundos
#define TEMPO_ACIONADO 20
 
Servo servo;
 
AdafruitIO_Feed*gmail_feed = io.feed("gmail"); //Configura o feed do Gmail do Adafruit
 
void setup() {
   
  Serial.begin(115200);
 
  Serial.print("Notificador de e-mails do Gmail");
   
  servo.attach(PINO_SERVO);
 
  // Conexão inicial com a Adafruit IO
  Serial.print("Conectando com Adafruit IO");
  io.connect();
  
  gmail_feed->onMessage(handleMessage); //Criação de um manipulador de mensagens

  //Aguarda a conexão estabelecer
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  //Se passar, é pq conectou
  Serial.println();
  Serial.println(io.statusText());
  gmail_feed->get();
   
  // Coloca a bandeira na posição 1
  servo.write(POS_INICIAL);
}
 
void loop() {
  //Esta função é simplesmente para manter o cliente conectado ao io.adafruit.com
   io.run();
}
 
// Função chamada sempre que há uma novo dado na Adafruit IO
//A função handleMessage é chamada quando o feed do gmail é atualizado pelo Zapier
void handleMessage(AdafruitIO_Data *data) {
  Serial.println("Você tem um novo e-mail!");
  servo.write(POS_NOVO_EMAIL);
  delay(TEMPO_ACIONADO * 1000);
  servo.write(POS_INICIAL);
}

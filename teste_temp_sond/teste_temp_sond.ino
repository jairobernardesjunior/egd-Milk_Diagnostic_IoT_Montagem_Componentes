/*
  -     CONECTA E RECEBE DADOS DO DS18B20 SONDA
  =================================================
  ==================================================
*/

/*inclusão das bibliotecas necessárias*/
#include <OneWire.h>  
#include <DallasTemperature.h>
/********************************************************************/

#define dados 33 /*o pino de dados do sensor está ligado na porta 2 do Arduino*/

OneWire oneWire(dados);  /*Protocolo OneWire*/
/********************************************************************/
DallasTemperature sensors(&oneWire); /*encaminha referências OneWire para o sensor*/
/********************************************************************/ 
void setup(void) /*laço de configuração*/
{ 
 Serial.begin(9600); /*definição de Baudrate de 9600*/
 Serial.println("Demonstração do funcionamento do sensor"); /*Printa "Demonstração do funcionamento do sensor"*/
 sensors.begin(); /*inicia biblioteca*/
} 
void loop(void) /*laço de repetição*/
{ 
 /* use sensors.requestTemperatures() para o requerimento de temperatura de todos os dispositivos ligados */
/********************************************************************/
 Serial.print(" Requerimento de temperatura..."); 
 sensors.requestTemperatures(); /* Envia o comando para leitura da temperatura */
 Serial.println("Pronto");  /*Printa "Pronto" */
/********************************************************************/
 Serial.print("A temperatura é: "); /* Printa "A temperatura é:" */
 Serial.print(sensors.getTempCByIndex(0)); /* Endereço do sensor */
}
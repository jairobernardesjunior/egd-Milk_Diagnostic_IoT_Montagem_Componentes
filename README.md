Esta primeira parte do projeto de hardware e software embutido Milk_Diagnostic_Hardware visa fazer a montagem das placas que fazem
a composição do dispositivo e o teste de software de cada placa-componente para validar o funcionamento do sistema físico.
Milk Diagnostic Hardware é um dispositivo IoT que vai medir a temperatura do leite no reservatório da fazenda e enviar os dados
via sms ou email 24 horas por dia e 7 dias da semana, onde será recebido na caixa de mensagem do gmail receptor, sendo os valores, 
capturados por uma aplicação python, rodando em AWS Lambda, transformando os dados e armazenando em AWS BucketS3 como arquivo json, para análise do cientista e analista de dados.
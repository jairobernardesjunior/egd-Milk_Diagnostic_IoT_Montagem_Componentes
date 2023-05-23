// Programa : mede corrente

float voltage;

void setup()
{
  Serial.begin(9600);

  //Define a porta do led como saida
  pinMode(11, OUTPUT);
  //Acende o led
  digitalWrite(11, HIGH);  
}
  
void loop()
{
  unsigned int x=0;
  float AcsValue=0.0,Samples=0.0,AvgAcs=0.0,AcsValueF=0.0;
  for (int x = 0; x < 10; x++)          //Get 10 samples
  {
    AcsValue = analogRead(A0);           //Read current sensor values   
    Samples = Samples + AcsValue;        //Add samples together
    delay (3);                           // let ADC settle before next sample 3ms
  }
  AvgAcs=Samples/10.0;                   //Taking Average of Samples
  voltage=AvgAcs*(5.0 / 1024.0);         //((AvgAcs * (5.0 / 1024.0)) is converitng the read voltage in 0-5 volts
  Serial.print("Raw Voltage:");
  Serial.print(voltage);
  AcsValueF = (2.5 - voltage)*1000/0.185; //2.5 is offset,,,   0.185v is rise in output voltage when 1A current flows at input
  Serial.print("\t");
  Serial.print("Corrente :");
  Serial.print(AcsValueF);               //Print the read current on Serial monitor
  Serial.println(" mA");

  delay(2000);
}

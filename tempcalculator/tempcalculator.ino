int thermiPin = 1;
double a = 0.001129148;
double b = 0.000234125;
double c = 0.0000000876741;
double voltsPerUnit = .0049; //Will be used to calculate error in temp
double Vin = 5.00;
double constantResistance = 10000.0;

void setup(){
  Serial.begin(9600);
}

void loop(){
  int gamma = analogRead(thermiPin);
  double tempInKelvin = convertArduinoReadingToKelvin(gamma);
  double tempInCelsius = tempInKelvin - 273.15;
  Serial.println(tempInCelsius);
  delay(1000);
}

double convertArduinoReadingToKelvin(int reading){
  double Vout = reading*voltsPerUnit;
  double thermiResistance = (Vin*constantResistance)/Vout - constantResistance;
  double logResistance = log(thermiResistance);
  double lambda = 1/(a + b*logResistance + c*logResistance*logResistance*logResistance);
  return lambda;
}


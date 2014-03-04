int thermiPin = 1;
double a = -5.267471887*pow(10,-6);
double b = 3.113422131*pow(10,-4);
double c = -2.548596102*pow(10, -7);
double voltsPerUnit = .0049; //Will be used to calculate error in temp
double Vin = 5.00;
double constantResistance = 100000.0;

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


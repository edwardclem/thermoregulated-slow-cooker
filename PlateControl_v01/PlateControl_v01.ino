int thermiPin = 1;
int relayPin = 2;
double a = -5.267471887*pow(10,-6);
double b = 3.113422131*pow(10,-4);
double c = -2.548596102*pow(10, -7);
double voltsPerUnit = .0049; //Will be used to calculate error in temp
double Vin = 5.00;
double constantResistance = 100000.0;
double targetTemp = 110.0;
double tempRange = 3.0; //acceptable range for cooking
double threshold = 1.0; // range for detecting when a temperature has been reached
boolean cookingNow = false;
boolean relayOn = false;
double cookTimeInMins = 100;
double cookStartTime;

#include <LiquidCrystal.h>

LiquidCrystal lcd(7,8,9,10,11,12);

void setup(){
  lcd.begin(16, 2);
  Serial.begin(9600);
  lcd.print("Temp:");
  lcd.setCursor(10, 0);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Warming Up");
  
  //acivates relay
  pinMode(relayPin, OUTPUT);
  
  digitalWrite(relayPin, HIGH);
  relayOn = true;
  
}

void loop(){
  
  //reads and prints out temperature
  int gamma = analogRead(thermiPin);
  double tempInKelvin = convertArduinoReadingToKelvin(gamma);
  double tempInCelsius = tempInKelvin - 273.15;
  Serial.println(tempInCelsius);
  lcd.setCursor(6,0);
  lcd.print(tempInCelsius);
  
  //cooking threshold reached, begin cooking
  if (!cookingNow && tempInCelsius > (target - threshold) && tempInCelsius < (target + threshold)){
    cookingNow = true;
    
    //deactivates hot plate
    digitalWrite(relayPin, LOW);
    relayOn = false;
    
    //prints status to display
    lcd.setCursor(0, 1);
    lcd.print("Cooking Start");
    Serial.println("Cooking Start");
    
    //records start time
    cookStartTime = millis();
    
  }
  
  if(cookingNow){
    //prints current time 
    
    lcd.setCursor(0, 1);
    lcd.print("Time Left:");
    Serial.println("Time Left:");
    lcd.setCursor(11, 1);
    
    double timeElapsed = (millis() - cookStartTime)*60*1000; 
    
    lcd.print(cookTimeInMins - timeElapsed);
    Serial.println(cookTimeInMins - timeElapsed);
    
    //checks if cooking has finished   
    if (millis() == (cookStartTime + cookTimeInMins*60*1000)){
      lcd.setCursor(0,1);
      lcd.print("Done!")
      Serial.println("Done!");
      digitalWrite(relayPin, LOW);
      relayOn = false;
      cookingNow = false;
    }
    else if (!relayOn && tempInCelsius < (targetTemp - tempRange)){ // too cold, turn relay on
         digitalWrite(relayPin, HIGH);
         relayOn = true;
         Serial.println("Too cold, turning relay on");
    }
    else if (relayOn && tempInCelsius > (targetTemp + tempRange)){ //too hot, turn relay off
         digitalWrite(relayPin, LOW);
         relayOn = false;
         Serial.println("Too hot, turning relay off");
    }
    
  }
  
  delay(1000);
}

double convertArduinoReadingToKelvin(int reading){
  double Vout = reading*voltsPerUnit;
  double thermiResistance = (Vin*constantResistance)/Vout - constantResistance;
  double logResistance = log(thermiResistance);
  double lambda = 1/(a + b*logResistance + c*logResistance*logResistance*logResistance);
  return lambda;
}


int thermiPin = 1;

void setup(){
  Serial.begin(9600);
}

void loop(){
  Serial.println(analogRead(thermiPin));
  delay(1000);
}



int switchPin[] = {4,3,2};//meant to control relay
int inputPin = A0;//takes input from LM35 temperature sensor
double last5Sum = 0;// holds a sum of the last 5 temperatures

int currentTime;
int lastTime = millis();
int val;

void setup() {
  
  Serial.begin(9600);
    pinMode(switchPin[0],OUTPUT);
    pinMode(switchPin[1],OUTPUT);
    pinMode(switchPin[2],OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
   
   currentTime = millis();//essentially this loop every 1 second will take 5 readings from the temperature sensor print them to the serial monitor, and send them into tempcheck for analysis
   if(currentTime - lastTime>= 1000){
      for(int i = 0; i < 5; i++){
        val = analogRead(inputPin);
         float mv = ( val/1024.0)*5000;
         float cel = mv/10;
         last5Sum += cel;
         
         Serial.print("TEMPRATURE = ");
         Serial.print(cel);
         Serial.print("*C");
         Serial.println(); 
      }
      tempCheck(last5Sum);
      last5Sum = 0;
      lastTime = millis();
   }
   
  
  
  
}
void tempCheck(double sumOfTemps){//takes in a sum of 5 temperatures, averages them out for accuracy. if temperature is below desired, relay switch is activated allowing heating unit to engage
  double avg = sumOfTemps/5;
  if (avg <= 33){
    
    digitalWrite(switchPin[0],HIGH);
    digitalWrite(switchPin[1],HIGH);
    digitalWrite(switchPin[2],HIGH);
    
  }
  else{//if temperature is above desired the heating unit will shut off
    digitalWrite(switchPin[0],LOW);
    digitalWrite(switchPin[1],LOW);
    digitalWrite(switchPin[2],LOW);
  
  }
  Serial.println(avg);//prints average temperature to command line for analysis
}

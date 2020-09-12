#include "HX711.h"
#include <LiquidCrystal_I2C.h> //Library for LCD
LiquidCrystal_I2C lcd(0x27,16,2); 
#define calibration_factor 172000.0 //This value is obtained using the SparkFun_HX711_Calibration sketch

#define DOUT  3
#define CLK  2

HX711 scale;

void setup() {
//Initiate the LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0); //Set the cursor on the first column and first row.
  lcd.print("    DiGiTRON"); //Print the string "Hello World!"
  lcd.setCursor(0,1); //Set the cursor on the third column and the second row (counting starts at 0!.
  lcd.print("RESEARCH COMPANY");
  delay(2000);
  
//Initiate the HX711 
  Serial.begin(9600);
  scale.begin(3, CLK);
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0

 // Serial.println("Readings:");
}
int start = 0;
void loop() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH);
  pinMode(7, INPUT_PULLUP);
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
  digitalWrite(9, LOW);
  
  int weights[5][5];
  int output[5];
  int sw;  //imput from prox sw
 //1st loop
  if (start == 0){
    sw = HIGH;
    sw = digitalRead(7);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("EGG GRADER 2019");
    lcd.setCursor(0,1);
    lcd.print("    READY..");
    delay(2000);
    for (int i=0; i<=4; i++){
      for (int j=0; j<=4; j++)weights[i][j]=LOW;
      output[i]=LOW;
    start=1;
    }
  }
  
//weighting
   sw = digitalRead(7);
   if (sw == LOW) {  //sw: proximity switch signal
    //insert egg
      digitalWrite(6, LOW);
      delay(500);
      digitalWrite(6, HIGH);
      
    //read input
      float w = scale.get_units()*0.45359237; //scale.get_units() returns a float
      
    //LCD print
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("WEIGHT:");
      lcd.setCursor(9,0);
      //String stringOne = "Weight: ";
      String stringTwo = " g";
      String stringThree = (int)(w*1000) + stringTwo;
      lcd.print(stringThree);
      
      digitalWrite(13, output[0]);
      digitalWrite(12, output[1]);
      digitalWrite(11, output[2]);
      digitalWrite(10, output[3]);
      digitalWrite(9, output[4]);
      delay(500);
    // transform table  
      if ((w < 0.4) & (w > 0.1))         weights[0][0] = HIGH;
      else if ((w < 0.6)& (w > 0.1))     weights[1][1] = HIGH;
      else if ((w < 0.8)& (w > 0.1))     weights[2][2] = HIGH;
      else if ((w < 1.6)& (w > 0.1))     weights[3][3] = HIGH;
      else if (w > 1.6)                  weights[4][4] = HIGH;
      
      
    // next round
      for (int pos=0; pos<=4; pos++){
        output[pos]=weights[pos][0];
        for (int tim=1; tim<=4; tim++) weights[pos][tim-1]=weights[pos][tim];
        weights[pos][4]=LOW;
      }
    //outputs
    
    digitalWrite(9, output[1]); //ti fasi??????

   }
   else {
    sw = digitalRead(7);   
   }
   
}

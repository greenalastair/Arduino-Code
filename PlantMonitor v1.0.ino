
/***********SETUP***************
 1.Connection Diagram: https://www.dfrobot.com/wiki/index.php?title=Capacitive_Soil_Moisture_Sensor_SKU:SEN0193
 
 2.Arduino UNO Wiring:  
            - soil sensor Analogue signal - > A0 
            - soil sensor power -> 5V
            -LCD VCC -> 3.3V
            -LCD SDA -> A4
            -LCD SCL -> A5
            -TEMP power -> 13
            -temp Analogue signal -> A1
            
 3. soil Sensor is connect to Analog 0 port.
 4. temp Sensor is connect to Analog 1 port.
 5. Need to calibrate the sensor fully dry and fully wet, change values below.
 ****************************************************/

const int AirValue = 565;   //value with sensor completely dry
const int WaterValue = 278;  //value with sensor submerged in water up to circuit board
int intervals = (AirValue - WaterValue)/3;
int soilMoistureValue = 0;
float soilMoisturePct = 0;
int Temp = 13; //temp probe power source

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x20,20,4);  // set the LCD address to 0x20 for a 20 chars and 4 line display 

void setup() {
  Serial.begin(9600); // open serial port, set the baud rate to 9600 bps
  lcd.init();                      // initialize the lcd
  lcd.backlight();                  // turn on the lcd backlight
  pinMode(Temp, OUTPUT);        //set 13 to output 3.3V for temp probe
  digitalWrite(Temp, HIGH);    // turn on pin 13 to power temp probe

}
void loop() {
    uint16_t val;
    double dat;
    val=analogRead(A1);//Connect LM35 on Analog 0
    dat = (double) val * (5/10.24);
soilMoistureValue = analogRead(A0);  //put Sensor insert into soil
soilMoisturePct = ((1.0-(analogRead(A0) - 278.0)/287.0)*100.0);
Serial.println(soilMoistureValue);
Serial.println(soilMoisturePct);
lcd.setCursor(0, 0);
lcd.print("Plant Monitor v1.0");
lcd.setCursor(0, 1);
lcd.print("Air Temp: ");
lcd.setCursor(10, 1);
lcd.print(dat, 1);
lcd.setCursor(15, 1);
lcd.print("C");
lcd.setCursor(0, 2);
lcd.print("Soil:");
lcd.setCursor(0, 3);
lcd.print("Moisture: ");
lcd.setCursor(15, 3);
lcd.print("%");
lcd.setCursor(10, 3);
lcd.print(soilMoisturePct, 0);


if(soilMoistureValue < (WaterValue + intervals))
{ 
  lcd.setCursor(6, 2);
  lcd.print("Wet          ");
}

if(soilMoistureValue >= (WaterValue + intervals) && soilMoistureValue <= (AirValue - intervals))
{
  lcd.setCursor(6, 2);
  lcd.print("Damp        ");
}

if(soilMoistureValue > (AirValue - intervals))
{  
  lcd.setCursor(6, 2);
  lcd.print("Dry          ");
}
  
delay(500);
lcd.setCursor(12, 3);     //this deletes the third value on outputs above 99% to 
lcd.print(" ");           //avoid contaminating lower values, eg after 103%  40% would be displayed as 403%


}

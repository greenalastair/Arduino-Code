# PlantMonitor
Displays air temperature and soil moisture (capacitive) on an LCD. 

1. Connection Diagram: https://www.dfrobot.com/wiki/index.php?title=Capacitive_Soil_Moisture_Sensor_SKU:SEN0193
 
2. Arduino UNO Wiring:  soil sensor Analogue signal - > A0 //
            soil sensor power -> 5V //
            LCD VCC -> 3.3V //
            LCD SDA -> A4 //
            LCD SCL -> A5 //
            TEMP power -> 13 //
            temp Analogue signal -> A1
            
3. soil Sensor is connect to Analog 0 port.
4. temp Sensor is connect to Analog 1 port.
5. Need to calibrate the sensor fully dry and fully wet, change values below.

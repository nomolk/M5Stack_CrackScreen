#include <M5Stack.h>
#include "utility/MPU9250.h"

MPU9250 IMU;

void setup(void) {

  M5.begin();
  Wire.begin();
  Serial.begin(115200);

  M5.Lcd.setBrightness(200);
  M5.Lcd.fillScreen(BLACK);
  IMU.calibrateMPU9250(IMU.gyroBias, IMU.accelBias);
  IMU.initMPU9250();
}

void loop() {
  if (IMU.readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01)
  {  
    IMU.readAccelData(IMU.accelCount);
    IMU.getAres();
    
    IMU.ax = (float)IMU.accelCount[0]*IMU.aRes; // - accelBias[0];
    IMU.ay = (float)IMU.accelCount[1]*IMU.aRes; // - accelBias[1];
    IMU.az = (float)IMU.accelCount[2]*IMU.aRes; // - accelBias[2];

  }

  IMU.delt_t = millis() - IMU.count;

  if (IMU.delt_t > 200)
  {
    Serial.println(abs((int)1000*IMU.ax) + abs((int)1000*IMU.ay) + abs((int)1000*IMU.az));

    if(abs((int)1000*IMU.ax) + abs((int)1000*IMU.ay) + abs((int)1000*IMU.az) > 3000){
      M5.Lcd.drawJpgFile(SD, "/crack.jpg");
    }
  }
  
  M5.update();
  if(M5.BtnA.wasPressed() || M5.BtnB.wasPressed() || M5.BtnC.wasPressed()) {
    M5.Lcd.fillScreen(BLACK);
  }
}

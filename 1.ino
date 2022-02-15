#include <Wire.h>
int ADXL345 = 0x53; // The ADXL345 sensor I2C address

float X_out, Y_out, Z_out;
float Y_aux, X_aux = 0;
int drawleft, drawright, speedbump = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin(); 
  Wire.beginTransmission(ADXL345);
  Wire.write(0x2D);
  
  Wire.write(8);
  Wire.endTransmission();
  delay(100);
}

void loop() {
  Wire.beginTransmission(ADXL345);
  Wire.write(0x32);
  Wire.endTransmission(false);
  Wire.requestFrom(ADXL345, 6, true); 
  X_out = ( Wire.read() | Wire.read() << 8); 
  X_out = X_out / 256;
  Y_out = ( Wire.read() | Wire.read() << 8);
  Y_out = Y_out / 256;
  Z_out = ( Wire.read() | Wire.read() << 8);
  Z_out = Z_out / 256;

  Serial.print("Xa= ");
  Serial.print(X_out);
  Serial.print("   Ya= ");
  Serial.print(Y_out);
  Serial.print("   Za= ");
  Serial.println(Z_out);

  if ((Y_out - Y_aux > 0.3) && Y_out < -0.6)
  {
    drawleft = 1;
    //Serial.println("groapa stanga");
    Serial.print(drawleft);
    Serial.println(" lat: 100, long 12");
  }
  if ((Y_out - Y_aux > 0.3) && Y_out > -0.6)
  {
    drawright = 2;
    //  Serial.println("groapa dreapta");
    Serial.print(drawright);
    Serial.println(" lat: 100, long 12");
  }
  else
  {
    drawleft = 0;
    drawright = 0;
  }
  Y_aux = Y_out;

  /////
  if ((X_out - X_aux > 0.2) && X_out > 0)
  {
    speedbump = 3;
    //speedbump
    Serial.print(speedbump);
    Serial.println(" lat: 100, long 12");
  }
  else
  {
    speedbump = 0;
  }
  X_aux = X_out;
  delay(500);
}

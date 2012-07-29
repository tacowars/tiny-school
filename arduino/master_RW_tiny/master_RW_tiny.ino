// Wire Master Reader / Writer code from Arduino examples

#include <Wire.h>

int led = 13;
int position = 0;
int temp = 0;

void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(115200);  // start serial for output'
  pinMode(led, OUTPUT);
  Serial.println("Boot!");
}

void loop()
{
  digitalWrite(led, HIGH);
  delay(100);

  digitalWrite(led, LOW);
  delay(100);
  
  position = getPot();
  Serial.println(position);
  
  position = getTemp();
  Serial.println(position);
  
  toggleLED();
  
  
}

int getPot() {
  byte x1 = B00000000;
  byte x2 = B00000000;
  // Set up and Read first reg
  Wire.beginTransmission(2); // transmit to device #2
  Wire.write(1);              // sends one byte to start ADC and return half of reading
  Wire.endTransmission();    // stop transmitting
  
  Wire.requestFrom(2, 1);    // ID first, byte count second
  while(Wire.available())    // slave may send less than requested
  { 
    x1 = Wire.read(); // receive a byte as an integer
    //Serial.print(x1);         // print the character
    //Serial.println(" 1st");
  }
  
  // Set up and Read second reg
  Wire.beginTransmission(2); // transmit to device #2
  Wire.write(2);              // sends one byte to get second half of readinf
  Wire.endTransmission();    // stop transmitting
  
  Wire.requestFrom(2, 1);    // ID first, byte count second
  while(Wire.available())    // slave may send less than requested
  { 
    x2 = Wire.read(); // receive a byte as an integer
    //Serial.print(x2);         // print the number
    //Serial.println("");
  }
  int reading = ( x1 | ( x2 << 8 )); // only 10 bits
  return reading;
}

int getTemp() {
  byte x4 = B00000000;
  byte x5 = B00000000;
  // Set up and Read first reg
  Wire.beginTransmission(2); // transmit to device #2
  Wire.write(4);              // sends one byte to start ADC on temp and return half of reading
  Wire.endTransmission();    // stop transmitting
  
  Wire.requestFrom(2, 1);    // ID first, byte count second
  while(Wire.available())    // slave may send less than requested
  { 
    x4 = Wire.read(); // receive a byte as an integer
  }
  
  Serial.println(x4);         // print the character
  
  // Set up and Read second reg
  Wire.beginTransmission(2); // transmit to device #2
  Wire.write(5);              // sends one byte to get second half of readinf
  Wire.endTransmission();    // stop transmitting
  
  Wire.requestFrom(2, 1);    // ID first, byte count second
  while(Wire.available())    // slave may send less than requested
  { 
    x5 = Wire.read(); // receive a byte as an integer
  }
  
  Serial.println(x5);         // print the character
  
  int reading = ( x4 | ( x5 << 8 ));
  return reading;
}

void toggleLED() {
  byte x3 = B00000000;
  Wire.beginTransmission(2); // transmit to device #2
  Wire.write(3);              // sends one byte to trigger toggle 
  Wire.endTransmission();    // stop transmitting
  
  Wire.requestFrom(2, 1);    // ID first, byte count second
  while(Wire.available())    // slave may send less than requested
  { 
    x3 = Wire.read(); // receive a byte as an integer
    //Serial.print(x3);         // print the character
    //Serial.println("LED TOGGLED");
  }
}

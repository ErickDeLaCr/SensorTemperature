#include <Adafruit_MLX90614.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SoftwareSerial.h>

const int tempAddress = 0;
const int rx_pin = 4;
const int tx_pin = 3;
const int displayLen = 16;
const int prox_pin = A0;
int ir = 5;
float maxTemp = 40.00;
float temp_0 = 0.0;
float error = 0.0;
int threshold = 800;

char TitanName[] = {"TitaniumPass"};
char TempName[] = {"Temp: 28.4"};
char access_G[] = {"Access granted"};
char access_D[] = {"Access denied"};
char waitMess[] = {"Please wait"};
char TakingTemp[] = {"Checking..."};

int measureTime = 500;
const int dropAvg = 2;
const int Avg = 25;
double tempArray[Avg];
double ObjectTemp = 0;

SoftwareSerial BlueT(rx_pin, tx_pin);
LiquidCrystal_I2C lcd(0x27, 20, 4);
Adafruit_MLX90614 tempSens =  Adafruit_MLX90614();

void setup() {
  Serial.begin(9600);
  lcd.init();
  tempSens.begin();
  BlueT.begin(9600);

  pinMode(prox_pin, INPUT);
  pinMode(ir, OUTPUT);

  //printTitle();
  delay(1000);
  lcd.backlight();
  lcd.clear();

  centerPrint(TitanName, 'U');
}

int getDistance() {
  //int prox_val = analogRead(prox_pin);
  int prox_val = smartDetect();
  int result = 0;
  Serial.print("Distance: ");
  Serial.println(prox_val);
  if (prox_val == 5) {
    result = 1;
    delay(500);
    //temp_0 = tempSens.readObjectTempC() + 2.6;
    for(int i = 0; i < Avg; i++) {
      tempArray[i] = tempSens.readObjectTempC();
    }
    sort2(tempArray, Avg);
    for(int j = dropAvg; j < Avg - dropAvg; j++) {
      ObjectTemp += tempArray[j];
    }
    ObjectTemp = (ObjectTemp / (Avg-(dropAvg*2))) - error;
    lcd.clear();
    centerPrint(TakingTemp, 'U');
    lcd.setCursor(3, 1);
    lcd.print(prox_val);
    //centerPrint(waitMess, 'L'); 
    delay(1500);
    Serial.println(ObjectTemp);
    //delay(500);
    printTemp(ObjectTemp);
    sendBT(ObjectTemp);
  }
  return result;
}

void sendBT(float message) {
  BlueT.println(message);
  Serial.println("Data sent");
  delay(3000);
  lcd.clear();
  centerPrint(TitanName, 'U');
}

void sort2(double ia[], int size0) {
  for(int x = 0; x < size0; x++) {
    for(int y = 0; y < size0 - 1; y++) {
      if(ia[y] > ia[y + 1]) {
        int tmp = ia[y + 1];
        ia[y + 1] = ia[y];
        ia[y] = tmp;
      }
    }
  }
}

int smartDetect() {
  signed int proxVec = 0;
  for (int i = 0; i < 4; i++) {
    PORTD = ~(PORTD) ^ 0xDF;
    int val = analogRead(prox_pin);
    Serial.println(val);
    if (val < threshold) {
      proxVec = proxVec << 1;
      proxVec |= 1;
    }
    else {
      proxVec = proxVec << 1;
      proxVec |= 0;
    }
  }
  return proxVec;
}

void loop() {
  int isProx = getDistance();
  delay(1000);
  
}

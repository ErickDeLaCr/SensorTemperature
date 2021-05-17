void printTitle() {
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("Titanium");
  lcd.setCursor(2,1);
  lcd.print(32.8);
}

void centerPrint(char* text_0, char row_0) {
  int result_0 = strlen(text_0);
  int row_1 = 0;
  int compV = 0;
  compV = 0x01 & result_0;
  result_0 = result_0 / 2;
  result_0 = (displayLen / 2) - result_0;
  
  switch(row_0) {
    case 'U':
      row_1 = 0;
    break;

    case 'L':
      row_1 = 1;
    break;

    default:
      Serial.println("Row incorrect, U or L required");
    break;
  }

  if(compV != 0) {
    result_0 = result_0 - 1;
  }
  
  lcd.setCursor(result_0, row_1);
  lcd.print(text_0);
}

void printTemp(double temp_1){
  lcd.clear();
  //float maxTemp_1 = readMaxTemp();
  if (temp_1 > maxTemp) {
    centerPrint(access_D, 'U');
    lcd.setCursor(3, 1);
    lcd.print("Temp: ");
    lcd.setCursor(9, 1);
    lcd.print(temp_1);
  }
  else {
    centerPrint(access_G, 'U');
    lcd.setCursor(3, 1);
    lcd.print("Temp: ");
    lcd.setCursor(9, 1);
    lcd.print(temp_1);
  }
 
}

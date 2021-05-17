void Dec2Bin(float val_0, unsigned int *msb, unsigned int *lsb) {
  
  unsigned int result_a = 1;
  unsigned int result_b = 0;
  unsigned int result_c = 0;
  *msb = 0;
  *lsb = 0;
  int i = 0;

  
  
  while(val_0 >= 0.1) {

    Serial.print("iteration: ");
    Serial.println(i);
    Serial.print("Val: ");
    Serial.println(val_0);
    Serial.print("result_a before: ");
    Serial.println(result_a, BIN);
    Serial.print("result_b before: ");
    Serial.println(result_b, BIN);
    Serial.println("");
    
    if(i < 15) {
      val_0 *= 2;
      Serial.print("Val on if: ");
      Serial.println(val_0);
      result_a = result_a << 1;
      if(val_0 >= 1) {
        result_a |= 1;
        val_0 = val_0 - int(val_0);
      }
      else {
        result_a |= 0;
      }
      i++; 
    }

    else {
      result_b = result_a;
      i = 0;
    }

  Serial.print("result_a after: ");
  Serial.println(result_a, BIN);
  Serial.print("result_b after: ");
  Serial.println(result_b, BIN);

  } 


  result_c = result_b >> (16 - i);
  Serial.print("result_a final: ");
  Serial.println(result_a, HEX);
  Serial.print("result_c final: ");
  Serial.println(result_c, HEX);
  Serial.println("");
  *lsb = result_a;
  *msb = result_c;
  //return result_a;
}

int getInt(float a) {
  a = int(a);
  return a;
}

float getDec(float b) {
  int a = int(b);
  b = b - a;
  return b;
}

int getExp(int a) {
  int mask = 0x8000;
  int c = 0, i = 15;
  bool out = false;
  do {
    c = a & mask;
    if (c != 0) {
      out = true;
    }
    else {
      i--;
      mask = mask >> 1;
    }
  } while(out == false);
 return i;
}

/*
  float temp = 23.85;
  Serial.println(temp);
  int a = int(temp);
  Serial.println(a, BIN);
  float b = temp - a;
  Serial.println(b, BIN);
  unsigned int a , b;
  //unsigned int res = Dec2Bin(0.41, &a, &b);
  Dec2Bin(0.28, &a, &b);
  //Serial.println(res, BIN);
  Serial.println(a, HEX);
  Serial.println(b, HEX);
*/

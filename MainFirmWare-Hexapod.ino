//servo driver config.
const int servoRangeMin = 800,servoRangeMax = 2200;
int row,column;
byte servoChannels[6][3] = {        {0x00,0x01,0x02},
                                    {0x03,0x04,0x05},
                                    {0x06,0x07,0x08},
                                    {0x09,0x0A,0x0B},
                                    {0x0C,0x0D,0x0E},
                                    {0x0F,0x10,0x11},
                  };
unsigned int a=1500,b=1100,c=800;
unsigned int servoPW[6][3] = {        {a,b,c},  //servoPW fonksiyonunu çağırırken bunalar set edilip driver a yollanıyor.
                                      {a,b,c},
                                      {a,b,c},
                                      {a,b,c},
                                      {a,b,c},
                                      {a,b,c},
                  };
byte formattedPW[36];
byte CommandSetServoPW = 0x84; // command for setting pulse width for a servo
byte CommandSetMultipleServoPW = 0x9F; // command for setting pulse width for multiple servos
byte CommandSetServoSpeed = 0x87; // command for setting speed for a servo
const int SIZE=3;
byte commandBytes[SIZE];

// receiver USART1 config.
const int dataSIZE=19;
char charData[dataSIZE],buttons;
int data;
unsigned int index = 0,joystick1X,joystick1Y,joystick2X,joystick2Y,analogButtons1,analogButtons2,digiButton1;
bool dataErrorFlage=0,dataReceiveComplete=0;

void setup() {
  Serial.begin(115200);  // For print on PC screen
  Serial1.begin(9600);    // USART1 receiver config. for receiving controlling pad status 
  Serial2.begin(115385);  // USART2 transmitter for controlling servo driver

  setAllServoSpeed(50);
  setAllServoPW();
}

void loop() {
  if (Serial1.available() > 0) {
    data = Serial1.read();
    //'s'
    if(data == 115) {
      dataErrorFlage = 0;
      index = 0;
      //index < 19
      while(data != '\n') {
        if (Serial1.available() > 0) {
          data = Serial1.read(); 

          //char c = data;
          //Serial.print('d'); 
          
          //Serial.print(c); 
          //Serial.print(' '); 
                     
          if(data == '\n') {
            Serial.print('b'); Serial.print('\n'); 
            if (index < 19) {
              dataErrorFlage = 1;
            }
            break; 
          }
          else if(dataErrorFlage == 0 && data >= 48 && data <= 57 ) { 
            if (index < 19) {
                charData[index++] = data;  
            } else {
                dataErrorFlage = 1;
            }
            
            
            //Serial.print(index - 1);  
            //char x = data;
            //Serial.print(x); 
            
            //Serial.print('\n');
          }  
          else {
            dataErrorFlage = 1;
            Serial.print('e'); Serial.print('\n'); 
            //break;
          }          
        }        
      }
    
      if (dataErrorFlage == 0) 
        dataReceiveComplete = 1;
      else {
        dataReceiveComplete=0;
        dataErrorFlage=0;
      }       
             
    }

    if(dataReceiveComplete) { 
     printCharData();
      //charArrayToInt(joystick1X,charData,3,6); 
      //joystick1X = map(joystick1X,0,1023,servoRangeMin,servoRangeMax);  
      charArrayToInt(joystick1Y,charData,7,10); 
      joystick1Y = map(joystick1Y,0,1023,servoRangeMin,servoRangeMax);
      //Serial.print(joystick1Y); Serial.print('\n');
      analogButtons1 = charData[0]-'0';  // integerData += charData[i]-'0';

     //charArrayToInt(analogButtons1,charData,0,0);
      //Serial.print(analogButtons1); Serial.print('\n');

    
     if(joystick1Y<1200) {
        turnRight();
     }
      else if(joystick1Y>1600) {
        turnLeft();
      } 

      //delay(1000);

      if (analogButtons1 == 0) {
        Serial.print(analogButtons1); Serial.print('\n');
    setAllServoSpeed(50);
  //setAllServoPW
  servoPW[0][0]=1500; servoPW[0][1]=1100; servoPW[0][2]=800; //1. leg
  servoPW[1][0]=1500; servoPW[1][1]=1100; servoPW[1][2]=800; //2. leg
  servoPW[2][0]=1500; servoPW[2][1]=1100; servoPW[2][2]=800; //3. leg
  servoPW[3][0]=1500; servoPW[3][1]=1100; servoPW[3][2]=800; //4. leg
  servoPW[4][0]=1500; servoPW[4][1]=1100; servoPW[4][2]=800; //5. leg
  servoPW[5][0]=1500; servoPW[5][1]=1100; servoPW[5][2]=800; //6. leg 
  setAllServoPW();
  delay(300);
    //turnRight();
       
      }  
       
       else if(analogButtons1 == 1) { 
        Serial.print(analogButtons1); Serial.print('\n');      
  setAllServoSpeed(80);
  //
  servoPW[0][0]=800; servoPW[0][1]=800;  //1. leg
  servoPW[1][0]=800; servoPW[1][1]=800;  //2. leg
  servoPW[2][0]=800; servoPW[2][1]=800;  //3. leg
  servoPW[3][0]=800; servoPW[3][1]=800;  //4. leg
  servoPW[4][0]=800; servoPW[4][1]=800;  //5. leg
  servoPW[5][0]=800; servoPW[5][1]=800;  //6. leg
  setAllServoPW();
  delay(200); 
    //turnLeft();
      } 
      
      else if (analogButtons1 == 2) {
    setAllServoSpeed(140);
  //
  servoPW[0][0]=800; servoPW[0][1]=1100; servoPW[0][2]=800; //1. leg
  servoPW[1][0]=800; servoPW[1][1]=1100; servoPW[1][2]=800; //2. leg
  servoPW[2][0]=800; servoPW[2][1]=1100; servoPW[2][2]=800; //3. leg
  servoPW[3][0]=800; servoPW[3][1]=1100; servoPW[3][2]=800; //4. leg
  servoPW[4][0]=800; servoPW[4][1]=1100; servoPW[4][2]=800; //5. leg
  servoPW[5][0]=800; servoPW[5][1]=1100; servoPW[5][2]=800; //6. leg 
  setAllServoPW();
  delay(300);
}
 
      
      else if (analogButtons1 == 3) {
    setAllServoSpeed(10);
  //
  servoPW[0][0]=800; servoPW[0][1]=1100; servoPW[0][2]=800; //1. leg
  servoPW[1][0]=800; servoPW[1][1]=1100; servoPW[1][2]=800; //2. leg
  servoPW[2][0]=800; servoPW[2][1]=1100; servoPW[2][2]=800; //3. leg
  servoPW[3][0]=800; servoPW[3][1]=1100; servoPW[3][2]=800; //4. leg
  servoPW[4][0]=800; servoPW[4][1]=1100; servoPW[4][2]=800; //5. leg
  servoPW[5][0]=800; servoPW[5][1]=1100; servoPW[5][2]=800; //6. leg 
  setAllServoPW();
  delay(300);
}

      
      //setServoPW(motor2 ,joystick1Y);
      //setServoPW(motor3 ,joystick1X);
      //Serial.print(joystick1X);Serial.print(' ');
      //Serial1.print(joystick1Y); Serial1.print('\n');  
      dataReceiveComplete=0;
    }
    
  }   
  
  }
 
void turnLeft() {
  setAllServoSpeed(50);
  //yükselme bu 3 baçağı havaya kadır
  servoPW[0][0]=1500; servoPW[0][1]=800; servoPW[0][2]=800; //1. leg
  servoPW[2][0]=1500; servoPW[2][1]=800; servoPW[2][2]=800; //3. leg
  servoPW[4][0]=1500; servoPW[4][1]=800; servoPW[4][2]=800; //5. leg
  setAllServoPW();
  delay(300);
  
   //Havadaki motorları hafif döndür
  servoPW[0][0]=1100; servoPW[0][1]=800; servoPW[0][2]=800; //1. leg
  servoPW[2][0]=1100; servoPW[2][1]=800; servoPW[2][2]=800; //3. leg
  servoPW[4][0]=1100; servoPW[4][1]=800; servoPW[4][2]=800; //5. leg
  setAllServoPW();
  delay(300);

  //Havadaki motorları indir
  servoPW[0][0]=1100; servoPW[0][1]=1100; servoPW[0][2]=800; //1. leg
  servoPW[2][0]=1100; servoPW[2][1]=1100; servoPW[2][2]=800; //3. leg
  servoPW[4][0]=1100; servoPW[4][1]=1100; servoPW[4][2]=800; //5. leg
  setAllServoPW();
  delay(300);

  //Diğer motorları kaldır
  servoPW[1][0]=1500; servoPW[1][1]=800; servoPW[1][2]=800;
  servoPW[3][0]=1500; servoPW[3][1]=800; servoPW[3][2]=800;
  servoPW[5][0]=1500; servoPW[5][1]=800; servoPW[5][2]=800;
  setAllServoPW();
  delay(300);

  //Eski motorları normala getir(robotun dönmesi)
  servoPW[0][0]=1500; servoPW[0][1]=1100; servoPW[0][2]=800; //1. leg
  servoPW[2][0]=1500; servoPW[2][1]=1100; servoPW[2][2]=800; //3. leg
  servoPW[4][0]=1500; servoPW[4][1]=1100; servoPW[4][2]=800; //5. leg
  setAllServoPW();
  delay(300);

  //Diğer motorları indir
  servoPW[1][0]=1500; servoPW[1][1]=1100; servoPW[1][2]=800;
  servoPW[3][0]=1500; servoPW[3][1]=1100; servoPW[3][2]=800;
  servoPW[5][0]=1500; servoPW[5][1]=1100; servoPW[5][2]=800;
  setAllServoPW();
  delay(300);
}

void turnRight() {
 setAllServoSpeed(50);
  //yükselme bu 3 baçağı havaya kadır
  servoPW[0][0]=1500; servoPW[0][1]=800; servoPW[0][2]=800; //1. leg
  servoPW[2][0]=1500; servoPW[2][1]=800; servoPW[2][2]=800; //3. leg
  servoPW[4][0]=1500; servoPW[4][1]=800; servoPW[4][2]=800; //5. leg
  setAllServoPW();
  delay(300);
  
   //Havadaki motorları hafif döndür
  servoPW[0][0]=1900; servoPW[0][1]=800; servoPW[0][2]=800; //1. leg
  servoPW[2][0]=1900; servoPW[2][1]=800; servoPW[2][2]=800; //3. leg
  servoPW[4][0]=1900; servoPW[4][1]=800; servoPW[4][2]=800; //5. leg
  setAllServoPW();
  delay(300);

  //Havadaki motorları indir
  servoPW[0][0]=1900; servoPW[0][1]=1100; servoPW[0][2]=800; //1. leg
  servoPW[2][0]=1900; servoPW[2][1]=1100; servoPW[2][2]=800; //3. leg
  servoPW[4][0]=1900; servoPW[4][1]=1100; servoPW[4][2]=800; //5. leg
  setAllServoPW();
  delay(300);


  //Diğer motorları kaldır
  servoPW[1][0]=1500; servoPW[1][1]=800; servoPW[1][2]=800;
  servoPW[3][0]=1500; servoPW[3][1]=800; servoPW[3][2]=800;
  servoPW[5][0]=1500; servoPW[5][1]=800; servoPW[5][2]=800;
  setAllServoPW();
  delay(300);
  

  //Eski motorları normala getir(robotun dönmesi)
  servoPW[0][0]=1500; servoPW[0][1]=1100; servoPW[0][2]=800; //1. leg
  servoPW[2][0]=1500; servoPW[2][1]=1100; servoPW[2][2]=800; //3. leg
  servoPW[4][0]=1500; servoPW[4][1]=1100; servoPW[4][2]=800; //5. leg
  setAllServoPW();
  delay(300);

  //Diğer motorları indir
  servoPW[1][0]=1500; servoPW[1][1]=1100; servoPW[1][2]=800;
  servoPW[3][0]=1500; servoPW[3][1]=1100; servoPW[3][2]=800;
  servoPW[5][0]=1500; servoPW[5][1]=1100; servoPW[5][2]=800;
  setAllServoPW();
  delay(300);
}

unsigned int pos;
void sweep(){ //test function
  for(pos=1000;pos<2000;pos+=10) {
    for(row=0;row<6;++row) {
      for(column=0;column<3;++column) {
        servoPW[row][column]= pos;
      }
    }
    setAllServoPW();
  }
  
  for(pos=2000;pos>1000;pos-=10) {
    for(row=0;row<6;++row) {
      for(column=0;column<3;++column) {
        servoPW[row][column]= pos;
      }
    }
    setAllServoPW();
  }
  
}

void formatPW(unsigned int PW, byte &lowerBits,byte &higherBits) {
  PW *= 4;  //microsec to quater-microsec
  lowerBits=higherBits=0x00; //clearing all bits;
  lowerBits = PW & 0x007F ; // masking lower 7 bits
  higherBits = (PW & 0x3F80) >> 7 ; // masking higher 7 bits shifting 8 bits to right
}

void setServoPW(byte &servoNr ,unsigned int PW) {
  commandBytes[0] = servoNr;
  formatPW(PW,commandBytes[1],commandBytes[2]);
    
  Serial2.write(CommandSetServoPW);
  Serial2.write(commandBytes[0]);
  Serial2.write(commandBytes[1]);
  Serial2.write(commandBytes[2]);
}

void setAllServoPW() { 
  int i=-1;  
  for(row=0;row<6;++row) {
    for(column=0;column<3;++column) {
        formatPW(servoPW[row][column],formattedPW[++i],formattedPW[++i]);
      }
  }
    
  Serial2.write(CommandSetMultipleServoPW);
  Serial2.write(0x12); // 18 nr. of targets
  Serial2.write(0x00); // first channel
  Serial2.write(formattedPW,36);
}


void formatSpeed(int Speed, byte &lowerBits,byte &higherBits) { //Speed = 1 = 3.5 μs/ms
  //Speed *= 1;  //microsec to quater-microsec
  lowerBits=higherBits=0x00; //clearing all bits;
  lowerBits = Speed & 0x007F ; // masking lower 7 bits
  higherBits = (Speed & 0x3F80) >> 7 ; // masking higher 7 bits shifting 8 bits to right
}

void setServoSpeed(byte &servoNr ,int &Speed) {
  commandBytes[0] = servoNr;
  formatSpeed(Speed,commandBytes[1],commandBytes[2]);

  Serial2.write(CommandSetServoSpeed);
  Serial2.write(commandBytes[0]);
  Serial2.write(commandBytes[1]);
  Serial2.write(commandBytes[2]);
}

void setAllServoSpeed(int Speed) {
  for(row=0;row<6;++row) {
    for(column=0;column<3;++column) {
        setServoSpeed(servoChannels[row][column],Speed);
      }
  }
}


void charArrayToInt(unsigned int &integerData, char charData[],int digitFirst,int digitLast) {
    integerData=0;
    for(int i=digitFirst;i<=digitLast;++i) {
      integerData += charData[i]-'0';
      integerData *= 10;
    } 
    integerData /= 10;
}
void printCharData() {
  
  for(int i = 0; i < dataSIZE; i++) {
    Serial.print(charData[i]);
    
    if(i==2)
      Serial.print(' ');
    else if(i==6)
      Serial.print(' ');
    else if(i==10)
      Serial.print(' ');
    else if(i==14)
      Serial.print(' ');
    
  }
  Serial.print('\n');
}


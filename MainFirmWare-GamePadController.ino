unsigned int joystick1X,joystick1Y,joystick2X,joystick2Y,analogButtons1,analogButtons2,digiButton1,digiButton2,digiButton3,digiButton4,digiButton5,digiButton6;
const int dataSIZE=21;
int delayTime=1030;

void setup() {
 Serial.begin(115200);
 Serial1.begin(9600);
}

void loop() {
  joystick1X = analogRead(0);
  joystick1Y = analogRead(1);
  joystick2X = analogRead(2);
  joystick2Y = analogRead(3);
  analogButtons1 = analogRead(4);
  analogButtons2 = analogRead(5);
  pinMode(0,  INPUT_PULLUP);
  pinMode(1,  INPUT_PULLUP);
  pinMode(2,  INPUT_PULLUP);
  pinMode(3,  INPUT_PULLUP);
  pinMode(4,  INPUT_PULLUP);
  pinMode(5,  INPUT_PULLUP);

  char charData[dataSIZE] = {'s','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','\n'};
  
  if(joystick1X>480 && joystick1X<530) joystick1X = 500 ; //neutral position
  if(joystick1Y>480 && joystick1Y<530) joystick1Y = 500 ; //neutral position
  if(joystick2X>480 && joystick2X<530) joystick2X = 500 ; //neutral position
  if(joystick2Y>480 && joystick2Y<530) joystick2Y = 500 ; //neutral position

  digiButton1=digitalRead(0);
  digiButton2=digitalRead(1);
  digiButton3=digitalRead(2);
  digiButton4=digitalRead(3);
  digiButton5=digitalRead(4);
  digiButton6=digitalRead(5);
       if(digiButton1==LOW) charData[3] = '1';
  else if(digiButton2==LOW) charData[3] = '2';
  else if(digiButton3==LOW) charData[3] = '3';
  else if(digiButton4==LOW) charData[3] = '4';
  else if(digiButton5==LOW) charData[3] = '5';
  else if(digiButton6==LOW) charData[3] = '6';
  else charData[3] = '0';
  
  if(analogButtons1>500&&analogButtons1<600) charData[1]='1';
  else if(analogButtons1>600&&analogButtons1<650) charData[1]='2';
  else if(analogButtons1>650&&analogButtons1<700) charData[1]='3';
  else if(analogButtons1>700&&analogButtons1<800) charData[1]='4';
  else if(analogButtons1>800&&analogButtons1<900) charData[1]='5';

  if(analogButtons2>500&&analogButtons2<600) charData[2]='1';
  else if(analogButtons2>600&&analogButtons2<650) charData[2]='2';
  else if(analogButtons2>650&&analogButtons2<700) charData[2]='3';
  else if(analogButtons2>700&&analogButtons2<800) charData[2]='4';
  else if(analogButtons2>800&&analogButtons2<900) charData[2]='5';
  //Serial.print(dataY);Serial.print('\n');
  
  intToCharArray(joystick1X,charData,7);
  intToCharArray(joystick1Y,charData,11);
  intToCharArray(joystick2X,charData,15);
  intToCharArray(joystick2Y,charData,19);

  
   for(int i=0;i<dataSIZE;++i)       
      Serial1.write(charData[i]);           
    
  
 for(int i=0;i<dataSIZE;++i) {           
      Serial.print(charData[i]);
    }
    
}
void intToCharArray(unsigned int integerData, char charData[],int digitPlace) {
    int i=digitPlace;
    while(integerData) {
      charData[i] = '0' + (integerData%10);
      integerData = integerData/10;
      --i;
    }  
}



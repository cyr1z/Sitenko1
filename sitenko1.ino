
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <PCF8574.h>

#define forward  7 // Input3 подключен к выводу 6 
#define backward  8 // Input4 подключен к выводу 7
#define motorSpeed  9 // Input4 подключен к выводу 9

LiquidCrystal_I2C lcd(0x3E, 20, 4); // set the LCD address to 0x3E for a 20 chars and 4 line display
PCF8574 pcf;

int averageFactor = 5;
uint32_t milTimer;
int sensorValue; //потенциометр
uint32_t currentMillis;
uint32_t SkurchMillis;
uint32_t ms_button = 0;
long previousMillisTimeSW = 0; //счетчик прошедшего времени для мигания изменяемых значений.
long intervalTimeSW = 300;     //интервал мигания изменяемых значений.
bool blinkI=0;
int processI = 0;
bool way = 1;
uint32_t startTime;
uint32_t secI=0;
int sCursor = 5;
int count = 0;
int razgib = 0;
int sgib = 90;
int temp = 5;
int timeMin = 10;
int timeSec = 0;
int tempR=0;
int skurchSensorValue;
bool     buttonRazgib = false;
bool     buttonSgib = false;
bool     buttonTemp = false;
bool     buttonTime = false;
bool     buttonPlus = false;
bool     buttonMinus = false;
bool     buttonStart = false;
bool     buttonStop = false;
int mI = 0;
double ave;
double sum;


void setup()
{
  delay(2000);
  lcd.init();                      // initialize the lcd
   delay(2000);
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0, 2);
  lcd.print("TEM\250: ");
  lcd.setCursor(0, 0);
  lcd.print("PA\244\241\245\240: ");
  lcd.setCursor(0, 1);
  lcd.print("C\241\245\240: ");
  lcd.setCursor(0, 3);
  lcd.print("BPEM\261: ");

  

  // Подключаем PCFку, задаем адрес I2C
  pcf.begin(0x38);
  // Устанавливаем направление пинов
  pcf.pinMode(0, INPUT_PULLUP); // Вход
  pcf.pinMode(1, INPUT_PULLUP); // Вход
  pcf.pinMode(2, INPUT_PULLUP); // Вход
  pcf.pinMode(3, INPUT_PULLUP); // Вход
  pcf.pinMode(4, INPUT_PULLUP); // Вход
  pcf.pinMode(5, INPUT_PULLUP); // Вход
  pcf.pinMode(6, INPUT_PULLUP); // Вход
  pcf.pinMode(7, INPUT_PULLUP); // Вход


  pinMode (motorSpeed, OUTPUT);
  pinMode (backward, OUTPUT);
  pinMode (forward, OUTPUT);
  digitalWrite (backward, LOW);
  digitalWrite (forward, LOW);
}

void loop()
{
  
  currentMillis = millis(); // время

  //потенциометр
  sensorValue = analogRead(A1); //потенциометр
  int oldsensorValue = (sensorValue);
  sensorValue = (oldsensorValue * (averageFactor - 1) + sensorValue) / averageFactor;

  if (processI==2 && SkurchMillis<currentMillis-2000)  {
    if(sensorValue==skurchSensorValue){
      if(way){
        digitalWrite(forward, LOW);
        digitalWrite(backward, HIGH);
        way=!way;
      
      }
      else {
        digitalWrite(forward, HIGH);
        digitalWrite(backward, LOW);
        way=!way;
        }
      }
      skurchSensorValue=sensorValue;
      SkurchMillis=currentMillis;
    }
    
  sum = sum + (double) sensorValue;
  mI++;
  if (mI >= 9) {
    ave = sum / 10;
    mI = 0;
    sum = 0;
  }

  //int kneeConner =(int) ave;
  int kneeConner =  map((int) ave, 145, 520, 0, 110);
  if(kneeConner<2) kneeConner=0;
  if(kneeConner>108) kneeConner=110;

  
  tempR=map(temp, 0, 5, 0, 255);

  //Вывод на экран
  //pazgib
  lcd.setCursor(8, 0);
  if (sCursor == 0 ) {
    if (currentMillis - previousMillisTimeSW >= intervalTimeSW) {                   //Если счетчик превысил интервал,
      blinkI = !blinkI;
      previousMillisTimeSW = previousMillisTimeSW + intervalTimeSW;
    }   //меняем значение переменной i, добавляем к переменной время интервала.
    if (blinkI == 1) {

      lcd.print(razgib);
    }
    if (blinkI == 0) {
      lcd.print("   ");
    }
  } else {

    lcd.print(razgib);
  }

  //cgib
  lcd.setCursor(8, 1);
  if (sCursor == 1 ) {
    if (currentMillis - previousMillisTimeSW >= intervalTimeSW) {                   //Если счетчик превысил интервал,
      blinkI = !blinkI;
      previousMillisTimeSW = previousMillisTimeSW + intervalTimeSW;
    }   //меняем значение переменной i, добавляем к переменной время интервала.
    if (blinkI == 1) {

      lcd.print(sgib);
      lcd.print("  ");
    }
    if (blinkI == 0) {
      lcd.print("   ");
    }
  } else {

    lcd.print(sgib);
  }
  //temp
  lcd.setCursor(8, 2);
  if (sCursor == 2 ) {
    if (currentMillis - previousMillisTimeSW >= intervalTimeSW) {                   //Если счетчик превысил интервал,
      blinkI = !blinkI;
      previousMillisTimeSW = previousMillisTimeSW + intervalTimeSW;
    }   //меняем значение переменной i, добавляем к переменной время интервала.
    if (blinkI == 1) {
      if (temp < 10) lcd.print("0");
      lcd.print(temp);
    }
    if (blinkI == 0) {
      lcd.print("  ");
    }
  } else {
    if (temp < 10) lcd.print("0");
    lcd.print(temp);
  }
  //time
  lcd.setCursor(8, 3);
  if (sCursor == 3 ) {
    if (currentMillis - previousMillisTimeSW >= intervalTimeSW) {                   //Если счетчик превысил интервал,
      blinkI = !blinkI;
      previousMillisTimeSW = previousMillisTimeSW + intervalTimeSW;
    }   //меняем значение переменной i, добавляем к переменной время интервала.
    if (blinkI == 1) {
      if (timeMin < 10) lcd.print("0");
      lcd.print(timeMin);
    }
    if (blinkI == 0) {
      lcd.print("  ");
    }
  } else {
    if (timeMin < 10) lcd.print("0");
    lcd.print(timeMin);
  }
  lcd.print(":");
  if (timeSec < 10) lcd.print("0");
  lcd.print(timeSec);



  //---КНОПКИ----
  //кнопка разгиб
 
  if (!pcf.digitalRead(7) && !buttonRazgib && ( currentMillis - ms_button ) > 50) {
    buttonRazgib = true;
    ms_button    = currentMillis;
    sCursor = 0;
    // processI = 0;

  }
  // Фиксируем отпускание кнопки
  if ( pcf.digitalRead(7) && buttonRazgib && ( currentMillis - ms_button ) > 50) {
    buttonRazgib = false;
    ms_button    = currentMillis;
  }

  //кнопка сгиб
  
  if (!pcf.digitalRead(0) && !buttonSgib && ( currentMillis - ms_button ) > 50) {
    buttonSgib = true;
    ms_button    = currentMillis;
    sCursor = 1;
  //processI = 0;
  }
  // Фиксируем отпускание кнопки
  if ( pcf.digitalRead(0) && buttonSgib && ( currentMillis - ms_button ) > 50) {
    buttonSgib = false;
    ms_button    = currentMillis;
  }

  //кнопка Время
  if (!pcf.digitalRead(3) && !buttonTime && ( currentMillis - ms_button ) > 50) {
    buttonTime = true;
    ms_button    = currentMillis;
    sCursor = 3;
 // processI = 0;
  }
  // Фиксируем отпускание кнопки
  if ( pcf.digitalRead(3) && buttonTime && ( currentMillis - ms_button ) > 50) {
    buttonTime = false;
    ms_button    = currentMillis;
  }
  //нопка темп
  if (!pcf.digitalRead(6) && !buttonTemp && ( currentMillis - ms_button ) > 50) {
    buttonTemp = true;
    ms_button    = currentMillis;
    sCursor = 2;
  //  processI = 0;

  }
  // Фиксируем отпускание кнопки
  if ( pcf.digitalRead(6) && buttonTemp && ( currentMillis - ms_button ) > 50) {
    buttonTemp = false;
    ms_button    = currentMillis;
  }
  //кнопка плюс
  if (!pcf.digitalRead(1) && !buttonPlus && ( currentMillis - ms_button ) > 50) {
    buttonPlus = true;
    ms_button    = currentMillis;

    switch ( sCursor ) {
      case 0:
        if (razgib >= sgib-5) razgib = 0;
        else razgib += 5;
        break;
      case 1:
        if (sgib >= 110) sgib = razgib+5;
        else sgib += 5;
        break;
      case 2:
        if (temp >= 5) temp = 1;
        else temp++;
        break;
      case 3:
        if (timeMin >= 90) timeMin = 1;
        else if (timeMin < 10) timeMin++;
        else if (timeMin >= 10 && timeMin < 30) timeMin += 5;
        else if (timeMin >= 30 && timeMin < 60) timeMin += 10;
         else if (timeMin <= 60) timeMin += 30;
        else timeMin++;
        break;
    }

  }
  // Фиксируем отпускание кнопки
  if ( pcf.digitalRead(1) && buttonPlus && ( currentMillis - ms_button ) > 50) {
    buttonPlus = false;
    ms_button    = currentMillis;
  }
  //кнопка минус
  if (!pcf.digitalRead(2) && !buttonMinus && ( currentMillis - ms_button ) > 50) {
    buttonMinus = true;
    ms_button    = currentMillis;

    switch ( sCursor ) {
      case 0:
        if (razgib <= 0) razgib = sgib-5;
        else razgib -= 5;
        break;
      case 1:
        if (sgib <= razgib+5) sgib = 110;
        else sgib -= 5;
        break;
      case 2:
        if (temp <= 1) temp = 5;
        else temp--;
        break;
      case 3:
        if (timeMin <= 1) timeMin = 90;
        else if (timeMin <= 10) timeMin--;
        else if (timeMin > 10 && timeMin <= 30) timeMin -= 5;
        else if (timeMin > 30 && timeMin <=60) timeMin -= 10;
        else if (timeMin > 60 ) timeMin -= 30;
        else timeMin--;
        break;
    }

  }
  // Фиксируем отпускание кнопки
  if ( pcf.digitalRead(2) && buttonMinus && ( currentMillis - ms_button ) > 50) {
    buttonMinus = false;
    ms_button    = currentMillis;
  }
  //Кнопка старт
  if (!pcf.digitalRead(5) && !buttonStart && ( currentMillis - ms_button ) > 50) {
     sCursor = 5;
    buttonStart = true;
    ms_button    = currentMillis;

    switch ( processI ) {
      case 0:
      if( kneeConner== razgib || kneeConner==razgib+2 || kneeConner==razgib-2  ){
        lcd.setCursor(12, 0);  lcd.print("    ");
        milTimer=timeMin*60000;
        timeMin--;
        timeSec=59;
        startTime=currentMillis;
        processI=2;
      }
        else processI = 1;
        break;
      case 1: 
       
        break;
      case 2:
        
        break;
      case 3:
        lcd.setCursor(12, 0);  lcd.print("    ");
        milTimer=timeMin*60000;
        timeMin--;
        timeSec=59;
         startTime=currentMillis;
        processI=2;
        break;
        case 4:
        
        break;
    }
  }
  // Фиксируем отпускание кнопки
  if ( pcf.digitalRead(5) && buttonStart && ( currentMillis - ms_button ) > 50) {
    buttonStart = false;
    ms_button    = currentMillis;
  }

  // кнопка СТОП
  if (!pcf.digitalRead(4) && !buttonStop && ( currentMillis - ms_button ) > 50) {
     sCursor = 5;
    
    buttonStop = true;
    ms_button    = currentMillis;
    count=0;
    
        analogWrite(motorSpeed, 0);
        digitalWrite(forward, LOW);
        digitalWrite(backward, LOW);

    switch ( processI ) {
      case 0:
        processI=4;
        lcd.setCursor(12, 0);  lcd.print("        ");
         count = 0;
         razgib = 0;
         sgib = 90;
         temp = 5;
         timeMin = 10;
         timeSec = 0;
        break;
      case 1:
        processI=0;
        break;
      case 2:
        processI=0;

      case 3:
        processI=0;
        break;

    }
  }
  // Фиксируем отпускание кнопки
  if ( pcf.digitalRead(4) && buttonStop && ( currentMillis - ms_button ) > 50) {
    buttonStop = false;
    ms_button    = currentMillis;
  }
  //---Процессы----
  
if(processI==0){
        analogWrite(motorSpeed, 0);
        digitalWrite(forward, LOW);
        digitalWrite(backward, LOW);
        } ;
// основной процесс разработки
 if(processI==2){
  //таймер
  // if (currentMillis - startTime >= milTimer){ processI=0; timeSec=0; timeMin=0; }
    if (currentMillis - secI >= 1000){ timeSec--; secI = currentMillis; }
    if (timeSec <= 0){ 
      if (timeMin==0){
        timeMin=0;
        timeSec = 0;
        processI=0;
        } else {
        timeSec=59;
        timeMin--; 
      }
    
    }
    
      
      lcd.setCursor(16, 0);
     if (count<10) { lcd.print("00"); lcd.print(count);}
      else if (count>=10 && count<100) { lcd.print("0"); lcd.print(count);}
      else { lcd.print(count);}
      
      if(way && kneeConner>=sgib){
        analogWrite(motorSpeed, 0);
        digitalWrite(forward, LOW);
        digitalWrite(backward, LOW);
         delay(10); 
         way=!way;
        } else if(!way && kneeConner<=razgib){
        analogWrite(motorSpeed, 0);
        digitalWrite(forward, LOW);
        digitalWrite(backward, LOW);
         delay(10); 
         way=!way;
          count++;
        } else if(way ){
            digitalWrite(forward, HIGH);
            analogWrite(motorSpeed, tempR);
        } else if(!way ){
            digitalWrite(backward, HIGH);
            analogWrite(motorSpeed, tempR);
        } 
        } ;
 
 if(processI==1){
  //моргаем словом разгиб
 if (currentMillis - previousMillisTimeSW >= intervalTimeSW) {                   //Если счетчик превысил интервал,
      blinkI = !blinkI;
      previousMillisTimeSW = previousMillisTimeSW + intervalTimeSW;
    }   //меняем значение переменной i, добавляем к переменной время интервала.
    if (blinkI) {
      lcd.setCursor(12, 0);    lcd.print("PA\244\241\245\240  "); 
    } else  {
       lcd.setCursor(12, 0);  lcd.print("        ");
    }
  
      if( kneeConner==razgib || kneeConner==razgib+2 || kneeConner==razgib-2 ){
        analogWrite(motorSpeed, 0);
        digitalWrite(forward, LOW);
        digitalWrite(backward, LOW);
        processI=3;
        
        } else if( kneeConner<razgib+2){
        analogWrite(motorSpeed, 255);
        way=1;
        digitalWrite(forward, HIGH);
        digitalWrite(backward, LOW);

        } else if( kneeConner>razgib-2){
        analogWrite(motorSpeed, 255);
        way=0;
        digitalWrite(forward, LOW);
        digitalWrite(backward, HIGH);

        }
        }
        
 if(processI==3){
        lcd.setCursor(12, 0);    lcd.print(" \241OTOB  ");
        way=1; 
        } 
 if(processI==4){

        
        if( kneeConner<=0){
            analogWrite(motorSpeed, 0);
            digitalWrite(forward, LOW);
            digitalWrite(backward, LOW);
            processI=0;

        }  
        if( kneeConner>0){
        analogWrite(motorSpeed, 255);
        way=0;
        digitalWrite(forward, LOW);
        digitalWrite(backward, HIGH);

        } 
        } ;
}

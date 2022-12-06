#include <LiquidCrystal.h>
#include <LedControl.h>
#include <EEPROM.h>

bool inGame = false;
bool inMenu = true;
bool inSettings = false;
byte settingsOption = 0;//name, brightness lcd, brightness matrix, sound, exit
byte settingsOptionsMax = 4;
bool inName = false;
bool inExit = false;
bool inHighscore = false;
byte highscorePos = 1;
bool inAbout = false;
bool inHowToPlay = false;
byte menuOption = 0;//0-start 1-highscore 2-settings 3-about 4-how to play
byte menuOptionsMax = 4;
byte highscorePosMax = 5;
bool inSound = false;
bool inBLCD = false;
bool inBMatrix = false;


byte aboutSlide = 0;

// in Eprom
byte lcdBrightness;
byte matrixBrightness;
bool soundOn;
char hName1[16];
char hName2[16];
char hName3[16];
char hName4[16];
char hName5[16];

void ReadFromEEPROM() {
  lcdBrightness = EEPROM.read(0);
  matrixBrightness = EEPROM.read(1);
  soundOn = EEPROM.read(2);
  for(int i=0;i<16;i++) {
    hName1[i] = EEPROM.read(3+i);
    hName2[i] = EEPROM.read(19+i);
    hName3[i] = EEPROM.read(35+i);
    hName4[i] = EEPROM.read(51+i);
    hName5[i] = EEPROM.read(67+i);
  }
}


void setup() {
  // put your setup code here, to run once:
  ReadFromEEPROM();
  JoystickSetup();
  MatrixSetup();
  LCDSetup();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  JoystickLoop();
  MatrixLoop();
  LCDLoop();
}

//Joystick Controller
//Joystick pins
const int xPin = A0;
const int yPin = A1;
const int pinSw = 2;

const int minThreshold = 200;
const int maxThreshold = 600;
int xValue = 0;
int yValue = 0;
bool swState = HIGH;

//debounce for joystick
long lastTime = 0;
long lastJoyTime = 0;
int interval = 50;
byte reading = LOW;
byte joyState = LOW;
byte lastReading = LOW;
byte joyReading = LOW;
byte lastJoyReading = HIGH;
bool joyMoved = false;

//matrix controller
const int dinPin = 12;
const int clockPin = 11;
const int loadPin = 10;

LedControl lc = LedControl(dinPin, clockPin, loadPin, 1); // DIN, CLK, LOAD, No. DRIVER

byte xPos = 0;
byte yPos = 0;
byte xLastPos = 0;
byte yLastPos = 0;


const byte matrixSize = 8;
bool matrixChanged = true;

byte matrix[matrixSize][matrixSize] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}  
};

//LCD pins
const byte RS = 9;
const byte enable = 8;
const byte d4 = 7;
const byte d5 = 6;
const byte d6 = 5;
const byte d7 = 4;
const byte brightnessPin = 3;
LiquidCrystal lcd(RS, enable, d4, d5, d6, d7);


byte lcdCols = 16;
byte lcdRows = 2;
int maxBrightnessValue = 5;
int minBrightnessValue = 1;
int maxBrightnessValueRaw = 255;
int minBrightnessValueRaw = 0;

String const alphabet[] = {" ","A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
short alphabetLength = 26;
short name[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
short letterPos = 0;

void LCDSetup() {
  ClearLCD();
  lcd.begin(lcdCols, lcdRows);
  pinMode(brightnessPin, INPUT);
  ShowMenuOption();
  SetLCDBrightness(lcdBrightness);
}

void SetLCDBrightness(int brightness) {
  analogWrite(brightnessPin,map(brightness,minBrightnessValue,maxBrightnessValue,minBrightnessValueRaw,maxBrightnessValueRaw));
}

void SetMatrixBrightness(int brightness) {
  lc.setIntensity(0, map(brightness,minBrightnessValue,maxBrightnessValue,minBrightnessValueRaw,maxBrightnessValueRaw+10));
}

void StartWritingName() {
  letterPos = 0;
  lcd.setCursor(letterPos, 1);
}

void ShowMenuOption() {
  ClearLCD();
  if (menuOption == 0) {
    lcd.print("Start game");
  }
  if (menuOption == 1) {
    lcd.print("Highscore");
  }
  if (menuOption == 2) {
    lcd.print("Settings");
  }
  if (menuOption == 3) {
    lcd.print("About");
  }
  if (menuOption == 4) {
    lcd.print("How to play");
  }
}

void ShowSettingsOption() {
  ClearLCD();
  if (settingsOption == 0) {
    WriteName();
  }
  if (settingsOption == 1) {
    WriteLCDBrightnessScreen();
  }
  if (settingsOption == 2) {
    WriteMatrixBrightnessScreen();
  }
  if (settingsOption == 3) {
    WriteSound();
  }
  if (settingsOption == 4) {
    WriteExit();
  }
}

void WriteExit() {
  ClearLCD();
  lcd.write("Exit");
}

void ClearLCD() {
  lcd.clear();
}

void WriteHighscorePos(int pos) {
  ClearLCD();
  lcd.print("Highscore");
  lcd.setCursor(0,1);
  lcd.print(String(pos));
  lcd.print(".");
  for(int i=0;i<16;i++) {
    if(pos == 1) {
      lcd.print(hName1[i]);
    }
    if(pos == 2) {
      lcd.print(hName2[i]);
    }
    if(pos == 3) {
      lcd.print(hName3[i]);
    }
    if(pos == 4) {
      lcd.print(hName4[i]);
    }
    if(pos == 5) {
      lcd.print(hName5[i]);
    }
  }
}

void WriteSound() {
  ClearLCD();
  lcd.write("ON/OFF sound");
  lcd.setCursor(0, 1);
  if(soundOn == true) {
    lcd.print("ON");
  }
  else {
    lcd.print("OFF");
  }
}

void WriteName() {
  ClearLCD();
  lcd.setCursor(0, 0);
  lcd.write("Name");
  lcd.setCursor(0,1);
  for(int i=0;i<16;i++){
    lcd.print(alphabet[name[i]]);
  }
}

void JoystickSetup() {
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(pinSw, INPUT_PULLUP);
}

void JoystickLoop() {
  JoystickClickHandler();
  JoystickMovementHandler();

}


void JoystickClickHandler() {
  reading = digitalRead(pinSw);

  if (reading != lastReading){
    lastTime = millis();
  } 

  if (millis() - lastTime > interval){
    if (reading != swState){
      swState = reading;
      if (swState == LOW){
         JoystickClicked();
      }
    }
  } 
  lastReading = reading;
}

long lastMoved;
int moveInterval = 100;

void JoystickMovementHandler() {
  ///joystick movements
  xValue = analogRead(xPin);
  yValue = analogRead(yPin);

  if ((xValue > minThreshold && xValue < maxThreshold) || (yValue > minThreshold && yValue < maxThreshold)) {
        joyReading = LOW;   
      }
  if((xValue < minThreshold || xValue > maxThreshold) || (yValue < minThreshold || yValue > maxThreshold)){
        joyReading = HIGH;   
      }

  if(joyReading != lastJoyReading){
        lastJoyTime = millis();
      }

  if(millis()-lastJoyTime > interval) 
    if(joyReading != joyState){ 
      joyState = joyReading;
      if(joyReading==HIGH)  
        joyMoved = false;
    }
  
  if (xValue > maxThreshold && joyMoved == false) { // in sus
    joyMoved = true;
    JoystickUp();
  } 
  if (xValue < minThreshold && joyMoved == false)  { //in jos
      joyMoved = true;
      JoystickDown();
      }
  if (yValue > maxThreshold && joyMoved == false) { // in dreapta
        joyMoved = true;
        JoystickRight();
      } 
  if (yValue < minThreshold && joyMoved == false)  { //in stanga
        joyMoved = true;
        JoystickLeft();
      }
  if (millis() - lastMoved > moveInterval){   
    if (xValue > maxThreshold) { // in sus
      joyMoved = true;
      JoystickUpGame();
    }
    if (xValue < minThreshold)  { //in jos
      joyMoved = true;
      JoystickDownGame();
      }
      if (yValue > maxThreshold) { // in dreapta
        joyMoved = true;
        JoystickRightGame();
      } 
  if (yValue < minThreshold)  { //in stanga
        joyMoved = true;
        JoystickLeftGame();
      }
    
    lastMoved = millis();

  } 
        
  lastJoyReading = joyReading;
}

int rx = 3;
int ry = 3 ;

void GenerateRandomFood() {
  if(matrix[xPos][yPos] == 2) {
      rx=random(0,8);
      ry=random(0,8);
      Serial.println(rx);
      while(matrix[rx][ry] == 1) {
        rx=random(0,8);
        ry=random(0,8);
      }
      matrix[rx][ry] = 2;
    }
}
void JoystickUpGame() {
  if (inGame == true) {
    matrix[xPos][yPos] = 0;
    matrixChanged = true;
    GameMoveUp();
    
    matrix[xPos][yPos] = 1;
  }
}

void JoystickDownGame() {
  if (inGame == true) {
    matrix[xPos][yPos] = 0;
    matrixChanged = true;
    GameMoveDown();
    
    matrix[xPos][yPos] = 1;
  }
}

void JoystickRightGame() {
  if (inGame == true) {
    matrix[xPos][yPos] = 0;
    matrixChanged = true;
    GameMoveRight();
    
    matrix[xPos][yPos] = 1;
  }
}

void JoystickLeftGame() {
  if (inGame == true) {
    matrix[xPos][yPos] = 0;
    matrixChanged = true;
    GameMoveLeft();
    
    matrix[xPos][yPos] = 1;
  }
}

void ShowAbout() {
  if(aboutSlide == 0) {
    ClearLCD();
    lcd.setCursor(0, 0);
    lcd.print("Game name");
    lcd.setCursor(0, 1);
    lcd.print("Snake");
  }
  else if(aboutSlide == 1) {
    ClearLCD();
    lcd.setCursor(0, 0);
    lcd.print("Author");
    lcd.setCursor(0, 1);
    lcd.print("Solomon Flavius");
  }
  else {
    ClearLCD();
    lcd.setCursor(0, 0);
    lcd.print("Github name");
    lcd.setCursor(0, 1);
    lcd.print("SolomonFlavius");
  }
}

void JoystickClicked() {
  if (inMenu == true) {//0-start 1-highscore 2-settings 3-about 4-how to play
    inMenu = false;
    if (menuOption == 0) {
      inGame = true;
    }
    if (menuOption == 1) {
      inHighscore = true;
      WriteHighscorePos(1);
    }
    if (menuOption == 2) {
      inSettings = true;
      WriteName();
    }
    if (menuOption == 3) {
      inAbout = true;
      ShowAbout();
    }
    if (menuOption == 4) {
      inHowToPlay = true;
      ClearLCD();
      lcd.print("Move joystick to");
      lcd.setCursor(0, 1);
      lcd.print("catch food");
    }
  }
  else if (inHighscore == true) {
    inHighscore = false;
    inMenu = true;
    ShowMenuOption();
  }
  else if (inSettings == true) {
    inSettings = false;
    if  (settingsOption == 0){
      inName = true;
      StartWritingName();
    }
    if  (settingsOption == 1){
      inBLCD = true;
      WriteLCDBrightnessScreen();
    }
    if  (settingsOption == 2){
      inBMatrix = true;
      WriteMatrixBrightnessScreen();
    }
    if  (settingsOption == 3){
      inSound = true;
    }
    if  (settingsOption == 4){
      inMenu = true;
      ShowMenuOption();
    }
  }
  else if (inName == true) {
    inName = false;
    inSettings = true;
    WriteName();
  }
  else if (inBLCD == true) {
    inSettings = true;
    inBLCD = false;
    WriteLCDBrightnessScreen();
    EEPROM.update(0,lcdBrightness);
  }
  else if (inBMatrix == true) {
    inSettings = true;
    inBMatrix = false;
    WriteMatrixBrightnessScreen();
    EEPROM.update(1,matrixBrightness);
  }
  else if (inSound == true) {
    inSound = false;
    inSettings = true;
    EEPROM.update(2,soundOn);
  }
  else if(inAbout == true) {
    inAbout = false;
    inMenu = true;
    ShowMenuOption();
  }
  else if(inHowToPlay == true) {
    inHowToPlay = false;
    inMenu = true;
    ShowMenuOption();
  }
}

void JoystickUp() {
  if (inMenu == true) {
    if(menuOption == 0) {
      menuOption = 0;
    }
    else {
      menuOption -= 1;
    }
    ShowMenuOption();
  }
  if (inHighscore == true) {
    if(highscorePos == 1) {
      highscorePos = 1;
    }
    else {
      highscorePos -= 1;
      WriteHighscorePos(highscorePos);
    }
  }
  if (inSettings == true) {
    if(settingsOption == 0) {
      settingsOption = 0;
    }
    else {
      settingsOption -= 1;
    }
    ShowSettingsOption();
  }
  if (inName == true) {
    if (name[letterPos] == alphabetLength) {
      name[letterPos] = alphabetLength;
    }
    else {
      name[letterPos] += 1;
    }
  }
}

void JoystickDown() {
  if (inMenu == true) {
    if(menuOption == menuOptionsMax) {
      menuOption = menuOptionsMax;
    }
    else {
      menuOption += 1;
    }
    ShowMenuOption();
  }
  if (inHighscore == true) {
    if(highscorePos == highscorePosMax) {
      highscorePos = highscorePosMax;
    }
    else {
      highscorePos += 1;
      WriteHighscorePos(highscorePos);
    }
  }
  if (inSettings == true) {
    if(settingsOption == settingsOptionsMax) {
      settingsOption = settingsOptionsMax;
    }
    else {
      settingsOption += 1;
    }
    ShowSettingsOption();
  }
  if (inName == true) {
    if (name[letterPos] == 0) {
      name[letterPos] = 0;
    }
    else {
      name[letterPos] -= 1;
    }
  }
}

void JoystickLeft() {
  
  if (inName == true) {
    if(letterPos == 0) {
      letterPos = 0;
    }
    else {
      lcd.print(alphabet[name[letterPos]]);
      letterPos -=1;
    }
  }
  if (inBLCD == true) {
    if (lcdBrightness == minBrightnessValue) {
      lcdBrightness = minBrightnessValue;
    }
    else {
      lcdBrightness -= 1;
      SetLCDBrightness(lcdBrightness);
      WriteLCDBrightnessScreen();
    }
  }
  if (inBMatrix == true) {
    if (matrixBrightness == minBrightnessValue) {
      matrixBrightness = minBrightnessValue;
    }
    else {
      matrixBrightness -= 1;
      SetMatrixBrightness(matrixBrightness);
      WriteMatrixBrightnessScreen();
    }
  }
  if (inSound == true) {
    soundOn = !soundOn;
    WriteSound();
  }
  if (inAbout == true) {
    if (aboutSlide == 0) {
      aboutSlide = 0;
    }
    else {
      aboutSlide -= 1;
      ShowAbout();
    }
  }
}

void WriteLCDBrightnessScreen() {
  ClearLCD();
  lcd.print("LCD Brightness");
  lcd.setCursor(0, 1);
  lcd.print("1");
  for(int i=minBrightnessValue;i<=maxBrightnessValue;i++) {
    if(i<=lcdBrightness){
    lcd.print((char)0);
    }
    else {
      lcd.print(" ");
    }
  }
  lcd.print("5");
}

void WriteMatrixBrightnessScreen() {
  ClearLCD();
  lcd.print("Matrix Brightness");
  lcd.setCursor(0, 1);
  lcd.print("1");
  for(int i=minBrightnessValue;i<=maxBrightnessValue;i++) {
    if(i<=matrixBrightness){
    lcd.print((char)0);
    }
    else {
      lcd.print(" ");
    }
  }
  lcd.print("5");
}

long int startedFlash = 0;
short intervalBlink = 500;
bool isPrinted = false;
String charToPrint = "_";

void LCDLoop() {
  if (inName == true) {
    lcd.setCursor(letterPos,1);
    if (millis() - startedFlash > intervalBlink)
    {
      if (isPrinted)
    {
      lcd.setCursor(letterPos, 1);
      lcd.print(alphabet[name[letterPos]]); 
      isPrinted = false;
    }
    else
    {
      lcd.setCursor(letterPos, 1);
      lcd.print("_"); 
      isPrinted = true;
    }
    startedFlash = millis();

  }
  }
}

void JoystickRight() {
  if (inName == true) {
    if(letterPos == 16) {
      letterPos = 16;
    }
    else {
      lcd.print(alphabet[name[letterPos]]);
      letterPos +=1;
    }
  }
  if (inBLCD == true) {
    if (lcdBrightness == maxBrightnessValue) {
      lcdBrightness = maxBrightnessValue;
    }
    else {
      lcdBrightness += 1;
      SetLCDBrightness(lcdBrightness); 
      WriteLCDBrightnessScreen();
    }
  }
  if (inBMatrix == true) {
    if (matrixBrightness == maxBrightnessValue) {
      matrixBrightness = maxBrightnessValue;
    }
    else {
      matrixBrightness += 1;
      SetMatrixBrightness(matrixBrightness); 
      WriteMatrixBrightnessScreen();
    }
  }
  if (inSound == true) {
    soundOn = !soundOn;
    WriteSound();
  }
  if (inAbout == true) {
    if(aboutSlide == 2) {
      aboutSlide = 2;
    }
    else {
      aboutSlide += 1;
      ShowAbout();
    }
  }
}



void MatrixSetup() {
  lc.shutdown(0, false); // turn off power saving, enables display
  SetMatrixBrightness(matrixBrightness);
  lc.clearDisplay(0);// clear screen
  matrix[xPos][yPos] = 1;
  rx = 3;
  ry = 3;
  matrix[rx][ry] = 2;
}

long lastBlink = 0;
int blinkTime = 200;
bool isShown = true;

void MatrixLoop() {
  if (inGame == true) {
    if(millis() - lastBlink > blinkTime)
    {
      if(isShown == true) {
        isShown = false;
      }
      else {
        isShown = true;
      }
      lc.setLed(0,rx,ry,isShown);
      lastBlink = millis();
    }
    if (matrixChanged = true) {
      // matrix display logic
      UpdateMatrix();
      matrixChanged = false;
    }
  }
}

void UpdateMatrix() {
  for (int row = 0; row < matrixSize; row++) {
    for (int col = 0; col < matrixSize; col++) {
      if(matrix[row][col] != 2) {
        lc.setLed(0, row, col, matrix[row][col]);
      }
    }
  }
}

void GameMoveUp() {
  if (xPos > 0) {
      xPos--;
    }
    else {
      xPos = matrixSize - 1;
    }
  GenerateRandomFood();
}

void GameMoveDown() {
  if (xPos < matrixSize - 1) {
      xPos++;
    } 
    else {
      xPos = 0;
    }
    GenerateRandomFood();
}

void GameMoveLeft() {
  
    if (yPos > 0) {
      yPos--;
    }
    else {
      yPos = matrixSize - 1;
    }
    GenerateRandomFood();
}

void GameMoveRight() {
  
    if (yPos < matrixSize - 1) {
      yPos++;
    } 
    else {
      yPos = 0;
    }
    GenerateRandomFood();
}

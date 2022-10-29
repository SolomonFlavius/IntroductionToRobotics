const int ledRedCarPin = 3;
const int ledYellowCarPin = 4;
const int ledGreenCarPin = 5;
const int ledGreenHumanPin = 6;
const int ledRedHumanPin = 7;
const int buttonPin = 2;
const int buzzerPin = 8;

byte buzzerState;
const int buzzerTone = 3000;
const int buzzerDuration = 100;

byte buttonState = HIGH;
byte lastButtonState;
byte reading;
byte ledGreenHumanState;

bool inState1 = true;
bool inState2 = false;
bool inState3 = false;
bool inState4 = false;
bool buttonPressedInState1 = false;

unsigned int lastDebounceTime = 0;
unsigned int debounceDelay = 50;

unsigned long previousMillis = 0;
unsigned long lastBeepMillis = 0;
unsigned long lastBlinkMillis = 0;
unsigned int timeState1 = 8000;
unsigned int timeState2 = 3000;
unsigned int timeState3 = 8000;
unsigned int timeState4 = 4000;

const int normalBeepInterval = 700;
const int fasterBeepInterval = 300;
const int blinkInterval = 500;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledRedCarPin, OUTPUT);
  pinMode(ledYellowCarPin, OUTPUT);
  pinMode(ledGreenCarPin, OUTPUT);
  pinMode(ledGreenHumanPin, OUTPUT);
  pinMode(ledRedHumanPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  state1();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;   
      if (buttonState == LOW && inState1) {
        buttonPressedInState1 = !buttonPressedInState1;
        previousMillis = millis();
      }
    }
  }
  lastButtonState = reading;

  if(inState1) {
    state1();
  }

  if (buttonPressedInState1 && millis() - previousMillis > timeState1) {
    inState1 = false;
    buttonPressedInState1 = !buttonPressedInState1;
    state2();
    inState2 = true;
    previousMillis = millis();
  }

  if(inState2 && millis() - previousMillis > timeState2) {
    state3();
    inState2 = false;
    inState3 = true;
    previousMillis = millis();
  }

  if(inState3) {
    if (millis() - lastBeepMillis >= normalBeepInterval) {
      lastBeepMillis = millis();
      if (buzzerState == LOW) {
        buzzerState = HIGH;
        tone(buzzerPin, buzzerTone, buzzerDuration);
      } 
      else {
        noTone(buzzerPin);
        buzzerState = LOW;
      }  
    }
    if (millis() - previousMillis > timeState3) {
      state4();
      inState3 = false;
      inState4 = true;
      previousMillis = millis();
    }
  }

  if(inState4) {
    if (millis() - lastBeepMillis >= fasterBeepInterval) {
      lastBeepMillis = millis();
      if (buzzerState == LOW) {
        buzzerState = HIGH;
        tone(buzzerPin, buzzerTone, buzzerDuration);
      } 
      else {
        noTone(buzzerPin);
        buzzerState = LOW;
      }  
    }
    if (millis() - lastBlinkMillis >= blinkInterval) {
      lastBlinkMillis = millis();
      digitalWrite(ledGreenHumanPin, !digitalRead(ledGreenHumanPin));  
    }
    if (millis() - previousMillis > timeState4) {
      state1();
      noTone(buzzerPin);
      inState4 = false;
      inState1 = true;
    }
  }

}

void state1() {    
  digitalWrite(ledGreenCarPin, HIGH);
  digitalWrite(ledRedHumanPin, HIGH);
  digitalWrite(ledGreenHumanPin, LOW);
  digitalWrite(ledRedCarPin, LOW);
  digitalWrite(ledYellowCarPin, LOW);
}

void state2() {
  digitalWrite(ledYellowCarPin, HIGH);
  digitalWrite(ledRedHumanPin, HIGH);
  digitalWrite(ledGreenCarPin, LOW);
  digitalWrite(ledGreenHumanPin, LOW);
  digitalWrite(ledRedCarPin, LOW);
}

void state3() {
  digitalWrite(ledRedCarPin, HIGH);
  digitalWrite(ledGreenHumanPin, HIGH);
  digitalWrite(ledGreenCarPin, LOW);
  digitalWrite(ledYellowCarPin, LOW);
  digitalWrite(ledRedHumanPin, LOW);
}

void state4() {
  digitalWrite(ledRedCarPin, HIGH);
  digitalWrite(ledGreenCarPin, LOW);
  digitalWrite(ledGreenHumanPin, LOW);
  digitalWrite(ledYellowCarPin, LOW);
  digitalWrite(ledRedHumanPin, LOW);
}

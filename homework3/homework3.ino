// pins for 7-segment
const int pinA = 4;
const int pinB = 5;
const int pinC = 6;
const int pinD = 7;
const int pinE = 8;
const int pinF = 9;
const int pinG = 10;
const int pinDP = 11;
const int segSize = 8;

// pins for joystick
const int pinSW = 2; 
// these 2 below are changed because the joystick stays on a side
const int pinX = A0; 
const int pinY = A1; 

// joystick variables
byte swState = LOW;
int xValue = 0;
int yValue = 0;
bool joyMovedX = false;
bool joyMovedY = false;
int minThreshold = 400;
int maxThreshold = 600;
bool commonAnode = false;
byte state = HIGH;
byte lastSwState = LOW;

// blinking variables
const int blinkDelay = 300;
unsigned long lastBlink = 0;
int blinkSegmentState = HIGH;

// long press
const int longPressTime = 5000;
unsigned long lastPressTime = 0;
unsigned int lastDebounce = 0;
unsigned long pressDuration = 0;
unsigned long pressedTime = 0;
unsigned long releasedTime = 0;

// enum for segments
enum Segment {
  a,b,c,d,e,f,g,dp
};

// pins array
int segments[segSize] = {
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

// segments values array
// 0 OFF 1 ON 2 ON IT 3 SELECTED
int segmentsState[segSize] = {
  3,0,0,0,0,0,0,0
};

// segment selection variables
int selectedSegment = 0;
int previousSegmentState = 0;
int chosenSegmentState = LOW;
bool changingState = false;

void setup() {
  for (int i = 0; i < segSize; i++) {
    pinMode(segments[i],OUTPUT);
  }
  if (commonAnode == true) {
    state = !state;
  }
  pinMode(pinSW, INPUT_PULLUP);
  Serial.begin(9600);
}
void loop() {
  WriteSegments();
  ReadJoystickMovement();

}

void WriteSegments() {
  for (int i = 0; i < segSize; i++) {
    if (segmentsState[i] < 2) { // ON or OFF
      digitalWrite(segments[i],segmentsState[i]);
    }
    // blinking
    if (segmentsState[i] == 3) {
      if (millis() - lastBlink >= blinkDelay) {
        lastBlink = millis();
        blinkSegmentState = !blinkSegmentState;
        digitalWrite(segments[i],blinkSegmentState);
      }
    }
    // selected with a press of a button
    if (segmentsState[i] == 4) {
      digitalWrite(segments[i],chosenSegmentState);
    }
  }
}

void ReadJoystickMovement() {
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);

  if (xValue < minThreshold && joyMovedX == false) {
    if (!changingState) {
      Move('l');
    }
    if (segmentsState[selectedSegment] == 4) {
      chosenSegmentState = !chosenSegmentState;
    }
    joyMovedX = true;
  }
  if (xValue > maxThreshold && joyMovedX == false) {
    if (!changingState) {
      Move('r');
    }
    if (segmentsState[selectedSegment] == 4) {
      chosenSegmentState = !chosenSegmentState;
    }
    joyMovedX = true;
  }
  if (xValue >= minThreshold && xValue <= maxThreshold) {
    joyMovedX = false;
  }

  if (yValue < minThreshold && joyMovedY == false) {
    if (!changingState) {
      Move('d');
    }
    joyMovedY = true;
  }
  if (yValue > maxThreshold && joyMovedY == false) {
    if (!changingState) {
      Move('u');
    }
    joyMovedY = true;
  }
  if (yValue >= minThreshold && yValue <= maxThreshold) {
    joyMovedY = false;
  }

  swState = digitalRead(pinSW);
  if (swState != lastSwState) {
    if (swState == LOW) {
      ButtonPressed();
      pressedTime = millis();
    }
  }
  if (swState == lastSwState && swState == LOW) {
    if (millis() - pressedTime >= longPressTime) {
      pressedTime = millis();
      ResetSegments();
    }
  }
  lastSwState = swState;
}

void Move(char direction) {
  switch (direction) {
    case 'r':
      switch (selectedSegment) {
        case Segment::a:
          ChangeSelectedSegment(Segment::a, Segment::b);
          selectedSegment = Segment::b;
          break;
        case Segment::c:
          ChangeSelectedSegment(Segment::c, Segment::dp);
          selectedSegment = Segment::dp;
          break;
        case Segment::d:
          ChangeSelectedSegment(Segment::d, Segment::c);
          selectedSegment = Segment::c;
          break;
        case Segment::e:
          ChangeSelectedSegment(Segment::e, Segment::c);
          selectedSegment = Segment::c;
          break;
        case Segment::f:
          ChangeSelectedSegment(Segment::f, Segment::b);
          selectedSegment = Segment::b;
          break;
        default:
          break;
      }
      break;
    case 'l':
      switch (selectedSegment) {
        case Segment::a:
          ChangeSelectedSegment(Segment::a, Segment::f);
          selectedSegment = Segment::f;
          break;
        case Segment::b:
          ChangeSelectedSegment(Segment::b, Segment::f);
          selectedSegment = Segment::f;
          break;
        case Segment::c:
          ChangeSelectedSegment(Segment::c, Segment::e);
          selectedSegment = Segment::e;
          break;
        case Segment::d:
          ChangeSelectedSegment(Segment::d, Segment::e);
          selectedSegment = Segment::e;
          break;
        case Segment::dp:
          ChangeSelectedSegment(Segment::dp, Segment::c);
          selectedSegment = Segment::c;
          break;
        default:
          break;
      }
    break;
    case 'd':
      switch (selectedSegment) {
        case Segment::a:
          ChangeSelectedSegment(Segment::a, Segment::g);
          selectedSegment = Segment::g;
          break;
        case Segment::b:
          ChangeSelectedSegment(Segment::b, Segment::g);
          selectedSegment = Segment::g;
          break;
        case Segment::c:
          ChangeSelectedSegment(Segment::c, Segment::d);
          selectedSegment = Segment::d;
          break;
        case Segment::e:
          ChangeSelectedSegment(Segment::e, Segment::d);
          selectedSegment = Segment::d;
          break;
        case Segment::f:
          ChangeSelectedSegment(Segment::f, Segment::g);
          selectedSegment = Segment::g;
          break;
        case Segment::g:
          ChangeSelectedSegment(Segment::g, Segment::d);
          selectedSegment = Segment::d;
          break;
        default:
          break;
      }
    break;
    case 'u':
      switch (selectedSegment) {
        case Segment::b:
          ChangeSelectedSegment(Segment::b, Segment::a);
          selectedSegment = Segment::a;
          break;
        case Segment::c:
          ChangeSelectedSegment(Segment::c, Segment::g);
          selectedSegment = Segment::g;
          break;
        case Segment::d:
          ChangeSelectedSegment(Segment::d, Segment::g);
          selectedSegment = Segment::g;
          break;
        case Segment::e:
          ChangeSelectedSegment(Segment::e, Segment::g);
          selectedSegment = Segment::g;
          break;
        case Segment::f:
          ChangeSelectedSegment(Segment::f, Segment::a);
          selectedSegment = Segment::a;
          break;
        case Segment::g:
          ChangeSelectedSegment(Segment::g, Segment::a);
          selectedSegment = Segment::a;
          break;
        default:
          break;
      }
    break;
  }
}

void ChangeSelectedSegment(int oldSegment, int newSegment) {
  segmentsState[oldSegment] = previousSegmentState;
  previousSegmentState = segmentsState[newSegment];
  segmentsState[newSegment] = 3;
}

void ButtonPressed() {
  if (segmentsState[selectedSegment] == 4) {
    segmentsState[selectedSegment] = 3;
    previousSegmentState = chosenSegmentState;
    changingState = false;
  }
  else {
    segmentsState[selectedSegment] = 4;
    changingState = true;
  }
}

void ResetSegments() {
  for (int i = 0; i < segSize; i++) {
    segmentsState[i] = 0;
  }
  segmentsState[0] = 3;
  selectedSegment = 0;
  previousSegmentState = 0;
  chosenSegmentState = LOW;
  changingState = false;
}


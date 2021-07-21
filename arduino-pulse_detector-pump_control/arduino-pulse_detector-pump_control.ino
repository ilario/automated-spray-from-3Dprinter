const int inputPin = A0;
const int outputPin = 13;
const int directionPin = 12;
const int thresholdUp = 100;
const int thresholdDown = 30;
const int maxTimeToOff = 650;
const int sleepDuration = 50;
const boolean invertedFlowBefore = false;
const int invertedFlowBeforeDuration = 100; 
const boolean invertedFlowAfter = false;
const int invertedFlowAfterDuration = 2000; 

int inputStatus = 0;
int statusOnOff = 0;
int statusOnOffPrevious = 0;
int timeToOff = 0;
int inputStatusPrevious = -1;

void setup() {
  // initialize serial communication at 2*9600 bits per second:
  Serial.begin(19200);
  // initialize digital pin enablePort as an output.
  pinMode(outputPin, OUTPUT);
  digitalWrite(outputPin, LOW);
  pinMode(directionPin, OUTPUT);
  digitalWrite(directionPin, HIGH);
}

void loop() {
  int inputValue = analogRead(inputPin);
  if (inputValue > thresholdUp) {
    inputStatus = 1;
  }
  if (inputValue < thresholdDown) {
    inputStatus = 0;
  }
  // check if inputStatus changed
  if (inputStatusPrevious == -1 || inputStatus == inputStatusPrevious) {
    timeToOff = max(timeToOff - sleepDuration, 0);
  } else {
    timeToOff = maxTimeToOff;
  }
  // store inputStatus value
  inputStatusPrevious = inputStatus;
  Serial.print("Input = ");
  Serial.print(inputValue);
  Serial.print(";\ttimeToOff =");
  Serial.print(timeToOff);
  // detect status
  if (timeToOff == 0) {
    statusOnOff = 0;
    Serial.print(";\tOFF");
    // apply OFF status
    digitalWrite(outputPin, LOW);
    delay(2);
  } else {
    statusOnOff = 1;
    Serial.print(";\tON");
    // apply ON status
    //digitalWrite(outputPin, LOW);
    //delay(2);
    digitalWrite(outputPin, HIGH);
    delay(2);
  }
  // pull back shortly for stirring the solution before spraying
  if (statusOnOff > statusOnOffPrevious) {
    Serial.print(";\t GOING ON");
    if (invertedFlowBefore) {
      Serial.print(";\tBACK FLOW");
      digitalWrite(outputPin, LOW);
      delay(2);
      digitalWrite(directionPin, LOW);
      delay(2);
      digitalWrite(outputPin, HIGH);
      delay(invertedFlowBeforeDuration);
      // reestablish the normal pump direction
      digitalWrite(outputPin, LOW);
      delay(2);
      digitalWrite(directionPin, HIGH);
      delay(2);
      digitalWrite(outputPin, HIGH);
    }
  }

  // pull back shortly for avoiding a thin tail of spray
  if (statusOnOff < statusOnOffPrevious) {
    Serial.print(";\tGOING OFF");
    if (invertedFlowAfter) {
      Serial.print(";\tBACK FLOW");
      digitalWrite(directionPin, LOW);
      delay(2);
      digitalWrite(outputPin, HIGH);
      delay(invertedFlowAfterDuration);
      digitalWrite(outputPin, LOW);
      delay(2);
      digitalWrite(directionPin, HIGH);
    }
  }
  Serial.println();
  // store status
  statusOnOffPrevious = statusOnOff;
  delay(sleepDuration);
}

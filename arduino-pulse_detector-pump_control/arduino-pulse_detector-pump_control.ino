// rev 20210730
const int inputPin = A0;
const int outputPin = 13;
const int PWMoutputPin = 6; // pin 5 and 6 has a PWM output of 980 Hz on Arduino Uno, double than the other PWM pins
const int PWMoutputValue = 50; // 0-255
const int directionInputPin = 8;
const int directionOutputPin = 12;
const int inputThresholdHigh = 100;
const int inputThresholdLow = 30;
const int maxTimeToOff = 650;
const int sleepDuration = 100;
const boolean invertedFlowBefore = false;
const int invertedFlowBeforeDuration = 100; 
const boolean invertedFlowAfter = false;
const int invertedFlowAfterDuration = 2000;
// how many voltage changes should be observed before starting the spray
const int observedTransientsMinimum = 2;

int inputStatus = 0;
int statusOnOff = 0;
int statusOnOffPrevious = 0;
int timeToOff = 0;
int inputStatusPrevious = -1;
int observedTransients = 0;

void setup() {
  // initialize serial communication at 2*9600 bits per second:
  Serial.begin(19200);
  // initialize digital pin enablePort as an output.
  pinMode(outputPin, OUTPUT);
  digitalWrite(outputPin, LOW);
  pinMode(directionOutputPin, OUTPUT);
  pinMode(directionInputPin, INPUT);
  analogWrite(PWMoutputPin, PWMoutputValue);
}

void loop() {
  int inputValue = analogRead(inputPin);
  if (inputValue > inputThresholdHigh) {
    inputStatus = 1;
  }
  if (inputValue < inputThresholdLow) {
    inputStatus = 0;
  }
  // check if inputStatus changed
  if (inputStatusPrevious == -1 || inputStatus == inputStatusPrevious) {
    timeToOff = max(timeToOff - sleepDuration, 0);
  } else {
    // some times, movement of any motor (X, Y or Z) triggers a voltage step in the extruder cable (e.g. initial auto homing), causing a false positive
    observedTransients = observedTransients + 1;
    if (observedTransients > observedTransientsMinimum) {
      timeToOff = maxTimeToOff;
    }
  }
  // store inputStatus value
  inputStatusPrevious = inputStatus;
  Serial.print(inputValue);
  Serial.print(";\t");
  Serial.print(timeToOff);
  // detect status
  if (timeToOff == 0) {
    statusOnOff = 0;
    Serial.print(";\tOFF");
    // apply OFF status
    digitalWrite(outputPin, LOW); delay(2);
  } else {
    statusOnOff = 1;
    Serial.print(";\tON");
    // apply ON status
    digitalWrite(outputPin, HIGH); delay(2);
  }
  // pull back shortly for stirring the solution before spraying
  if (statusOnOff > statusOnOffPrevious) {
    Serial.print(";\t GOING ON");
    if (invertedFlowBefore) {
      Serial.print(";\tBACK FLOW");
      digitalWrite(outputPin, LOW); delay(2);
      digitalWrite(directionOutputPin, LOW);
      // maybe is good to have some time off at direction changes
      delay(20);
      digitalWrite(outputPin, HIGH);
      delay(invertedFlowBeforeDuration);
      // reestablish the normal pump direction
      digitalWrite(outputPin, LOW); delay(2);
      digitalWrite(directionOutputPin, HIGH);
      // maybe is good to have some time off at direction changes
      delay(20);
      digitalWrite(outputPin, HIGH); delay(2);
    }
  }

  // pull back shortly for avoiding a thin tail of spray
  if (statusOnOff < statusOnOffPrevious) {
    Serial.print(";\tGOING OFF");
    // reset the counter
    observedTransients = 0;
    if (invertedFlowAfter) {
      Serial.print(";\tBACK FLOW");
      digitalWrite(outputPin, LOW); delay(2);
      digitalWrite(directionOutputPin, LOW);
      // maybe is good to have some time off at direction changes
      delay(20);
      digitalWrite(outputPin, HIGH);
      delay(invertedFlowAfterDuration);
      digitalWrite(outputPin, LOW); delay(2);
      digitalWrite(directionOutputPin, HIGH); delay(2);
    }
  }
  // store status
  statusOnOffPrevious = statusOnOff;
  directionInputStatus = digitalRead(directionInputPin);
  if (directionInputStatus == HIGH) {
    Serial.print(";\tBACK FLOW");
    // button is pressed, pulses of inverted flow direction
    digitalWrite(outputPin, LOW); delay(2);
    digitalWrite(directionOutputPin, LOW);
    // maybe is good to have some time off at direction changes
    delay(20);
    digitalWrite(outputPin, HIGH);
    delay(100);
    digitalWrite(outputPin, LOW);
    // maybe is good to have some time off at direction changes
    delay(20);
  } else {
    // button is not pressed, normal flow direction
    digitalWrite(directionOutputPin, HIGH); delay(2);
    digitalWrite(outputPin, HIGH); delay(2);
    delay(sleepDuration);
  }
  Serial.println();
}

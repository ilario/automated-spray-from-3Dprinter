// rev 20210831
const int inputPin = A0;
// a digital pin should be enough for the enable/disable connection but for some reason it does not work so an analog one is used
const int outputPin = 11;
const int PWMoutputPin = 6; // pin 5 and 6 has a PWM output of 980 Hz on Arduino Uno, double than the other PWM pins
// this is the flow of the pump, from 0 to 255
const int PWMoutputValue = 50; // 0-255
const int directionInputPin = 8;
const int directionOutputPin = 12;
const int inputThresholdHigh = 100;
const int inputThresholdLow = 30;
const int maxTimeToOff = 650;
const int sleepDuration = 100;
const boolean invertedFlowBefore = false;
const int invertedFlowBeforeDuration = 100; 
const boolean invertedFlowAfter = true;
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
  disable(); delay(1000);
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
    disable();
    //analogWrite(outputPin,0); delay(2);
  } else {
    statusOnOff = 1;
    Serial.print(";\tON");
    // apply ON status
    enable();
    //analogWrite(outputPin,255); delay(2);
  }
  if (statusOnOff > statusOnOffPrevious) {
    Serial.print(";\t GOING ON");
    // pull back shortly for stirring the solution before spraying
    if (invertedFlowBefore) {
      Serial.print(";\tBACK FLOW");
      disable();
      digitalWrite(directionOutputPin, LOW);
      // maybe is good to have some time off at direction changes
      delay(20);
      enable();
      delay(invertedFlowBeforeDuration);
      // reestablish the normal pump direction
      disable();
      digitalWrite(directionOutputPin, HIGH);
      // maybe is good to have some time off at direction changes
      delay(20);
      enable();
    }
  }

  if (statusOnOff < statusOnOffPrevious) {
    Serial.print(";\tGOING OFF");
    // reset the counter
    observedTransients = 0;
    // pull back shortly for avoiding a thin tail of spray
    if (invertedFlowAfter) {
      Serial.print(";\tBACK FLOW");
      disable();
      digitalWrite(directionOutputPin, LOW);
      // maybe is good to have some time off at direction changes
      delay(20);
      enable();
      delay(invertedFlowAfterDuration);
      disable();
      digitalWrite(directionOutputPin, HIGH); delay(2);
    }
  }
  // store status
  statusOnOffPrevious = statusOnOff;
  if (digitalRead(directionInputPin) == HIGH) {
    Serial.print(";\tBACK FLOW");
    // button is pressed, pulses of inverted flow direction
    disable();
    digitalWrite(directionOutputPin, LOW);
    // maybe is good to have some time off at direction changes
    delay(20);
    analogWrite(PWMoutputPin, 150);
    enable();
    delay(1000);
    analogWrite(PWMoutputPin, PWMoutputValue);
    disable();
    // maybe is good to have some time off at direction changes
    delay(20);
  } else {
    // button is not pressed, normal flow direction
    digitalWrite(directionOutputPin, HIGH); delay(2);
    delay(sleepDuration);
  }
  Serial.println();
}

void enable(){
  analogWrite(outputPin, 255); delay(2);
}

void disable(){
  analogWrite(outputPin, 0); delay(2);
}

#define fanPin 15
#define pumpPin 13

unsigned long msFan = 0;
unsigned long msFand = 0;

unsigned long msPump = 0;
unsigned long msPumpd = 0;

// Fan Variables:
int fanCounter = 0;
int fanRpmd = 0;
int fanState = 0;
int lastFanState = 0;

// Pump Variables:
int pumpCounter = 0;
int pumpRpmd = 0;
int pumpState = 0;
int lastPumpState = 0;

void setup() {
  // initialize the fan pin as an input:
  pinMode(fanPin, INPUT_PULLUP);

  // initialize the pump pin as a input:
  pinMode(pumpPin, INPUT_PULLUP);

  // initialize serial communication:
  Serial.begin(115200);
  while (!Serial);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  FAN_RPM_MONITOR();
  PUMP_RPM_MONITOR();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void FAN_RPM_MONITOR() {
  // read the pushbutton input pin:
  fanState = digitalRead(fanPin);
  if (fanState != lastFanState) {
    // if the state has changed, increment the counter
    if (fanState == LOW) {
      fanCounter++;
      msFan = millis();
    }
  }
  if ((fanState == lastFanState) && (millis() - msFan >= 1500)) {
    Serial.println("error: fan stop!");
    msFan = millis();
  }
  lastFanState = fanState;
  if ((millis() - msFand >= 500) && (fanCounter != 0)) {
    msFand = millis();
    fanRpmd = map(fanCounter, 0, 30, 0, 1800);
    //    fanRpmd = fanCounter;
    Serial.print("Fan RPM: ");
    Serial.println(fanRpmd);
    fanCounter = 0;
  }
}

void PUMP_RPM_MONITOR() {
  // read the pump input pin:
  pumpState = digitalRead(pumpPin);
  if (pumpState != lastPumpState) {
    // if the state has changed, increment the counter
    if (pumpState == LOW) {
      // if the current state is LOW then the button went from off to on:
      pumpCounter++;
      msPump = millis();
    }
  }
  if ((pumpState == lastPumpState) && (millis() - msPump >= 1500)) {
    Serial.println("error: pump stop!");
    msPump = millis();
  }
  lastPumpState = pumpState;
  if ((millis() - msPumpd >= 500) && (pumpCounter != 0)) {
    msPumpd = millis();
    pumpRpmd = map(pumpCounter, 0, 108, 0, 2600);
    //pumpRpmd = pumpCounter;
    Serial.print("Pump RPM: ");
    Serial.println(pumpRpmd);
    pumpCounter = 0;
  }
}

#define solarVoltage A0   //OK
#define chargingGate D1   //D1
#define RedLed D2
#define GreenLed D6
#define ledGate D5    //OK
#define batteryLevel D7   //OK

float solarMin =200 ;
bool ledState = false;

void setup() {
  Serial.begin(115200);
  Serial.println("Getting Started!");

  pinMode(solarVoltage, INPUT);
  pinMode(batteryLevel, INPUT);
  pinMode(chargingGate, OUTPUT);
  pinMode(RedLed, OUTPUT);
  pinMode(GreenLed, OUTPUT);
  pinMode(ledGate, OUTPUT);

  digitalWrite(chargingGate, HIGH);
  digitalWrite(ledGate, LOW);
  digitalWrite(RedLed, LOW);
  digitalWrite(GreenLed, LOW);

  if(analogRead(solarVoltage) <= solarMin)
    ledState = true;
  else
    ledState = false;
}

void loop() {
  int data = analogRead(solarVoltage);
  Serial.print("battery: ");
  Serial.println(digitalRead(batteryLevel));
  // Serial.println(data);
  delay(500);
  if (data <= solarMin) {
    Serial.print("DAY ");
    Serial.println(data);
    if (ledState) {
      ledState = false;
      digitalWrite(ledGate, LOW);
      Serial.println("LED OFF ");
      if (digitalRead(batteryLevel)) {
        digitalWrite(chargingGate, HIGH);
        digitalWrite(GreenLed, HIGH);  // if battery full charged GREEN led is ON
        digitalWrite(RedLed, LOW);
        Serial.println("charging off");
      } else {
        digitalWrite(chargingGate, LOW);
        Serial.println("charging on");
        digitalWrite(RedLed, HIGH);  // if charging RED led is ON
        digitalWrite(GreenLed, LOW);
      }
    }
  } else {
    Serial.print("NIGHT ");
      Serial.println(data);
    if (!ledState) {
      ledState = true;
      digitalWrite(ledGate, HIGH);
      Serial.println("LED ON");
      Serial.print("NIGHT ");
      digitalWrite(RedLed, LOW);  // Battery is nither charging nor full charged so both LED is OFF
      digitalWrite(GreenLed, LOW);
      digitalWrite(chargingGate, HIGH);
      Serial.println("charging OFF");
    }
  }
}

#define TRIGPIN 8
#define ECHOPIN 9
#define CTM 10
void setup(){
  Serial.begin(9600);
  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
}

unsigned long previousMillis = 0;
const long interval = 50;
float currentHz = 1500;

void loop(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    int dur;
    float dis;
    digitalWrite(TRIGPIN, HIGH);
    delayMicroseconds(CTM);
    digitalWrite(TRIGPIN, LOW);
    dur = pulseIn(ECHOPIN, HIGH, 30000);
    dis = constrain((float) dur*0.017, 10, 50); \\distance is from 10cm to 50cm
    Serial.print(dis);
    Serial.print("cm ");
    int baseHz = 2000 - (((dis - 10) / 80) * 1500);
    currentHz = currentHz + ((baseHz - currentHz)*0.2);
    float wave = sin(millis() * 0.02); 
    int a = analogRead(A0);
    int vivrato = map(a,0,1023,0,15);
    int finalHz = currentHz + (wave * vivrato);
    Serial.println(finalHz);
    if (dis < 10 || dis > 50){
      noTone(12);
    }
    else {
      tone(12, finalHz);
    }
  }
}
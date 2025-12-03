
const int ForwardA = 9;
const int BackwardA = 10;

const int ForwardB = 5;
const int BackwardB = 6;

int joyAVert = A0;
int joyAposVert = 512;
int spdA = 0;

int joyBVert = A1;
int joyBposVert = 512;
int spdB = 0;


void setup() {
  Serial.begin(9600);
  pinMode(ForwardA, OUTPUT);
  pinMode(BackwardA, OUTPUT);
  pinMode(ForwardB, OUTPUT);
  pinMode(BackwardB, OUTPUT);
}
void loop() {

  // Get user input for motorA
  joyAposVert = analogRead(joyAVert);
  spdA = map(abs(analogRead(joyAVert) - 512), 0, 512, 0, 255);

  // Get user input for motorB
  joyBposVert = analogRead(joyBVert);
  spdB = map(abs(analogRead(joyBVert) - 512), 0, 512, 0, 255);
  
  //MotorA
  if (joyAposVert < 440) {
    analogWrite(ForwardA, spdA);  // Set forward motor pin to MaxSpeed

  } else if (joyAposVert > 560) {
    analogWrite(BackwardA, spdA); // Set backward motor pin to MaxSpeed

  } else {
    analogWrite(ForwardA, 0);
    analogWrite(BackwardA, 0);
  }


  //MotorB
  if (joyBposVert < 440) {
    analogWrite(ForwardB, spdB);  // Set forward motor pin to MaxSpeed

  } else if (joyBposVert > 560) {
    analogWrite(BackwardB, spdB); // Set backward motor pin to MaxSpeed

  } else {
    analogWrite(ForwardB, 0);
    analogWrite(BackwardB, 0);
  }

}
int IR = 3;
int val = 0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(IR, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly
val = digitalRead(IR);
Serial.println(val);
}

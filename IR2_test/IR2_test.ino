const static int input = 11;
const static int led = 13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(input, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int input_val = digitalRead(input);
  Serial.println(input_val);

}

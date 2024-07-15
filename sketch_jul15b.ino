int x;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available())
  {}
    x = Serial.readString().toInt();

    Serial.print("Arduino sends: ");
    Serial.println(x + 1);
    Serial.flush();
  
}

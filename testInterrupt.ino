
volatile int state = HIGH;

void setup()
{
  pinMode(13, OUTPUT);
  attachInterrupt(0, blink, CHANGE);
}

void loop()
{
  digitalWrite(13, state);
}

void blink()
{
  state = !state;
}

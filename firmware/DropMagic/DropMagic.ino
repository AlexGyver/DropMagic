// усилитель (DAC) на D4
#define LED_PULSE 700   // длина вспышки, мкс
#define LED_PRD 19500   // период вспышек, мкс
bool ledFlag;
byte sinTable[256];
uint32_t tmrSin;
uint32_t tmrLED;
byte countSin;
#define PRD_50HZ 78     // синус 50 Гц 8 бит
#define LED_PIN 3       // пин светодиодов

void setup() {
  // заполняем таблицу синуса
  for (int i = 0; i < 256; i++) {
    sinTable[i] = (1 + sin((float)i * TWO_PI / 256)) / 2 * 255;
  }
  // настраиваем пины
  analogReference(DEFAULT);
  pinMode(DAC0, ANALOG);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // таймер синуса
  if (micros() - tmrSin >= PRD_50HZ) {
    tmrSin += PRD_50HZ;
    analogWrite(DAC0, sinTable[countSin++]);
  }
  // таймер вспышек
  if (micros() - tmrLED >= (ledFlag ? LED_PULSE : (LED_PRD - LED_PULSE))) {
    tmrLED += ledFlag ? LED_PULSE : (LED_PRD - LED_PULSE);
    digitalWrite(LED_PIN, ledFlag = !ledFlag);
  }
}

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#define SWITCH_PIN 2 // ขาเชื่อมต่อ Switch
#define LED_COUNT 8
const int leds[LED_COUNT] = {23, 19, 18, 5, 17, 16, 4, 0};

// สร้างออบเจกต์ LCD (ที่อยู่ I2C = 0x27, ขนาด 20x4)
LiquidCrystal_I2C lcd(0x27, 20, 4);

int menu = 1;

void setup() {
  lcd.init(); // เริ่มต้น LCD
  lcd.backlight(); // เปิดไฟแบ็คไลต์
  pinMode(SWITCH_PIN, INPUT_PULLUP);

  // ตั้งค่าขา LED ทั้งหมดเป็น OUTPUT
  for (int i = 0; i < LED_COUNT; i++) {
    pinMode(leds[i], OUTPUT);
  }

  lcd.setCursor(0, 0);
  lcd.print("Menu: ");
  lcd.print(menu);
}

void loop() {
  // ตรวจจับการกดปุ่มเพื่อเปลี่ยนเมนู
  static bool prevSwitchState = HIGH;
  bool currSwitchState = digitalRead(SWITCH_PIN);

  if (prevSwitchState == HIGH && currSwitchState == LOW) {
    menu++;
    if (menu > 6) menu = 1; // วนกลับมาที่เมนู 1
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Menu: ");
    lcd.print(menu);
  }
  prevSwitchState = currSwitchState;

  // ควบคุม LED ตามเมนูที่เลือก
  switch (menu) {
    case 1: // เมนู 1: เปิด LED ทั้งหมด
      for (int i = 0; i < LED_COUNT; i++) digitalWrite(leds[i], HIGH);
      break;

    case 2: // เมนู 2: กระพริบสลับคู่-คี่
      for (int i = 0; i < LED_COUNT; i++) digitalWrite(leds[i], i % 2 == 0 ? HIGH : LOW);
      delay(200);
      for (int i = 0; i < LED_COUNT; i++) digitalWrite(leds[i], i % 2 == 0 ? LOW : HIGH);
      delay(200);
      break;

    case 3: // เมนู 3: สว่างทีละหลอดวนไปเรื่อย ๆ
      for (int i = 0; i < LED_COUNT; i++) {
        digitalWrite(leds[i], HIGH);
        delay(200);
        digitalWrite(leds[i], LOW);
      }
      break;

    case 4: // เมนู 4: ติดเป็นคู่
      for (int i = 0; i < LED_COUNT; i += 2) {
        digitalWrite(leds[i], HIGH);
        if (i + 1 < LED_COUNT) digitalWrite(leds[i + 1], HIGH);
      }
      delay(200);
      for (int i = 0; i < LED_COUNT; i++) digitalWrite(leds[i], LOW);
      delay(200);
      break;

    case 5: // เมนู 5: สว่างเรียงแล้วดับกลับ
      for (int i = 0; i < LED_COUNT; i++) {
        digitalWrite(leds[i], HIGH);
        delay(200);
      }
      for (int i = LED_COUNT - 1; i >= 0; i--) {
        digitalWrite(leds[i], LOW);
        delay(200);
      }
      break;

    case 6: // เมนู 6: กระพริบทั้งหมดพร้อมกัน
      for (int i = 0; i < LED_COUNT; i++) digitalWrite(leds[i], HIGH);
      delay(200);
      for (int i = 0; i < LED_COUNT; i++) digitalWrite(leds[i], LOW);
      delay(200);
      break;

    default:
      break;
  }
}

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inicializa o LCD com endereço 0x27 e tamanho 16x2
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();              // Inicializa o LCD
  lcd.backlight();         // Liga a luz de fundo do LCD
  pinMode(12, INPUT);      // Configura o pino 12 como entrada
}

void loop() {
  if (digitalRead(12) == HIGH) {
    lcd.clear();                    // Limpa a tela antes de escrever
    lcd.setCursor(0, 0);            // Primeira linha, primeira coluna
    lcd.print("12ETC");
  } else {
    lcd.clear();                    // Limpa a tela antes de escrever
    lcd.setCursor(0, 0);            // Primeira linha, primeira coluna
    lcd.print("11ETC");
  }

  delay(500);  // Pequeno atraso para evitar flickering
}

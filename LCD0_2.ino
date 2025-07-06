#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inicializa o LCD no endereço 0x27, tamanho 16x2
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();          // Inicializa o LCD
  lcd.backlight();     // Liga a luz de fundo
  lcd.setCursor(0, 0); // Primeira linha, primeira coluna
  lcd.print("11ETC");  // Escreve a mensagem
}

void loop() {
  // Nada precisa ser feito aqui
}

const int stepPin = 3;    // Pino STEP do A4988
const int dirPin = 4;     // Pino DIR do A4988
const int enablePin = 5;  // Pino ENABLE (opcional)

void setup() {
  Serial.begin(9600);               // Inicia comunicação serial
  pinMode(stepPin, OUTPUT);         // Define os pinos como saída
  pinMode(dirPin, OUTPUT);
  pinMode(enablePin, OUTPUT);

  digitalWrite(enablePin, LOW);     // Ativa o driver A4988 (LOW ativa)

  // Limpa o buffer serial
  while (Serial.available() > 0) {
    Serial.read();
  }
}

void stepMotor(int steps, bool direction) {
  digitalWrite(dirPin, direction ? HIGH : LOW);  // Define a direção

  for (int i = 0; i < steps; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(800); // Controla a velocidade
    digitalWrite(stepPin, LOW);
    delayMicroseconds(800);
  }
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();

    if (command == 'U') {
      stepMotor(100, true);   // Movimento em uma direção (ex: subir)
    }
    else if (command == 'D') {
      stepMotor(100, false);  // Movimento oposto (ex: descer)
    }
  }
}

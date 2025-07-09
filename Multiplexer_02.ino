// Pinos de seleção do multiplexer
const int S0 = 2;
const int S1 = 3;
const int S2 = 4;
const int S3 = 5;

// Pino de sinal
const int SIG_PIN = A0;

// Pino Enable (se usares no Arduino)
const int EN = 6;

void setup() {
  Serial.begin(9600);

  // Configurar pinos de controle como saída
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  // Ativa o multiplexador (caso uses EN)
  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW);

  // SIG como entrada com pull-up ativado
  pinMode(SIG_PIN, INPUT_PULLUP);

  Serial.println("Iniciando leitura dos sensores magnéticos...");
}

void loop() {
  for (int channel = 0; channel < 16; channel++) {
    selectChannel(channel);

    // Lê valor do sensor (LOW = ativado)
    int sensorState = digitalRead(SIG_PIN);

    Serial.print("Sensor ");
    Serial.print(channel);
    Serial.print(" -> ");
    if (sensorState == LOW) {
      Serial.println("MAGNETO DETECTADO");
    } else {
      Serial.println("Sem ímã");
    }

    delay(100);
  }

  Serial.println("----------------");
  delay(1000);
}

// Seleciona canal no multiplexer
void selectChannel(int channel) {
  digitalWrite(S0, channel & 0x01);
  digitalWrite(S1, (channel >> 1) & 0x01);
  digitalWrite(S2, (channel >> 2) & 0x01);
  digitalWrite(S3, (channel >> 3) & 0x01);
}

int contador = 0;
int a = 13;
int b = 12;
int c = 11;
int d = 10;
int e = 9;
int f = 8;
int g = 7;

void setup() {
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
}

void loop() {
  // Desliga todos os segmentos
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);

  if (contador == 0) {
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
  }

  if (contador == 1) {
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
  }

  if (contador == 2) {
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(g, LOW);
    digitalWrite(e, LOW);
    digitalWrite(d, LOW);
  }

  if (contador == 3) {
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(g, LOW);
  }

  if (contador == 4) {
    digitalWrite(f, LOW);
    digitalWrite(g, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
  }

  if (contador == 5) {
    digitalWrite(a, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
  }

  if (contador == 6) {
    digitalWrite(a, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
  }

  if (contador == 7) {
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
  }

  if (contador == 8) {
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, LOW);
  }

  if (contador == 9) {
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, LOW);
  }

  delay(1000);
  contador++;

  if (contador == 10) {
    contador = 0;
  }
}

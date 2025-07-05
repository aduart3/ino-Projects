#include <WiFi.h>
#include <WebServer.h>
#include <map>

const char* ssid = "NOME_DO_WIFI";
const char* password = "SENHA_DO_WIFI";

WebServer server(80);

std::map<String, int> ledMap = {
  {"A3", 2}, {"B3", 4}, {"C3", 5},
  {"A2", 12}, {"B2", 13}, {"C2", 14},
  {"A1", 15}, {"B1", 18}, {"C1", 19}
};

String ledAtivo = "B2";  // LED inicial ativo

void desligarTodos() {
  for (auto const& par : ledMap) {
    digitalWrite(par.second, LOW);
  }
}

// Piscar todos os LEDs por 5 segundos
void piscarTodos() {
  unsigned long tempoInicio = millis();
  while (millis() - tempoInicio < 5000) {
    for (auto const& par : ledMap) {
      digitalWrite(par.second, HIGH);
    }
    delay(500);
    for (auto const& par : ledMap) {
      digitalWrite(par.second, LOW);
    }
    delay(500);
  }
  // Após piscar, liga só o LED ativo
  desligarTodos();
  digitalWrite(ledMap[ledAtivo], HIGH);
}

// Verifica se o movimento é válido (um passo em cima, baixo, esquerda ou direita)
bool movimentoValido(String atual, String destino) {
  if (atual.length() != 2 || destino.length() != 2) return false;

  char col1 = atual.charAt(0);
  char lin1 = atual.charAt(1);
  char col2 = destino.charAt(0);
  char lin2 = destino.charAt(1);

  int dcol = abs(col1 - col2);
  int dlin = abs(lin1 - lin2);

  return (dcol + dlin == 1);
}

String gerarPagina() {
  String html = "<html><body><h2>Matriz 3x3 - Controle de LED (ativo: " + ledAtivo + ")</h2>";
  html += "<table border='1' style='text-align:center;'>";

  String linhas[3] = {"3", "2", "1"};
  String colunas[3] = {"A", "B", "C"};

  for (int l = 0; l < 3; l++) {
    html += "<tr>";
    for (int c = 0; c < 3; c++) {
      String nome = colunas[c] + linhas[l];
      html += "<td><a href='/led?nome=" + nome + "' style='font-size:20px;'>" + nome + "</a></td>";
    }
    html += "</tr>";
  }

  html += "</table></body></html>";
  return html;
}

void setup() {
  Serial.begin(115200);

  for (auto const& par : ledMap) {
    pinMode(par.second, OUTPUT);
    digitalWrite(par.second, LOW);
  }

  digitalWrite(ledMap[ledAtivo], HIGH);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado!");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, []() {
    server.send(200, "text/html", gerarPagina());
  });

  server.on("/led", HTTP_GET, []() {
    String nome = server.arg("nome");
    nome.trim();
    nome.toUpperCase();

    if (!ledMap.count(nome)) {
      server.send(400, "text/plain", "LED inválido.");
      return;
    }

    if (!movimentoValido(ledAtivo, nome)) {
      piscarTodos();
      server.send(200, "text/html", "<p>Movimento inválido! LEDs piscando...</p><a href='/'>Voltar</a>");
      return;
    }

    desligarTodos();
    digitalWrite(ledMap[nome], HIGH);
    ledAtivo = nome;

    server.send(200, "text/html", "<p>LED " + nome + " aceso</p><a href='/'>Voltar</a>");
  });

  server.begin();
}

void loop() {
  server.handleClient();
}

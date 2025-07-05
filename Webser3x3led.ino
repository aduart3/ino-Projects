#include <WiFi.h>
#include <WebServer.h>
#include <map>

const char* ssid = "NOME_DO_WIFI";
const char* password = "SENHA_DO_WIFI";

WebServer server(80);

// Mapeamento LED nome → GPIO
std::map<String, int> ledMap = {
  {"A3", 2}, {"B3", 4}, {"C3", 5},
  {"A2", 12}, {"B2", 13}, {"C2", 14},
  {"A1", 15}, {"B1", 18}, {"C1", 19}
};

// Desliga todos os LEDs
void desligarTodos() {
  for (auto const& par : ledMap) {
    digitalWrite(par.second, LOW);
  }
}

// Página com botões/links
String gerarPagina() {
  String html = "<html><body><h2>Matriz 3x3 - Controle de LED</h2>";
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

  // Inicializa os pinos
  for (auto const& par : ledMap) {
    pinMode(par.second, OUTPUT);
    digitalWrite(par.second, LOW);
  }

  // Conecta ao Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("\nWiFi conectado!");
  Serial.println(WiFi.localIP());

  // Página principal
  server.on("/", HTTP_GET, []() {
    server.send(200, "text/html", gerarPagina());
  });

  // Rota /led?nome=A2
  server.on("/led", HTTP_GET, []() {
    String nome = server.arg("nome");
    nome.trim(); nome.toUpperCase();

    if (ledMap.count(nome)) {
      desligarTodos();
      digitalWrite(ledMap[nome], HIGH);
      server.send(200, "text/html", "<p>LED " + nome + " aceso</p><a href='/'>Voltar</a>");
    } else {
      server.send(400, "text/plain", "LED inválido.");
    }
  });

  server.begin();
}

void loop() {
  server.handleClient();
}

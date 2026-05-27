// ================================================================
//  CTRL::PANEL — Arduino UNO
//  Controle de Lâmpadas via Web Serial (9600 baud)
//
//  COMPONENTES:
//    - Relé 1  → pino Digital 2  (Lâmpadas 1)
//    - Relé 2  → pino Digital 3  (Lâmpadas 2)
//
//  PROTOCOLO — Interface → Arduino:
//    "rele1 on"        → liga   Lâmpadas 1
//    "rele1 off"       → desliga Lâmpadas 1
//    "rele2 on/off"    → liga/desliga Lâmpadas 2
//    "brilho1 <0-100>" → intensidade Lâmpadas 1 (PWM se disponível)
//    "brilho2 <0-100>" → intensidade Lâmpadas 2
//    "status"          → retorna estado de todos os relés
//
//  PROTOCOLO — Arduino → Interface:
//    "RELE1:ON"        / "RELE1:OFF"
//    "RELE2:ON"        / "RELE2:OFF"
//    "BRILHO1:XX"      (0-100)
//    "BRILHO2:XX"
//    "PRONTO"
// ================================================================

// ── PINOS ────────────────────────────────────────────────────────
#define RELE1_PIN  2
#define RELE2_PIN  3

// ── ESTADO ───────────────────────────────────────────────────────
bool   rele[3]   = {false, false, false}; // índices 1-2
int    brilho[3] = {0, 100, 100};         // % (0-100), índices 1-2
String inputBuffer = "";

// ── MAPEAMENTO PINO ──────────────────────────────────────────────
int pinRele(int n) {
  if (n == 1) return RELE1_PIN;
  if (n == 2) return RELE2_PIN;
  return -1;
}

// ================================================================
void setup() {
  Serial.begin(9600);

  pinMode(RELE1_PIN, OUTPUT);
  pinMode(RELE2_PIN, OUTPUT);

  // Módulos relé ativo em LOW → inicializa HIGH (desligado)
  digitalWrite(RELE1_PIN, HIGH);
  digitalWrite(RELE2_PIN, HIGH);

  Serial.println("PRONTO");
}

// ================================================================
void loop() {
  lerSerial();
}

// ================================================================
void lerSerial() {
  while (Serial.available() > 0) {
    char c = (char)Serial.read();
    if (c == '\n' || c == '\r') {
      inputBuffer.trim();
      if (inputBuffer.length() > 0) {
        processarComando(inputBuffer);
        inputBuffer = "";
      }
    } else {
      inputBuffer += c;
    }
  }
}

// ================================================================
void processarComando(String cmd) {
  cmd.trim();
  cmd.toLowerCase();

  // ── RELE N ON/OFF ────────────────────────────────────────────
  for (int n = 1; n <= 2; n++) {
    String prefOn  = "rele" + String(n) + " on";
    String prefOff = "rele" + String(n) + " off";

    if (cmd == prefOn) {
      rele[n] = true;
      digitalWrite(pinRele(n), LOW);   // LOW = ativa relé
      Serial.println("RELE" + String(n) + ":ON");
      return;
    }
    if (cmd == prefOff) {
      rele[n] = false;
      digitalWrite(pinRele(n), HIGH);  // HIGH = desativa relé
      Serial.println("RELE" + String(n) + ":OFF");
      return;
    }
  }

  // ── BRILHO N <0-100> ─────────────────────────────────────────
  for (int n = 1; n <= 2; n++) {
    String pref = "brilho" + String(n) + " ";
    if (cmd.startsWith(pref)) {
      int pct = constrain(cmd.substring(pref.length()).toInt(), 0, 100);
      brilho[n] = pct;
      // Nota: relés são on/off — o brilho é armazenado e enviado de volta
      // para a interface usar como referência visual. Se usar dimmer externo
      // via PWM, substitua a linha abaixo por analogWrite(pinRele(n), map(pct,0,100,0,255))
      Serial.println("BRILHO" + String(n) + ":" + String(pct));
      return;
    }
  }

  // ── STATUS GERAL ─────────────────────────────────────────────
  if (cmd == "status") {
    for (int n = 1; n <= 2; n++) {
      Serial.println("RELE"   + String(n) + ":" + (rele[n]   ? "ON" : "OFF"));
      Serial.println("BRILHO" + String(n) + ":" + String(brilho[n]));
    }
    return;
  }

  // ── DESCONHECIDO ─────────────────────────────────────────────
  Serial.println("ERRO:CMD>" + cmd);
}



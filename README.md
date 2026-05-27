# 💡 Controle de Luz — Arduino + Interface Web

Aviso:

- **UTILIZAMOS O FIGMA APENAS PARA REALIZAR O DESIGN DAS TELAS, TODAS AS FUNÇÕES DO FRONT-END FORAM FEITAS EM Html / Css / React / Web Serial API.**

- **No figma, não tem funções das telas integradas.**

--> DESENVOLVIDO PELOS ESTUDANTES: 

Henderson Lério Grossi - RA: 26000986

Pietro Emanuel da Silva Batista - RA: 26000307

Kauê Valério Baesso - RA: 26001167

Washington Luiz da Silva - RA: 26001289
---------------------------------------------

Sistema de controle de iluminação para sala de aula desenvolvido com Arduino UNO e interface web em React. Permite ligar e desligar lâmpadas remotamente pelo computador ou celular via cabo USB, sem necessidade de internet.

---

## 📋 Sobre o Projeto

Este projeto foi desenvolvido como trabalho acadêmico e demonstra a integração de conceitos de **IoT**, **programação**, **interface web** e **redes e comunicação serial**.

O sistema utiliza um Arduino UNO para controlar um módulo relé de 2 canais, permitindo o acionamento de até 2 circuitos de iluminação independentes através de uma interface visual moderna rodando no navegador.

---

## 🛠️ Materiais Necessários

| Componente | Quantidade |
|---|---|
| Arduino UNO | 1 |
| Módulo Relé 2 Canais 5V | 1 |
| Cabo USB tipo B | 1 |
| Fios Jumper macho-fêmea | 4 |
| Fonte 12V (mínimo 1A) | 1 |
| Bocal E27 com fios | 1 ou 2 |
| Lâmpada LED 12V E27 | 1 ou 2 |

---

## 🔌 Esquema de Ligação

### Arduino → Módulo Relé

| Arduino | Módulo Relé |
|---|---|
| 5V | VCC |
| GND | GND |
| Pino 2 | IN1 |
| Pino 3 | IN2 |

### Circuito da Lâmpada (por canal)

Fonte 12V (+) ──► COM ──► NO ──► Fio 1 do bocal
                                   Lâmpada
Fonte 12V (-)  ────────────────► Fio 2 do bocal

---

## 📁 Arquivos do Projeto


controle-de-luz-arduino/
arduino_control.ino       # Código do Arduino
front_pi.html             # Interface web (React + Web Serial API + html + css)
documentacao_codigo.docx  # Documentação técnica completa do código
README.md                 # Este arquivo

---

## 🚀 Como Usar

### 1. Gravar o código no Arduino

1. Baixe e instale o [Arduino IDE](https://www.arduino.cc/en/software)
2. Abra o arquivo `arduino_control.ino`
3. Selecione **Ferramentas → Placa → Arduino UNO**
4. Selecione **Ferramentas → Porta** → escolha a porta COM do Arduino
5. Clique em **Carregar** (seta →)
6. Aguarde a mensagem `PRONTO` no Monitor Serial (9600 baud)

### 2. Abrir a interface

1. Abra o arquivo `front_pi.html` no **Chrome** ou **Edge**
2. Faça login com as credenciais:
   - **Usuário:** `admin`
   - **Senha:** `admin`
3. Clique em **Conectar**
4. Selecione a porta do Arduino na janela que aparecer
5. Aguarde a mensagem `PRONTO` no log serial

> ⚠️ A Web Serial API só funciona no **Chrome** e **Edge**. Não funciona no Firefox ou Safari.

> ⚠️ Feche o Monitor Serial do Arduino IDE antes de conectar pela interface — a porta serial só pode ser usada por um programa de cada vez.

---

## 📡 Protocolo de Comunicação

### Interface → Arduino

| Comando | Ação |
|---|---|
| `rele1 on` | Liga Lâmpadas 1 |
| `rele1 off` | Desliga Lâmpadas 1 |
| `rele2 on` | Liga Lâmpadas 2 |
| `rele2 off` | Desliga Lâmpadas 2 |
| `brilho1 <0-100>` | Define intensidade Lâmpadas 1 |
| `brilho2 <0-100>` | Define intensidade Lâmpadas 2 |
| `status` | Retorna estado atual de todos os relés |

### Arduino → Interface

| Resposta | Significado |
|---|---|
| `PRONTO` | Arduino inicializado e pronto |
| `RELE1:ON` / `RELE1:OFF` | Confirmação estado Lâmpadas 1 |
| `RELE2:ON` / `RELE2:OFF` | Confirmação estado Lâmpadas 2 |
| `BRILHO1:XX` | Confirmação intensidade Lâmpadas 1 |
| `BRILHO2:XX` | Confirmação intensidade Lâmpadas 2 |

---

## 🖥️ Funcionalidades da Interface

- 🔐 Tela de login com autenticação
- 💡 Ligar/desligar cada lâmpada individualmente
- ⚡ Ligar/desligar todas as lâmpadas de uma vez
- 🔆 Controle de intensidade por slider (0–100%)
- 📋 Log serial em tempo real
- 🔔 Painel de notificações com histórico de ações
- 🌙 Tema claro e escuro
- 📱 Interface responsiva (funciona em celular e computador)

---

## 🧰 Tecnologias Utilizadas

| Tecnologia | Uso |
|---|---|
| C++ (Arduino) | Controle do hardware e comunicação serial |
| React 18 | Interface web reativa |
| Web Serial API | Comunicação USB entre navegador e Arduino |
| Babel CDN | Compilação JSX no navegador |
| CSS Variables | Temas claro e escuro |

---

## ⚠️ Observações

- **O PROJETO SIMULA O USO REAL, NÃO FOI FEITO NESSE SEMESTRE PARA FUNCIONAR NO CAMPUS.**

- O módulo relé é **ativo em LOW** — nível BAIXO (0V) liga o relé, nível ALTO (5V) desliga.

- Para uso com lâmpadas da **rede elétrica (127/220V)**, a instalação deve ser feita por um eletricista.
  
- Para testes seguros, utilize lâmpadas **12V** alimentadas por fonte DC.

---

## 📄 Licença

Projeto acadêmico de uso livre. Pode ser modificado e redistribuído.

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// --- SIMULATION DE LA BIBLIOTHÈQUE BRIDGE EN PANNE ---
class BridgeMock {
public:
  void begin() {}
  void get(const char* k, char* v, int l) { strcpy(v, "OK"); } // Renvoie "OK" par défaut
};
BridgeMock Bridge;
// -----------------------------------------------------

// Configuration de l'écran LCD (Adresse standard 0x27)
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo monServo;

// --- CONFIGURATION DES BROCHES SÉCURISÉES POUR ARDUINO YÚN ---
const int pinPIR = 1;      // Capteur mouvement (D1)
const int ledRouge = 6;    // LED RGB Rouge (D6)
const int ledVert = 5;     // LED RGB Vert (D5)
const int ledBleu = 13;    // LED RGB Bleu (D13)
const int pinTrig = 9;     // Ultrason Trig (D9)
const int pinEcho = 8;     // Ultrason Echo (D8)
const int pinServo = 10;   // Servomoteur (D10)
const int pinBuzzer = 11;  // Buzzer (D11)
const int pinMQ2 = A0;     // Capteur de gaz (A0)

// --- DRIVER MOTEUR L298N (PROPULSION UNIQUE SANS ENB/IN3/IN4) ---
const int IN1 = 4;  // Direction Moteur (D4)
const int IN2 = 7;  // Direction Moteur (D7)
const int ENA = 12; // Vitesse PWM (D12)

// --- VARIABLES DE CONTRÔLE ---
int angleActuel = 90;
int directionServo = 5;
const int SEUIL_GAZ = 350; // Seuil d'alerte ajustable selon l'air ambiant
int modePrecedent = -1;
char texteRick[64]; // Tampon de réception pour les chaînes réseau Wi-Fi

void setup() {
  // Lancement du pont Wi-Fi/Linux (Bloque le code ~2 secondes au démarrage)
  Bridge.begin();
  Serial.begin(9600);

  // Initialisation du LCD et du Servomoteur
  lcd.init();
  lcd.backlight();
  monServo.attach(pinServo);
  monServo.write(90);

  // Configuration des Entrées / Sorties
  pinMode(pinPIR, INPUT);
  pinMode(pinMQ2, INPUT);
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
  pinMode(pinBuzzer, OUTPUT);
  pinMode(ledRouge, OUTPUT);

  //COMMUNICATION ENTRE PYTHON ET ARDUINO


LiquidCrystal_I2C lcd(0x27,16,2);

const int capteur = 2;

String message = "";

void setup() {

  pinMode(capteur, INPUT);

  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
}


void loop() {

  if (Serial.available()) {

    message = Serial.readStringUntil('\n');
    message.trim();

    Serial.println("Recu : " + message);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(message);
  }
}
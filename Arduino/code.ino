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
String messagePython = ""; // Message reçu depuis Python via le port série

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
  pinMode(ledVert, OUTPUT);
  pinMode(ledBleu, OUTPUT);

  // Configuration du pont en H (Uniquement les 3 broches du Canal A)
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  // Séquence d'allumage du RickLab™
  lcd.setCursor(0, 0);
  lcd.print("RICK GUARDIAN tm");
  lcd.setCursor(0, 1);
  lcd.print("PRODUCTION MODE");
  allumerLED(0, 255, 255); // Cyan au démarrage
  stopRobot();
  delay(2000);
  lcd.clear();
}

void loop() {
  // 0. RÉCEPTION DU MESSAGE ENVOYÉ PAR PYTHON (VIA LE PORT SÉRIE)
  if (Serial.available()) {
    messagePython = Serial.readStringUntil('\n');
    messagePython.trim();
  }

  // 1. INTERCEPTION DES ALERTES WI-FI DE RICK (Réseau Linux)
  Bridge.get("danger", texteRick, 64);
  String motDanger = String(texteRick);

  // 2. LECTURE CONSTANTE DES CAPTEURS PHYSIQUES
  bool mouvement = digitalRead(pinPIR);
  int valeurGaz = analogRead(pinMQ2);

  // Mesure de distance par le capteur ultrason HC-SR04
  digitalWrite(pinTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);
  long duree = pulseIn(pinEcho, HIGH);
  int distance = duree * 0.034 / 2;

  // 3. MACHINE D'ÉTAT (Hiérarchie des modes de sécurité)
  int modeActuel = 0;
  if (messagePython == "NON VALIDE") {
    modeActuel = 4; // Priorité 1 : Mot interdit détecté depuis Python (analyse IA)
  } else if (valeurGaz > SEUIL_GAZ) {
    modeActuel = 3; // Priorité 2 : Taux de gaz toxique critique
  } else if (!mouvement) {
    modeActuel = 0; // Priorité 3 : Mode Veille (Laboratoire vide)
  } else if (distance > 0 && distance < 20) {
    modeActuel = 2; // Priorité 4 : Obstacle proche détecté par le scanner
  } else {
    modeActuel = 1; // Mode Patrouille active nominale
  }

  // Algorithme Anti-Freeze : Efface l'écran uniquement si le mode change
  if (modeActuel != modePrecedent) {
    lcd.clear();
    modePrecedent = modeActuel;
  }

  // 4. EXÉCUTION DES PROTOCOLES ET DES MOUVEMENTS
  switch (modeActuel) {
    case 4: // --- MODE DANGER LOGICIEL (ANALYSE PYTHON) ---
      stopRobot();
      allumerLED(255, 0, 0); // Rouge
      monServo.write(90);
      lcd.setCursor(0, 0);
      lcd.print("! WEB FORBIDDEN !");
      lcd.setCursor(0, 1);
      lcd.print(messagePython);
      declencherBuzzer(400);
      break;

    case 3: // --- MODE DANGER GAZ PHYSIQUE ---
      stopRobot();
      allumerLED(255, 0, 0); // Rouge
      monServo.write(90);
      lcd.setCursor(0, 0);
      lcd.print("!! DANGER GAZ !!");
      lcd.setCursor(0, 1);
      lcd.print("Taux: " + String(valeurGaz) + " ppm");
      declencherBuzzer(200);
      break;

    case 0: // --- MODE VEILLE NOMINALE ---
      stopRobot();
      noTone(pinBuzzer);
      allumerLED(0, 0, 255); // Bleu
      monServo.write(90);
      lcd.setCursor(0, 0);
      lcd.print("STANDBY MODE");
      lcd.setCursor(0, 1);
      lcd.print("ATTENTE PRESENCE");
      delay(200);
      break;

    case 2: // --- PROTOCOLE D'ÉVITEMENT (RECUL) ---
      reculer(); // Marche arrière adaptative sur un seul moteur
      noTone(pinBuzzer);
      allumerLED(255, 100, 0); // Orange
      lcd.setCursor(0, 0);
      lcd.print("OBSTACLE DETECTE");
      lcd.setCursor(0, 1);
      lcd.print("RECUL DE SECOURS");
      delay(300);
      break;

    case 1: // --- MODE PATROUILLE EN MARCHE ---
      avancer();
      noTone(pinBuzzer);
      allumerLED(0, 255, 0); // Vert
      lcd.setCursor(0, 0);
      lcd.print("PATROL: ACTIVE");
      lcd.setCursor(0, 1);
      lcd.print("G:" + String(valeurGaz) + " | Dist:" + String(distance));

      // Balayage angulaire automatique de la tourelle ultrason
      monServo.write(angleActuel);
      angleActuel += directionServo;
      if (angleActuel >= 135 || angleActuel <= 45) {
        directionServo = -directionServo;
      }
      delay(150);
      break;
  }
}

// --- FONCTIONS DE CONTRÔLE DE L'UNIQUE MOTEUR ACTIF ---
void avancer() {
  analogWrite(ENA, 170); // Puissance calibrée pour ligne droite (0 - 255)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void reculer() {
  analogWrite(ENA, 140); // Vitesse réduite en marche arrière
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void stopRobot() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
}

// --- CORRECTIF : INVERSION LOGIQUE POUR LED ANODE COMMUNE ---
void allumerLED(int r, int g, int b) {
  // On soustrait la valeur à 255 pour inverser le signal
  analogWrite(ledRouge, 255 - r);
  analogWrite(ledVert, 255 - g);
  analogWrite(ledBleu, 255 - b);
}

// --- CORRECTIF : INVERSION LOGIQUE POUR MODULE BUZZER ACTIF ---
void declencherBuzzer(int delai) {
  digitalWrite(pinBuzzer, LOW);  // ÉTAT INVERSÉ : LOW allume ce type de module
  delay(delai);
  digitalWrite(pinBuzzer, HIGH); // ÉTAT INVERSÉ : HIGH l'éteint
  delay(delai);
}

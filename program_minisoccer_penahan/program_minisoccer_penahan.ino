#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

// ==========================================
// 1. KONFIGURASI BLUETOOTH
// ==========================================

const char* bluetoothName = "ROBOT_PENAHAN";

// ==========================================
// 2. PIN DRIVER MOTOR L298N
// ==========================================

// Motor kiri
#define ENA 33
#define IN1 14
#define IN2 27

// Motor kanan
#define ENB 32
#define IN3 26
#define IN4 25

// ==========================================
// 3. PENGATURAN KECEPATAN
// ==========================================

int speedMotor = 250;

// Kalibrasi kecepatan gerakan lurus
// Nilai ini merupakan nilai percobaan awal
float correctionLeft = 0.950;
float correctionRight = 1.00;

char currentMotion = 'S';

unsigned long lastCommandTime = 0;
const unsigned long safetyTimeout = 1000;

// ==========================================
// 4. PENGATURAN KECEPATAN MOTOR
// ==========================================

// Digunakan untuk maju dan mundur
void applyStraightSpeed() {

  int speedLeft = constrain(
    (int)(speedMotor * correctionLeft),
    0,
    255
  );

  int speedRight = constrain(
    (int)(speedMotor * correctionRight),
    0,
    255
  );

  analogWrite(ENA, speedLeft);
  analogWrite(ENB, speedRight);
}

// Digunakan untuk gerakan belok
void applyTurnSpeed() {

  analogWrite(ENA, speedMotor);
  analogWrite(ENB, speedMotor);
}

// ==========================================
// 5. FUNGSI MOTOR
// ==========================================

void stopRobot() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  currentMotion = 'S';
}

// Gerakan maju
void maju() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  applyStraightSpeed();

  currentMotion = 'F';
}

// Gerakan mundur
void mundur() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  applyStraightSpeed();

  currentMotion = 'B';
}

// Gerakan kiri
void kiri() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  applyTurnSpeed();

  currentMotion = 'L';
}

// Gerakan kanan
void kanan() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  applyTurnSpeed();

  currentMotion = 'R';
}

// ==========================================
// 6. MEMPERBARUI KECEPATAN
// ==========================================

void updateSpeed() {

  switch (currentMotion) {

    case 'F':
      maju();
      break;

    case 'B':
      mundur();
      break;

    case 'L':
      kiri();
      break;

    case 'R':
      kanan();
      break;

    default:
      stopRobot();
      break;
  }
}

// ==========================================
// 7. MEMPROSES PERINTAH BLUETOOTH
// ==========================================

void processCommand(char command) {

  // Mengubah huruf kecil menjadi huruf besar
  if (command >= 'a' && command <= 'z') {
    command = command - 32;
  }

  Serial.print("Perintah diterima: ");
  Serial.println(command);

  switch (command) {

    case 'F':
      maju();
      break;

    case 'B':
      mundur();
      break;

    case 'L':
      kiri();
      break;

    case 'R':
      kanan();
      break;

    case 'S':
      stopRobot();
      break;

    // Kecepatan rendah
    case '1':
      speedMotor = 100;
      updateSpeed();
      break;

    // Kecepatan sedang
    case '2':
      speedMotor = 170;
      updateSpeed();
      break;

    // Kecepatan tinggi
    case '3':
      speedMotor = 255;
      updateSpeed();
      break;

    default:
      return;
  }

  lastCommandTime = millis();
}

// ==========================================
// 8. SETUP
// ==========================================

void setup() {

  Serial.begin(115200);

  // Konfigurasi pin motor
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Pastikan robot berhenti saat awal
  stopRobot();

  // Aktifkan Bluetooth Classic
  SerialBT.begin(bluetoothName);

  Serial.println();
  Serial.println("==============================");
  Serial.println(" MINI SOCCER ROBOT ESP32");
  Serial.println("==============================");

  Serial.print("Bluetooth: ");
  Serial.println(bluetoothName);

  Serial.println("Status: Menunggu koneksi HP");
  Serial.println("==============================");
}

// ==========================================
// 9. LOOP UTAMA
// ==========================================

void loop() {

  // Membaca data Bluetooth
  while (SerialBT.available()) {

    char command = SerialBT.read();

    // Abaikan karakter enter
    if (command == '\n' || command == '\r') {
      continue;
    }

    processCommand(command);
  }

  // Pengaman ketika Bluetooth terputus
  if (!SerialBT.hasClient()) {

    if (currentMotion != 'S') {
      stopRobot();
      Serial.println("Bluetooth terputus: Robot berhenti!");
    }
  }

  // Pengaman jika perintah terhenti
  else if (
    currentMotion != 'S' &&
    millis() - lastCommandTime > safetyTimeout
  ) {

    stopRobot();

    Serial.println("TIMEOUT: Robot berhenti!");
  }
}
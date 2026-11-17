# 🤖 Mini Soccer Robot — ESP32

Proyek robot mini soccer berbasis **ESP32** yang dirancang untuk menjalankan strategi permainan sebagai robot penyerang dan robot penahan. Robot dikendalikan menggunakan komunikasi Bluetooth melalui smartphone.

## 📌 Deskripsi Proyek

Mini Soccer Robot merupakan proyek robotika yang mengimplementasikan sistem kendali motor, komunikasi Bluetooth, dan pemrograman mikrokontroler ESP32.

Proyek ini memiliki dua program robot dengan peran berbeda:

- **Robot Penyerang:** Program kendali robot untuk menjalankan peran menyerang dalam permainan mini soccer.
- **Robot Penahan:** Program kendali robot untuk menjalankan peran bertahan dan menghalau serangan lawan.

## 🛠️ Teknologi dan Komponen

- ESP32 DevKit V1 / ESP-WROOM-32
- Motor Driver L298N
- Motor DC
- Bluetooth
- Arduino IDE
- Arduino Bluetooth Controller

## ⚙️ Konfigurasi Pin

| Komponen | Pin ESP32 |
|---|---|
| ENA (Motor kiri) | GPIO 33 |
| IN1 (Motor kiri) | GPIO 14 |
| IN2 (Motor kiri) | GPIO 27 |
| ENB (Motor kanan) | GPIO 32 |
| IN3 (Motor kanan) | GPIO 26 |
| IN4 (Motor kanan) | GPIO 25 |

## 📂 Struktur Repository

```text
program_robot_minisoccer/
├── program_minisoccer_penahan/
├── program_minisoccer_penyerang/
└── README.md
```

## 🎮 Sistem Kendali

Robot menggunakan komunikasi Bluetooth untuk menerima perintah gerakan dari smartphone melalui aplikasi Arduino Bluetooth Controller.

Nama Bluetooth perangkat: `MINI_SOCCER_ESP32`

## 🎯 Tujuan Proyek

- Menerapkan pemrograman mikrokontroler ESP32.
- Mengimplementasikan kendali motor menggunakan L298N.
- Menerapkan komunikasi Bluetooth antara smartphone dan robot.
- Mengembangkan sistem kendali robot untuk permainan mini soccer.

## 👩‍💻 Pengembang

**Bunga Indah**

Mahasiswa Informatika — Universitas Negeri Padang

GitHub: [Bungaindah186](https://github.com/Bungaindah186)

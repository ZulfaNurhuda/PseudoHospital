#ifndef DATATYPES_H
#define DATATYPES_H

// >>> Untuk Menambahkan Representasi dari Tipe Data Boolean
#include "boolean.h"

// >>> Untuk Menambahkan Representasi dari Tipe Data Enum dari Role
typedef enum Role
{
    MANAGER,
    DOCTOR,
    PATIENT
} Role;

// +--------------------------------------------------------------+
// |               PENGELOLAAN KONFIGURASI ENIGMA                 |
// +--------------------------------------------------------------+

// >>> ADT PASSWORD TERENKRIPSI

/* ADT Sederhana - untuk penyimpanan password terenkripsi */
typedef struct PasswordData
{
    char encryptedContent[100];
} PasswordData;

// +--------------------------------------------------------------+
// |                    PENGELOLAAN PENGGUNA                      |
// +--------------------------------------------------------------+

// >>> ADT USER

/* ADT Sederhana - untuk representasi data pengguna dasar */
typedef struct User
{
    int id;
    char username[50];
    PasswordData password; // Enkripsi Enigma
    Role role;             // "MANAJER", "DOKTER", atau "PASIEN"
} User;

/* ADT Set (array-based) - untuk penyimpanan kumpulan user */ // Changed comment
typedef struct UserSet
{
    User *elements;
    int capacity;
    int nEff;
} UserSet; // Renamed

// >>> ADT PASIEN

/* ADT List - untuk penyimpanan obat yang diresepkan dokter */
typedef struct PatientMedicationPrescribedList
{
    int *medicationId;
    int capacity;
    int nEff;
} PatientMedicationPrescribedList;

/* ADT Stack - untuk penyimpanan data obat yang telah diminum */
typedef struct PatientMedicationTakenList
{
    int *medicationId;
    int capacity;
    int top;
} PatientMedicationTakenList;

/* ADT Sederhana - untuk representasi data pasien */
typedef struct Patient
{
    int id;
    char username[50];
    char disease[50];
    int life;         // Untuk fitur B04 - Dead or Alive (mulai dengan 3)
    float bananaRich; // Untuk fitur B03 - BananaRich

    // Data kesehatan
    float bodyTemperature;
    int systolicBloodPressure;
    int diastolicBloodPressure;
    int heartRate;
    int oxygenSaturation;
    float bloodSugarLevel;
    float weight;
    float height;
    float cholesterolLevel;
    int platelets;

    // Untuk tracking obat yang diminum dan diresepkan
    PatientMedicationTakenList medicationsTaken; // List ID obat yang sudah diminum

    PatientMedicationPrescribedList medicationsPrescribed; // List ID obat yang diresepkan oleh dokter

    // Informasi status antrian dan pengobatan
    char queueRoom[5]; // Ruangan tempat pasien mengantri (misal: "A1")
    int queuePosition; // Posisi dalam antrian (1, 2, 3, dst)

    boolean diagnosedStatus; // false: belum, true: sudah
    boolean treatedStatus;   // false: belum, true: sudah diresep obat
} Patient;

/* ADT List - untuk daftar pasien yang dinamis */
typedef struct PatientList
{
    Patient *elements;
    int capacity;
    int nEff;
} PatientList;

// >>> ADT DOKTER

/* ADT Sederhana - untuk representasi data dokter */
typedef struct Doctor
{
    int id;
    char username[50];
    char specialization[50];
    int aura;
    float bananaRich; // Untuk fitur B03 - BananaRich
    float checkupCost; // Biaya checkup yang ditetapkan dokter
    char room[5];     // Contoh: "A1", "B2", dll.
} Doctor;

/* ADT List - untuk daftar dokter yang dinamis */
typedef struct DoctorList
{
    Doctor *elements;
    int capacity;
    int nEff;
} DoctorList;

// +--------------------------------------------------------------+
// |               PENGELOLAAN RUANGAN DAN DENAH                  |
// +--------------------------------------------------------------+

// >>> ADT RUANGAN

typedef struct PatientInRoom
{
    int *patientId;
    int capacity;
    int nEff;
} PatientInRoom;

/* ADT Sederhana - untuk representasi data ruangan */
typedef struct Room
{
    char code[5]; // Contoh: "A1", "B2", dll.
    int capacity;
    int doctorId; // ID dokter yang menempati ruangan ini

    // Data pasien yang berada dalam ruangan
    PatientInRoom patientInRoom;
} Room;

// >>> ADT DENAH

/* ADT Matrix - untuk representasi denah rumah sakit 2D */
typedef struct Layout
{
    Room **elements; // Matrix dari pointer ke Ruangan
    int rowCapacity;
    int colCapacity;
    int rowEff; // Jumlah baris efektif
    int colEff; // Jumlah kolom efektif
} Layout;

// +--------------------------------------------------------------+
// |               PENGELOLAAN PENYAKIT DAN DIAGNOSIS              |
// +--------------------------------------------------------------+

// >>> ADT PENYAKIT

/* ADT Sederhana - untuk representasi data penyakit */
typedef struct Disease
{
    int id;
    char name[50];
    float bodyTemperatureMin;
    float bodyTemperatureMax;
    int systolicBloodPressureMin;
    int systolicBloodPressureMax;
    int diastolicBloodPressureMin;
    int diastolicBloodPressureMax;
    int heartRateMin;
    int heartRateMax;
    float oxygenSaturationMin;
    float oxygenSaturationMax;
    float bloodSugarLevelMin;
    float bloodSugarLevelMax;
    float weightMin;
    float weightMax;
    float heightMin;
    float heightMax;
    float cholesterolLevelMin;
    float cholesterolLevelMax;
    int plateletsMin;
    int plateletsMax;
} Disease;

/* ADT List - untuk penyimpanan daftar penyakit */
typedef struct DiseaseList
{
    Disease *elements;
    int capacity;
    int nEff;
} DiseaseList;

// +--------------------------------------------------------------+
// |               PENGELOLAAN OBAT DAN RESEP                     |
// +--------------------------------------------------------------+

// >>> ADT OBAT

/* ADT Sederhana - untuk representasi data obat */
typedef struct Medication
{
    int id;
    char name[50];
} Medication;

/* ADT List - untuk penyimpanan daftar obat */
typedef struct MedicationList
{
    Medication *elements;
    int capacity;
    int nEff;
} MedicationList;

// >>> ADT RESEP

/* ADT Sederhana - untuk representasi data resep obat */
typedef struct MedicationPrescription
{
    int medicationId;
    int diseaseId;
    int doseOrder; // Urutan minum obat
} MedicationPrescription;

/* ADT List - untuk penyimpanan daftar resep */
typedef struct PrescriptionList
{
    MedicationPrescription *elements;
    int capacity;
    int nEff;
} PrescriptionList;

// +--------------------------------------------------------------+
// |               PENGELOLAAN ANTRIAN PASIEN                     |
// +--------------------------------------------------------------+

// >>> ADT QUEUE UNTUK ANTRIAN PASIEN PER RUANGAN

/* ADT Sederhana - untuk informasi pasien dalam antrian */
typedef struct QueueInfo
{
    int patientId;
} QueueInfo;

/* Node untuk Linked List Queue */
typedef struct QueueNode
{
    QueueInfo info;
    struct QueueNode *next;
    struct QueueNode *prev;
} QueueNode;

/* ADT Queue - untuk implementasi antrian pasien per ruangan (Linked List) */
typedef struct Queue
{
    char roomCode[5]; // Kode ruangan (misalnya: "A1", "B2", dll)
    QueueNode *head;
    QueueNode *tail;
    int size;
} Queue;

/* ADT List - untuk kumpulan antrian di rumah sakit */
typedef struct HospitalQueueList
{
    Queue *queues; // Array of Queues
    int nRooms;    // Jumlah ruangan yang memiliki antrian
    int capacity;
} HospitalQueueList;

// +--------------------------------------------------------------+
// |                 PENGELOLAAN BANANARICH                       |
// +--------------------------------------------------------------+

// >>> ADT UNTUK MANAJEMEN KEUANGAN RUMAH SAKIT

/* ADT Sederhana - untuk pengelolaan data keuangan rumah sakit */
typedef struct HospitalFinance
{
    float hospitalBalance;
} HospitalFinance;

// +--------------------------------------------------------------+
// |               PENGELOLAAN RIWAYAT PENGOBATAN                 |
// +--------------------------------------------------------------+

// >>> ADT RIWAYAT PENGOBATAN

/* ADT Sederhana - untuk mencatat riwayat pengobatan pasien */
typedef struct TreatmentHistory
{
    int patientId;
    int doctorId;
    char room[5];
    char disease[50];     // Bisa menggunakan timestamp atau struktur date
    boolean treatmentStatus; // false: belum selesai, true: selesai
} TreatmentHistory;

/* ADT List - untuk penyimpanan riwayat pengobatan */
typedef struct TreatmentHistoryList
{
    TreatmentHistory *elements;
    int capacity;
    int nEff;
} TreatmentHistoryList;

// +--------------------------------------------------------------+
// |                   PENGELOLAAN SESI LOGIN                     |
// +--------------------------------------------------------------+

// >> ADT SESION

/* ADT Sederhana - untuk mengelola sesi login pengguna */
typedef struct Session
{
    int userId;         // ID pengguna yang sedang login
    char username[50];  // Username pengguna
    Role role;          // Role: "MANAJER", "DOKTER", atau "PASIEN"
    boolean isLoggedIn; // Status login: true (login) atau false (logout)
} Session;

// +===============================================================+
// ||                                                             ||
// ||                MASTER ADT UNTUK RUMAH SAKIT                 ||
// ||                                                             ||
// +===============================================================+

/* ADT Sederhana - untuk integrasi seluruh komponen dalam satu struktur */
typedef struct Hospital
{
    // Pengguna
    UserSet users; // Renamed
    PatientList patients;
    DoctorList doctors;

    // Ruangan
    Layout layout;

    // Antrian
    HospitalQueueList queues;

    // Penyakit dan obat
    DiseaseList diseases;
    MedicationList medications;
    PrescriptionList prescriptions;

    // Finansial
    HospitalFinance finance;

    // Riwayat Pengobatan
    TreatmentHistoryList treatmentHistory;
} Hospital;

#endif // DATATYPES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Max number of patients and doctors
#define MAX_PATIENTS 100
#define MAX_DOCTORS 50

// Structure for Doctor
typedef struct {
    int doctor_id;
    char name[50];
    char specialization[50];
} Doctor;

// Structure for Patient
typedef struct {
    int patient_id;
    char name[50];
    int age;
    char gender[10];
    char contact[15];
    char admission_date[20];
    char discharge_date[20];
    int doctor_assigned;  // Doctor ID (if assigned)
} Patient;

// Hospital Management System structure
typedef struct {
    Patient patients[MAX_PATIENTS];
    Doctor doctors[MAX_DOCTORS];
    int patient_count;
    int doctor_count;
} HospitalSystem;

// Function prototypes
void register_patient(HospitalSystem *system);
void register_doctor(HospitalSystem *system);
void assign_doctor_to_patient(HospitalSystem *system);
void search_patient(HospitalSystem *system);
void search_doctor(HospitalSystem *system);
void display_patient(Patient *p);
void display_doctor(Doctor *d);

// Main function
int main() {
    HospitalSystem system = { .patient_count = 0, .doctor_count = 0 };
    int choice;
    
    while (1) {
        printf("\n*** Hospital Management System ***\n");
        printf("1. Register Patient\n");
        printf("2. Register Doctor\n");
        printf("3. Assign Doctor to Patient\n");
        printf("4. Search Patient\n");
        printf("5. Search Doctor\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // Consume newline character

        switch (choice) {
            case 1: register_patient(&system); break;
            case 2: register_doctor(&system); break;
            case 3: assign_doctor_to_patient(&system); break;
            case 4: search_patient(&system); break;
            case 5: search_doctor(&system); break;
            case 6: exit(0);
            default: printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Function to register a new patient
void register_patient(HospitalSystem *system) {
    if (system->patient_count >= MAX_PATIENTS) {
        printf("Cannot register more patients. Capacity reached.\n");
        return;
    }

    Patient *p = &system->patients[system->patient_count];
    
    p->patient_id = system->patient_count + 1;  // Patient ID starts from 1
    printf("Enter patient's name: ");
    fgets(p->name, sizeof(p->name), stdin);
    p->name[strcspn(p->name, "\n")] = '\0';  // Remove trailing newline

    printf("Enter age: ");
    scanf("%d", &p->age);
    getchar();  // Consume newline

    printf("Enter gender (Male/Female): ");
    fgets(p->gender, sizeof(p->gender), stdin);
    p->gender[strcspn(p->gender, "\n")] = '\0';  // Remove newline

    printf("Enter contact number: ");
    fgets(p->contact, sizeof(p->contact), stdin);
    p->contact[strcspn(p->contact, "\n")] = '\0';  // Remove newline

    printf("Enter admission date (dd-mm-yyyy): ");
    fgets(p->admission_date, sizeof(p->admission_date), stdin);
    p->admission_date[strcspn(p->admission_date, "\n")] = '\0';  // Remove newline

    printf("Enter discharge date (dd-mm-yyyy): ");
    fgets(p->discharge_date, sizeof(p->discharge_date), stdin);
    p->discharge_date[strcspn(p->discharge_date, "\n")] = '\0';  // Remove newline

    p->doctor_assigned = -1;  // No doctor assigned initially

    system->patient_count++;
    printf("Patient registered successfully.\n");
}

// Function to register a new doctor
void register_doctor(HospitalSystem *system) {
    if (system->doctor_count >= MAX_DOCTORS) {
        printf("Cannot register more doctors. Capacity reached.\n");
        return;
    }

    Doctor *d = &system->doctors[system->doctor_count];
    
    d->doctor_id = system->doctor_count + 1;  // Doctor ID starts from 1
    printf("Enter doctor's name: ");
    fgets(d->name, sizeof(d->name), stdin);
    d->name[strcspn(d->name, "\n")] = '\0';  // Remove newline

    printf("Enter doctor's specialization: ");
    fgets(d->specialization, sizeof(d->specialization), stdin);
    d->specialization[strcspn(d->specialization, "\n")] = '\0';  // Remove newline

    system->doctor_count++;
    printf("Doctor registered successfully.\n");
}

// Function to assign a doctor to a patient
void assign_doctor_to_patient(HospitalSystem *system) {
    int patient_id, doctor_id;
    
    printf("Enter patient ID: ");
    scanf("%d", &patient_id);
    getchar();  // Consume newline

    printf("Enter doctor ID: ");
    scanf("%d", &doctor_id);
    getchar();  // Consume newline

    if (patient_id <= 0 || patient_id > system->patient_count) {
        printf("Invalid patient ID.\n");
        return;
    }

    if (doctor_id <= 0 || doctor_id > system->doctor_count) {
        printf("Invalid doctor ID.\n");
        return;
    }

    system->patients[patient_id - 1].doctor_assigned = doctor_id - 1;
    printf("Doctor assigned to patient successfully.\n");
}

// Function to search for a patient by name
void search_patient(HospitalSystem *system) {
    char name[50];
    printf("Enter patient's name to search: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';  // Remove newline

    for (int i = 0; i < system->patient_count; i++) {
        if (strcmp(system->patients[i].name, name) == 0) {
            display_patient(&system->patients[i]);
            return;
        }
    }

    printf("Patient not found.\n");
}

// Function to search for a doctor by name
void search_doctor(HospitalSystem *system) {
    char name[50];
    printf("Enter doctor's name to search: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';  // Remove newline

    for (int i = 0; i < system->doctor_count; i++) {
        if (strcmp(system->doctors[i].name, name) == 0) {
            display_doctor(&system->doctors[i]);
            return;
        }
    }

    printf("Doctor not found.\n");
}

// Function to display patient details
void display_patient(Patient *p) {
    printf("\n--- Patient Details ---\n");
    printf("Patient ID: %d\n", p->patient_id);
    printf("Name: %s\n", p->name);
    printf("Age: %d\n", p->age);
    printf("Gender: %s\n", p->gender);
    printf("Contact: %s\n", p->contact);
    printf("Admission Date: %s\n", p->admission_date);
    printf("Discharge Date: %s\n", p->discharge_date);
    if (p->doctor_assigned != -1) {
        printf("Assigned Doctor: %s\n", p->doctor_assigned);
    } else {
        printf("No doctor assigned.\n");
    }
}

// Function to display doctor details
void display_doctor(Doctor *d) {
    printf("\n--- Doctor Details ---\n");
    printf("Doctor ID: %d\n", d->doctor_id);
    printf("Name: %s\n", d->name);
    printf("Specialization: %s\n", d->specialization);
}

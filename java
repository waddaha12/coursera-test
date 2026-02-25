import java.util.*;

// Person base class
abstract class Person {
    private String name;
    private int age;
    private String email;

    public Person(String name, int age, String email) {
        this.name = name;
        this.age = age;
        this.email = email;
    }

    public String getName() { return name; }
    public int getAge() { return age; }
    public String getEmail() { return email; }

    public abstract void displayInfo();
}

// Doctor class
class Doctor extends Person {
    private String specialization;
    private double consultationFee;
    private List<Appointment> appointments;

    public Doctor(String name, int age, String email, String specialization, double consultationFee) {
        super(name, age, email);
        this.specialization = specialization;
        this.consultationFee = consultationFee;
        this.appointments = new ArrayList<>();
    }

    public String getSpecialization() { return specialization; }
    public double getConsultationFee() { return consultationFee; }

    public void addAppointment(Appointment appointment) {
        appointments.add(appointment);
    }

    public void viewAppointments() {
        if (appointments.isEmpty()) {
            System.out.println("No appointments scheduled.");
        } else {
            System.out.println("\n--- Appointments for Dr. " + getName() + " ---");
            for (Appointment a : appointments) {
                a.displayInfo();
            }
        }
    }

    @Override
    public void displayInfo() {
        System.out.println("Doctor: " + getName() +
                " | Age: " + getAge() +
                " | Specialization: " + specialization +
                " | Fee: $" + consultationFee);
    }
}

// Patient class
class Patient extends Person {
    private String symptoms;
    private List<Prescription> prescriptions;

    public Patient(String name, int age, String email, String symptoms) {
        super(name, age, email);
        this.symptoms = symptoms;
        this.prescriptions = new ArrayList<>();
    }

    public String getSymptoms() { return symptoms; }

    public void addPrescription(Prescription prescription) {
        prescriptions.add(prescription);
    }

    public void viewPrescriptions() {
        if (prescriptions.isEmpty()) {
            System.out.println("No prescriptions yet.");
        } else {
            System.out.println("\n--- Prescriptions for " + getName() + " ---");
            for (Prescription p : prescriptions) {
                p.displayInfo();
            }
        }
    }

    @Override
    public void displayInfo() {
        System.out.println("Patient: " + getName() +
                " | Age: " + getAge() +
                " | Symptoms: " + symptoms);
    }
}

// Appointment class
class Appointment {
    private static int counter = 1;
    private int appointmentId;
    private Doctor doctor;
    private Patient patient;
    private String date;
    private String status;

    public Appointment(Doctor doctor, Patient patient, String date) {
        this.appointmentId = counter++;
        this.doctor = doctor;
        this.patient = patient;
        this.date = date;
        this.status = "Scheduled";
    }

    public int getAppointmentId() { return appointmentId; }
    public Doctor getDoctor() { return doctor; }
    public Patient getPatient() { return patient; }
    public String getStatus() { return status; }

    public void complete() { this.status = "Completed"; }
    public void cancel() { this.status = "Cancelled"; }

    public void displayInfo() {
        System.out.println("Appointment ID: " + appointmentId +
                " | Patient: " + patient.getName() +
                " | Doctor: Dr. " + doctor.getName() +
                " | Date: " + date +
                " | Status: " + status);
    }
}

// Prescription class
class Prescription {
    private int appointmentId;
    private String medication;
    private String dosage;
    private String notes;

    public Prescription(int appointmentId, String medication, String dosage, String notes) {
        this.appointmentId = appointmentId;
        this.medication = medication;
        this.dosage = dosage;
        this.notes = notes;
    }

    public void displayInfo() {
        System.out.println("Appointment ID: " + appointmentId +
                " | Medication: " + medication +
                " | Dosage: " + dosage +
                " | Notes: " + notes);
    }
}

// Consultation System (main controller)
class ConsultationSystem {
    private List<Doctor> doctors;
    private List<Patient> patients;
    private List<Appointment> appointments;

    public ConsultationSystem() {
        doctors = new ArrayList<>();
        patients = new ArrayList<>();
        appointments = new ArrayList<>();
    }

    public void registerDoctor(Doctor doctor) {
        doctors.add(doctor);
        System.out.println("Doctor registered: Dr. " + doctor.getName());
    }

    public void registerPatient(Patient patient) {
        patients.add(patient);
        System.out.println("Patient registered: " + patient.getName());
    }

    public Appointment bookAppointment(Patient patient, Doctor doctor, String date) {
        Appointment appointment = new Appointment(doctor, patient, date);
        appointments.add(appointment);
        doctor.addAppointment(appointment);
        System.out.println("Appointment booked! ID: " + appointment.getAppointmentId());
        return appointment;
    }

    public void conductConsultation(Appointment appointment, String medication, String dosage, String notes) {
        if (appointment.getStatus().equals("Scheduled")) {
            appointment.complete();
            Prescription prescription = new Prescription(
                    appointment.getAppointmentId(), medication, dosage, notes);
            appointment.getPatient().addPrescription(prescription);
            System.out.println("Consultation completed. Prescription issued.");
        } else {
            System.out.println("Appointment is not in scheduled state.");
        }
    }

    public void listDoctors() {
        System.out.println("\n--- Available Doctors ---");
        for (Doctor d : doctors) d.displayInfo();
    }

    public void listPatients() {
        System.out.println("\n--- Registered Patients ---");
        for (Patient p : patients) p.displayInfo();
    }

    public void listAllAppointments() {
        System.out.println("\n--- All Appointments ---");
        for (Appointment a : appointments) a.displayInfo();
    }
}

// Main class
public class OnlineDoctorConsultation {
    public static void main(String[] args) {

        ConsultationSystem system = new ConsultationSystem();

        // Register Doctors
        Doctor doc1 = new Doctor("Alice Smith", 45, "alice@clinic.com", "Cardiologist", 150.0);
        Doctor doc2 = new Doctor("Bob Jones", 38, "bob@clinic.com", "General Physician", 80.0);
        system.registerDoctor(doc1);
        system.registerDoctor(doc2);

        // Register Patients
        Patient p1 = new Patient("John Doe", 30, "john@mail.com", "Chest pain and fatigue");
        Patient p2 = new Patient("Jane Roe", 25, "jane@mail.com", "Fever and headache");
        system.registerPatient(p1);
        system.registerPatient(p2);

        // List Doctors & Patients
        system.listDoctors();
        system.listPatients();

        // Book Appointments
        Appointment a1 = system.bookAppointment(p1, doc1, "2025-03-10 10:00 AM");
        Appointment a2 = system.bookAppointment(p2, doc2, "2025-03-11 02:00 PM");

        // List all appointments
        system.listAllAppointments();

        // Conduct Consultations
        system.conductConsultation(a1, "Aspirin", "100mg daily", "Avoid stress and rest well.");
        system.conductConsultation(a2, "Paracetamol", "500mg every 8 hours", "Drink plenty of fluids.");

        // View doctor's appointments
        doc1.viewAppointments();
        doc2.viewAppointments();

        // View patient prescriptions
        p1.viewPrescriptions();
        p2.viewPrescriptions();

        // List updated appointments
        system.listAllAppointments();
    }
}
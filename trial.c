//admission.h
#ifndef ADMISSION_H
#define ADMISSION_H

struct Student {
        int regNo;
        char name[100];
        char gender;
        char nationality[50];
        char address[100];
        int phone;
        int dob;
    } student;

int readNumberFromFile();
void writeNumberToFile(int number);
int generateIncreasingNumber();
void maledetails();
void femaledetails();
void viewmaledetails();
void viewfemaledetails();
void searchmalestudent(int id);
void searchfemalestudent(int id);
void deleteMaleStudentRecord(int id);
void deleteFemaleStudentRecord(int id);

#endif  // ADMISSION_H

//admission.c
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "admission.h"
#include "hostels.h"

//generating admission number
int readNumberFromFile() {
    int number = 1;  // Default value if the file doesn't exist

    FILE* file = fopen("number.txt", "r");
    if (file != NULL) {
        fscanf(file, "%d", &number);
        fclose(file);
    }

    return number;
}

void writeNumberToFile(int number) {
    FILE* file = fopen("number.txt", "w");
    if (file != NULL) {
        fprintf(file, "%d", number);
        fclose(file);
    }
}

int generateIncreasingNumber() {
    int number = readNumberFromFile();
    printf("%03d\n", number);

    number++;
    writeNumberToFile(number);
}

void maledetails() {
    printf("Enter your Name: ");
    scanf(" %99[^\n]", student.name);

    printf("Enter your DOB: ");
    scanf("%d", &student.dob);

    printf("Enter your nationality: ");
    scanf(" %49[^\n]%*c", student.nationality);

    printf("Enter your address: ");
    scanf(" %[^\n]", student.address);

    printf("Enter your mobile phone number: ");
    scanf("%d", &student.phone);

    student.regNo = readNumberFromFile();
    writeNumberToFile(student.regNo + 1);

    FILE* malefile = fopen("maledetails.txt", "a");
    if (malefile != NULL) {
        fprintf(malefile, "%d, %s, %d, %s, %s, %d\n", student.regNo, student.name, student.dob, student.nationality, student.address, student.phone);
        fclose(malefile);
        printf("\n\nDetails captured successfully!\nYour registration number is %d\n", student.regNo);
    } else {
        printf("Error opening the file\n");
    }
}

//register new female students details
void femaledetails() {
    printf("Enter your Name: ");
    scanf(" %99[^\n]", student.name);

    printf("Enter your DOB: ");
    scanf("%d", &student.dob);

    printf("Enter your nationality: ");
    scanf(" %49[^\n]%*c", student.nationality);

    printf("Enter your address: ");
    scanf(" %[^\n]", student.address);

    printf("Enter your mobile phone number: ");
    scanf("%d", &student.phone);

    student.regNo = readNumberFromFile();
    writeNumberToFile(student.regNo + 1);

    FILE* malefile = fopen("femaledetails.txt", "a");
    if (malefile != NULL) {
        fprintf(malefile, "%d, %s, %d, %s, %s, %d\n", student.regNo, student.name, student.dob, student.nationality, student.address, student.phone);
        fclose(malefile);
        printf("\n\nDetails captured successfully!\nYour registration number is %d\n", student.regNo);
    } else {
        printf("Error opening the file\n");
    }
}

void viewmaledetails() {
    FILE* file = fopen("maledetails.txt", "r");
    if (file != NULL) {
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }
        fclose(file);
    } else {
        printf("Error opening the file\n");
    }
}


void viewfemaledetails() {
    FILE* file = fopen("femaledetails.txt", "r");
    if (file != NULL) {
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }
        fclose(file);
    } else {
        printf("Error opening the file\n");
    }
}
void searchmalestudent(int id) {
    printf("Enter student ID: ");
    scanf("%d",&id);
    FILE* file = fopen("maledetails.txt", "r");
    if (file != NULL) {
        char line[256];
        int found = 0;
        while (fgets(line, sizeof(line), file)) {
            int regNo;
            sscanf(line, "%d", &regNo);
            if (regNo == id) {
                printf("%s", line);
                found = 1;
                break;
            }
        }
        fclose(file);

        if (!found) {
            printf("Student with ID %d not found\n", id);
        }
    } else {
        printf("Error opening the file\n");
    }
}

//search female student
void searchfemalestudent(int id) {
    printf("Enter student ID: ");
    scanf("%d",&id);
    FILE* file = fopen("femaledetails.txt", "r");
    if (file != NULL) {
        char line[256];
        int found = 0;
        while (fgets(line, sizeof(line), file)) {
            int regNo;
            sscanf(line, "%d", &regNo);
            if (regNo == id) {
                printf("%s", line);
                found = 1;
                break;
            }
        }
        fclose(file);

        if (!found) {
            printf("Student with ID %d not found\n", id);
        }
    } else {
        printf("Error opening the file\n");
    }
}

void deleteMaleStudentRecord(int id) {
    printf("Enter student regNo to delete: ");
    scanf("%d", &id);

    FILE* file = fopen("maledetails.txt", "r");
    if (file != NULL) {
        FILE* tempFile = fopen("temp.txt", "w");
        if (tempFile != NULL) {
            char line[256];
            int found = 0;
            while (fgets(line, sizeof(line), file)) {
                int regNo;
                sscanf(line, "%d", &regNo);
                if (regNo != id) {
                    fprintf(tempFile, "%s", line);
                } else {
                    found = 1;
                }
            }
            fclose(tempFile);
            fclose(file);

            if (found) {
                remove("maledetails.txt");
                rename("temp.txt", "maledetails.txt");
                printf("Student with ID %d deleted successfully\n", id);
            } else {
                printf("Student with ID %d not found\n", id);
                remove("temp.txt");
            }
        } else {
            printf("Error creating temporary file\n");
            fclose(file);
        }
    } else {
        printf("Error opening the file\n");
    }
}

//delete female details
void deleteFemaleStudentRecord(int id) {
    printf("Enter student regNo to delete: ");
    scanf("%d", &id);

    FILE* file = fopen("femaledetails.txt", "r");
    if (file != NULL) {
        FILE* tempFile = fopen("temp1.txt", "w");
        if (tempFile != NULL) {
            char line[256];
            int found = 0;
            while (fgets(line, sizeof(line), file)) {
                int regNo;
                sscanf(line, "%d", &regNo);
                if (regNo != id) {
                    fprintf(tempFile, "%s", line);
                } else {
                    found = 1;
                }
            }
            fclose(tempFile);
            fclose(file);

            if (found) {
                remove("femaledetails.txt");
                rename("temp1.txt", "femaledetails.txt");
                printf("Student with ID %d deleted successfully\n", id);
            } else {
                printf("Student with ID %d not found\n", id);
                remove("temp.txt");
            }
        } else {
            printf("Error creating temporary file\n");
            fclose(file);
        }
    } else {
        printf("Error opening the file\n");
    }
}

//hostels.h
#ifndef HOSTELS_H
#define HOSTELS_H

struct Hostel {
    int roomNo;
    char hostelName[50];
    int bedNo;
};

void registermaleHostel();
void registerfemaleHostel();
void viewmalehostels();
void viewfemalehostels();
int checkAllocation(int regNo, int roomNo);
void allocatemalehostel();
void allocatefemalehostel();
void allocatedmalestudents();
void allocatedfemalestudents();

#endif  // HOSTELS_H

//hostels.c
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "hostels.h"
#include "admission.h"

//HOSTEL FUNCTIONS
//Register male hostels
void registermaleHostel(){
    struct Hostel hostel;
    char availability[]="available";
    srand(time(NULL));
    hostel.roomNo= generateIncreasingNumber();
    printf("The new hostel number is: %d\n",hostel.roomNo);
    printf("Enter hostel name: ");
    scanf(" %s",&hostel.hostelName);
    
    FILE*file=fopen("malehostel.txt","a");
    if(file !=NULL){
        fprintf(file, "%d, %s, %s\n",hostel.roomNo,hostel.hostelName,availability);
        fclose(file);
        printf("Hostel registered successfully!\n");
        }
        
        else{
            printf("Error opening file.\n");
        }
}

//register female hostel
void registerfemaleHostel(){
    struct Hostel hostel;
    char availability[]="available";
    srand(time(NULL));
    hostel.roomNo= generateIncreasingNumber();
    printf("The new hostel number is: %d\n",hostel.roomNo);
    printf("Enter hostel name: ");
    scanf(" %s",&hostel.hostelName);

    FILE*file=fopen("femalehostel.txt","a");
    if(file !=NULL){
        fprintf(file, "%d, %s, %s\n",hostel.roomNo,hostel.hostelName,availability);
        fclose(file);
        printf("Hostel registered successfully!\n");
        }
        
        else{
            printf("Error opening file.\n");
        }
}

//FUNCTIONS TO CHECK AVAILABLE HOSTELS
//view available male hostels
void viewmalehostels() {
    FILE* file = fopen("malehostel.txt", "r");
    if (file != NULL) {
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }
        fclose(file);
    } else {
        printf("Error opening the file\n");
    }
}

//view female hostels
void viewfemalehostels() {
    FILE* file = fopen("femalehostel.txt", "r");
    if (file != NULL) {
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }
        fclose(file);
    } else {
        printf("Error opening the file\n");
    }
}

//function for allocating hostel to students
//allocation of male hostel

int checkAllocation(int regNo, int roomNo) {
    FILE* allocfile = fopen("allocatedmalerooms.txt", "r");
    if (allocfile != NULL) {
        char line[256];
        while (fgets(line, sizeof(line), allocfile)) {
            int fileRegNo, fileRoomNo;
            sscanf(line, "Student regNo: %d\nHostel room number: %d", &fileRegNo, &fileRoomNo);
            if (fileRegNo == regNo || fileRoomNo == roomNo) {
                fclose(allocfile);
                return 1;  // Room or student already allocated
            }
        }
        fclose(allocfile);
    }
    return 0;  // Room and student not allocated
}

void allocatemalehostel() {
    struct Student student;
    struct Hostel hostel;
    char availability[20] = "available";

    int id, roomid;
    printf("Enter student registration number: ");
    scanf("%d", &id);

    // Check if student has already booked a room
    if (checkAllocation(id, -1)) {
        printf("Student with ID %d has already booked a room\n", id);
        return;
    }

    FILE* studentfile = fopen("maledetails.txt", "r");
    if (studentfile != NULL) {
        char line[256];
        int found = 0;
        while (fgets(line, sizeof(line), studentfile)) {
            sscanf(line, "%d,%[^,]%*c", &student.regNo, student.name);
            if (student.regNo == id) {
                found = 1;
                break;
            }
        }
        fclose(studentfile);

        if (!found) {
            printf("Student with ID %d not found\n", id);
            return;
        }
    } else {
        printf("Error opening the male students' details file\n");
        return;
    }

    printf("Enter room number: ");
    scanf("%d", &roomid);

    // Check if room is already allocated
    if (checkAllocation(-1, roomid)) {
        printf("Room with ID %d is already allocated\n", roomid);
        return;
    }

    FILE* malehostelfile = fopen("malehostel.txt", "r+");
    if (malehostelfile != NULL) {
        char line[256];
        int found = 0;
        while (fgets(line, sizeof(line), malehostelfile)) {
            sscanf(line, "%d, %s, %s", &hostel.roomNo, hostel.hostelName, availability);
            if (hostel.roomNo == roomid && strcmp(availability, "available") == 0) {
                fseek(malehostelfile, -strlen(line), SEEK_CUR);
                fprintf(malehostelfile, "%d, %s allocated\n", hostel.roomNo, hostel.hostelName);
                found = 1;
                break;
            }
        }
        fclose(malehostelfile);

        if (!found) {
            printf("Room with ID %d not found or not available\n", roomid);
            return;
        }
    } else {
        printf("Error opening the room details file\n");
        return;
    }

    FILE* allocfile = fopen("allocatedmalerooms.txt", "a");
    if (allocfile != NULL) {
        fprintf(allocfile, "Student name: %s\nStudent regNo: %d\nHostel room number: %d\nHostel name: %s \n\n", student.name, student.regNo, hostel.roomNo, hostel.hostelName);
        fclose(allocfile);
        printf("Room allocated successfully\n");
    } else {
        printf("Error opening the allocated room details file\n");
    }
}

//allocate female hostel

void allocatefemalehostel() {
    struct Student student;
    struct Hostel hostel;
    char availability[20] = "available";

    int id, roomid;
    printf("Enter student registration number: ");
    scanf("%d", &id);

    FILE* studentfile = fopen("femaledetails.txt", "r");
    if (studentfile != NULL) {
        char line[256];
        int found = 0;
        while (fgets(line, sizeof(line), studentfile)) {
            sscanf(line, "%d,%[^,]%*c", &student.regNo, student.name);
            if (student.regNo == id) {
                found = 1;
                break;
            }
        }
        fclose(studentfile);

        if (!found) {
            printf("Student with ID %d not found\n", id);
            return;
        }
    } else {
        printf("Error opening the female students' details file\n");
        return;
    }

    printf("Enter room number: ");
    scanf("%d", &roomid);

    FILE* femalehostelfile = fopen("femalehostel.txt", "r+");
    if (femalehostelfile != NULL) {
        char line[256];
        int found = 0;
        while (fgets(line, sizeof(line), femalehostelfile)) {
            sscanf(line, "%d, %s, %s", &hostel.roomNo, hostel.hostelName, availability);
            if (hostel.roomNo == roomid && strcmp(availability, "available") == 0) {
                fseek(femalehostelfile, -strlen(line), SEEK_CUR);
                fprintf(femalehostelfile, "%d, %s allocated\n", hostel.roomNo, hostel.hostelName);
                found = 1;
                break;
            }
        }
        fclose(femalehostelfile);

        if (!found) {
            printf("Room with ID %d not found or not available\n", roomid);
            return;
        }
    } else {
        printf("Error opening the room details file\n");
        return;
    }

    FILE* allocfile = fopen("allocatedfemalerooms.txt", "a");
    if (allocfile != NULL) {
        fprintf(allocfile, "Student name: %s\nStudent regNo: %d\nHostel room number: %d\nHostel name: %s \n\n", student.name, student.regNo, hostel.roomNo, hostel.hostelName);
        fclose(allocfile);
        printf("Room allocated successfully\n");
    } else {
        printf("Error opening the allocated room details file\n");
    }
}

//VIEW ALLOCATED MALE AND FEMALE HOSTELS
//view allocated male hostels
void allocatedmalestudents() {
    FILE* file = fopen("allocatedmalerooms.txt", "r");
    if (file != NULL) {
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }
        fclose(file);
    } else {
        printf("Error opening the file\n");
    }
}

//view allocated female hostels
void allocatedfemalestudents() {
    FILE* file = fopen("allocatedfemalerooms.txt", "r");
    if (file != NULL) {
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }
        fclose(file);
    } else {
        printf("Error opening the file\n");
    }
}





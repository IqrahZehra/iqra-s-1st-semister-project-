#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 50
#define NAME_LEN     30

/* ---------- Global Data ---------- */
int   roll[MAX_STUDENTS];
int   marks[MAX_STUDENTS];
float percentage[MAX_STUDENTS];
char  name[MAX_STUDENTS][NAME_LEN];
char  grade[MAX_STUDENTS];
int   count = 0;

/* ---------- Function Prototypes ---------- */
void  loadFromFile();
void  saveToFile();
int   findStudent(int r);
char  calculateGrade(float per);
void  addStudent();
void  viewAllStudents();
void  searchStudent();
void  updateStudent();
void  deleteStudent();
void  adminMenu();
void  studentMenu();
int   login(const char *role, const char *user, const char *pass);

/* ---------- File Handling ---------- */
void loadFromFile()
{
    FILE *fp = fopen("student.txt", "r");
    if (fp == NULL) return;

    while (count < MAX_STUDENTS &&
           fscanf(fp, "%d %29s %d %f %c",
                  &roll[count], name[count],
                  &marks[count], &percentage[count],
                  &grade[count]) == 5)
    {
        count++;
    }
    fclose(fp);
}

void saveToFile()
{
    FILE *fp = fopen("student.txt", "w");
    if (fp == NULL) { printf("Error: Cannot save file!\n"); return; }

    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%d %s %d %.2f %c\n",
                roll[i], name[i], marks[i],
                percentage[i], grade[i]);
    }
    fclose(fp);
}

/* ---------- Helpers ---------- */
int findStudent(int r)
{
    for (int i = 0; i < count; i++)
        if (roll[i] == r) return i;
    return -1;
}

char calculateGrade(float per)
{
    if (per >= 80) return 'A';
    if (per >= 60) return 'B';
    if (per >= 40) return 'C';
    return 'F';
}

/* ---------- CRUD Operations ---------- */
void addStudent()
{
    if (count >= MAX_STUDENTS) {
        printf("Maximum student limit reached!\n");
        return;
    }

    int r;
    printf("Enter Roll No: ");
    scanf("%d", &r);

    if (findStudent(r) != -1) {
        printf("Roll No already exists!\n");
        return;
    }

    roll[count] = r;

    printf("Enter Name: ");
    scanf("%29s", name[count]);

    printf("Enter Marks (0-100): ");
    scanf("%d", &marks[count]);

    if (marks[count] < 0 || marks[count] > 100) {
        printf("Invalid marks! Must be 0-100.\n");
        return;
    }

    percentage[count] = (float)marks[count];
    grade[count]      = calculateGrade(percentage[count]);

    count++;
    saveToFile();
    printf("Student Record Added Successfully!\n");
}

void viewAllStudents()
{
    if (count == 0) { printf("No records found!\n"); return; }

    printf("\n%-10s %-20s %-8s %-12s %-6s\n",
           "Roll No", "Name", "Marks", "Percent", "Grade");
    printf("-----------------------------------------------------------\n");

    for (int i = 0; i < count; i++)
        printf("%-10d %-20s %-8d %-12.2f %-6c\n",
               roll[i], name[i], marks[i], percentage[i], grade[i]);
}

void searchStudent()
{
    int r;
    printf("Enter Roll No to Search: ");
    scanf("%d", &r);

    int idx = findStudent(r);
    if (idx == -1) { printf("Record Not Found!\n"); return; }

    printf("\n--- Student Details ---\n");
    printf("Roll No    : %d\n",   roll[idx]);
    printf("Name       : %s\n",   name[idx]);
    printf("Marks      : %d\n",   marks[idx]);
    printf("Percentage : %.2f\n", percentage[idx]);
    printf("Grade      : %c\n",   grade[idx]);
}

void updateStudent()
{
    int r;
    printf("Enter Roll No to Update: ");
    scanf("%d", &r);

    int idx = findStudent(r);
    if (idx == -1) { printf("Record Not Found!\n"); return; }

    printf("Enter New Name: ");
    scanf("%29s", name[idx]);

    printf("Enter New Marks (0-100): ");
    scanf("%d", &marks[idx]);

    if (marks[idx] < 0 || marks[idx] > 100) {
        printf("Invalid marks!\n"); return;
    }

    percentage[idx] = (float)marks[idx];
    grade[idx]      = calculateGrade(percentage[idx]);

    saveToFile();
    printf("Record Updated Successfully!\n");
}

void deleteStudent()
{
    int r;
    printf("Enter Roll No to Delete: ");
    scanf("%d", &r);

    int idx = findStudent(r);
    if (idx == -1) { printf("Record Not Found!\n"); return; }

    for (int i = idx; i < count - 1; i++) {
        roll[i]       = roll[i + 1];
        strcpy(name[i], name[i + 1]);
        marks[i]      = marks[i + 1];
        percentage[i] = percentage[i + 1];
        grade[i]      = grade[i + 1];
    }
    count--;
    saveToFile();
    printf("Record Deleted Successfully!\n");
}

/* ---------- Menus ---------- */
void adminMenu()
{
    int choice;
    do {
        printf("\n--- ADMIN DASHBOARD ---\n");
        printf("1. Add Student\n");
        printf("2. View All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent();       break;
            case 2: viewAllStudents();  break;
            case 3: searchStudent();    break;
            case 4: updateStudent();    break;
            case 5: deleteStudent();    break;
            case 6: printf("Admin Logged Out.\n"); break;
            default: printf("Invalid Choice!\n");
        }
    } while (choice != 6);
}

void studentMenu()
{
    int choice;
    do {
        printf("\n--- STUDENT DASHBOARD ---\n");
        printf("1. View My Record\n");
        printf("2. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: searchStudent(); break;
            case 2: printf("Student Logged Out.\n"); break;
            default: printf("Invalid Choice!\n");
        }
    } while (choice != 2);
}

/* ---------- Login ---------- */
int login(const char *role, const char *validUser, const char *validPass)
{
    char user[20], pass[20];
    int attempts = 0;

    while (attempts < 3) {
        printf("Enter %s Username: ", role);
        scanf("%19s", user);
        printf("Enter %s Password: ", role);
        scanf("%19s", pass);

        if (strcmp(user, validUser) == 0 &&
            strcmp(pass, validPass) == 0)
        {
            printf("%s Login Successful!\n", role);
            return 1;
        }
        attempts++;
        printf("Wrong Login! Attempts Left: %d\n", 3 - attempts);
    }
    printf("Too many wrong attempts!\n");
    return 0;
}

/* ---------- Main ---------- */
int main()
{
    int mainChoice;

    loadFromFile();
    printf("===== STUDENT RECORD SYSTEM =====\n");

    do {
        printf("\n1. Admin Access\n");
        printf("2. Student Access\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &mainChoice);

        switch (mainChoice) {
            case 1:
                if (login("Admin", "admin", "123"))
                    adminMenu();
                break;
            case 2:
                if (login("Student", "student", "111"))
                    studentMenu();
                break;
            case 3:
                printf("Program Exit.\n");
                break;
            default:
                printf("Invalid Choice!\n");
        }
    } while (mainChoice != 3);

    return 0;
}

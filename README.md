# Student Management System (C)

A console-based **Student Record Management System** developed in C as a first-semester project.
It lets an admin manage student records and lets a student view their own record. All data is saved in a text file, so records are not lost when the program closes.

## Features

**Admin**
- Add a new student (roll no, name, marks)
- View all students in a table
- Search a student by roll number
- Update a student's name and marks
- Delete a student record

**Student**
- Search and view their own record by roll number

**General**
- Login system with 3 attempts for both Admin and Student
- Automatic percentage and grade calculation
- Data saved permanently in `student.txt` (file handling)
- Input validation (duplicate roll numbers, marks must be 0-100)

## Grading System

| Percentage | Grade |
|------------|-------|
| 80 and above | A |
| 60 - 79 | B |
| 40 - 59 | C |
| Below 40 | F |

## Demo Login Details

| Role | Username | Password |
|------|----------|----------|
| Admin | admin | 123 |
| Student | student | 111 |

## How to Run

**Using Dev-C++ / Code::Blocks**
1. Open the `.c` file in the IDE.
2. Compile and run (F11 in Dev-C++).

**Using GCC (terminal)**
```
gcc student_management.c -o student_management
./student_management
```

## Concepts Used

- Arrays and 2D character arrays
- Functions and function prototypes
- Loops and `switch` statements
- File handling (`fopen`, `fscanf`, `fprintf`, `fclose`)
- String functions (`strcmp`, `strcpy`)
- CRUD operations (Create, Read, Update, Delete)

## Limitations

- Maximum 50 students
- Name must be a single word (no spaces)
- Percentage is calculated out of 100 marks

## Author

**Iqrah Zehra**
BS Artificial Intelligence, 1st Semester Project

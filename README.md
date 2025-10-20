# 📚 GUB Online Library Portal

**GUB Online Library Portal** is a C-based console application designed to digitalize and manage the library operations of **Green University of Bangladesh (GUB)**.  
The system efficiently handles books, members, and transactions through a structured interface — ensuring fast, secure, and organized library management.

---

## 🚀 Project Overview

This project aims to replace traditional manual library management with a fully digital, file-based system.  
It supports **admin and member access**, provides **automated book issue/return management**, and tracks all transactions, overdue books, and fine collections.

Developed in **C programming language**, it demonstrates the use of:
- Structures and arrays  
- File handling for data persistence  
- Time/date manipulation  
- Menu-driven console interface  
- Modular function-based programming  

---

## 🔑 Key Features

### 1. Authentication System
- Secure **Admin login** using predefined credentials  
- **Member access** via ID verification  

### 2. Book Management
- Add, search, view, update, or delete books  
- Track available and total copies  
- Categorize books by department and type (Reference or Borrowable)

### 3. Member Management
- Add students, faculty, and staff with unique IDs  
- Assign different borrowing limits per member type  
- Track active/inactive status and join dates  

### 4. Transaction & Reporting System
- Issue and return books with automatic due date calculation  
- Apply fines for overdue returns  
- Generate comprehensive reports:
  - Total books, members, and transactions  
  - Overdue books list  
  - Fine collection summary  

### 5. Data Persistence
- All records (books, members, transactions) are saved to a file  
- Automatic load on program startup and save on exit  

---

## 🧩 Technologies Used

- **Language:** C  
- **IDE/Compiler:** Code::Blocks / Dev-C++ / GCC  
- **Data Storage:** File handling (`library_data.dat`)  
- **Platform:** Console-based  

---

## ⚙️ Installation & Setup

1. **Clone the repository**
   ```bash
   git clone https://github.com/YourUsername/GUB-Online-Library-Portal.git

2. **Navigate to the Project Folder**
cd GUB-Online-Library-Portal

3. **Compile the Program**
gcc library_portal.c -o library_portal

4. **Run the Executable**
./library_portal

# 📒 Address Book

> A lightweight contact management application written in C — store, view, search, and persist contact details using file handling and structured data.

---

## 📖 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Concepts Used](#concepts-used)
- [Technologies Used](#technologies-used)
- [Getting Started](#getting-started)
- [Sample Input / Output](#sample-input--output)
- [Author](#author)

---

## Overview

The **Address Book** is a terminal-based C application that lets users manage personal contacts. All contact data is persisted to a file (`contacts.txt`), so records survive between sessions. The project follows a modular design, with each core operation handled by a dedicated source file.This project demonstrates core Data Structures and File Handling concepts in C applied to a real-world problem.

---

## Features

- ➕ Add new contacts with name, phone number, and email
- 📋 View all saved contacts in a formatted list
- 🔍 Search contacts by name or phone number
- 💾 Persist contacts permanently using file handling
- 🗂️ Clean structured data management using C `struct`

---

## Project Structure

```
AddressBook/
│
├── main.c              # Entry point — menu loop and user interaction
├── add_contact.c       # Logic to add and save a new contact
├── view_contact.c      # Displays all stored contacts
├── search_contact.c    # Search by name or phone number
├── file_handler.c      # File open/read/write/close operations
├── addressbook.h       # Shared header — struct definitions and declarations
│
└── contacts.txt        # Flat-file database storing all contact records
```

---

## Concepts Used

| Concept | Usage |
|---|---|
| **Structures** | `struct Contact` holds name, phone, and email per record |
| **File Handling** | `fopen`, `fread`, `fwrite`, `fclose` for persistent storage |
| **Modular Programming** | Separate `.c` files for each operation (add, view, search) |
| **String Manipulation** | `strcmp`, `strstr` for name/number search matching |
| **Functions** | Clean separation of logic into reusable, single-purpose functions |

---

## Technologies Used

- **Language:** C (C99)
- **Compiler:** GCC
- **Platform:** Linux / Windows (GCC supported)

---

## Getting Started

### Prerequisites

Make sure GCC is installed:

```bash
gcc --version
```

### Compile

From the project root directory:

```bash
gcc *.c -o addressbook
```

### Run

**Linux / macOS:**
```bash
./addressbook
```

**Windows:**
```bash
addressbook.exe
```

---

## Sample Input / Output

### ➕ Adding a Contact

```
===== Address Book =====
1. Add Contact
2. View All Contacts
3. Search Contact
4. Exit
Enter choice: 1

Enter Name   : Vishwajit Sawant
Enter Phone  : 9876543210
Enter Email  : vishwajit@example.com

✅ Contact saved successfully!
```

### 📋 Viewing All Contacts

```
Enter choice: 2

----------------------------------------
Name   : Vishwajit Sawant
Phone  : 9876543210
Email  : vishwajit@example.com
----------------------------------------
Name   : Jane Doe
Phone  : 9123456780
Email  : jane@example.com
----------------------------------------
```

### 🔍 Searching a Contact

```
Enter choice: 3
Enter name or number to search: Jane

----------------------------------------
Name   : Jane Doe
Phone  : 9123456780
Email  : jane@example.com
----------------------------------------
```

```
Enter name or number to search: 0000000000

❌ No contact found.
```

---

## Author

**Vishwajit Sawant**

---



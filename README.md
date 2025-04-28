# Phone Book with Call Log System

A comprehensive C++ application that manages contacts and call logs with an interactive command-line interface. This system allows users to maintain their phone contacts and track call history efficiently.

## Features

### Phone Book Management
- Add new contacts with name, phone number, email, and address
- Update existing contact information
- Delete contacts
- Display all contacts
- Search contacts by name
- Display contacts alphabetically
- Automatic sorting of contacts

### Call Log System
- Record incoming and outgoing calls
- Store call duration, date, and time
- View complete call history
- Search call logs by contact name
- Display call logs chronologically
- Separate views for incoming and outgoing calls

## Technical Details

### Data Structures
- Hash Table for efficient contact storage and retrieval
- Queue for managing call logs
- Linked List for contact chaining

### File Management
- Persistent storage using text files
- Automatic file handling for phonebook and call logs
- Data integrity checks

## Setup Instructions

### Prerequisites
- C++ compiler (g++ or any compatible compiler)
- Windows operating system (for the executable)

### Installation
1. Clone the repository:
```bash
git clone [repository-url]
```

2. Compile the source code:
```bash
g++ "PHONE BOOK WITH CALL LOG SYSTEM.cpp" -o phonebook
```

3. Run the executable:
```bash
./phonebook
```

## Usage

### Main Menu Options
1. Add Record to Phone Book
2. Update Record in Phone Book
3. Delete Record from Phone Book
4. Display Phone Book
5. Display by Alphabet in Phone Book
6. Search Record
7. Search Call Log
8. Outgoing Calls
9. Incoming Calls
10. Display Call Log
11. Exit

### Adding a Contact
- Enter contact details:
  - Name
  - Phone Number
  - Email
  - Address

### Making a Call
- Select contact
- Choose call type (incoming/outgoing)
- Enter call duration
- System automatically records date and time

## File Structure
- `PHONE BOOK WITH CALL LOG SYSTEM.cpp` - Main source code
- `phonebook.txt` - Contact storage file
- `call_log.txt` - Call history storage file

## Contributing
Feel free to submit issues and enhancement requests!

## License
This project is open source

## Screenshots
The project includes several screenshots demonstrating the user interface and functionality. Check the `PHONE BOOK WITH CALL LOG SYSTEM USING C++` directory for visual examples.
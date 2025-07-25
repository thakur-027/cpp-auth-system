# Secure User Authentication System (C++)

A simple console-based system that supports:
- User Registration
- Login Verification
- Password Change
- Password Hashing using SHA-256
- CSV File-based User Data Storage

## Features

- Modular code (split across '.cpp' and '.h' files)
- Hashes passwords securely using a custom SHA-256
- Uses file I/O and string parsing with 'fstream' and 'stringstream'

### Project Structure

- system1.cpp // main logic
- securehash.cpp // hashing functions
- securehash.h // hashing header
- file.csv // user data 
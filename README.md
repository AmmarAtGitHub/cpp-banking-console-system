# C++ Banking Console System

## Overview
Console-based banking management system built in C++.

This project is being developed incrementally using 'clean code' principles and divide-and-conquer architecture.

## Day 1 Progress
- Project structure setup
- Main menu architecture
- Enum-driven menu design
- Client struct definition


## Day 2 – File Handling & Display
- Load clients from external file
- Convert file records into structured objects
- String parsing with custom delimiter
- Display formatted client table
- Separation of concerns (UI / File / Logic)

## Day 3 – Add Client + File Persistence
- Add new client from user input
- Validate unique account number
- Append new client to file
- Convert object to file format
- Basic input handling improvements
- Data persistence between program runs

## Day 4 – Delete Client
- Search client by account number
- Display client details before deletion
- Confirmation prompt before removing a client
- Remove client from memory
- Rewrite the clients file after deletion to maintain data integrity
- Prevent accidental deletions through user confirmation

## Day 5 – Update Client
- Search client by account number
- Display client information before update
- Confirmation prompt before modifying data
- Update client fields (PIN, Name, Phone, Balance)
- Preserve the account number as a unique identifier
- Rewrite the clients file with the updated client data

## Day 6 – Find Client
- Search client by account number
- Display client information if found
- Show error message if account does not exist
- Reuse existing search and display functions

---

## Goals
- Refresh/practice/enhance C++ fundamentals
- Improve software design thinking

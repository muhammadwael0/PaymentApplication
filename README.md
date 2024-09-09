# Payment Application
![UI](UI.png)

## Introduction
This C project implements a simple payment application that allows users to perform basic payment 
transactions. It provides a user-friendly interface for selecting payment options, entering amounts, and 
processing payments.
## Features

Amount Input:
- Prompts the user to enter the payment amount.

Payment Processing:
- Simulates payment processing based on the selected payment option.

Receipt Generation:
- Provides a basic receipt with transaction details.

## Getting Started
### Prerequisites:
A C compiler (e.g., GCC, Clang) installed on your system.

### Installation:
1. Clone this repository or download the project files.
2. Open a terminal or command prompt and navigate to the project directory.
3. Compile the project using the following command in app directory:
```Bash
gcc -std=c89 -o app app.c ../payment_system/card/card.c ../payment_system/terminal/terminal.c ../payment_system/server/server.c ../data_base/file_handling/file_handling.c ../data_structure/list/list.c ../data_structure/queue/queue.c
```
4. Usage Run the compiled executable:
```Bash
./app
```

## Code Structure

The project consists of the following files:

app.c : 
> Contains the main logic for the payment application, including user input, payment processing.

card.c :
> Contains the implementation for credit/debit card payment data like PAN, EXP_Date, card Holder Number.

terminal.c :
> Contains the implementation for terminal-related data and functionalities like terminal ID, max amount and get date from user

server.c :
> Contains the implementation for server logic like checks the data base and validate all data and save this data to data base

file_handeling.c :
> Contains the implementation for file handling operations, such as reading and writing to files.

list.c :
> Contains the implementation for Singly linked list data structure.

queue.c :
> Contains the implementation for Queue data structure.

## Future Enhancements

Security: 
> Implement encryption for sensitive payment data (e.g., credit card numbers).

Error Handling: 
> Improve error handling for invalid inputs or unexpected situations.

Integration: 
> Integrate with external payment gateways or APIs for real-time processing.



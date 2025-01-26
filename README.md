SuperMarket Billing System

Table of Contents

1. Introduction
2. Features
3. System Requirements
4. Setup Instructions
5. How to Run the Program
6. Acknowledgments


Introduction:

The Supermarket Billing System is a console-based program designed to streamline supermarket operations. It provides functionality for managing products, customer transactions, and generating bills. With a user-friendly interface, this system ensures efficiency for both administrators and customers.

The program is implemented in C++ and uses file handling for persistent storage of product and customer data.

Features:

Admin:

- Add new products to the inventory.
- Edit existing product details.
- Delete products from the inventory.
- View a list of all available products.

Customer:

- Authenticate and save customer details.
- Browse the product catalog.
- Search for products by ID or name.
- Add products to a shopping cart.
- Checkout and generate a detailed bill.

System Requirements:

To run this project, ensure your system meets the following requirements:

- Operating System: Windows, Linux, or macOS.
- Compiler: A C++ compiler supporting C++11 or higher (e.g., GCC, Clang, MSVC).
- IDE (optional): Code::Blocks, Visual Studio, or any text editor.

Setup Instructions:

- Clone the Repository

Compile the Program:

Use a C++ compiler to compile the source code

Prepare the Data Files:

- Ensure the following files are in the same directory as the compiled program:

-- products.txt (for storing product details).
-- customers.txt (for saving customer information).

If the files don't exist, the program will create them automatically on the first run.

How to Run the Program:

- Run the Executable
- Execute the compiled program

Select an Option

- The program displays a main menu with the following options

1. Admin: Access admin functionalities (requires login).
2. Customer: Access the customer menu for shopping.
3. Exit: Quit the program.

Admin Login

Use the following credentials to log in as an admin:

- Username: hefmart
- Password: 12345

Customer Operations

- Enter your details as a customer, browse the catalog, and add items to your cart.

Exit the Program

Save all changes before exiting.

Acknowledgments

- This project was created to demonstrate file handling, structured programming, and user interaction in C++. It is a foundation for more advanced billing and inventory management systems.

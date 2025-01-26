#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

const int MAX_PRODUCTS = 100; // Maximum number of products
const int MAX_CART_ITEMS = 100; // Maximum number of items in the cart

// Product structure
struct Product {
    int productID;
    char name[50];
    double price;
    int quantity;
};

// Customer structure
struct Customer {
    char name[50];
    char email[50];
    char phone[15];
    char cnic[15];
};

// Global product list
Product products[MAX_PRODUCTS];
int productCount = 0;

// Function Prototypes
void adminMenu();
void customerMenu();
void productMenu(); // New function
void loadProducts();
void saveProducts();
void saveCustomerDetails(const Customer &customer);
void addProduct();
void editProduct();
void deleteProduct();
void viewProducts();
void addToCart(Product cart[], int &cartSize, double &total);
void checkout(Product cart[], int cartSize, double total, const Customer &customer);
void authenticateCustomer(Customer &customer);
void searchProductByID();
void searchProductByName();
bool verifyAdmin();

// Load products from file
void loadProducts() {
    ifstream file("products.txt");
    if (!file) {
        cout << "Warning: Could not open products file. Starting fresh.\n";
        return;
    }

    productCount = 0;
    while (file >> products[productCount].productID) {
        file.ignore(); // Ignore newline
        file.getline(products[productCount].name, 50);
        file >> products[productCount].price >> products[productCount].quantity;
        productCount++;
    }

    file.close();
}

// Save products to file
void saveProducts() {
    ofstream file("products.txt", ios::trunc);
    if (!file) {
        cout << "Error: Could not save products.\n";
        return;
    }

    for (int i = 0; i < productCount; i++) {
        file << products[i].productID << "\n"
             << products[i].name << "\n"
             << products[i].price << " " << products[i].quantity << "\n";
    }
    file.close();
}

// Save customer details to file
void saveCustomerDetails(const Customer &customer) {
    ofstream file("customers.txt", ios::app);
    if (!file) {
        cout << "Error: Could not save customer details.\n";
        return;
    }

    file << "Name: " << customer.name << "\n"
         << "Email: " << customer.email << "\n"
         << "Phone: " << customer.phone << "\n"
         << "CNIC: " << customer.cnic << "\n\n";
    file.close();
}

// Admin: Add a new product
void addProduct() {
    if (productCount >= MAX_PRODUCTS) {
        cout << "Product list is full!\n";
        return;
    }

    Product newProduct;
    cout << "Enter product ID: ";
    cin >> newProduct.productID;

    // Check for duplicate product ID
    for (int i = 0; i < productCount; i++) {
        if (products[i].productID == newProduct.productID) {
            cout << "Error: Product ID already exists.\n";
            return;
        }
    }

    cin.ignore();
    cout << "Enter product name: ";
    cin.getline(newProduct.name, 50);
    cout << "Enter product price: ";
    cin >> newProduct.price;
    cout << "Enter product quantity: ";
    cin >> newProduct.quantity;

    products[productCount++] = newProduct;
    saveProducts();

    cout << "Product added successfully!\n";
}

// Admin: Edit an existing product
void editProduct() {
    int id;
    cout << "Enter product ID to edit: ";
    cin >> id;

    for (int i = 0; i < productCount; i++) {
        if (products[i].productID == id) {
            cout << "Editing product: " << products[i].name << "\n";
            cout << "Enter new name: ";
            cin.ignore();
            cin.getline(products[i].name, 50);
            cout << "Enter new price: ";
            cin >> products[i].price;
            cout << "Enter new quantity: ";
            cin >> products[i].quantity;

            saveProducts();
            cout << "Product updated successfully!\n";
            return;
        }
    }

    cout << "Product not found.\n";
}

// Admin: Delete a product
void deleteProduct() {
    int id;
    cout << "Enter product ID to delete: ";
    cin >> id;

    for (int i = 0; i < productCount; i++) {
        if (products[i].productID == id) {
            for (int j = i; j < productCount - 1; j++) {
                products[j] = products[j + 1];
            }
            productCount--;
            saveProducts();
            cout << "Product deleted successfully!\n";
            return;
        }
    }

    cout << "Product not found.\n";
}

// Admin: View all products
void viewProducts() {
    if (productCount == 0) {
        cout << "No products available.\n";
        return;
    }

    cout << left << setw(10) << "ID" << setw(30) << "Name" << setw(10) << "Price" << "Quantity\n";
    cout << string(60, '-') << "\n";

    for (int i = 0; i < productCount; i++) {
        cout << left << setw(10) << products[i].productID
             << setw(30) << products[i].name
             << setw(10) << products[i].price
             << products[i].quantity << "\n";
    }
}

// Customer: Add to cart and checkout
void addToCart(Product cart[], int &cartSize, double &total) {
    int id, qty;
    cout << "Enter product ID to add to cart: ";
    cin >> id;
    cout << "Enter quantity: ";
    cin >> qty;

    for (int i = 0; i < productCount; i++) {
        if (products[i].productID == id) {
            if (products[i].quantity >= qty) {
                products[i].quantity -= qty;

                cart[cartSize] = products[i];
                cart[cartSize].quantity = qty;
                cartSize++;
                total += products[i].price * qty;

                saveProducts();
                cout << "Added to cart.\n";
            } else {
                cout << "Insufficient stock.\n";
            }
            return;
        }
    }
    cout << "Product not found.\n";
}

// Customer: Checkout and display the bill
void checkout(Product cart[], int cartSize, double total, const Customer &customer) {
    if (cartSize == 0) {
        cout << "Your cart is empty.\n";
        return;
    }

    cout << "\nYour Cart:\n";
    cout << left << setw(10) << "ID" << setw(30) << "Name" << setw(10) << "Price" << "Quantity\n";
    cout << string(60, '-') << "\n";

    for (int i = 0; i < cartSize; i++) {
        cout << left << setw(10) << cart[i].productID
             << setw(30) << cart[i].name
             << setw(10) << cart[i].price
             << cart[i].quantity << "\n";
    }

    cout << "\nTotal: $" << fixed << setprecision(2) << total << "\n";
    cout << "Thank you for shopping with us, " << customer.name << "!\n";
}

// Customer: Authenticate customer details
void authenticateCustomer(Customer &customer) {
    cin.ignore();
    cout << "Enter your Name: ";
    cin.getline(customer.name, 50);
    cout << "Enter your Email: ";
    cin.getline(customer.email, 50);
    cout << "Enter your Phone Number: ";
    cin.getline(customer.phone, 15);
    cout << "Enter your CNIC: ";
    cin.getline(customer.cnic, 15);

    saveCustomerDetails(customer);

    cout << "\nThank you, " << customer.name << "! Let's start shopping.\n";
}

// Search products by ID
void searchProductByID() {
    int id;
    cout << "Enter product ID to search: ";
    cin >> id;

    for (int i = 0; i < productCount; i++) {
        if (products[i].productID == id) {
            cout << "Product found: " << products[i].name << "\n"
                 << "Price: " << products[i].price << "\n"
                 << "Available stock: " << products[i].quantity << "\n";
            return;
        }
    }

    cout << "Product not found.\n";
}

// Search products by Name
void searchProductByName() {
    char name[50];
    cout << "Enter product name to search: ";
    cin.ignore();
    cin.getline(name, 50);

    bool found = false;
    for (int i = 0; i < productCount; i++) {
        if (strstr(products[i].name, name)) {
            cout << "Product found: " << products[i].name << "\n"
                 << "Price: " << products[i].price << "\n"
                 << "Available stock: " << products[i].quantity << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "Product not found.\n";
    }
}

// Customer: Product menu (View/Search Products)
void productMenu() {
    while (true) {
        cout << "\nProduct Menu:\n";
        cout << "1. View All Products\n";
        cout << "2. Search Product by ID\n";
        cout << "3. Search Product by Name\n";
        cout << "4. Go Back\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                viewProducts();
                break;
            case 2:
                searchProductByID();
                break;
            case 3:
                searchProductByName();
                break;
            case 4:
                return;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}

// Customer Menu
void customerMenu() {
    Product cart[MAX_CART_ITEMS];
    int cartSize = 0;
    double total = 0;
    Customer customer;

    authenticateCustomer(customer);

    while (true) {
        cout << "\nCustomer Menu:\n";
        cout << "1. Product Menu\n";
        cout << "2. Add to Cart\n";
        cout << "3. Checkout\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                productMenu();
                break;
            case 2:
                addToCart(cart, cartSize, total);
                break;
            case 3:
                checkout(cart, cartSize, total, customer);
                return;
            case 4:
                return;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}

// Admin Menu
void adminMenu() {
    while (true) {
        cout << "\nAdmin Menu:\n";
        cout << "1. Add Product\n";
        cout << "2. Edit Product\n";
        cout << "3. Delete Product\n";
        cout << "4. View Products\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                editProduct();
                break;
            case 3:
                deleteProduct();
                break;
            case 4:
                viewProducts();
                break;
            case 5:
                return;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}

// Function to verify admin credentials
bool verifyAdmin() {
    string username, password;
    cout << "Enter Admin Username: ";
    cin >> username;
    cout << "Enter Admin Password: ";
    cin >> password;

    // Hardcoded admin credentials
    if (username == "admin" && password == "admin") {
        cout << "Access granted. Welcome, Admin!\n";
        return true;
    } else {
        cout << "Invalid username or password. Access denied.\n";
        return false;
    }
}

// Main Menu
int main() {
    loadProducts();

    while (true) {
        cout << "\nSupermarket Billing System:\n";
        cout << "1. Admin\n";
        cout << "2. Customer\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                if (verifyAdmin()) {
                    adminMenu();
                }
                break;
            case 2:
                customerMenu();
                break;
            case 3:
                saveProducts();
                cout << "Exiting program. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}

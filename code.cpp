#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <fstream>
using namespace std;

string getValidatedString(string text) {
    string input;
    bool valid;
    do {

        cout << text;
        getline(cin, input);  // Read the entire line as a string
        valid = true;

        // Check if the input contains any digits
        for (char c : input) {
            if (isdigit(c)) {
                valid = false;
                cout << "Invalid input. Please enter a valid string without digits." << endl;
                break;
            }
        }

        // Check if the input is empty
        if (input.empty()) {
            valid = false;
            cout << "Invalid input. Please enter a non-empty string." << endl;
        }
    } while (!valid);
    return input;
}

int getValidatedInt(string text) {
    int num;
    string input;
    bool valid;

    do {
        cout << text;
        getline(cin,input);
        
        // Trim leading and trailing whitespace
        input.erase(0, input.find_first_not_of(" \t"));
        input.erase(input.find_last_not_of(" \t") + 1);

        valid = true;

        // Check if the input is empty or contains invalid characters
        if (input.empty() || (input[0] == '-' && input.length() == 1) || (input[0] != '-' && !isdigit(input[0]))) {
            valid = false;
        } else {
            for (size_t i = 1; i < input.length(); ++i) {
                if (!isdigit(input[i])) {
                    valid = false;
                    break;
                }
            }
        }

        if (valid) {
            try {
                num = stoi(input);  // Convert the string to an integer
                if (num <= 0) {      // Check for positive numbers only
                    valid = false;
                    cout << "Please enter a number greater than 0." << endl;
                }
            } catch (const exception&) {
                valid = false;
            }
        }

        if (!valid) {
            cout << "Invalid input. Please enter a valid integer." << endl;
        }
    } while (!valid);

    return num;
}
class PaymentStrategy {
    public:
        virtual void pay(double amount) = 0;                    // Abstract method for making a payment
        virtual void logPayment(double amount, int orderNumber) = 0; // Abstract method for logging payment
        virtual ~PaymentStrategy() = default;                  // Virtual destructor
};

// GCash Payment Implementation
class GcashPayment : public PaymentStrategy {
    private:
        static GcashPayment* instance; // Static instance for singleton
    
        // Private constructor to prevent direct instantiation
        GcashPayment() {}
    
    public:
        // Delete copy constructor and assignment operator to enforce singleton
        GcashPayment(const GcashPayment&) = delete;
        GcashPayment& operator=(const GcashPayment&) = delete;
    
        // Public method to access the singleton instance
        static GcashPayment* getInstance() {
            if (instance == nullptr) {
                instance = new GcashPayment(); // Create the instance if it doesn't exist
            }
            return instance; // Return the existing instance
        }
    
        void pay(double amount) override {
            cout << "\nPaid PHP " << amount << " using GCash.\n";
        }
    
        void logPayment(double amount, int orderNumber) override {
            ofstream file("PaymentLog.txt", ios::app);
            if (file.is_open()) {
                file << "[LOG] -> Order ID: " << orderNumber
                     << " has been successfully checked out and paid using GCash: PHP " << amount << "\n";
                file.close();
            } else {
                cout << "Error: Unable to open payment log file.\n";
            }
        }
    };
    
    // Initialize the static instance
    GcashPayment* GcashPayment::instance = nullptr;
// Cash Payment Implementation
class CashPayment : public PaymentStrategy {
    private:
        static CashPayment* instance; // Static instance for singleton
    
        // Private constructor to prevent direct instantiation
        CashPayment() {}
    
    public:
        // Delete copy constructor and assignment operator to enforce singleton
        CashPayment(const CashPayment&) = delete;
        CashPayment& operator=(const CashPayment&) = delete;
    
        // Public method to access the singleton instance
        static CashPayment* getInstance() {
            if (instance == nullptr) {
                instance = new CashPayment(); // Create the instance if it doesn't exist
            }
            return instance; // Return the existing instance
        }
    
        void pay(double amount) override {
            cout << "Paid PHP " << amount << " in cash.\n";
        }
    
        void logPayment(double amount, int orderNumber) override {
            ofstream file("PaymentLog.txt", ios::app);
            if (file.is_open()) {
                file << "[LOG] -> Order ID: " << orderNumber
                     << " has been successfully checked out and paid using Cash: PHP " << amount << "\n";
                file.close();
            } else {
                cout << "Error: Unable to open payment log file.\n";
            }
        }
    };
    
    // Initialize the static instance
    CashPayment* CashPayment::instance = nullptr;
// Credit/Debit Card Payment Implementation
class CardPayment : public PaymentStrategy {
    public:
        void pay(double amount) override {
            cout << "Paid PHP " << amount << " using Credit/Debit Card.\n";
        }
    
        void logPayment(double amount, int orderNumber) override {
            ofstream file("PaymentLog.txt", ios::app);
            if (file.is_open()) {
                file << "[LOG] -> Order ID: " << orderNumber
                     << " has been successfully checked out and paid using Credit/Debit Card: PHP " << amount << "\n";
                file.close();
            }
        }
    };
class Product{
    private:
        string productId, name;
        long price;
    public:
    //Constructor
        Product(string productId, string name, long cost){
            this->productId = productId;
            this->name = name;
            this->price = cost;
        }
    //Methods
        string getProductId() const {
            return productId;
        }
        string getProductName() const {
            return name;
        }
        long getProductCost() const {
            return price;
        }
};

class ProductList{
    private:
        static const int productAvailable = 5;
        Product product[productAvailable] = {
            Product{"SDA", "Strawberry Seed", 500},     //Create the lists of products
            Product{"SDB", "Tomato Seed", 250},
            Product{"SDC", "Corn Seed", 300},
            Product{"SDD", "Mango Seed", 1000},
            Product{"SDE", "Grape Seed", 1500}
        };
        
    public:
        int getProductAvailable() const {         //Return the number of products in the list
            return productAvailable;
        }

        const Product& getProduct(int productNumber) const {
            if (productNumber >= 0 && productNumber < productAvailable) {          //Get the product's details
                return product[productNumber];                                     //If the ID inputted is between S1-S5, return the product details
            } else {
                throw out_of_range("Product does not exist.");                     //Otherwise, output product does not exist.
            }
        }

        void productDetails() const{                                      //Table of the list of products
            cout << string(70, '-') << endl;
            cout << "\t\t\tList of Products" << endl;
            cout << string(70, '-') << endl;
            cout << setw(25) << left << "Product ID"
                << setw(30) << left << "Product Name"
                << setw(20) << left << "Price" << endl;
            cout << string(70, '-') << endl;
        
            for (int i = 0; i < productAvailable; i++) {
                cout << setw(25) << left << product[i].getProductId()               // Display each product in the table
                    << setw(30) << left << product[i].getProductName()
                    << setw(20) << left << product[i].getProductCost() << endl;
            }
        }
};

class ShoppingCart {
    private:
        string id;
        int cartNumber = 0;              // The number of unique products in the cart
        int* quantity;                   // Dynamic array to track product quantities
        const Product** cart;            // Dynamic array for products
        string choice;

    public:
        ShoppingCart() {
            cart = new const Product*[50]; // Allocate memory for cart
            quantity = new int[50]();      // Allocate memory for quantity and initialize to 0
        }

        ~ShoppingCart() {
            delete[] cart;    // Free memory for cart
            delete[] quantity; // Free memory for quantity
        }

        void addProduct(ProductList& productList) {
            string choice;
            do {
                string id;
                bool foundInList = false;
                const Product* productAdded = nullptr;

                do {
                    try {
                        cout << "\nEnter the ID of the product you want to add to the shopping cart." << endl;
                        cout << "PRODUCT ID: ";
                        cin >> id;
                
                        // Search the product list for the inputted ID
                        foundInList = false; // Set to false everytime it runs
                        for (int i = 0; i < productList.getProductAvailable(); i++) {
                            const Product& product = productList.getProduct(i);
                            if (id == product.getProductId()) {
                                foundInList = true; // Set to true if the product is found in the list of products
                                productAdded = &product; // Store the product's info
                                break; 
                            }
                        }
                
                        // Throw exception if the product ID was not found
                        if (!foundInList) {
                            throw invalid_argument("Product ID not found. Please try again.");
                        }
                
                        // Check if the product is already in the cart
                        bool alreadyInCart = false;
                        for (int j = 0; j < cartNumber; j++) {
                            if (cart[j]->getProductId() == id) {
                                quantity[j] += 1; // Increase quantity of the existing product
                                alreadyInCart = true;
                                cout << "Product quantity updated in cart." << endl;
                                break;
                            }
                        }
                
                        // Add new product to the cart if not already present
                        if (!alreadyInCart) {
                            cart[cartNumber] = productAdded; // Add product to cart
                            quantity[cartNumber] = 1; // Set quantity to 1
                            cartNumber++;
                            cout << "Product added successfully." << endl;
                        }
                
                    } catch (const invalid_argument& e) {
                        // Handle invalid input exception
                        cout << e.what() << endl; // Display error message
                    }
                } while (!foundInList); // Repeat until a valid product ID is entered
                
                cin.ignore();
                choice = getValidatedString("\nAdd Another Product (Y/N)?: ");
                } while (choice == "Y" || choice == "y");
                system("cls");
        }

        void clearCart() {
            for (int i = 0; i < cartNumber; i++) {
                cart[i] = nullptr;
                quantity[i] = 0;
            }
            cartNumber = 0;
        }

        const Product** getCart() const {
            return cart;
        }

        int getCartNumber() const {
            return cartNumber;
        }

        int getQuantity(int num) const {
            return quantity[num];
        }

        void viewCart() const {
            if (cartNumber == 0) {
                return;
            }

            cout << "\n\t\t\t\tShopping Cart" << endl;
            cout << string(80, '-') << endl;
            cout << setw(25) << left << "Product ID"
                << setw(30) << left << "Product Name"
                << setw(15) << left << "Price"
                << setw(15) << left << "Quantity" << endl;
            cout << string(80, '-') << endl;

            for (int i = 0; i < cartNumber; i++) {
                cout << setw(25) << left << cart[i]->getProductId()
                    << setw(30) << left << cart[i]->getProductName()
                    << setw(15) << left << cart[i]->getProductCost()
                    << setw(15) << left << quantity[i] << endl;
            }
        }
};

class Order {
    private:
        const Product*** allOrders;       // Array to store products for each order
        int** allOrderQuantities;         // Array to track quantities for each order
        double* allTotalAmounts;          // Array to track total amounts for each order
        string* paymentMethods;           // Array to store payment methods for each order
        int currentOrderId = 0;           // Order ID counter
        int maxOrders = 50;               // Maximum number of orders allowed
        PaymentStrategy* strategy;        // Pointer to the current payment strategy
        int* orderSizes;
    
        static Order* instance;           // Static instance for Singleton
    
        // Private constructor to prevent external instantiation
        Order() {
            allOrders = new const Product**[maxOrders];       // Allocate space for product pointers
            allOrderQuantities = new int*[maxOrders];         // Allocate space for quantity arrays
            allTotalAmounts = new double[maxOrders];          // Allocate space for total amounts
            paymentMethods = new string[maxOrders];          // Allocate space for payment methods
    
            orderSizes = new int[maxOrders];
            for (int i = 0; i < maxOrders; i++) {
                orderSizes[i] = 0;
            }
            // Initialize arrays
            for (int i = 0; i < maxOrders; i++) {
                allOrders[i] = nullptr;
                allOrderQuantities[i] = nullptr;
                allTotalAmounts[i] = 0.0;
                paymentMethods[i] = "";
            }
    
            strategy = nullptr;
        }
    
    public:
        // Delete copy constructor and assignment operator to prevent copying
        Order(const Order&) = delete;
        Order& operator=(const Order&) = delete;
    
        // Destructor
        ~Order() {
            for (int i = 0; i < currentOrderId; i++) {
                delete[] allOrders[i];
                delete[] allOrderQuantities[i];
            }
            delete[] allOrders;
            delete[] allOrderQuantities;
            delete[] allTotalAmounts;
            delete[] paymentMethods;
            delete[] orderSizes;
    
            if (strategy) {
                delete strategy;
            }
        }
    
        // Static method to access the Singleton instance
        static Order* getInstance() {
            if (instance == nullptr) {
                instance = new Order();           // Create the instance if it doesn't exist
            }
            return instance;
        }
    
        void checkout(ShoppingCart& cartInstance) {
            if (cartInstance.getCartNumber() == 0) {
                cout << "Your shopping cart is empty" << endl;
                return;
            }
        
            string choice = getValidatedString("\nDo you want to checkout all the products? (Y/N): ");
        
            if (choice == "Y" || choice == "y") {
                int cartSize = cartInstance.getCartNumber();
                const Product** cartArray = cartInstance.getCart();
                double total = 0.0;
        
                // Allocate memory for current order details
                allOrders[currentOrderId] = new const Product*[cartSize];
                allOrderQuantities[currentOrderId] = new int[cartSize];
        
                for (int i = 0; i < cartSize; i++) {
                    allOrders[currentOrderId][i] = cartArray[i];               // Store product pointers
                    allOrderQuantities[currentOrderId][i] = cartInstance.getQuantity(i); // Store quantities
                    total += cartArray[i]->getProductCost() * allOrderQuantities[currentOrderId][i];
                }
        
                allTotalAmounts[currentOrderId] = total; // Store total amount for this order
        
                // Update orderSizes with the number of products in this order
                orderSizes[currentOrderId] = cartSize;
        
                // Choose and store the payment method
                cout << "Total Amount: PHP " << total;
                int paymentChoice = getValidatedInt("\nChoose a payment method (1: GCash, 2: Cash, 3: Credit/Debit Card): ");
        
                switch (paymentChoice) {
                    case 1:
                        strategy = GcashPayment::getInstance();
                        paymentMethods[currentOrderId] = "GCash";
                        break;
                    case 2:
                        strategy = CashPayment::getInstance();
                        paymentMethods[currentOrderId] = "Cash";
                        break;
                    case 3:
                        strategy = new CardPayment();
                        paymentMethods[currentOrderId] = "Credit/Debit Card";
                        break;
                    default:
                        cout << "Invalid payment choice. Checkout cancelled.\n";
                        delete[] allOrders[currentOrderId]; // Free allocated memory
                        delete[] allOrderQuantities[currentOrderId];
                        return;
                }
        
                if (strategy) {
                    strategy->pay(total);
                    strategy->logPayment(total, currentOrderId + 1);
                    delete strategy;
                    strategy = nullptr;
                }
        
                cartInstance.clearCart();
                cout << "\nCheckout complete! Thank you for your purchase.\n\n";
        
                currentOrderId++; // Increment order ID for next order
            }
            system("pause");
            system("cls");
        }
    
        void viewOrder() const {
            if (currentOrderId == 0) {
                cout << "No orders have been placed yet.\n";
                return;
            }
        
            for (int orderIndex = 0; orderIndex < currentOrderId; orderIndex++) {
                cout << "\nOrder Number: " << orderIndex + 1 << endl;
                cout << "Total Amount: PHP " << allTotalAmounts[orderIndex] << endl;
                cout << "Payment Method: " << paymentMethods[orderIndex] << endl;
                cout << "Order Details:" << endl;
                cout << string(80, '-') << endl;
                cout << setw(25) << left << "Product ID"
                     << setw(30) << left << "Product Name"
                     << setw(15) << left << "Price"
                     << setw(15) << left << "Quantity" << endl;
                cout << string(80, '-') << endl;
        
                // Use orderSizes[orderIndex] to determine the number of products
                for (int i = 0; i < orderSizes[orderIndex]; i++) {
                    cout << setw(25) << left << allOrders[orderIndex][i]->getProductId()
                         << setw(30) << left << allOrders[orderIndex][i]->getProductName()
                         << setw(15) << left << allOrders[orderIndex][i]->getProductCost()
                         << setw(15) << left << allOrderQuantities[orderIndex][i] << endl;
                }
            }
            cout << endl;
            system("pause");
            system("cls");
        }
    };
    
    // Initialize Singleton instance
    Order* Order::instance = nullptr;

int main(){
    int choice;
    ProductList products;
    ShoppingCart cart;
    Order* order = Order::getInstance();

    do {
        cout << "\n\t    Main Menu" << endl
            << "\t1) View Products" << endl
            << "\t2) View Shopping Cart" << endl
            << "\t3) View Orders" << endl
            << "\t4) Exit" << endl << endl;
        choice = getValidatedInt("Choice: ");
                switch (choice){
                    case 1: {
                        system("cls");
                        products.productDetails();
                        cart.addProduct(products);
                        break;
                    }
                    case 2 : {
                        system("cls");
                        cart.viewCart();
                        order->checkout(cart);
                        break;
                    }
                    case 3 : {
                        system("cls");
                        order->viewOrder();
                        break;
                    }
                    case 4 : {
                        system("cls");
                        cout << "Program Exit.";
                        break;
                    }
                    default:
                        system("cls");
                        cout << "Invalid Choice. Please Try Again.";
                }
    } while (choice != 4);
    
    return 0;
}
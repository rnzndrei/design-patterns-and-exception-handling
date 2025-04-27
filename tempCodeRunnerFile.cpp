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
    
                // Choose and store the payment method
                int paymentChoice = getValidatedInt("Choose a payment method (1: GCash, 2: Cash, 3: Credit/Debit Card): ");
    
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
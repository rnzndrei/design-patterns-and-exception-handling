#include <iostream>
#include <iomanip>
#include <stdexcept>
using namespace std;

class TableInterface{
    public:
        virtual void tableFormat() const = 0;
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
            Product{"S1", "Strawberry Seed", 500},     //Create the lists of products
            Product{"S2", "Tomato Seed", 250},
            Product{"S3", "Corn Seed", 300},
            Product{"S4", "Mango Seed", 1000},
            Product{"S5", "Grape Seed", 1500}
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
                << setw(20) << left << "Cost" << endl;
            cout << string(70, '-') << endl;
        
            for (int i = 0; i < productAvailable; i++) {
                cout << setw(25) << left << product[i].getProductId()               // Display each product in the table
                    << setw(30) << left << product[i].getProductName()
                    << setw(20) << left << product[i].getProductCost() << endl;
            }
        }
};

class ShoppingCart{
    private:
        string id;
        int cartNumber = 0;           //The number of unique product added in the cart
        int quantity[5] = {0};       //An array to define the number of quantity the product added to the cart
        char choice;                
        const Product** cart;       //Create a pointer of arrays

    public:
        ShoppingCart(){
            cart = new const Product*[50];       //Create a cart to store the product in
        }
        //Methods   
            void addProduct(ProductList& productList) {
                char choice;
                do {
                    string id;
                    bool foundInList = false;
                    const Product* productAdded = nullptr;
                    
                    cout << "\nEnter the ID of the product you want to add to the shopping cart." << endl;
                    cout << "PRODUCT ID: ";
                    cin >> id;
                    
                    // Look through the products list to see if the inputted ID exists in the list.
                    for (int i = 0; i < productList.getProductAvailable(); i++) {
                        const Product& product = productList.getProduct(i);
                        if (id == product.getProductId()) {
                            foundInList = true;              //Set as true if the product exists
                            productAdded = &product;         //Store the product found in a variable "productAdded"
                            break;
                        }
                    }
                    
                    if (!foundInList) {
                        cout << "Product ID not found. Please try again." << endl;
                    } else {
                        bool alreadyInCart = false;
                            for (int j = 0; j < cartNumber; j++) {
                                if (cart[j]->getProductId() == id) {     // Check if the product is already in the cart
                                    quantity[j] += 1;  // Increase quantity of the existing product
                                    alreadyInCart = true;  //Set as true if the product was added already
                                    break;
                                }
                            }
                        // Add new product if it wasn't already in the cart
                            if (!alreadyInCart) {
                                cart[cartNumber] = productAdded;     //Add the product stored earlier to the cart
                                quantity[cartNumber] = 1;            //Add quantity of the product added
                                cartNumber++;                        //Increase the cart number
                                cout << "Product added to cart: " << productAdded->getProductName() << endl;
                            } else {
                                cout << "Product quantity updated in cart." << endl;
                            }
                    }
                    
                    cout << "\nAdd Another Product (Y/N)?: ";
                    cin >> choice;
                } while (choice == 'Y' || choice == 'y');
            }
        
            void viewCart() const {
                if (cartNumber == 0) {
                    cout << "Your shopping cart is empty!" << endl;
                    return;
                }
        
                cout << "\nProducts in your cart:" << endl;
                cout << string(70, '-') << endl;
                cout << setw(25) << left << "Product ID"
                     << setw(30) << left << "Product Name"
                     << setw(15) << left << "Cost"
                     << setw(15) << left << "Quantity" << endl;
                cout << string(70, '-') << endl;
        
                for (int i = 0; i < cartNumber; i++) {
                    cout << setw(25) << left << cart[i]->getProductId()
                         << setw(30) << left << cart[i]->getProductName()
                         << setw(15) << left << cart[i]->getProductCost()
                         << setw(15) << left << quantity[i] << endl;
                }
            }

            //To do:
            //Gawin mo yung checkout
            //Payment
            //Patterns
            //Try and Catch
};

class Order{

};


int main(){
    char choice;
    ProductList products;
    ShoppingCart cart;

    do {

    cout << "\t    Main Menu" << endl
         << "\ta) View Products" << endl
         << "\tb) View Shopping Cart" << endl
         << "\tc) View Orders" << endl << endl;
    cout << "Choice: ";
        cin >> choice;
            switch (choice){
                case 'a': {
                    system("cls");
                    products.productDetails();
                    cart.addProduct(products);
                    break;
                }
                case 'b' : {
                    system("cls");
                    cart.viewCart();
                    break;
                }
                case 'c' : {
                    system("cls");
                    //View Orders
                    break;
                }
                case 'd' : {
                    cout << "Progmra Exit.";
                    break;
                }
                
            }
        } while (choice != 'd');
    
    return 0;
}
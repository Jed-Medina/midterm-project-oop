#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<iomanip>

using namespace std;

bool checkValidity(bool *restart) {
    if (cin) return false;

    *restart = true;
    cin.clear();
    cin.ignore(1000, '\n');
    system("cls");
    cout << "Invalid Input!\n";
    system("pause");
    return true;
}

string makeWordLower(string word) {
    string newWord;
    for (int i = 0; i < word.length(); i++) {
        newWord += tolower(word[i]);
    }
    return newWord;
}

class Item {
    private:
        string id;
        string name, category;
        int quantity;
        double price;

    public:
        Item(string pId, string pName, int pQuantity, double pPrice, string pCategory) : id(pId), name(pName), quantity(pQuantity), price(pPrice), category(pCategory) {}

        string getID() {return id;}

        string getName() {return name;}

        int getQuantity() {return quantity;}

        double getPrice() {return price;}

        string getCategory() {return category;}

        void setQuantity(int value) {quantity = value;}

        void setPrice(int value) {price = value;} 

        void display(int index) {
            cout << "|" << index << ". " << setw(17) << left << getID() << "|"
            << setw(20) << left << getName() << "|"
            << setw(20) << left << getQuantity() << "|"
            << setw(20) << left << getPrice() << "|"
            << setw(20) << left << getCategory() << "|\n";
        }
};

class Category {
    protected:
        string categoryName;
        
    public:
        Category(string pName) : categoryName(pName) {}

        string getCategoryName() {return categoryName;}

        virtual void displayCategoryItems(vector<Item> pItems) = 0;
};

class ClothingCategory : public Category {
    private:

    public:
        ClothingCategory() : Category("clothing") {}

        void displayCategoryItems(vector<Item> pItems) override {
            system("cls");
            bool isEmpty = true;
            cout << "Clothing Items:\n";
            cout << "__ID___________________NAME_________________QUANTITY_____________PRICE_______________CATEGORY____________\n";
            for (int i = 0; i < pItems.size(); i++) {
                if (pItems.at(i).getCategory() != getCategoryName()) continue;
                pItems.at(i).display(i+1);
                isEmpty = false;
            }
            if (isEmpty) {
                cout << "| " << setw(103) << left << "EMPTY! NO ITEMS IN CLOTHING CATEGORY!" << "|\n";
            }
            cout << "|____________________|____________________|____________________|____________________|____________________|\n";
            system("pause");
        }
};

class ElectronicsCategory : public Category {
    private:

    public:
        ElectronicsCategory() : Category("electronics") {}

        void displayCategoryItems(vector<Item> pItems) override {
            system("cls");
            bool isEmpty = true;
            cout << "Electronic Items:\n";
            cout << "__ID___________________NAME_________________QUANTITY_____________PRICE_______________CATEGORY____________\n";
            for (int i = 0; i < pItems.size(); i++) {
                if (pItems.at(i).getCategory() != getCategoryName()) continue;
                pItems.at(i).display(i+1);
                isEmpty = false;
            }
            if (isEmpty) {
                cout << "| " << setw(103) << left << "EMPTY! NO ITEMS IN ELECTRONICS CATEGORY!" << "|\n";
            }
            cout << "|____________________|____________________|____________________|____________________|____________________|\n";
            system("pause");
        }
};

class EntertainmentCategory : public Category {
    private:

    public:
        EntertainmentCategory() : Category("entertainment") {}

        void displayCategoryItems(vector<Item> pItems) override {
            system("cls");
            bool isEmpty = true;
            cout << "Entertainment Items:\n";
            cout << "__ID___________________NAME_________________QUANTITY_____________PRICE_______________CATEGORY____________\n";
            for (int i = 0; i < pItems.size(); i++) {
                if (pItems.at(i).getCategory() != getCategoryName()) continue;
                pItems.at(i).display(i+1);
                isEmpty = false;
            }
            if (isEmpty) {
                cout << "| " << setw(103) << left << "EMPTY! NO ITEMS IN ENTERTAINMENT CATEGORY!" << "|\n";
            }
            cout << "|____________________|____________________|____________________|____________________|____________________|\n";
            system("pause");
        }
};

class Inventory {
    private:
        ClothingCategory clothing;
        ElectronicsCategory electronics;
        EntertainmentCategory entertainment;
        vector<Item> items;

    public:
        bool checkItemID(string pID) {
            for (int i = 0; i < items.size(); i++) {
                if (makeWordLower(items.at(i).getID()) == makeWordLower(pID)) {
                    system("cls");
                    cout << "Invalid Input! ID Already Exists! ID Must Be Unique!\n";
                    system("pause");
                    return true;
                }
            }
            return false;
        }

        void addItem() {
            string id, name; 
            int quantity;
            double price;
            string category;

            bool restartType;
            do {
                restartType = false;
                system("cls");
                cout << "- CLOTHING\n"
                    << "- ELECTRONICS\n"
                    << "- ENTERTAINMENT\n"
                    << "Input A Category For Item: ";
                getline(cin, category);

                if (checkValidity(&restartType)) continue;
                category = makeWordLower(category);
                if (category != clothing.getCategoryName() && category != electronics.getCategoryName() && category != entertainment.getCategoryName()) {
                        restartType = true;
                        system("cls");
                        cout << "Category <" << category << "> does not exist!\n";
                        system("pause");
                }
            } while (restartType);

            do {
                system("cls");
                cout << "Enter Item ID: ";
                getline(cin, id);
            } while (checkItemID(id));

            system("cls");
            cout << "Enter Item Name: ";
            getline(cin, name);

            bool restartQuantity;
            do {
                system("cls");
                restartQuantity = false;
                cout << "Enter Quantity: ";
                cin >> quantity;
                checkValidity(&restartQuantity);
            } while (restartQuantity);

            bool restartPrice;
            do {
                system("cls");
                restartPrice = false;
                cout << "Enter Item Price: ";
                cin >> price;
                checkValidity(&restartPrice);
            } while (restartPrice);

            system("cls");
            cout << "Item added successfully!\n";
            items.push_back(Item{id, name, quantity, price, category});
            system("pause");
        }
        
        Item* searchItem() {
            system("cls");
            string id;
            cout << "Enter ID Of Item: ";
            getline(cin, id);
            Item* item;
            for (int i = 0; i < items.size(); i++) {
                item = &items.at(i);
                if (makeWordLower(item->getID()) == makeWordLower(id)) return item;
            }
            system("cls");
            cout << "Item Not Found!\n";
            system("pause");
            return nullptr;
        }
        
        void updateItem() {
            Item* item = searchItem();
            if (item == nullptr) return;
            bool restart;
            do {
                restart = false;
                int choice;
                system("cls");
                cout << "1 - Quantity\n"
                    << "2 - Price\n"
                    << "Choose What To Update [1-2]: ";
                cin >> choice;

                if (checkValidity(&restart)) continue;

                switch (choice)
                {
                case 1:{
                    bool restart;
                    do {
                        restart = false;
                        int newQuantity;
                        system("cls");
                        cout << "Set New Quantity: ";
                        cin >> newQuantity;

                        if (checkValidity(&restart)) continue;

                        cout << "Quantity of Item <" << item->getName() << "> is updated from <" << item->getQuantity() << "> to <"
                            << newQuantity << ">\n";
                        item->setQuantity(newQuantity);
                        system("pause");
                    } while (restart);
                    break;
                }
                case 2:
                    bool restart;
                    do {
                        restart = false;
                        int newPrice;
                        system("cls");
                        cout << "Set New Price: ";
                        cin >> newPrice;

                        if (checkValidity(&restart)) continue;

                        cout << "Price of Item <" << item->getName() << "> is updated from <" << item->getPrice() << "> to <" 
                            << newPrice << ">\n";
                        item->setPrice(newPrice);
                        system("pause");
                    } while (restart);
                    break;
                default:
                    restart = true;
                    system("cls");
                    cout << "Invalid Input! Please Choose From The Options!\n";
                    system("pause");
                    break;
                }
            } while(restart);
        }

        void removeItem() {
            Item* item = searchItem();
            if (item == nullptr) return;
            int index = -1;
            for (int i = 0; i < items.size(); i++) {
                if (items.at(i).getID() == item->getID()) {
                    index = i;
                }
            }
            cout << "Item <" << item->getName() << "> has been removed from the inventory\n";
            if (index != -1) {
                items.erase(items.begin()+index);
            }
            system("pause");
        }

        void displayItems() {
            system("cls");
            cout << "All Items:\n";
            cout << "__ID___________________NAME_________________QUANTITY_____________PRICE_______________CATEGORY____________\n";
            for (int i = 0; i < items.size(); i++) {
                items.at(i).display(i+1);
            }
            if (items.size() <= 0) {
                cout << "| " << setw(103) << left << "EMPTY! NO ITEMS!" << "|\n";
            }
            cout << "|____________________|____________________|____________________|____________________|____________________|\n";
            system("pause");
        }

        void displayItemsByCategory() {
            bool restart;
            do {
                string category;
                restart = false;
                system("cls");
                cout << "- CLOTHING\n"
                    << "- ELECTRONICS\n"
                    << "- ENTERTAINMENT\n"
                    << "Input A Category For Item: ";
                getline(cin, category);

                if (checkValidity(&restart)) continue;
                category = makeWordLower(category);
                if (category != clothing.getCategoryName() && category != electronics.getCategoryName() && category != entertainment.getCategoryName()) {
                        restart = true;
                        system("cls");
                        cout << "Category <" << category << "> does not exist!\n";
                        system("pause");
                        continue;
                }

                if (category == clothing.getCategoryName()) {
                    clothing.displayCategoryItems(items);
                }
                else if (category == electronics.getCategoryName()) {
                    electronics.displayCategoryItems(items);
                }
                else if (category == entertainment.getCategoryName()) {
                    entertainment.displayCategoryItems(items);
                }
                else {
                    restart = true;
                    system("cls");
                    cout << "Invalid Input! Please Choose From The Options!\n";
                    system("pause");
                }
            } while (restart);
        }

        void sortAscending(bool checkPrice) {
            for (int i = 0; i < items.size() - 1; i++) {
                for (int j = 0; j < items.size() - i - 1; j++) {
                    if (checkPrice && items[j].getPrice() > items[j + 1].getPrice()) {
                        swap(items[j], items[j + 1]);
                    } else if (!checkPrice && items[j].getQuantity() > items[j + 1].getQuantity()) {
                        swap(items[j], items[j + 1]);
                    }
                }
            }
        }

        void sortDescending(bool checkPrice) {
            for (int i = 0; i < items.size() - 1; i++) {
                for (int j = 0; j < items.size() - i - 1; j++) {
                    if (checkPrice && items[j].getPrice() < items[j + 1].getPrice()) {
                        swap(items[j], items[j + 1]);
                    } else if (!checkPrice && items[j].getQuantity() < items[j + 1].getQuantity()) {
                        swap(items[j], items[j + 1]);
                    }
                }
            }
        }

        void displaySortedItems() {
            system("cls");
            if (items.size() <= 0) {
                cout << "There Are No Items In Inventory To Sort!\n";
                system("pause");
                return;
            }
            bool restart;
            int sortChoice;
            int typeChoice;
            do {
                restart = false;
                system("cls");
                cout << "1 - Quantity\n"
                    << "2 - Price\n"
                    << "Choose What To Sort By [1-2]: ";
                cin >> typeChoice;

                if (checkValidity(&restart)) continue;
                cin.ignore();

                if (typeChoice != 1 && typeChoice != 2) {
                    system("cls");
                    cout << "Invalid Input! Please Choose From The Options!\n";
                    system("pause");
                    restart = true;
                }

            } while (restart);

            system("cls");
            do {
                restart = false;
                int sortChoice;
                system("cls");
                cout << "1 - Ascending\n"
                    << "2 - Descending\n"
                    << "Choose How Items Should Be Sorted [1-2]: ";
                cin >> sortChoice;

                if (checkValidity(&restart)) continue;
                cin.ignore();

                switch (sortChoice) {
                    case 1:
                        sortAscending(typeChoice-1);
                        break;
                    case 2:
                        sortDescending(typeChoice-1);
                        break;
                    default:
                        system("cls");
                        cout << "Invalid Input! Please Choose From The Options!\n";
                        system("pause");
                        restart = true;
                        break;
                }
                
            } while (restart);
            displayItems();
        }

        void displayLowStockItems() {
            system("cls");
            cout << "Entertainment Items:\n";
            cout << "__ID___________________NAME_________________QUANTITY_____________PRICE_______________CATEGORY____________\n";
            for (int i = 0; i < items.size(); i++) {
                if (items.at(i).getQuantity() > 5) continue;
                items.at(i).display(i+1);
            }
            if (items.size() <= 0) {
                cout << "| " << setw(103) << left << "EMPTY! NO ITEMS!" << "|\n";
            }
            cout << "|____________________|____________________|____________________|____________________|____________________|\n";
            system("pause");
        }
};

int main() {
    Inventory inventory;
    bool restart;
    do {
        restart = true;
        int choice;
        system("cls");
        cout << "Menu\n"
        << "1 - Add Item\n"
        << "2 - Update Item\n"
        << "3 - Remove Item\n"
        << "4 - Display Items by Category\n"
        << "5 - Display All Items\n"
        << "6 - Search Item\n"
        << "7 - Sort Items\n"
        << "8 - Display Low Stock Items\n"
        << "9 - Exit\n";
        cin >> choice;

        if (checkValidity(&restart)) continue;
        cin.ignore();

        switch(choice) {
            case 1:
                inventory.addItem();
                break;
            case 2:
                inventory.updateItem();
                break;
            case 3:
                inventory.removeItem();
                break;
            case 4:
                inventory.displayItemsByCategory();
                break;
            case 5:
                inventory.displayItems();
                break;
            case 6:{
                system("cls");
                Item* item = inventory.searchItem();
                if (item == nullptr) break;
                cout << "__ID___________________NAME_________________QUANTITY_____________PRICE_______________CATEGORY____________\n";
                item->display(1);
                cout << "|____________________|____________________|____________________|____________________|____________________|\n";
                system("pause");
                break;
            }
            case 7:
                inventory.displaySortedItems();
                break;
            case 8:
                inventory.displayLowStockItems();
                break;
            case 9:
                system("cls");
                cout << "Program Is Now Exiting\n";
                system("pause");
                restart = false;
                break;
            default:
                system("cls");
                cout << "Invalid Input! Please Choose From The Options!\n";
                system("pause");
                break;
        }
    } while (restart);
    return 0;
}
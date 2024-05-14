/***-------------------LOST-AND-FOUND-SYSTEM------------------------------***
 map<string, stirng> GroupC;
 GroupC["U20230078"] = "Akash Gupta";
 GroupC["U20230140"] = "Kabir Gupta";
 GroupC["U20230043"] = "Pehar jhamb";
 GroupC["U20230112"] = "Raj karan";
 GroupC["U20230016"] = "Saumya Chauhan";
 GroupC["U20230017"] = "Udaiveer";
 */

#include <iostream>
#include <string>
#include <map>
#include <list>
#include <chrono>
#include <algorithm>
#include <unordered_map> //for claimed_data data member
#include <cctype> //specially for using tolower function
#include <sstream> //for isstringstream

using namespace std;

// Object class
class Item {
private:
    int ID;
    string type;
    string color;
    string brandName;
    string identificationMark;
    string location;
    string time;
    string otherDescription;
    chrono::system_clock::time_point claimed_time;
    bool claimed_status;

public:
    static int ID_counter;

    //int dummy is here to handle the case of lost and found object's creation
    Item(int dummy = 0);
    Item(const string& type, const string& color, const string& brandName = "", const string& identificationMark = "", const string& location = "", const string& otherDescription = "", const string& claimed_time = "", const string& claimed_status = "");

    // Copy constructor
    Item(const Item& other);
    
    // Copy assignment operator
    Item& operator=(const Item& other);

    // Getters
    int getID() const;
    string getType() const;
    string getColor() const;
    string getBrandName() const;
    string getIdentificationMark() const;
    string getLocation() const;
    string getTime() const;
    string getOtherDescription() const;
    chrono::system_clock::time_point getClaimedTime() const;
    bool getClaimedStatus() const;

    // Setters
    void set_Id(int);
    void set_type(string val);
    void set_color(string val);
    void set_brandname(string val);
    void set_identificationMark(string val);
    void set_location(string val);
    void set_time();
    void set_otherDescription(string val);
    void set_claimedTime();
    void set_ClaimedStatus();
    
};

// Lost and Found class
class LostAndFoundSystem {
private:
    // Hash table to store every data we have
    static map<int, list<Item>> hashTable;
    static unordered_map<string, Item*> claimed_Data;

    // Color values has every possible values for colors we can have
    map<string, int> colorValues = {
        {"red", 1}, {"green", 2}, {"blue", 3}, {"yellow", 4}, {"orange", 5},
        {"black", 6}, {"white", 7}, {"brown", 8}, {"purple", 9}, {"pink", 10},
        {"cyan", 11}, {"magenta", 12}, {"lime", 13}, {"teal", 14}, {"turquoise", 15},
        {"silver", 16}, {"gold", 17}, {"gray", 18}, {"beige", 19}, {"maroon", 20}
    };

    // Type values has every possible type values that we have or we can have
    map<string, int> typeValues = {
        {"watch", 1}, {"earphones", 2}, {"pen", 3}, {"clothes", 4}, {"laundry", 5},
        {"bag", 6}, {"keys", 7}, {"wallet", 8}, {"jewelry", 9}, {"sunglasses", 10},
        {"umbrella", 11}, {"phone", 12}, {"laptop", 13}, {"headphones", 14}, {"book", 15},
        {"hat", 16}, {"shoes", 17}, {"glasses", 18}, {"water bottle", 19}, {"others", 20}
    };

    map<string, int> other_count; // For miscellaneous items count

    int generateKey(const Item& item);
    void displayItem(const Item& item) const;

public: 
    void print_maps(map<string, int>& data);
    void createObject(Item& i, int ch = 0);
    void addItem(const Item& item);
    void searchItems(Item& searchItem, const string& UID = "");
    void delete_data();
    void displayClaimedData();
};

// Function to check whether a particular value is present in the map or not
bool check_input(map<string, int> data, string value) {
    bool isValuePresent = false;

    // Iterate over the map and check if the value is present
    for (const auto& pair : data) {
        if (pair.second == stoi(value)) {
            isValuePresent = true;
            break;
        }
    }
    return isValuePresent;
} 

//Function to get current time...........
chrono::system_clock::time_point getCurrentTime() {
    return chrono::system_clock::now();
}

//Function to convert the string into lower cases
string toLowerCase(const string& str) {
    string result;
    result.reserve(str.size()); // Reserve space for efficiency

    for (char c : str) {
        if (isalpha(c)) {
            result.push_back(tolower(c));
        } else {
            result.push_back(c); // Keep digits unchanged
        }
    }

    return result;
}

//to specifically print keys of the map for printing colors
void printMapKeys(const map<string, int>& myMap) {
    for (const auto& pair : myMap) {
        cout << pair.first << endl;
    }
}


//-----------Function-definition-for-Item-class ----------------------

int Item::ID_counter = 100;

// Default constructor to manage user inputs, with its int dummy
Item::Item(int dummy) {
    LostAndFoundSystem admin;
    admin.createObject(*this, dummy);
}

// Parameterized constructor, mainly for inserting test cases
Item::Item(const string& type, const string& color, const string& brandName, const string& identificationMark, const string& location, const string& otherDescription, const string& claimed_time, const string& claimed_status)
    : type(type), color(color), brandName(brandName), identificationMark(identificationMark), location(location), otherDescription(otherDescription) {

    if (this->type.empty() || this->color.empty()) {
        cout << "Error: Type and color must be provided." << endl;
        exit(1);
    }

    ID = ID_counter++;
    time_t currentTime_t = chrono::system_clock::to_time_t(getCurrentTime()); 
    time = ctime(&currentTime_t);  
}

// Copy constructor
Item::Item(const Item& other)
    : ID(other.ID), type(other.type), color(other.color), brandName(other.brandName),
      identificationMark(other.identificationMark), location(other.location), time(other.time),
      otherDescription(other.otherDescription), claimed_time(other.claimed_time),
      claimed_status(other.claimed_status) {}

// Copy assignment operator
Item& Item::operator=(const Item& other) {
    if (this != &other) {
        ID = other.ID;
        type = other.type;
        color = other.color;
        brandName = other.brandName;
        identificationMark = other.identificationMark;
        location = other.location;
        time = other.time;
        otherDescription = other.otherDescription;
        claimed_time = other.claimed_time;
        claimed_status = other.claimed_status;
    }
    return *this;
}

// Getters of the function
int Item::getID() const { return ID; }
string Item::getType() const { return type; }
string Item::getColor() const { return color; }
string Item::getBrandName() const { return brandName; }
string Item::getIdentificationMark() const { return identificationMark; }
string Item::getLocation() const { return location; }
string Item::getTime() const { return time; }
string Item::getOtherDescription() const { return otherDescription; }
bool Item::getClaimedStatus() const { return claimed_status; }
chrono::system_clock::time_point Item::getClaimedTime() const { return claimed_time; }

// Setters to set all the values of items
void Item::set_type(string val) { type = val; }
void Item::set_color(string val) { color = val; }
void Item::set_brandname(string val) { brandName = val; }
void Item::set_identificationMark(string val) { identificationMark = val; }
void Item::set_location(string val) { location = val; }

void Item::set_time() { 
    time_t currentTime_t = chrono::system_clock::to_time_t(getCurrentTime()); 
    time = ctime(&currentTime_t);  
} 

void Item::set_otherDescription(string val) { otherDescription = val; }
void Item::set_claimedTime() { claimed_time = getCurrentTime(); }
void Item::set_ClaimedStatus() { claimed_status = true; }
void Item::set_Id(int val) { ID = val; }

/*-------------------End of Item Class--------------------*/

// Function definition for lost and found class

// Definition of static member variables
map<int, list<Item>> LostAndFoundSystem::hashTable;
unordered_map<string, Item*> LostAndFoundSystem::claimed_Data;

int LostAndFoundSystem::generateKey(const Item& item) {
    int typeCode;
    if (typeValues.find(item.getType()) != typeValues.end()) {
        typeCode = typeValues[item.getType()];
    } else {
        typeCode = typeValues["other"];
        other_count[item.getType()]++; // Increment count of miscellaneous items
        if (other_count[item.getType()] >= 3) { // Threshold reached, add to typeValues
            typeValues[item.getType()] = typeValues.size() + 1;
        }
    }
    int colorCode = colorValues[item.getColor()];
    return typeCode * 100 + colorCode;
}

// Display function to print the data when user found the value
void LostAndFoundSystem::displayItem(const Item& item) const {
    cout << "ID: " << item.getID() << "\n";
    cout << "Type: " << item.getType() << "\n";
    cout << "Color: " << item.getColor() << "\n";
    cout << "Brand Name: " << item.getBrandName() << "\n";
    cout << "Identification Mark: " << item.getIdentificationMark() << "\n";
    cout << "Location: " << item.getLocation() << "\n";
    cout << "Time: " << item.getTime();
    cout << "Other Description: " << item.getOtherDescription() << "\n\n";
}

// This function is for the user representation when we will be giving him instructions
void LostAndFoundSystem::print_maps(map<string, int>& data) {
    map<string, int>::iterator it;
    for (it = data.begin(); it != data.end(); it++) {
        cout << it->second << " : " << it->first << endl;
    }
}

// Adding items to the hash_table, which is also our database as well
void LostAndFoundSystem::addItem(const Item& item) {
    int key = generateKey(item);
    hashTable[key].push_front(item);
}

// Function to create object and adding it to the database
void LostAndFoundSystem::createObject(Item& i, int dummy) {
    i.set_Id(i.ID_counter++);
    string temp;

    cout << "Enter type of object: ";
    getline(cin, temp);
    while(temp.empty()){
        cout << "Please enter type: ";
        getline(cin, temp);
    }
    i.set_type(toLowerCase(temp));

    if(dummy == 0){
        printMapKeys(colorValues);
    }
    cout << "Enter color of object: ";
    getline(cin, temp);
    while(temp.empty()){    
        cout << "Please enter a color: ";
        getline(cin, temp);
    }
    i.set_color(toLowerCase(temp));

    cout << "Enter Brand name: ";
    getline(cin, temp);
    i.set_brandname(toLowerCase(temp));

    cout << "Enter identification mark: ";
    getline(cin, temp);
    i.set_identificationMark(toLowerCase(temp));

    cout << "Enter location: ";
    getline(cin, temp);
    i.set_location(toLowerCase(temp));

    i.set_time();

    cout << "Enter other description: ";
    getline(cin, temp);
    i.set_otherDescription(toLowerCase(temp));


    //it represents the  only that data will be added to the database that is inserted by the founder.
    if (dummy == 0) {
        addItem(i);
    }
}

// Function for searching using Two Hash maps, One to show value and the other one to store after it is claimed
void LostAndFoundSystem::searchItems(Item& searchItem, const string& UID) {
    
    int key = generateKey(searchItem);
    auto entry = hashTable.find(key);
    if (entry != hashTable.end()) {
        cout << "Items found with similar characteristics:\n";
        bool found = false;
        list<Item>& itemList = entry->second;
        auto it = itemList.begin();
        while (it != itemList.end()) {
            if (it->getBrandName() == searchItem.getBrandName() && it->getLocation() == searchItem.getLocation()) {
                displayItem(*it);
                found = true;

                claimed_Data[UID] = &(*it);
                claimed_Data[UID]->set_claimedTime();
                claimed_Data[UID]->set_ClaimedStatus();

                
                it = itemList.erase(it);

            } else {
                ++it;
            }
        }

        if (!found) {
            bool hasItems = false;
            cout << "We couldn't find any " << searchItem.getColor() << " " << searchItem.getType();
            if (!searchItem.getBrandName().empty()) {
                cout << " from " << searchItem.getBrandName();
            }

            if (!searchItem.getIdentificationMark().empty()) {
                cout << " with identification mark " << searchItem.getIdentificationMark();
            }

            cout << ", but here are other " << searchItem.getColor() << " " << searchItem.getType() << " we have:\n";
            for (auto& item : itemList) {
                if (item.getBrandName() != searchItem.getBrandName() || item.getIdentificationMark() != searchItem.getIdentificationMark()) {
                    hasItems = true;
                    displayItem(item);
                }
            }
            // Letting the user choose their object if it exists
            string choice;
            cout << "Does your object exist from above(y/n): ";
            getline(cin, choice);
            if (choice == "y" || choice == "Y") {
                cout << "Enter the Object's id number: ";
                getline(cin, choice);
                auto outer_it = hashTable.find(key); // Changed the name to outer_it
                if (outer_it != hashTable.end()) {
                    list<Item>& itemList = outer_it->second;
                    auto it = itemList.begin();
                    while (it != itemList.end()) {
                        if (to_string(it->getID()) == choice) {
                            cout << "Item Claimed" << endl;

                            claimed_Data[UID] = &(*it);
                            claimed_Data[UID]->set_claimedTime();
                            claimed_Data[UID]->set_ClaimedStatus();

                            it = itemList.erase(it); // Increment iterator after erase
                            break; // Exit the loop after claiming the item
                        } else {
                            ++it;
                        }
                    }
                    cout << "--------------Thank you For Using Our Service---------------\n";
                }

            } else {
                cout << "Sorry, but your object is not here\n";
                cout << "--------------Thank you For Using Our Service---------------\n";

            }

            if (!hasItems) {
                cout << "Take a look at the claimed products similar to yours: ";

                displayClaimedData();

            }
        }
    } else {

        // No items found with similar characteristics, check for items with the "other" type and same color
        int otherKey = typeValues["other"] * 100 + colorValues[searchItem.getColor()];
        auto otherEntry = hashTable.find(otherKey);
        if (otherEntry != hashTable.end()) {
            cout << "No items found with similar characteristics.\n";
            cout << "Here are other " << searchItem.getColor() << " items with type 'other':\n";
            bool hasOtherItems = false;
            for (auto it = otherEntry->second.begin(); it != otherEntry->second.end(); it++) {
                if (it->getColor() == searchItem.getColor()) {
                    hasOtherItems = true;
                    displayItem(*it);
                }
            }

            // Letting the user choose items with "other" type but same color
            if (hasOtherItems) {
                string choice;
                cout << "Do you want to claim any of these items? (y/n): ";
                getline(cin, choice);
                if (choice == "y" || choice == "Y") {
                    cout << "Enter the ID of the item you want to claim: ";
                    getline(cin, choice);
                    for (auto it = otherEntry->second.begin(); it != otherEntry->second.end(); it++) {
                        if (to_string(it->getID()) == choice) {
                            // Claim the chosen item
                            cout << "Item Claimed" << endl;
                            claimed_Data[UID] = &(*it);
                            claimed_Data[UID]->set_claimedTime();
                            claimed_Data[UID]->set_ClaimedStatus();
                            otherEntry->second.erase(it);
                            return;
                        }
                    }
                    cout << "Invalid item ID.\n";
                }
            } else {
                cout << "No items with 'other' type and the same color were found.\n";
            }
        } else {
            cout << "No items found with similar characteristics.\n";
            cout << "No items with 'other' type and the same color were found.\n";
        }
    }

}

void LostAndFoundSystem::delete_data() {
    auto currentTime = chrono::system_clock::now();

    // Iterate over the claimed_Data map
    for (auto it = claimed_Data.begin(); it != claimed_Data.end();) {

        // Calculate the difference in time
        auto difference = currentTime - it->second->getClaimedTime();
        auto differenceHours = chrono::duration_cast<chrono::hours>(difference).count();

        if (differenceHours >= 24 * 30) { 
            // Erase the item from the map
            it = claimed_Data.erase(it);
        } else {
            // Move to the next item
            ++it;
        }
    }
}

void LostAndFoundSystem::displayClaimedData() {
    for (const auto& pair : claimed_Data) {
        cout << "ID: " << pair.first << endl;
        const Item& item = *pair.second;
        displayItem(item);
    }
    string choice;
    cout << "Is your item present here(y/n): ";
    cin >> choice;
    if(choice == "y" || choice == "Y"){
        cout << "You can reach the person through his id and contact to the main gate for more information\n";
        cout << "------------Thankyou for using our service----------";
    } else{
        cout << "----Sorry, but your item hasn't appear in lost and found\n";
    }
}


// User class to implement the founder and loser
class User {
protected:
    string ID;
    string Name;
    int RoomNo;

public:
    User() {}
    User(const string& username, const string& p_id, const string& name, int roomNo)
        : ID(p_id), Name(name), RoomNo(roomNo) {}

    string geId() const { return ID; }
    string getName() const { return Name; }
    int getRoomNo() const { return RoomNo; }
};

class Loser : public User {
public:
    static map<string, pair<string, int>> loser_data;
    Loser(LostAndFoundSystem& system) {
        cout << "Enter the following details based on the time you lost your object: \n";
        Item item(1);
        cout << "Enter Your name: ";
        getline(cin, Name);

        cout << "Enter Your id: ";
        getline(cin, ID);

        cout << "Enter your room number: ";
        cout << "Enter Your Name: ";
        
        string roomNoStr;
        while (true) {
            cout << "Enter room number: ";
            getline(cin, roomNoStr);

            // Use stringstream to convert string to int
            istringstream iss(roomNoStr);
            if (iss >> RoomNo) {
                // Conversion successful
                break;
            } else {
                cout << "Invalid input. Please enter an integer." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        loser_data[ID] = make_pair(Name, RoomNo);
        system.searchItems(item, ID);
    }
};

class Finder : public User {
public:
    static map<string, string> founderData;
    Finder(LostAndFoundSystem& system) {
        Item item;
        string temp;
        cout << "Enter your name: ";
        getline(cin, temp);

        cout << "Enter your uid: ";
        getline(cin, temp);

        founderData["UID"] = temp;
    }       
    Finder(const string& username, const string& password, const string& name, int roomNo)
        : User(username, password, name, roomNo) {}
};

int main() {
    LostAndFoundSystem system;

    // Adding test cases to the database
    Item item1("Watch", "Red", "Rolex", "1234", "Office", "None");
    Item item2("Earphones", "Black", "Sony", "Initials", "Cafe", "Wireless earbuds");
    Item item3("Watch", "Red", "Rolex", "1113", "you know", "None");
    Item item4("Pen", "Blue", "Parker", "456", "School", "Fountain pen");
    Item item5("Wallet", "Black", "Louis Vuitton", "789", "Street", "Leather wallet");
    Item item6("Bag", "Brown", "Nike", "1011", "Gym", "Sports bag");
    Item item7("Phone", "Silver", "Samsung", "1213", "Park", "Smartphone");
    Item item8("Umbrella", "Yellow", "Gucci", "1415", "Beach", "Designer umbrella");
    Item item9("Laptop", "Gray", "Apple", "1617", "Home", "MacBook Pro");
    Item item10("Keys", "Silver", "BMW", "1819", "Parking lot", "Car keys");

    // Adding items to the system
    system.addItem(item1);
    system.addItem(item2);
    system.addItem(item3);
    system.addItem(item4);
    system.addItem(item5);
    system.addItem(item6);
    system.addItem(item7);
    system.addItem(item8);
    system.addItem(item9);
    system.addItem(item10);

    // Adding 4 items with the same unlisted type
    cout << "\nAdding 4 items with the same unlisted type:\n";
    Item unlistedItem1("Sunglasses", "Black", "Ray-Ban", "2222", "Beach", "Aviators");
    Item unlistedItem2("Sunglasses", "Black", "Gucci", "3333", "Pool", "Round frame");
    Item unlistedItem3("Sunglasses", "Black", "Prada", "4444", "Resort", "Cat-eye");
    Item unlistedItem4("Sunglasses", "Black", "Oakley", "5555", "Park", "Sports");

    system.addItem(unlistedItem1);
    system.addItem(unlistedItem2);
    system.addItem(unlistedItem3);
    system.addItem(unlistedItem4);


    cout << "--------------------------------WELCOME TO PLAKSHA's LOST AND FOUND SYSTEM----------------------------------\n";
    while (1) {
        string choice;
        cout << "Enter Your Option: \n1. Lost \t 2. Found\t 3. Exit \nEnter: ";
        getline(cin, choice);
        if (choice == "1") {
            Loser Lost(system);
        } else if (choice == "2") {
            Finder Found(system);
        } else if (choice == "3") {
            cout << "Thank you for using the service....";
            break;
        } else {
            cout << "Please choose an appropriate option..." << endl;
            continue;
        }
    }

    return 0;
}
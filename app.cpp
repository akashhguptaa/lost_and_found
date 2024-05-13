/****-------------------LOST AND FOUND BY PLAKSHA--------------------------****

Map<string, string> Group_C;
Group_C["U20230078"] = "Akash Gupta";
Group_C["U202300ab"] = "Kabir Gupta";
Group_C["U202300ab"] = "Pehar jhamb";
Group_C["U202300ab"] = "Raj Karan";
Group_C["U202300ab"] = "Saumya";
Group_C["U202300ab"] = "Udaiveer"

*/

#include <iostream>
#include <string>
#include <map>
#include <list>
#include <chrono>
#include <algorithm>
#include <unordered_map>

using namespace std;


//Obbject class
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
    chrono :: system_clock :: time_point claimed_time;
    bool claimed_status ;

public:
    static int ID_counter;
    Item(int dummy = 0);
    Item(const string& type, const string& color, const string& brandName = "", const string& identificationMark = "", const string& location = "", const string& otherDescription = "", const string& claimed_time = "",const string& claimed_status = "");
    
    //Getters
    int getID() const;
    string getType() const;
    string getColor() const;
    string getBrandName() const;
    string getIdentificationMark() const;
    string getLocation() const;
    string getTime() const;
    string getOtherDescription() const;
    chrono :: system_clock:: time_point getClaimedTime() const;
    bool getClaimedStatus() const;

    void set_type(string val);
    void set_color(string val);
    void set_brandname(string val);
    void set_identificationMark(string val);
    void set_location(string val);
    void set_time();
    void set_otherDescription(string val);
    void set_claimedTime();
    void set_ClaimedStatus();
    void set_Id(int);

};

//Lost and FOunnd claassss
class LostAndFoundSystem {
private:

    //Hash table to store every data we have
    static map<int, list<Item>> hashTable;
    static unordered_map<string, Item> claimed_Data;
    //color values has every possible values for colors we can have
    map<string, int> colorValues = {
        {"Red", 1}, {"Green", 2}, {"Blue", 3}, {"Yellow", 4}, {"Orange", 5},
        {"Black", 6}, {"White", 7}, {"Brown", 8}, {"Purple", 9}, {"Pink", 10},
        {"Cyan", 11}, {"Magenta", 12}, {"Lime", 13}, {"Teal", 14}, {"Turquoise", 15},
        {"Silver", 16}, {"Gold", 17}, {"Gray", 18}, {"Beige", 19}, {"Maroon", 20}
    };

    //typevalues has every possible type values that we have or we can have
    map<string, int> typeValues = {
        {"Watch", 1}, {"Earphones", 2}, {"Pen", 3}, {"Clothes", 4}, {"Laundry", 5},
        {"Bag", 6}, {"Keys", 7}, {"Wallet", 8}, {"Jewelry", 9}, {"Sunglasses", 10},
        {"Umbrella", 11}, {"Phone", 12}, {"Laptop", 13}, {"Headphones", 14}, {"Book", 15},
        {"Hat", 16}, {"Shoes", 17}, {"Glasses", 18}, {"Water Bottle", 19}, {"others", 20}
    };
    int generateKey(const Item& item);
    void displayItem(const Item& item)const;

    public: 
    
    void print_maps(map<string, int>& data);
    void createObject(Item& i, int ch = 0);
    void addItem(const Item& item);
    void searchItems(Item& searchItem,const string& str = "");
    void delete_data();
    void displayClaimedData();
    
};


//Function to check whether a particular  value is present in the map or not
bool check_input(map<string, int> data, string value){
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
chrono :: system_clock:: time_point getCurrentTime() {
    return chrono::system_clock::now();
}


/*-----------Function definitionn for Item class ----------------------*/
//Default constructor to manage user inputs
int Item::ID_counter = 100;

Item :: Item(int dummy){
    LostAndFoundSystem admin;
    admin.createObject(*this, dummy);
        
}
    //parameterized constructor
Item :: Item(const string& type, const string& color, const string& brandName , const string& identificationMark  , const string& location , const string& otherDescription, const string& claimed_time, const string& claimed_status )
    : type(type), color(color), brandName(brandName), identificationMark(identificationMark), location(location), otherDescription(otherDescription) {

    if (this->type.empty() || this->color.empty()) {
        cout << "Error: Type and color must be provided." << endl;
        exit(1);
    }

    ID = ID_counter++;
    time_t currentTime_t = chrono::system_clock::to_time_t(getCurrentTime()); 
    time = ctime(&currentTime_t);  
}

    //getters of the function
int Item :: getID() const { return ID; }
string Item :: getType() const { return type; }
string Item :: getColor() const { return color; }
string Item :: getBrandName() const { return brandName; }
string Item :: getIdentificationMark() const { return identificationMark; }
string Item :: getLocation() const { return location; }
string Item ::getTime() const { return time; }
string Item :: getOtherDescription() const { return otherDescription; }
bool Item :: getClaimedStatus() const{ return claimed_status; }
chrono :: system_clock:: time_point Item :: getClaimedTime() const {return claimed_time; }

//setters to set all the values of items
//we are considering that there will be some value assign to the type
//Aprart from setters every other data member can be assigned to null

//setter for type
void Item :: set_type(string val){type = val;}

//setter for setting color
void Item :: set_color(string val){
    color = val;
    if (color.empty()) {
        this->color = "null";
    }
}

//setter for setting brandname
void Item :: set_brandname(string val){
    brandName = val;
    if (brandName.empty()) {
        this->brandName = "null";
    }
}

//setter for setting identification mark
void Item :: set_identificationMark(string val){
    identificationMark = val;
    if (identificationMark.empty()) {
        this->identificationMark = "null";
    }
}
    
//setter for location
void Item :: set_location(string val){
    location = val;
    if (location.empty()) {
        this->location = "null";
    }
}

    //setter for setting time from get time
void Item :: set_time(){ 
    time_t currentTime_t = chrono::system_clock::to_time_t(getCurrentTime()); 
    time = ctime(&currentTime_t);  
} 

    //setters for setting other description
void Item :: set_otherDescription(string val){ 
    otherDescription=val;
    if (otherDescription.empty()) {
        this->otherDescription = "null";
    }

}

//if item will get claimed it will assign a date of next 30 days an will get deleted 
void Item :: set_claimedTime(){
    claimed_time = getCurrentTime();
    
}

void Item :: set_ClaimedStatus(){
    claimed_status = true;

}
void Item :: set_Id(int val){
    ID = val;
}

/*-------------------End of Item Class--------------------*/
//FUnction definition for lost and found class

// Definition of static member variable
map<int, list<Item>> LostAndFoundSystem::hashTable;
unordered_map<string, Item> LostAndFoundSystem :: claimed_Data;

int LostAndFoundSystem :: generateKey(const Item& item) {
        int typeCode = typeValues.find(item.getType()) != typeValues.end() ? typeValues[item.getType()] : typeValues["other"];
        int colorCode = colorValues[item.getColor()];
        return typeCode * 100 + colorCode;
    }

    //Display function to print the data when user found the value
void LostAndFoundSystem :: displayItem(const Item& item) const {
        cout << "ID: " << item.getID() << "\n";
        cout << "Type: " << item.getType() << "\n";
        cout << "Color: " << item.getColor() << "\n";
        cout << "Brand Name: " << item.getBrandName() << "\n";
        cout << "Identification Mark: " << item.getIdentificationMark() << "\n";
        cout << "Location: " << item.getLocation() << "\n";
        cout << "Time: " << item.getTime();
        cout << "Other Description: " << item.getOtherDescription() << "\n\n";
    }


 //This function is for the user representation when we will be giving him instructions
void LostAndFoundSystem :: print_maps(map<string, int>& data){
        map<string, int>:: iterator it;
        for( it = data.begin(); it != data.end(); it++){
            cout << it->second << " : " << it->first << endl;

        }

    }
//Adding items to the hash_table
void LostAndFoundSystem::addItem(const Item& item) {
        int key = generateKey(item);
        hashTable[key].push_back(item);
}
    //function to create object and adding it to the database
void LostAndFoundSystem :: createObject(Item& i, int dummy){
    i.set_Id(i.ID_counter ++);
    cout << "atleast working: "<< i.getID() <<endl;
    //A temporary value to handle any inputs about object
    string temp;

    //Entering for the type of object
    print_maps(typeValues);
    cout << "Enter type number: ";
    cin >> temp;
    
    bool flag = check_input(typeValues, temp);

    //To avoid wrong user inputs
    while(!flag){
        cout << "Enter the correct number: ";
        cin >> temp;
        flag = check_input(typeValues, temp);
    }

    auto lastIterator = typeValues.rbegin();
    if(temp == to_string(lastIterator->second)){
        cout << "Enter the new type: ";
        cin >> temp;
        auto it = --typeValues.end();
        typeValues.insert(make_pair(temp, it->second));
        ++typeValues["others"];
        i.set_type(temp);
    }

    else{
        for (const auto& pair : typeValues) {
            if (pair.second == stoi(temp)) {
                i.set_type(pair.first);
                break;
            }
        }
    }

    //Handling of Colorvalues
    print_maps(colorValues);
    cout << "Enter color of object: ";
    cin >> temp;
    bool flag1 = check_input(colorValues, temp);

    //To avoid wrong user inputs
    while(!flag1){
        cout << "Enter the correct number: ";
        cin >> temp;
        flag1 = check_input(colorValues, temp);
    }
    for (const auto& pair : colorValues) {
        if (pair.second == stoi(temp)) {
            i.set_color(pair.first);
            break;
        }
    }
        
    cout << "Enter Brand_name: ";
    cin >> temp;
    i.set_brandname(temp);

    cout << "Enter identification Mark: ";
    cin >> temp;
    i.set_identificationMark(temp);

    string loc;
    cout << "Enter Location: ";
    cin >> loc;
    i.set_location(loc);

    i.set_time();

    cout << "Enter other_description: ";
    cin >> temp;
    i.set_otherDescription(temp);

    if(dummy == 0){
        addItem(i);    
    }
}


//Function for searching using Two Hash maps, One to show value and the other one to store after it is claimed
void LostAndFoundSystem::searchItems(Item& searchItem, const string& UID) {
    // Function implementation
    int key = generateKey(searchItem);
    auto entry = hashTable.find(key);
    if (entry != hashTable.end()) {
        cout << "Items found with similar characteristics:\n";
        bool found = false;
        list<Item>& itemList = entry->second;
        auto it = itemList.begin();
        while (it != itemList.end()) {
            if (it->getBrandName() == searchItem.getBrandName() && it->getIdentificationMark() == searchItem.getIdentificationMark()) {
                displayItem(*it);
                found = true;
                it -> set_claimedTime();
                it -> set_ClaimedStatus();

                claimed_Data[UID] = *it;
                it = itemList.erase(it);
                
            
            }else{
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
            //Letting the user choose his object if exist
            string choice;
            cout << "Does your object exist from above(y/n): ";
            cin >> choice;
            if(choice == "y" || choice == "Y"){
                cout << "Enter the Object's id number: ";
                cin >> choice;
                Item* reference = nullptr; 

                //Iterating over the whole list of items.....
                auto it = hashTable.find(key);
                if (it != hashTable.end()) {
                    list<Item>& itemList = it->second;
                    for (auto it = itemList.begin(); it != itemList.end();) {
                        if (to_string(it->getID()) == choice) {
                            cout << "Item Claimed" << endl;
                            reference = &(*it);

                            reference->set_claimedTime();
                            reference->set_ClaimedStatus();

                            claimed_Data[UID] = *reference;
                            it = itemList.erase(it); // Increment iterator after erase
                        } else {
                            ++it;
                        }
                           
                    }
                    cout << "--------------Thankyou For Using Our Service---------------\n";
                    
                
                }
                    
            } else{
                cout << "Sorry But Your Object is not here\n";
                cout << "--------------Thankyou For Using Our Service---------------\n";
                
            }

            cout << "Take a look at the claimed products similar to yours: ";

            displayClaimedData();

            if (!hasItems) {
                cout << "No other items found with the same color and type.\n";
                
            }
        }
    } 
    else {
        cout << "No items found with similar characteristics.\n";
        
    }

}

void LostAndFoundSystem::delete_data() {
    auto currentTime = chrono::system_clock::now();

    // Iterate over the claimed_Data map
    for (auto it = claimed_Data.begin(); it != claimed_Data.end();) {
        // Calculate the difference in time
        auto difference = currentTime - it->second.getClaimedTime();
        auto differenceHours = chrono::duration_cast<chrono::hours>(difference).count();

        // Check if the claimed time is older than 30 days
        if (differenceHours >= 24 * 30) {
            // Erase the item from the map
            it = claimed_Data.erase(it);
        } else {
            // Move to the next item
            ++it;
        }
    }
}


void LostAndFoundSystem :: displayClaimedData(){
    for (const auto& pair : claimed_Data) {
        cout << "ID: " << pair.first << endl;
        const Item& item = pair.second;
        displayItem(item);
    }
    cout << "Reach the person if he has your stuff through his UID" << endl;
    cout << "Thankyou for using our service\n";
}

//user class to implement the founder and looser
//User class

class User {
protected:
    string ID;
    string Name;
    int RoomNo;

public:
    User(){}
    User(const string& username, const string& p_id, const string& name, int roomNo)
        : ID(p_id), Name(name), RoomNo(roomNo) {
        
    }

    string geId() const { return ID; }
    string getName() const { return Name; }
    int getRoomNo() const { return RoomNo; }
};

class Loser : public User {
public:
    map<string, pair<string, int>> loser_data;
    Loser(LostAndFoundSystem& system){

        cout << "Enter the following details based on the time you lost your object: \n";
        Item item(1);
        cout << "Enter Your name: ";
        cin >> Name;

        cout << "Enter Your id: ";
        cin >> ID;
                
        cout << "Enter your room number: ";
        cin >> RoomNo;

        loser_data[ID]= make_pair(Name, RoomNo);
        system.searchItems(item ,ID);
    }  
};


class Finder : public User {
public:
    map<string, string> founderData;
    Finder(LostAndFoundSystem& system){
        Item item;
        string temp;

        cout << "Enter  Your Name: ";
        cin >> temp;
        founderData["Name"] = temp;

        cout << "Enter Your Id: ";
        cin >> temp;
        founderData["UID"] = temp;


    }
    Finder(const string& username, const string& password, const string& name, int roomNo)
        : User(username, password, name, roomNo) {}

};


int main() {
    LostAndFoundSystem system;

    // Add some sample items
    Item item1("Watch", "Red", "Rolex", "1234", "Office", "None");
    Item item2("Earphones", "Black", "Sony", "Initials", "Cafe", "Wireless earbuds");
    Item item3("Watch", "Red", "Rolex", "1113", "you know", "None");
    Item searchItem("Earphones", "black", "", "", "None"); 
 
    // Adding items
    system.addItem(item1);
    system.addItem(item2);
    system.addItem(item3);
    // Item test;
    // system.displayHashMap();
   
 
    // system.searchItems(searchItem);

    cout <<"--------------------------------WELCOME TO PLAKSHA's LOST AND FOUND SYSTEM----------------------------------\n";
    while (1){
        string choice;
        cout << "Enter Your Option: \n1.Lost \t 2.Found\t 3.Exit \nEnter: ";
        cin >> choice;
        if(choice == "1"){
            Loser Lost(system);
        }

        else if( choice == "2"){
            system.addItem(item3);
            Finder Found(system);
        }
        
        else if(choice == "3"){
            cout << "Thankyou for using the service....";
            break;
        }
        else{
            cout << "Please Choose an appropriate option..."<<endl;
            continue;
        }

    }

    return 0;
}

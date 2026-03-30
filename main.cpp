        #include <fstream>
        #include <sstream>
        #include <cstdlib>
        #include <iostream>
        #include <limits>
        #include <vector>
        #include <fstream>
        using namespace std;
        struct Equipment{
        int id;
        string name;
        int quantity;
    };

    void viewEquipment(const vector<Equipment>& equipments);
    void searchEquipment(const vector<Equipment>& equipments);
    void issueEquipment(vector<Equipment>& equipments, string username);   
    void returnEquipment(vector<Equipment>& equipments);
    void addEquipment(vector<Equipment>& equipments);
    void updateQuantity(vector<Equipment>& equipments);
    void deleteEquipment(vector<Equipment>& equipments);
    void saveToFile(const vector<Equipment>& equipments);
    void loadFromFile(vector<Equipment>& equipments);

    struct User{
        string username;
        string password;
        string role; // student or faculty
    };


    //load users from file 
    void loadUsers(vector<User>& users){

        ifstream file("users.txt");

        if(!file) return;

        User u;

        while(getline(file,u.username,'|')){
            getline(file,u.password,'|');
            getline(file,u.role);

            users.push_back(u);
        }

        file.close();
    }

    //save users to file
    void saveUsers(const vector<User>& users){

        ofstream file("users.txt");

        for(const auto& u : users){
                file<<u.username<<"|"<<u.password<<"|"<<u.role<<endl;
        }

        file.close();
    }

    // what student has actully issued
    void viewMyIssued(const vector<Equipment>& equipments, string username){
    
    ifstream file("issued.txt");

    if(!file){
        cout<<"No issued records found\n";
        return;
    }

    string line;
    bool found = false;

    while(getline(file, line)){
        
        stringstream ss(line);
        string fileUser, idStr;

        getline(ss, fileUser, '|');
        getline(ss, idStr);

        int id = stoi(idStr);

        if(fileUser == username){
            
            for(const auto& e : equipments){
                if(e.id == id){
                    cout<<"ID: "<<e.id<<" | Name: "<<e.name<<endl;
                    found = true;
                }
            }
        }
    }

    if(!found){
        cout<<"No equipment issued by you\n";
    }

    file.close();
}
    //register new user
    void registerUser(vector<User>& users){

        User u;

        cout<<"Enter Username: ";
        cin>>u.username;
        for(const auto& existing : users){
        if(existing.username == u.username){
            cout<<"Username already exists!\n";
            return;
        }
    }

        cout<<"Enter Password: ";
        cin>>u.password;

        int roleChoice;

        cout<<"1. Student\n2. Faculty\nChoose Role: ";
        cin>>roleChoice;

        if(roleChoice==1){
        u.role="student";
        }
        else if(roleChoice==2){
        u.role="faculty";
        }
        else{
        cout<<"Invalid Role\n";
        return;
        }
        
        users.push_back(u);

        saveUsers(users);

        cout<<"User Registered Successfully\n";
    }

    //login system
    bool login(vector<User>& users,string& role,string& username){

        string password;

        cout<<"Enter Username: ";
        cin>>username;

        cout<<"Enter Password: ";
        cin>>password;

        for(auto& u: users){

            if(u.username==username && u.password==password){
                role=u.role;
                return true;
            }
        }

        return false;
    }
        //student menu function
            void studentMenu(vector<Equipment>& equipments, string username){
            int choice;
            while(true){
                cout<<"\n===== Student Menu =====\n";
            cout<<"1. View Equipment"<<endl;
            cout<<"2. Search Equipment"<<endl;
            cout<<"3. Issue Equipment"<<endl;
            cout<<"4. View my Equipment"<<endl;
            cout<<"5. Return Equipment"<<endl;
            cout<<"5. Logout"<<endl;
            cin>>choice;
            if(choice==1){
                viewEquipment(equipments);
            }
            else if(choice==2){
                searchEquipment(equipments);
            }
            else if(choice==3){
                issueEquipment(equipments, username);
                saveToFile(equipments);
            }
            else if(choice==4){
                   viewMyIssued(equipments, username);
            }
            else if(choice==5){
                returnEquipment(equipments); 
                saveToFile(equipments);  
            }
            else if(choice==6){
                cout<<"Logging Out"<<endl;
                break;

            }else{
                cout<<"Inavlid Choice"<<endl;
            }

            }

        }   
        //Faculty menu
    void facultyMenu(vector<Equipment>& equipments){
        int choice;
        while(true){
            cout<<"\n===== Faculty Menu =====\n";
            cout<<"1. Add Equipment"<<endl;
            cout<<"2. View Equipment"<<endl;
            cout<<"3. Search Equipment"<<endl;
            cout<<"4. Update Quantity"<<endl;
            cout<<"5. Delete Equipment"<<endl;
            cout<<"6. Logout"<<endl;
            cin>>choice;
            if(choice==1){
                addEquipment(equipments);
                saveToFile(equipments);
            }
            else if(choice==2){
                viewEquipment(equipments);
            }
            else if(choice==3){
                searchEquipment(equipments);
            }
            else if(choice==4){
                updateQuantity(equipments);
                saveToFile(equipments);
            }
            else if(choice==5){
                deleteEquipment(equipments);
                saveToFile(equipments);
            }
            else if(choice==6){
                cout<<"Logging Out...\n";
                break;
            }
            else{
                cout<<"Invalid Choice\n";
            }

        }
    }
        //Return Equipment
        void returnEquipment(vector<Equipment>& equipments){
        if(equipments.empty()){
                cout<<"No Equipment is Available"<<endl;
                return;
        }
                int id;
                cout<<"Enter Equipment ID To Return : ";
                cin>>id;
                for(auto &e : equipments){
                if(e.id==id){
                        e.quantity++;
                        cout<<"Quantity Return Successfully"<<endl;
                        cout<<"Update Quantity: "<<e.quantity<<endl;
                    return;
                    }
                }   
            
            cout<<"Equipment With This Id Is Not Found !";
        }
        //issue equipment
        
    void issueEquipment(vector<Equipment>&equipments, string username){
        

    if(equipments.empty()){
        cout<<"No Equipment is Available"<<endl;
        return;
    }

    int id;
    cout<<"Enter A Id To Issue : ";
    cin>>id;
    ifstream checkFile("issued.txt");
    string line;

    while(getline(checkFile, line)){
    
    stringstream ss(line);
    string fileUser, idStr;

    getline(ss, fileUser, '|');
    getline(ss, idStr);

    int fileId = stoi(idStr);

    if(fileUser == username && fileId == id){
        cout<<"You already issued this equipment!\n";
        checkFile.close();
        return;
    }   
    }

checkFile.close();

    for(auto &e : equipments){

        if(e.id==id){

            if(e.quantity>0){

                e.quantity--;

                cout<<"Quantity Issued Successfully"<<endl;
                cout<<"Remaining Quantity: "<<e.quantity<<endl;

                // 🔥 NEW FEATURE
                ofstream file("issued.txt", ios::app);
                file << username << "|" << id << endl;
                file.close();

            }else{
                cout<<"Quantity Is Out Of Stock"<<endl;
            }
            return;
        }
    }

    cout<<"Equipment With This Id Is Not Found";
}
        // to save file
        void saveToFile(const vector<Equipment>& equipments){
            ofstream file("equipment.txt");
            for(const auto& e:equipments){
                file<<e.id<<"|"<<e.name<<"|"<<e.quantity<<endl;

            }   
            file.close();
        }
        //for load and open file
        void loadFromFile(vector<Equipment>& equipments){
        ifstream file("equipment.txt");
        if(!file)return;//file not present
        Equipment e;
        char delimeter;
        while(file>>e.id>>delimeter){
            getline(file,e.name,'|');
            file>>e.quantity;
            equipments.push_back(e);

        }
        file.close();
        }
        //to update quantity and if not then return message 
        void updateQuantity(vector<Equipment>&equipments){
            if(equipments.empty()){
                cout<<"No Equipment Available to update"<<endl;
                return;
            }
            int id; 
            cout<<"Enter Equipment ID To Update :";
        cin>>id;
        for(auto& e:equipments){
            if(e.id==id){
                int newQty;
                cout<<"Enter New Quantity : ";
                cin>>newQty;
                if(newQty<0){
                    cout<<"Quantity Cannot Be Negative";
                    cout<<endl;
                    return;
                }
                e.quantity = newQty;
                cout<<"Quantity is updated successfully";
                cout<<endl;
                return;
                }
            }
            cout<<"Equipment with this ID is not found!"<<endl;
        }


        // adding equipment 
        void addEquipment(vector<Equipment>&equipments){
        Equipment e;
        cout<<"Enter Equipment ID : ";
        int newId;
        cin>>newId;
        for(const auto& eq: equipments){
            if(eq.id==newId){
                cout<<"Equipment With This is already Exist."<<endl;
                return;
            }
        }
        e.id=newId;
        cout<<"Enter Equipment Name : ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin,e.name);
        cout<<"Enter A Quantity";
        cin>>e.quantity;
        equipments.push_back(e);
        cout<<"Equipment Is Added Succesfully";
        }
        //function to view equipment 
        void viewEquipment(const vector<Equipment>& equipments){
            if(equipments.empty()){
                cout<<"No Equipment Is Available";
                cout<<endl;
                return;
            }
                cout<<"\n-- Equipment List --\n";            
                for(const auto&e : equipments){
                    cout<<"ID : "<<e.id;
                    cout<<" Name: "<<e.name;
                    cout<<" Quantity: "<<e.quantity;
                    cout<<endl;
                }
            }
        void searchEquipment(const vector<Equipment>& equipments){  
            if(equipments.empty()){
                cout<<"Equipment Is Not Available"<<endl;
                return;
            }
            int searchId;
            cout<<"Enter Equipment ID To search : ";
            cin>>searchId;
            for(const auto& e:equipments){
                if(e.id==searchId){
                    cout<<"Equipment Found "<<endl;
                    cout<<"ID: "<<e.id<<endl;
                    cout<<"Name: "<<e.name<<endl;
                    cout<<"Quanitiy : "<<e.quantity<<endl;
                    return;

                }
                
            }
            
                    cout<<"Equipment With ID "<<searchId<<" Is Not Found "<<endl;

        }

        //to delete equipment 
        void deleteEquipment(vector<Equipment>& equipments){
        if(equipments.empty()){
            cout<<"No Equipment Available to delete"<<endl;
            return;
        }
        int id;
        cout<<"Enter Equipment ID To Delete";
        cin>>id;
        for(int i=0;i<equipments.size();i++){
            if(equipments[i].id==id){
                equipments.erase(equipments.begin()+i);
                cout<<"Equipment Deleted Successfully"<<endl;
                return;
            }
        }
        cout<<"Equipment With This Is Id Is Not Found!"<<endl;

        }




        int main(){

        vector<Equipment> equipments;
        loadFromFile(equipments);
        vector<User> users;
        loadUsers(users);
        int choice;
        while(true){

            cout << "\n=====================================\n";
            cout << "Laboratory Equipment Management System\n";
            cout << "=====================================\n";

            cout<<"1. Register"<<endl;
            cout<<"2. Login"<<endl;
            cout<<"3. Exit"<<endl;

            cin>>choice;
    if(choice==1){
        registerUser(users);
    }
    else if(choice==2){
string role, username;

if(login(users,role,username)){

            if(role=="student"){
            studentMenu(equipments, username);            }
            else if(role=="faculty"){
                facultyMenu(equipments);
            }

        }else{
            cout<<"Invalid Username or Password"<<endl;
        }
    }
    else if(choice==3){
        cout<<"Exiting System"<<endl;
        break;
    }
    else{
        cout<<"Invalid Choice, Try Again"<<endl;
    }

    }
        saveToFile(equipments);

        }
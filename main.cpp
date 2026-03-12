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
cin.ignore();
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
    cout<<"--Equipment List--";
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

    int choice;
    while(true){
    cout << "=====================================";
    cout<<endl;
    cout<<"Laboratory Equipment Managment System";
    cout<<endl;
    cout << "=====================================";
    cout<<endl;
    cout<<"1.Add Equipment "<<endl;
    cout<<"2.View Equipment "<<endl;
    cout<<"3.Search Equipments"<<endl;
    cout<<"4.Update Quantity"<<endl;
    cout<<"5.Delete Equipment"<<endl;
    cout<<"6.Exit "<<endl;
    cin>>choice;
    if(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max());
        cout <<endl;
        cout<<"Inavlid Input! Enter A Number "<<endl;
        continue;

        

    }
    
    if(choice==1){
        addEquipment(equipments);
    }else if (choice==2){
        viewEquipment(equipments);
    }
    else if (choice==3){
        searchEquipment(equipments);
    }
    else if (choice ==4){

    updateQuantity(equipments);
    }
    else if(choice==5){
        deleteEquipment(equipments);
    }
    else if(choice ==6){
        cout<<"Exiting System"<<endl;
    }
    else{
        cout<<"Invalid Choice, Try Again";
    }   
        cout<<endl;
    }
        return 0;
        saveToFile(equipments);
        addEquipment(equipments);
}

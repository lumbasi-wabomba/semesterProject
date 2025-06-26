#include <iostream>
#include <map>
#include <random>
#include <ctime>
#include <fstream>



using namespace std;

 struct loginDetails{
        string userUsername;   
        string userPassword;
    };
    struct userInfo{
        string firstName;
        string secondName;
        int phoneNumber;
        string email;
        double accountBal;
    };
    struct carInfo{
        string carMake;
        string carModel;
        string numberPlate;
    };
const int carRentDays =30;
class Admin;
class User{
    Admin* myUser;
    int myId, tellNo;
    string fname, sname, email, usrname, passwd;
    double accBal;
    map<int, userInfo> myDetails;
    ifstream fileRead;
    ofstream fileWrite;
    public:
        void displayMyDetails(int id, userInfo){
            
            fileRead.open("userDB.txt");
            while(fileRead>> myId>>fname >> sname>> tellNo>> email>> accBal){
                if(id == myId){
                    myDetails[myId] = userInfo{fname, sname, tellNo, email, accBal};
                }
            }
            fileRead.close();
            for (auto& detail : myDetails){
                cout<<"userID "<<detail.first<< "\n" 
                <<"names "<< detail.second.firstName<< " "<< detail.second.secondName<<"\n"
                <<"telephone number " << detail.second.phoneNumber<<"\n"
                <<"email "<< detail.second.email<<"\n"
                <<"account balance "<< detail.second.accountBal;
            }

        }
        void changePassword(string user, string pass, string newPass, loginDetails){
            fileRead.open("users.txt");
            map<int, loginDetails> tempUserLoginMap;
            while(fileRead >>myId >> usrname>> passwd){
              tempUserLoginMap[myId] = loginDetails{usrname, passwd};  
            }
            for(auto& entry : tempUserLoginMap){
                if(entry.second.userUsername == user && entry.second.userPassword == passwd){
                    entry.second.userPassword = newPass;
                }
            }
            fileRead.close();
            fileWrite.open("users.txt");
            for(auto& [myId, loginDetails] : tempUserLoginMap){
                fileWrite << myId<< " "<< loginDetails.userUsername <<" "<<  loginDetails.userPassword;
            }
        fileWrite.close();  
        }
        int checkAccountBal(){

        }
        string carRequest(string make, string model, int days){
            if(myUser && myUser->checkCarExists(make, model)){  
                return "approved, countdown started";
            }
            return "not approved";
            
        }

};

class Admin{
public:
    User myClient;
    int userId;
    map <int, loginDetails>userLoginDetails;
    map <int, userInfo>userDetails;
    map <string, carInfo> carInventory;
    
    
    void addCarInventory(string numberPlate, string carMake, string carModel){
        carInventory[numberPlate] = carInfo{carMake, carModel};
    }
    void addUserDetails(int userId, string firstName, string secondName, int phoneNumber,  string email, double accountBal){
        userDetails[userId] = userInfo{firstName, secondName, phoneNumber, email, accountBal};
    }
    void addLoginDetails(int userId, string userUsername, string userPassword){
        userLoginDetails[userId] = loginDetails{userUsername, userPassword};
    }

    ofstream fileOut;
    void saveUserDetails(){ 
        fileOut.open("userDB.txt");
        for (auto&  [userId, userInfo] : userDetails){
            fileOut<< userId << userInfo.firstName << " "<< userInfo.secondName <<" "<< userInfo.phoneNumber <<" "<< userInfo.email <<" "<< userInfo.accountBal;
        }
    }
    void saveLoginDetails(){
        fileOut.open("users.txt");
        for(auto& [userId, loginDetails] : userLoginDetails){
            fileOut<< userId <<" "<< loginDetails.userUsername <<" "<< loginDetails.userPassword;
        }
    }
    void savecarInventory(){
        fileOut.open("carsDB.txt");
        for(auto& [numberplate, carInfo] : carInventory){
            fileOut<< numberplate <<" "<< carInfo.carMake <<" "<< carInfo.carModel;
        }
    }

    ifstream fileIn;
    ofstream fileOut;
    int id, tellNo;
    string fname, sname, email;
    double accBal;
    void viewRegisteredUsers(){
        map<int, userInfo>viewUsers;
        fileIn.open("userDB.txt");
        while(fileIn>> id>>fname >> sname>> tellNo>>email >>accBal){
            viewUsers[id] = userInfo{fname, sname, tellNo, email, accBal};
        }
    }
    string make, model, numPlate;
    void viewCars(){
        map<string, carInfo>viewCars;
        fileIn.open("carsDB.txt");
        while(fileIn>> make>> model>> numPlate){
            viewCars[numPlate] = carInfo{make, model, numPlate};
        }
    }
    bool checkCarExists( string make, string model){
            for(auto& [numberplate, carInfo]: carInventory){
                if(carInfo.carMake == make && carInfo.carModel == model){
                    return true;
                }
        }
         return false;
    }
    string updateCarDB(string plate){
       map<string, carInfo>updateCars;
        fileIn.open("carsDB.txt");
        while(fileIn>> make>> model>> numPlate){
            updateCars[numPlate] = carInfo{make, model, numPlate};
        }
        for(auto& [numplate, carInfo] : updateCars){
            if(numplate == plate){
                updateCars.erase(numplate);
                break;
            }
        }
        fileOut.open("carsDB.txt");
        for(auto& [numberplate, carInfo] : updateCars){
            fileOut<< numberplate <<" "<< carInfo.carMake <<" "<< carInfo.carModel;
        }
        fileOut.close();
       return "updated";
        }
    
    string updateCarReturn(string plate, string make, string model){
            ofstream fileOut("carsDB.txt", ios::app);
            fileOut<<plate<< " "<<make<<" "<< model;
        return "updated CarsDB";
         }
    };
   

int idGenerator(){
    srand(time(0));
    int myId = rand() % 10000;
    return myId;
}
bool checkUserlogin(int role, string username, string password){
    string savedUsername, savedPassword;
    int savedId;
    ifstream fileIn;
    map <int, pair<string, string>> users;
    if (role ==1){
        fileIn.open("users.txt");
        while(fileIn >>savedId >>savedUsername >> savedPassword ){
            if (username == savedUsername && password == savedPassword){
                return true;
            }
        }
        fileIn.close();
    }else if( role == 2){
        fileIn.open("admin.txt");
        while(fileIn>>savedUsername >> savedPassword){
            if(username == savedUsername && password == savedPassword){
                return true;
            }
        }
        fileIn.close();
    }else {
        cerr <<"invalid input";
    }
}

int main(){
    cout<<"****** Welcome to CAR RENTAL SYSTEM ******" <<endl;
    cout<<"Select your role to proceed"<<endl;
    cout<<"        1. Normal User Login"<<endl;
    cout<<"        2. Adminstrator Login"<<endl;
    cout<<"        3. Exit"<<endl;
    cout<<"Enter role to proceed: "<<endl;
    cout<<"------------------------------------------"<<endl;
    int role;
    string username, password;
    cin>>role;

    int option;
    ifstream readFile;
    ofstream writeFile;
    switch(role){
        case 1:
            cout<<"****WELCOME TO USER LOGIN PAGE****"<<endl;
            cout<<"Enter your username: "<<endl;
            cin>>username;
            cout<<"Enter your password"<<endl;
            cin>>password;
            cout<<"------------------------------------------"<<endl;

            if(checkUserlogin(role, username, password)){
                cout<<"Successfully logged in"<<endl;
                cout<<" "<<endl;
                cout<<"Select one of the options below"<<endl;
                cout<<"        1.View personal details"<<endl;
                cout<<"        2.Request to rent a car"<<endl;
                cout<<"        3.Return a rented car"<<endl;
                cout<<"        4.Change balance"<<endl;
            }
            break;

        case 2:
            cout<<"****WELCOME TO ADMINSTRATOR LOGIN PAGE****"<<endl;
            cout<<"Enter admin username: "<<endl;
            cin>>username;
            cout<<"Enter admin password"<<endl;
            cin>>password;
            cout<<"------------------------------------------"<<endl;

            
            if(checkUserlogin(role, username, password)){
                cout<<"Successfully logged in"<<endl;
                cout<<" "<<endl;
                cout<<"Select one of the options below"<<endl;
                cout<<"        1.Register new users"<<endl;
                cout<<"        2.Approve user's Car rent request"<<endl;
                cout<<"        3.Update system on returned cars"<<endl;
                cout<<"        4.Change password"<<endl;
                cout<<"        5.View registered users"<<endl;
                cout<<"        6.View available cars"<<endl;

                switch(option){
                case 1:{
                    string fName;
                    string sName;
                    int phone;
                    string Email;
                    double accBal;
                    cout<<"Enter the user's name(first and last): "<<endl;
                    cin>> fName >> sName;
                    cout<<"enter the user's phone number"<<endl;
                    cin>> phone;
                    cout<<"enter user's email"<<endl;
                    cin>>Email;
                    cout<<"enter the deposited amount"<<endl;
                    cin>>accBal;
                    int ID = idGenerator();

                    Admin user;
                    user.addUserDetails(ID, fName, sName, phone, Email, accBal);
                    user.saveUserDetails();
                }
                    break;
                case 2:{
                     //approve user car rent request 
                }
                    break;
                case 3:{
                   //Update system on returned cars

                }
                    break;   
                case 4:{
                    //Change password
                    string name, pass, newPass;
                    readFile.open("admin.txt");
                    string adminDetails[2] ={};
                    while(readFile>> name >>pass){
                        for(int i=0; i< sizeof(adminDetails)/ sizeof(adminDetails[0]); i++)
                            adminDetails[i] = name;
                    }
                }
                    break;   
                case 5:{
                    //View registered users
                }
                    break;   
                case 6: {
                     //View available cars
                }
                    break;

                default:
                    cout<<"invalid input!"<<endl;

                }
            }
           
            

             break;


        case 3:
            exit(0);
            break;
        default:
            cout<<"Invalid output"<<endl;
    }

    return 0;
}
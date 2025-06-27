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

class Admin;
class User{
 public:
    Admin* myUser;
    int myId, tellNo;
    string fname, sname, email, usrname, passwd, carplate;
    double accBal;
    map<int, userInfo> myDetails;
    ifstream fileRead;
    ofstream fileWrite;

    void displayMyDetails(string usrname){
        
        fileRead.open("userDB.txt");
        while(fileRead>> myId>>fname >> sname>> tellNo>> email>> accBal){
            if(usrname == email){
                myDetails[myId] = userInfo{fname, sname, tellNo, email, accBal};
            }
            for(auto& [myId, userInfo] : myDetails){
                cout<<"your userID: "<<myId<<" first name: "<<userInfo.firstName<<" second name: "<<userInfo.secondName<<" phone number: "<< userInfo.phoneNumber<<" email: "<<userInfo.email<<" account balance: "<< userInfo.accountBal<<endl;
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
    string changePassword(string user, string pass, string newPass){
        fileRead.open("users.txt");
        map<int, loginDetails> tempUserLoginMap;
        while(fileRead >>myId >> usrname>> passwd){
            tempUserLoginMap[myId] = loginDetails{usrname, passwd};  
        }
        for(auto& entry : tempUserLoginMap){
            if(entry.second.userUsername == user && entry.second.userPassword == passwd){
                entry.second.userPassword = newPass;
                return "password updated";
            }else{
                return "failed to update";
            }
        }
        fileRead.close();
        fileWrite.open("users.txt");
        for(auto& [myId, loginDetails] : tempUserLoginMap){
            fileWrite << myId<< " "<< loginDetails.userUsername <<" "<<  loginDetails.userPassword;
        }
    fileWrite.close();  
    return " ";
    }
    int updateAccountBal(string usrname, int money){
            int updatedBal;
            fileRead.open("userDB.txt");
            fileWrite.open("tempUserDB.txt");
            while(fileRead>> myId>>fname >> sname>> tellNo>> email>> accBal){
                if(usrname == email){
                    accBal += money;
                    updatedBal = accBal;
                }
                fileWrite << myId << " " << fname << " " << sname << " "
                  << tellNo << " " << email << " " << accBal;
            }
            fileRead.close();
            fileWrite.close();
            remove("UserDB.txt");
            rename("tempUserDB.txt", "userDB.txt");
            return updatedBal;
        }
//car request
    string requestCar(string usernme, string make, string model){
        fileWrite.open("request.txt" , ios::app);
        fileWrite<<usernme<<" "<<make<<" "<<model;
        return "requested a car to rent";

    }
    string returnCar(string make, string model, string plate){
        fileWrite.open("return.txt");
        fileWrite<<make<<" "<<model<<" "<<plate;
        return "requested a return of a car";
    }
};

class Admin{
public:
    User myClient;
    int userId;
    map <int, loginDetails>userLoginDetails;
    map <int, userInfo>userDetails;
    map <string, carInfo> carInventory;
    ofstream fileOut;
    ifstream fileIn;
    int id, tellNo;
    string fname, sname, email;
    double accBal;
    string make, model, numPlate;

    void addCarInventory(string numberPlate, string carMake, string carModel){
        carInventory[numberPlate] = carInfo{carMake, carModel};
    }
    void addUserDetails(int userId, string firstName, string secondName, int phoneNumber,  string email, double accountBal){
        userDetails[userId] = userInfo{firstName, secondName, phoneNumber, email, accountBal};
    }
    void addLoginDetails(int userId, string userUsername, string userPassword){
        userLoginDetails[userId] = loginDetails{userUsername, userPassword};
    }


    void saveUserDetails(){ 
        fileOut.open("userDB.txt");
        for (auto&  [userId, userInfo] : userDetails){
            fileOut<< userId << userInfo.firstName << " "<< userInfo.secondName <<" "<< userInfo.phoneNumber <<" "<< userInfo.email <<" "<< userInfo.accountBal;
        }
        fileOut.close();
    }
    void saveLoginDetails(){
        fileOut.open("users.txt");
        for(auto& [userId, loginDetails] : userLoginDetails){
            fileOut<< userId <<" "<< loginDetails.userUsername <<" "<< loginDetails.userPassword;
        }
        fileOut.close();
    }
    void savecarInventory(){
        fileOut.open("carsDB.txt");
        for(auto& [numberplate, carInfo] : carInventory){
            fileOut<< numberplate <<" "<< carInfo.carMake <<" "<< carInfo.carModel;
        }
        fileOut.close();
    }

    void viewRegisteredUsers(){
        map<int, userInfo>viewUsers;
        fileIn.open("userDB.txt");
        while(fileIn>> id>>fname >> sname>> tellNo>>email >>accBal){
            viewUsers[id] = userInfo{fname, sname, tellNo, email, accBal};
        }
        fileIn.close();
        for(auto& [id, userInfo]: viewUsers){
            cout<<"user id: "<<id<<" first name: "<<userInfo.firstName<<" second name: "<<userInfo.secondName<<" phone number: "<< userInfo.phoneNumber<<" email: "<<userInfo.email<<" account balance: "<< userInfo.accountBal<<endl;
        }
    }
    void viewCars(){
        map<string, carInfo>viewCars;
        fileIn.open("carsDB.txt");
        while(fileIn>> numPlate>> make>> model){
            viewCars[numPlate] = carInfo{make, model, numPlate};
        }
        fileIn.close();
        for (auto& [numPlate, carInfo] : viewCars){
            cout<< "number plate: "<<numPlate<<" make: "<< carInfo.carMake <<" model: "<<carInfo.carModel<<endl;
        }
    }
    string checkCarExists( string make, string model){
           fileIn.open("carsDB.txt");
           string carMake, carModel;
           while(fileIn>>numPlate >> carMake>> carModel){
                if( carMake == make && carModel == model){
                    return numPlate;
                }
           }
           fileIn.close();
         return " ";
    }

    string updateCarDB(string plate){
       map<string, carInfo>updateCars;
        fileIn.open("carsDB.txt");
        while(fileIn>> numPlate>> make>> model){
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
        fileIn.close();
        fileOut.close();
       return "updated";
        }
    string updateCarReturn(){
            fileIn.open("return.txt");
            fileOut.open("carsDB.txt", ios::app);
            while(fileIn >> make >> model >> numPlate){
                 fileOut<<numPlate<< " "<<make<<" "<< model;
            }
           fileIn.close();
            fileOut.close();
        return "updated CarsDB";
         }
    string changeAdminPasswd(string passwdOld, string newPasswd){
        string passwd, usrname;
        fileIn.open("admin.txt");
        fileOut.open("tempAdmin.txt");
        while(fileIn>> usrname >> passwd){
            if (passwdOld == passwd){
                passwd = newPasswd;
                break;
            }
            fileOut<< usrname<<" "<< passwd;
        }
        fileIn.close();
        fileOut.close();
        return "password changed";
    }
    bool checkUserAccBal(string usrName){
        fileIn.open("userDB.txt");
        while(fileIn>> id>>fname >> sname>> tellNo>>email >>accBal){
            if(usrName == email){
                if(accBal > 10500){
                    return true;
                }
                return false;
            }
        }
       return  false;
    }
    string approveCarRequest(string make, string model, string usrname) {
        string usernme, mak, mdl;
        fileIn.open("request.txt");
        while(fileIn>>usrname>> mak>> mdl){
            string carPlate = checkCarExists(make, model);
            if (!carPlate.empty()) {
                if (checkUserAccBal(usrname)) {
                    updateCarDB(carPlate);
                    return "Car request approved";
                } else {
                    return "Insufficient funds";
                }
            } else {
                return "Car not available";
            }
        }
        fileIn.close();
        return " ";
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
    return false;
}

int main(){
    while(true){
    Admin myAdmin;
    User client;
    cout<<"****** Welcome to CAR RENTAL SYSTEM ******" <<endl;
    cout<<"Select your role to proceed"<<endl;
    cout<<"        1. Normal User Login"<<endl;
    cout<<"        2. Adminstrator Login"<<endl;
    cout<<"        3. Exit"<<endl;
    cout<<"Enter role to proceed: "<<endl;
    cout<<"------------------------------------------"<<endl;
    int role;
    string username, password, newPasswd;
    int cash;
    cin>>role;

    int option;
    string make, model, usrname, plate, oldPass, newPass;
    string fName, sName, Email;
    int phone;
    double accBal;

    switch(role){
        case 1: {
            cout<<"****WELCOME TO USER LOGIN PAGE****"<<endl;
            cout<<"Enter your username(email): "<<endl;
            cin>>username;
            cout<<"Enter your password"<<endl;
            cin>>password;
            cout<<"------------------------------------------"<<endl;

            if(checkUserlogin(role, username, password)){
                cout<<"Successfully logged in"<<endl;
                cout<<" "<<endl;
                int userOption;
                do{
                    cout<<"Select one of the options below"<<endl;
                    cout<<"        1.View personal details"<<endl;
                    cout<<"        2.Request to rent a car"<<endl;
                    cout<<"        3.Return a rented car"<<endl;
                    cout<<"        4.Update account balance"<<endl;
                    cout<<"        5.Change password"<<endl;
                    cout<<"        6.Logout"<<endl;

                    cin>>userOption;
                    switch(userOption){
                        case 1:{
                            //display user details;
                            client.displayMyDetails(username);
                        }
                            break;
                        case 2:{
                            cout<<"enter car make you want(eg toyota): "<<endl;
                            cin>>make;
                            cout<<"enter the model you want"<<endl;
                            cin>>model;
                            client.requestCar(username, make, model);
                            cout<<"admin needs to approve. enter the admin username and password please"<<endl;
                            cin>>usrname>>password;
                            if (checkUserlogin(2, username, password)){
                                myAdmin.approveCarRequest(username, make, model);
                            }
                        }
                            break;
                        case 3:{
                            cout<<"input the make you want to return (eg Toyota): "<<endl;
                            cin>>make;
                            cout<<"input the model you want to return(eg prado): "<<endl;
                            cin>>model;
                            cout<<"enter the number plate"<<endl;
                            cin>>plate;
                            client.returnCar(make,model, plate);
                        }
                            break;
                        case 4:{
                            //update account balance
                            cout<<"enter cash you want to add to your account"<<endl;
                            cin>>cash;
                            client.updateAccountBal(username, cash);
                        }
                            break;
                        case 5:{
                            //change password
                            cout<<"enter your current password: "<<endl;
                            cin>>password;
                            cout<<"enter new password: "<<endl;
                            cin>>newPasswd;
                            client.changePassword(username, password, newPasswd);
                        }
                            break;
                        case 6:
                            cout<<"Logging out..."<<endl;
                            break;
                        default:
                            cout<<"invalid input"<<endl;
                    }
                }while(userOption !=6);
            }else{
                cout<<"failed to login. Try again!"<<endl;
            }
            break;
        }
        case 2:{
            cout<<"****WELCOME TO ADMINSTRATOR LOGIN PAGE****"<<endl;
            cout<<"Enter admin username: "<<endl;
            cin>>username;
            cout<<"Enter admin password"<<endl;
            cin>>password;
            cout<<"------------------------------------------"<<endl;

    
            if(checkUserlogin(role, username, password)){
                cout<<"Successfully logged in"<<endl;
                cout<<" "<<endl;
                do{
                cout<<"Select one of the options below"<<endl;
                cout<<"        1.Register new users"<<endl;
                cout<<"        2.Approve user's Car rent request"<<endl;
                cout<<"        3.Update system on returned cars"<<endl;
                cout<<"        4.Change password"<<endl;
                cout<<"        5.View registered users"<<endl;
                cout<<"        6.View available cars"<<endl;
                cout<<"        7. logout"<<endl;

                cin>>option;
                switch(option){
                case 1:{
                    //register new user
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
                    //enter q to quit/a**00 to go back to main/ call the loop again
                }
                    break;
                case 2:{
                     //approve user car rent request 
                    cout<<"input the make you want (eg Toyota): "<<endl;
                    cin>>make;
                    cout<<"input the model you want(eg prado): "<<endl;
                    cin>>model;
                    cout<<"enter your username/ email"<<endl;
                    cin>>usrname;
                    
                }
                    break;
                case 3:{
                   //Update system on returned cars
                    myAdmin.updateCarReturn();
                }
                    break;   
                case 4:{
                    //Change password
                   cout<<"enter the current password"<<endl;
                   cin>>oldPass;
                   cout<<"enter the new password"<<endl;
                   cin>>newPass;
                   myAdmin.changeAdminPasswd(oldPass, newPass);
                }
                    break;   
                case 5:{
                    //View registered users
                    myAdmin.viewRegisteredUsers();
                }
                    break;   
                case 6: {
                     //View available cars
                     myAdmin.viewCars();
                }
                    break;
                default:
                    cout<<"invalid input!"<<endl;

                }
            }while(option !=7);
            }else{
                cout<<"invalid login. Try again!"<<endl;
            }
       
        }
        break;
        case 3:
            exit(0);
            break;
        default:
            cout<<"Invalid input"<<endl;
    }
}
    return 0;
}
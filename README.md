#  Car Rental System in C++

A simple command-line **Car Rental Management System** built using C++. It allows both **Users** and **Administrators** to interact with the system for renting and managing cars.

---

##  Features

### 👤User
- Login with email and password
- View personal account details
- Request to rent a car
- Return a rented car
- Update account balance
- Change login password

### 🛠️Admin
- Login with admin credentials
- Register new users
- Approve or reject car rental requests
- Update car inventory upon return
- Change admin password
- View all registered users
- View all available cars

---

##  Files Created and Their Purposes

| File Name      | Purpose                                            | Format / Example                                       |
|----------------|----------------------------------------------------|--------------------------------------------------------|
| `users.txt`    | Stores user login credentials                      | `1001 john.doe@example.com car123`                     |
| `userDB.txt`   | Stores full user profiles                          | `1001 John Doe 0712345678 john.doe@example.com 15000`  |
| `carsDB.txt`   | Stores available cars with make and model          | `KDA123A Toyota Corolla`                               |
| `request.txt`  | Temporary store for user rental requests           | `john.doe@example.com Toyota Corolla`                  |
| `return.txt`   | Temporary store for car return requests            | `KDA123A Toyota Corolla`                               |
| `admin.txt`    | Stores administrator credentials                   | `admin admin123`                                       |

---

##  Requirements

- A C++ compiler (supports C++17 or above)
- Command-line terminal or shell

---

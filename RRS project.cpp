#include <iostream>
#include <string>
#include <queue>
#include<iomanip>


using namespace std;


void goToNextScreen(const string& screenTitle) {
 
#ifdef _WIN32
    system("CLS"); 
#else
    system("clear"); 
#endif

   
    cout << "\n-------------------------\n";
    cout << "|    " << screenTitle << "    | \n";
    cout << "-------------------------\n";
}

class Customer {
public:
    string name;
    int reservationID;
    string reservationTime;
    string reservationDate;
    string specialRequest;
    string tableNumber;
    int numberOfGuests;
    
    

    Customer(string customerName, string time, string date, int guests, string table) {
        name = customerName;
        reservationTime = time;
        reservationDate = date;
        numberOfGuests = guests;
        tableNumber = table;
        specialRequest = "";
    }

    void addSpecialRequest(string request) {
        specialRequest = request;
    }
};




class ReservationNode {
public:
    Customer* customer;
    ReservationNode* next;

    ReservationNode(Customer* customer) {
        this->customer = customer;
        this->next =NULL;
    }
};


class ReservationList {
public:
    ReservationNode* head;

    ReservationList() {
        head = NULL;
    }

    void addReservation(Customer* customer) {
        ReservationNode* newNode = new ReservationNode(customer);
        if (head == NULL) {
            head = newNode;
        } else {
            ReservationNode* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        cout << "Reservation for " << customer->name << " at " << customer->reservationTime << " added successfully.\n";
    }

    void showReservations() {
        if (head == NULL) {
            cout << "No reservations found.\n";
            return;
        }
        ReservationNode* temp = head;
        while (temp != NULL) {
            cout << "Name: " << temp->customer->name << ", Reservation Time: " << temp->customer->reservationTime << endl;
            if (!temp->customer->specialRequest.empty()) {
                cout << "Special Request: " << temp->customer->specialRequest << endl;
            }
            temp = temp->next;
        }
    }

    void cancelReservation(string name) {
        if (head == NULL) {
            cout << "No reservations to cancel.\n";
            return;
        }

        ReservationNode* temp = head;
        ReservationNode* prev = NULL;

        if (temp !=NULL&& temp->customer->name == name) {
            head = temp->next;
            delete temp;
            cout << "Reservation for " << name << " cancelled successfully.\n";
            return;
        }

        while (temp != NULL&& temp->customer->name != name) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL) {
            cout << "Reservation not found for " << name << ".\n";
            return;
        }

        prev->next = temp->next;
        delete temp;
        cout << "Reservation for " << name << " cancelled successfully.\n";
    }
};


class ReservationQueue {
public:
    ReservationNode* front;  
    ReservationNode* rear;   


  
    ReservationQueue() : front(NULL), rear(NULL) {}

   
    ~ReservationQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

ReservationNode* Front() {
    return front; 
}

     
    
    void enqueue(Customer* customer) {
        ReservationNode* newNode = new ReservationNode(customer);

        
        if (rear == NULL) {
            front = rear = newNode;
        } else {
            
            rear->next = newNode;
            rear = newNode;
        }
        cout << "Reservation for " << customer->name << " added to the queue.\n";
    }

   
    void dequeue() {
        if (isEmpty()) {
            cout << "No reservations in the queue.\n";
            return;
        }

        
        ReservationNode* temp = front;
        front = front->next;

       
        if (front == NULL) {
            rear = NULL;
        }

        cout << "Serving reservation for " << temp->customer->name << " at " << temp->customer->reservationTime << ".\n";
        delete temp;  
    }

    
    void showQueue() {
        if (isEmpty()) {
            cout << "No reservations in the queue.\n";
            return;
        }

        cout << "Reservations in Queue:\n";
        ReservationNode* temp = front;
        while (temp != NULL) {
            cout << "Name: " << temp->customer->name << ", Reservation Time: " << temp->customer->reservationTime << endl;
            temp = temp->next;
        }
    }

    
    bool isEmpty() {
        return front == NULL;
    }

   
    Customer* peekFront() {
        if (isEmpty()) {
            return NULL;
        }
        return front->customer;
    }
};



static const int max_feedback = 100;

class Feedback {
	
    string customerName;
    string message;
    
    
    
    public:
    	int top;
    
    Feedback(){
    	customerName=" ";
    	message=" ";
    	top=-1;
	}

     Feedback(string name, string feedbackMessage, int Top) {
        customerName = name;
        message = feedbackMessage;
        top = Top;
    }

   
    bool isFull() {
        return top == max_feedback - 1;
    }

   
    bool isEmpty() {
        return top == -1;
    }

  
    void push(string name, string feedbackMessage, Feedback stack[]) {
        if (isFull()) {
            cout << "Feedback stack is full! Cannot add more feedback.\n";
            return;
        }
        top++;  
        stack[top] = Feedback(name, feedbackMessage, top);  
        cout << "Thank you, " << name << ", for your feedback!\n";
    }

    
    void displayFeedback(Feedback stack[], int top) {
    if (top == -1) {  
        cout << "No feedback available yet.\n";
        return;
    }

    cout << "\nFeedback History (Most Recent First):\n";
    cout << "=====================================\n";
    for (int i = top; i >= 0; i--) {
        cout << "Feedback " << (top - i + 1) << ":\n";
        cout << "Customer Name: " << stack[i].customerName << "\n";
        cout << "Message: " << stack[i].message << "\n";
        cout << "-------------------------------------\n";
    }
    cout << "=====================================\n";
}


    
    int getTop() {
        return top;
    }
};
Feedback stack[max_feedback];

class Admin{
	
	ReservationQueue reservationQueue;
	ReservationList reservationList;
	Feedback feedback;
const string adminUsername = "admin";
const string adminPassword = "password123";	

public:
void adminLogin() {
       string username, password;
       do{
    
        cout <<"\n-------------------------\n";
        cout << " Enter username:";
        cin >> username;
        cout << " Enter password: ";
        cin >> password;
        cout <<"-------------------------\n";

        if (username == adminUsername && password == adminPassword) {
            cout << "     Login successful!     \n";
            break;
        } else {
            cout << "     Invalid credentials!     \n";
            
        }
    }while(true);
}
void searchReservationByName(string name) {
    bool found = false;

    // Search in the reservation list
    ReservationNode* currentNode = reservationList.head; // Head of the linked list
    while (currentNode != NULL) {
        if (currentNode->customer->name == name) {
            // Reservation found in the linked list
            cout << "Reservation Found in List:\n";
            cout << "Name: " << currentNode->customer->name << "\n";
            cout << "Date: " << currentNode->customer->reservationDate << "\n";
            cout << "Time: " << currentNode->customer->reservationTime << "\n";
            cout << "Table Number: " << currentNode->customer->tableNumber << "\n";
            cout << "Guests: " << currentNode->customer->numberOfGuests << "\n";
            if (!currentNode->customer->specialRequest.empty()) {
                cout << "Special Request: " << currentNode->customer->specialRequest << "\n";
            }
            cout << "------------------\n";
            found = true;
        }
        currentNode = currentNode->next; // Move to the next node
    }

    // Search in the reservation queue
    currentNode = reservationQueue.Front(); // Front of the queue
    while (currentNode != NULL) {
        if (currentNode->customer->name == name) {
            // Reservation found in the queue
            cout << "Reservation Found in Queue:\n";
            cout << "Name: " << currentNode->customer->name << "\n";
            cout << "Date: " << currentNode->customer->reservationDate << "\n";
            cout << "Time: " << currentNode->customer->reservationTime << "\n";
            cout << "Table Number: " << currentNode->customer->tableNumber << "\n";
            cout << "Guests: " << currentNode->customer->numberOfGuests << "\n";
            if (!currentNode->customer->specialRequest.empty()) {
                cout << "Special Request: " << currentNode->customer->specialRequest << "\n";
            }
            cout << "------------------\n";
            found = true;
        }
        currentNode = currentNode->next; // Move to the next node
    }

    if (!found) {
        cout << "No reservation found for customer: " << name << "\n";
    }
}






 void displayMenu() {
         cout << "\n-------------------------------------------------------------\n";
         cout << "\n       Welcome to the Restaurant Reservation System!\n";
         cout << "\n-------------------------------------------------------------\n";
       
        cout << "1. Show Reservations\n";
      //  cout << "2. Show sorted reservations\n";
        cout << "2. search reservation\n";  
        cout << "3. Display feedbacks\n";     
        cout << "0. Exit\n";
        cout << "\n-------------------------------------------------------------\n";
    }	
	
	void run() {
		int top=stack->top;
		
		goToNextScreen("|      ADMIN      |");
        adminLogin();
        
    

        while (true) {
            displayMenu();
            int choice;
            string name;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
             
               case 1: reservationList.showReservations(); break;
          //     case 2 : sortReservationsByDateAndTime(reservationList);
                      reservationList.showReservations(); break;  
					  case 2: cout<<"Enter name to search resservation:";
					  cin>>name;
					  searchReservationByName(name);
					  break;
               case 3: feedback.displayFeedback(stack,top); break;
        
                default: cout << "Invalid choice. Try again.\n"; break;
            }
        }
    }
    
};


class RestaurantReservationSystem {
private:
    
    const string customerUsername ="eshal";
    const string customerPassword ="c123";
    ReservationList reservationList;
    ReservationQueue reservationQueue;
  

public:
    



void generateEReceipt(const string& name, ReservationList& reservationList) {
    if (reservationList.head == NULL) {
        cout << "No reservations found. Please make a reservation first.\n";
        return;
    }

    ReservationNode* temp = reservationList.head;
    while (temp != NULL) {
        if (temp->customer->name == name) {
            
            cout << "\n===============================================\n";
            cout << "                 E-RECEIPT                     \n";
            cout << "===============================================\n";
            cout << setw(20) << left << "Restaurant Name:" << "Quick Seat Restaurant" << "\n";
            cout << setw(20) << left << "Reservation ID:" << temp->customer->name.length() * 100 + temp->customer->numberOfGuests << "\n"; // Simple ID logic
            cout << setw(20) << left << "Customer Name:" << temp->customer->name << "\n";
            cout << setw(20) << left << "Reservation Date:" << temp->customer->reservationDate << "\n";
            cout << setw(20) << left << "Reservation Time:" << temp->customer->reservationTime << "\n";
           
            cout << setw(20) << left << "Total Guests:" << temp->customer->numberOfGuests << "\n";
            cout << setw(20) << left << "Special Request:"
                 << (temp->customer->specialRequest.empty() ? "None" : temp->customer->specialRequest) << "\n";
            cout << "-----------------------------------------------\n";
            cout << "Note: Please arrive 10 minutes earlier.\n";
            cout << "-----------------------------------------------\n";
            cout << setw(20) << left << "Contact Info:" << "+1234567890\n";
            cout << setw(20) << left << "Email:" << "info@quickseat.com\n";
            cout << "===============================================\n";
            cout << "Thank you for choosing Quick Seat Restaurant!\n";
            cout << "We look forward to serving you. Bon Appétit!\n";
            cout << "===============================================\n";
            return;
        }
        temp = temp->next;
    }

    cout << "No reservation found for the name: " << name << ". Please check the name and try again.\n";
}

void giveFeedback() {
	Feedback feedback;
    string name, feedbackMessage;
    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter your feedback: ";
    getline(cin, feedbackMessage);

    
    feedback.push(name, feedbackMessage, stack);
    
}
    
    void viewFeedbackHistory(Feedback& feedbackStack) {
    	
	int top=stack->top;
        feedbackStack.displayFeedback(stack,top);
    }



    void modifyBooking() {
    if (reservationList.head == NULL) {
        cout << "No reservations to modify.\n";
        return;
    }

    string name;
    cout << "Enter the name for modifying the booking: ";
    cin.ignore();
    getline(cin, name);

    ReservationNode* temp = reservationList.head;
    while (temp != NULL) {
        if (temp->customer->name == name) {
            cout << "Enter new reservation time (current: " << temp->customer->reservationTime << "): ";
            getline(cin, temp->customer->reservationTime);

            char specialRequestChoice;
            cout << "Do you want to update the special request? (y/n): ";
            cin >> specialRequestChoice;

            if (specialRequestChoice == 'y' || specialRequestChoice == 'Y') {
                cout << "Enter new special request: ";
                cin.ignore();
                getline(cin, temp->customer->specialRequest);
            }

            cout << "Booking updated successfully for " << name << ".\n";
            return;
        }
        temp = temp->next;
    }

    cout << "Reservation not found for " << name << ".\n";
}

void customerLogin() {
    string name, phone, time, specialRequest;
    int choice;
    string username, password;
       do{
    
        cout <<"\n-------------------------\n";
        cout << " Enter username:";
        cin >> username;
        cout << " Enter password: ";
        cin >> password;
        cout <<"-------------------------\n";

        if (username == customerUsername && password == customerPassword) {
            cout << "     Login successful!     \n";
            break;
        } else {
            cout << "     Invalid credentials!     \n";
            
        }
    }while(true);
    goToNextScreen("|   OPTIONS   |");
    do{
    
	
    cout<<"\n--------------------------------------";
    cout<<"\n  1.MAKE RESERVATION                  |";
    cout<<"\n  2.VIEW YOUR RESERVATION DETAILS     |";
    cout<<"\n  3.VIEW YOUR E-RECEIPT               |";
    cout<<"\n  4.MAKE CHANGES IN YOUR BOOKING      |";
    cout<<"\n  5.CANCEL BOOKING                    |";
	cout<<"\n  6.GIVE FEEDBACK                     |";
    cout<<"\n  0.LOGOUT                            |";
    cout << "\n--------------------------------------\n";
    cout << " Enter your choice: ";
    cin >> choice;

          switch (choice) {
            case 1:
            	goToNextScreen("BOOK A TABLE");
                addReservation();  
                break;
            case 2:
            	goToNextScreen("MY BOOKING");
                showReservations(); 
                break;
            case 3:
            	goToNextScreen("E_RECEIPT");
            	cout<<"Enter your name for the receipt:";
            	cin>>name;
                generateEReceipt(name,reservationList);  
                break;
            case 4:
            	goToNextScreen("MODIFY BOOKING");
                modifyBooking();  
                break;
            case 5:
            	goToNextScreen("CANCEL BOOKING");
                cancelReservation();  
                break;
            case 6:
            	 goToNextScreen("GIVE FEEDBACK");
            	 giveFeedback();
            	break;
            case 0:
                cout << "Thank you for using the reservation system. Goodbye!\n";
                return;  
            default:
                cout << "Invalid choice! Please select a valid option.\n";
        }
    } while (choice != 0);

}

    
   
   

    void addReservation() {
        string name, time,date,table;
		int NoOfGuests;
        cout << "Enter customer's name: ";
        cin.ignore();
        getline(cin, name);
        cout<<"Enter reservation date:";
        getline(cin,date);
        cout << "Enter reservation time (e.g. 7:00 PM): ";
        getline(cin, time);
        cout<<"Enter number of guests";
        cin>> NoOfGuests;

        Customer* newCustomer = new Customer(name, time,date,NoOfGuests,table);
        reservationList.addReservation(newCustomer);
        reservationQueue.enqueue(newCustomer); 
    }

    void showReservations() {
        reservationList.showReservations();
    }

    void cancelReservation() {
        string name;
        cout << "Enter the name of the reservation to cancel: ";
        cin.ignore();
        getline(cin, name);

        reservationList.cancelReservation(name);
    }

    void addSpecialRequest() {
        string name, request;
        cout << "Enter the customer's name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter the special request: ";
        getline(cin, request);

        ReservationNode* temp = reservationList.head;
        while (temp != NULL) {
            if (temp->customer->name == name) {
                temp->customer->addSpecialRequest(request);
                cout << "Special request added for " << name << ".\n";
                return;
            }
            temp = temp->next;
        }

        cout << "Reservation not found for " << name << ".\n";
    }

    void showRestaurantMenu() {
        cout << "\nRestaurant Menu:\n";
        cout << "1. Pizza\n";
        cout << "2. Pasta\n";
        cout << "3. Salad\n";
        cout << "4. Burger\n";
        cout << "5. Dessert\n";
        cout << "6. Drinks\n";
    }

    void showContactUs() {
        cout << "\nContact Us:\n";
        cout << "Phone: +1234567890\n";
        cout << "Email: info@restaurant.com\n";
        cout << "Address: 123 Main Street, Food City\n";
    }

    void addToQueue() {
        string name, time,date,table;
		int NoOfGuests;
        cout << "Enter customer's name: ";
        cin.ignore();
        getline(cin, name);
        cout<<"Enter reservation date:";
        getline(cin,date);
        cout << "Enter reservation time (e.g. 7:00 PM): ";
        getline(cin, time);
        cout<<"Enter number of guests";
        cin>> NoOfGuests;

        Customer* newCustomer = new Customer(name, time,date,NoOfGuests,table);
        reservationQueue.enqueue(newCustomer);
    
    }

    

    
};

int main() {
    RestaurantReservationSystem system;
    Admin admin;
    int role;
    
    cout << "\n\n======================================================================RESTAURANT RESERVATION SYSTEM=====================================================================\n\n\n\n";

    cout << "   WELCOME \n";
	                                                       do{
														   
    
    cout << "\n                                       1.Admin ";
    cout << "\n                                       2.Customer ";
    cout << "\n                                       Login as :  ";                                
    
    cin >> role;



    if (role == 1) {
        admin.run();
    } else if (role == 2) {
        system.customerLogin();
    } else {
        cout << "Invalid role! Try again\n";
        
    }

}while(true);


 return 0;
}

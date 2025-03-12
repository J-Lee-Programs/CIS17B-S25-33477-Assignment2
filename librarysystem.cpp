#include <iostream>
#include <string>
#include <mutex>
using namespace std;

//independent functions

bool search(string search[], string verify, int key, int numberlabel[], bool isThere) {
	for (int i = 0; i < 50; i++) {
		if (search[i] == verify) {
			isThere = true;
			return isThere;
		}
		else if (numberlabel[i] == key) {
			isThere = true;
			return isThere;
		}
		isThere = false;
		return isThere;
	}
}

void error(bool disrupt) {
	try {
		if (disrupt)
			throw runtime_error("User error, input not allowed.");
	}
	catch (const exception& e) {
		cout << "Warning: " << e.what() << endl;
	}
}

//MAIN CLASSES
class Book {
private:
	string title[50], author, tempTitle;
	int ibsn[50], query;
	bool available;
public:
	void bookChanges(int choice) {//take input variables and update them here
		switch (choice) {
		case 1: { //add AND check in
			cout << ">Please input the name followed by the IBSN number." << endl;
			cin.ignore(1000, '\n');
			getline(cin, tempTitle);
			cin >> query;
			cout << "This book is: ";
			available = search(title, tempTitle, query, ibsn, available);
			if (!available) {
				cout << "Not in the catalog." << endl;
				tempTitle = title[50];
				query = ibsn[50];
				cout << "Adding. . ." << endl;
			}
			else {
				cout << "In the catalog." << endl;
				error(available);
			}
			break;
		}
		case 2: {//edit
			cout << ">Please input the name followed by the IBSN number." << endl;
			cin.ignore(1000, '\n');
			getline(cin, tempTitle);
			cin >> query;
			cout << "This book is: ";
			available = search(title, tempTitle, query, ibsn, available);
			if (!available) {
				cout << "Not in the catalog." << endl;
				error(available);
			}
			else {
				cout << "In the catalog." << endl;
				tempTitle = title[50];//edit values at index . . .
				query = ibsn[50]; //edit values at index. . .
			};
			break;
		}
		case 3: {//remove AND checkout
			cout << ">Please input the name followed by the IBSN number." << endl;
			cin.ignore(1000, '\n');
			getline(cin, tempTitle);
			cin >> query;
			cout << "This book is: ";
			available = search(title, tempTitle, query, ibsn, available);
			if (!available) {
				cout << "Not in the catalog." << endl;
				error(available);
			}
			else {
				cout << "In the catalog." << endl;
				tempTitle = title[50];//edit values at index . . .
				query = ibsn[50]; //edit values at index. . .
				tempTitle = ""; //remove
				query = NULL; //remove
			}
			break;
		}
		}
	}
	void retrieveData() {
		cout << title[50] << endl;
		cout << ibsn[50] << endl;
	}
};

//------------------------------------------------------------------------------------//

class User { //*stores specialized data of student AND faculty
private:
	string name[50]; //store 50 strings
	int userID[50]; //store 50 ids
	bool available;
public:
	void userChanges(string newName, int ID, int choice) {
		switch (choice) {
		case 1: { //add
			cout << ">Please input the User followed by the their student or staff number." << endl;
			cin.ignore(1000, '\n');
			getline(cin, newName);
			cin >> ID;
			cout << "This user is: ";
			available = search(name, newName, ID, userID, available);
			if (!available) {
				cout << "Not in the database." << endl;
				newName = name[30];
				ID = userID[30];
				cout << "Adding . . ." << endl;
			}
			else {
				cout << "In the base." << endl;
				error(available);
			}
			break;
		}
		case 2: {//edit
			switch (choice) {
			case 1: { //add
				cout << ">Please input the User followed by the their student or staff number." << endl;
				cin.ignore(1000, '\n');
				getline(cin, newName);
				cin >> ID;
				cout << "This user is: ";
				available = search(name, newName, ID, userID, available);
				if (!available) {
					cout << "Not in the database." << endl;
					error(available);
				}
				else {
					cout << "In the database." << endl;
					newName = name[50];
					ID = userID[50];
				};
				break;
			}
			case 3: { //remove
				cout << ">Please input the User followed by the their student or staff number." << endl;
				cin.ignore(1000, '\n');
				getline(cin, newName);
				cin >> ID;
				cout << "This User is: ";
				available = search(name, newName, ID, userID, available);
				if (!available) {
					cout << "Not in the database." << endl;
					error(available);
				}
				else {
					cout << "In the database." << endl;
					newName = name[50];//edit values at index . . .
					ID = userID[50]; //edit values at index. . .
					name[50] = ""; //remove
					userID[50] = NULL; //remove
				}
			}
			}
		}
		}
		}
	void retrieveData() {
		cout << name[50] << endl;
		cout << userID[50] << endl;
	
	}
};

	//CHILD CLASSES
	class Student : public User {
	private:
		string studentName[50];
		int studentID[50];

	public: //retrieves student data and sends it back
		void upload(int choice) {
			userChanges(*studentName, *studentID, choice);
		}
	};

	class Faculty : public User {
	private:
		string facultyName[50];
		int facultyID[50];

	public: //retrieves faculty data and sends it back
		void upload(int choice) {
			userChanges(*facultyName, *facultyID, choice);
		}
	};

	//------------------------------------------------------------------------------------//

class Library {
private:
	Book Archive;
	Student Pupil;
	Faculty Staff;
	User Accounts;
	//SINGLETON
	static Library* instancePtr;
	static mutex mtx;
	Library() {}
public:

	Library(const Library& obj) = delete;

	static Library* getInstance() {
		if (instancePtr == nullptr) {
			lock_guard<mutex> lock(mtx);
			if (instancePtr == nullptr) {
				instancePtr = new Library();
			}
		}
		return instancePtr;
	}
		//SINGLETON
		//---------------------------------------//
		//MAIN FUNCTIONS


	void printLists(int choice) {
		switch (choice) {
		case 1://print all books
			Archive.retrieveData();
		case 2://print all users
			Accounts.retrieveData();
		}
	}
	void bookData(int choice) {
		cin >> choice;
		switch (choice) {
		case 1: 
			Archive.bookChanges(choice); //add
			break;
		case 2: 
			Archive.bookChanges(choice); //edit
			break;
		case 3: 
			Archive.bookChanges(choice); //remove
			break;
		case 4:
			break;
		}
	}

	void userData(int choice) {
		string options = ">Choose between (1) student and (2) faculty.";
		string student = ">Please input information for this student.";
		string faculty = ">Please input information for this staff member.";
		cin >> choice;
		switch (choice) {
		case 1: { //add
			cout << options << endl;
			cin >> choice;
			switch (choice) {
			case 1:
				cout << student << endl;
				Pupil.upload(choice);
			case 2:
				cout << faculty << endl;
				Staff.upload(choice);
			}
		}
		break;
		case 2: { //edit
			cout << options << endl;
			cin >> choice;
			switch (choice) {
			case 1:
				cout << student << endl;
				Pupil.upload(choice);
			case 2:
				cout << faculty << endl;
				Staff.upload(choice);
			}
		}
		break;
		case 3: { //remove
			cout << options << endl;
			cin >> choice;
			switch (choice) {
			case 1:
				cout << student << endl;
				Pupil.upload(choice);
			case 2:
				cout << faculty << endl;
				Staff.upload(choice);
			}
		}
		break;
		case 4:
			break;
		}
	}

	void transaction(int choice) {

		cin >> choice;
		switch (choice) {
		case 1: {
			Archive.bookChanges(choice); //out
		}
		break;
		case 2: {
			Archive.bookChanges(choice); //in
		}
		break;
		case 3: {
			printLists(choice); //print books
		}
		break;
		case 4: {
			printLists(choice); //print users
		}
		break;
		case 5:
			break;
		}
	}

};

	Library* Library::instancePtr = nullptr;
	mutex Library::mtx;

	//------------------------------------------------------------------------------------//


	//driver program
int main() {
	//Starting variables, blank slate
	Library* Archive = Library::getInstance();
	int choice;
	//Main Menu
	cout << "Welcome to the Library System" << endl;
	do {
		cout << endl;
		cout << "MAIN MENU" << endl;
		cout << ">1. Manage Books" << endl;
		cout << ">2. Manage Users" << endl;
		cout << ">3. Manage Transactions" << endl;
		cout << ">4. Exit" << endl;
		cout << endl;
		cout << ">Enter your choice" << endl;
		cin >> choice;
		switch (choice) {
		case 1: {
			//call the book data function here
			cout << "Manage Books" << endl;
			cout << ">1. Add a book" << endl;
			cout << ">2. Edit a book" << endl;
			cout << ">3. Remove a book" << endl;
			cout << ">4. Go back" << endl;
			Archive->bookData(choice);
		}
		break;
		case 2: {
			//call the user data function here
			cout << "Manage Users" << endl;
			cout << ">1. Add a user" << endl;
			cout << ">2. Edit a user" << endl;
			cout << ">3. Remove a user" << endl;
			cout << ">4. Go back" << endl;
			Archive->userData(choice);
		}
		break;
		case 3: {
			//call the transaction function here
			cout << "Manage Transactions" << endl;
			cout << ">1. Check out a book" << endl;
			cout << ">2. Check in a book" << endl;
			cout << ">3. List all books" << endl;
			cout << ">4. List all users" << endl;
			Archive->transaction(choice);
		}
		break;
		}
		if (!choice) {
				error(true);
		}
	} while (choice != 4);
return 0;
}

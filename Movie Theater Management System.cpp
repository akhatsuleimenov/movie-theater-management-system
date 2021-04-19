// Version      : 1.0
// Date Created : 13/02/21
// Date Modified: 21/02/21
// Copyright    : All rights are reserved
// Description  : Movie Theater Management System in C++
//============================================================================

#include<iostream>
#include<string>
#include<fstream>
#include<exception>
#include<cstdlib>
#include<vector>
#include<iomanip>
#include<stdlib.h>
#include<algorithm>
using namespace std;
using std::vector;


vector <int> li_gu_ID;
vector <int> li_ad_ID;
vector <int> li_mo_ID;

void print (int ID); // forward declaration of function to use it in the LL
void print_movies (int ID); // forward declaration of function to use it in the LL

// Node class with int elem and two pointers
class Node {
	private:
		int elem;
		Node* next;
		Node* prev; 
		friend class LinkedList;
		
	public:
		Node(): next(NULL), prev(NULL)
		{}
		Node(int elem) : elem(elem), next(NULL), prev(NULL)
		{}
};

// Linkedlist for the list of guests and list of bookings
class LinkedList {
	private:
		Node* head;
		Node* tail;
	public:
		LinkedList (); 
		~LinkedList (); 
		bool empty() const; 
		void addBefore(Node *ptr, const int& elem);	 
		void addBack(const int& elem); 
		void remove(const int& e); // remove element
		void removeFront();
		void display() const; // display Guest elements
		void display_movies() const; // display Movie elements
		void dumpData(ofstream &file) const; // dump data into the file
		bool find(const int& e); // find if an element is in the list
};

// constructor 
LinkedList::LinkedList () {
	head = new Node;
	tail = new Node;
	head->next = tail;
	tail->prev = head;
	head->prev = NULL;
	tail->next = NULL;
}

// desctructor
LinkedList::~LinkedList () {
	while(!empty()) removeFront();
	delete head;
	delete tail;
}

bool LinkedList::empty() const {
	return head->next == tail;
}

void LinkedList::addBefore(Node *ptr, const int& elem) {
	Node *v = new Node(elem);
	v->next = ptr;
	v->prev = ptr->prev;
	ptr->prev = v;
	v->prev->next = v;
}

void LinkedList::addBack(const int& elem) {
	addBefore(tail, elem);
}

void LinkedList::removeFront() {
	if (!empty()) {
		Node* old = head->next; 
		head->next = old->next;
		old->next->prev = head; 
		delete old;
	}
	else
		throw runtime_error("List is empty");
}

void LinkedList::remove(const int& e) {
	Node* curr = head->next;
	while(curr->next != NULL) {
		// switch pointers of two adjacent nodes
		if (curr->elem == e) {
			curr->prev->next = curr->next;
			curr->next->prev = curr->prev;
			delete curr;
			break;
		}
		curr = curr->next;
	}
}

// check if element is in the list
bool LinkedList::find(const int& e) {
	Node* curr = head->next;
	while(curr->next != NULL) {
		if (curr->elem == e) {
			return 0;
		}
		curr = curr->next;
	}
	return -1;
}

// display the list of guests signed up for a movie
void LinkedList::display() const {
	Node *curr=head->next;

	if (curr->next == NULL)
		cout << "No guests";
	while (curr->next!=NULL) {
		print(curr->elem);
		curr=curr->next;
	};
	cout << endl;
}

// display the list of movies of a guest
void LinkedList::display_movies() const {
	Node *curr=head->next;

	if (curr->next == NULL)
		cout << "No bookings have been made";
	while (curr->next!=NULL) {
		print_movies(curr->elem);
		curr=curr->next;
	};
	cout << endl;
}

// dump linked list into the file
void LinkedList::dumpData(ofstream &file) const {
	Node* curr = head->next;
	while (curr->next != NULL) {
		file << curr->elem;
		if (curr->next != tail)
			file << ",";
		curr = curr->next;
		}
}


// parent class of Guest and Admin
class Person{
public:
	int guestID;
	string first_name;
	string last_name;
	string username;
	string password;
};

class Admin : public Person{
public:
	int adminID;
};

class Guest : public Person{
public:
	LinkedList list_of_bookings;
};

class MovieScreening{
public:
	int movieScreeningID;
	string movie_name;
	int number_guests;
	int capacity;
	string date;
	string time;
	string hall_name;
	LinkedList list_of_guests;
};

void user_listCommands() {
	cout<<"List of available Commands:"<<endl
		<<"viewAvailableMovieScreenings(1)		: View movie screenings available for screening. Display all the movie's information"<<endl
		<<"viewMovieScreeningsWithSeats(2)		: View movie screenings that are not full. Display all the movie's information"<<endl
		<<"bookASeat(3)                   		: Book a seat in a movie"<<endl
		<<"cancelBooking(4)              		: Cancel a booking in a movie"<<endl
		<<"help(5)                        		: Display the list of available commands"<<endl
		<<"quitProgram(6)                 		: Quit the Program"<<endl;
}

void admin_listCommands() {
	cout<<"List of available Commands:"<<endl
		<<"registerGuest(1)               		: Register guest"<<endl
		<<"addMovieScreening(2)           		: Add a new movie screening"<<endl
		<<"deleteMovieScreening(3)        		: Delete movie screening"<<endl
		<<"updateMovieScreening(4)        		: Update movie screening"<<endl
		<<"viewMovieScreeningDetails(5)   		: View the movie screening details"<<endl
		<<"viewListOfGuests(6)            		: View the list of guests"<<endl
		<<"viewListOfBookings(7)          		: View the list of bookings"<<endl
		<<"viewAvailableMovieScreenings(8)		: View movie screenings available for screening. Display all the movie's information"<<endl
		<<"viewMovieScreeningsWithSeats(9)		: View movie screenings that are not full. Display all the movie's information"<<endl
		<<"help(10)                       		: Display the list of available commands"<<endl
		<<"quitProgram(11)                		: Quit the Program"<<endl;
}


Guest li_guests[10000];
Admin li_admins[10000];
MovieScreening li_movies[10000];

// print the first name and last name of the guest when called in the linked list function
void print (int ID) {
	cout << li_guests[ID].first_name << " " << li_guests[ID].last_name << endl;
}

// print the movie name and date when called in the linked list function
void print_movies (int ID) {
	cout << li_movies[ID].movie_name << " " << li_movies[ID].date << endl;
}

// sort the elements of vectors
void sort(vector <int> &list) {
	int temp;

	for (int i = 0; i < list.size(); i++) {		
		for (int j = i + 1; j < list.size(); j++) {
			if (list[i] > list[j]) {
				temp = list[i];
				list[i] = list[j];
				list[j] = temp;
			}
		}
	}
}


void quitProgram(){
	sort(li_ad_ID); 
	sort(li_gu_ID);
	sort(li_mo_ID);

	// save data into admins.txt
	ofstream file_1("Admins.txt");
	if (file_1.is_open()){
		file_1 << "admin_id,first_name,last_name,username,password";
		for (int i = 0, n = li_ad_ID.size(); i < n; i++) {
			file_1 	<< '\n' << li_ad_ID[i] << ','
					<< li_admins[li_ad_ID[i]].first_name << ','
					<< li_admins[li_ad_ID[i]].last_name << ','
					<< li_admins[li_ad_ID[i]].username << ','
					<< li_admins[li_ad_ID[i]].password;
		}
		file_1.close();
	}
	else cout << "Can't open Admins.txt" << endl;

	// save data into guests.txt
	ofstream file_2("Guests.txt");
	if (file_2.is_open()){
		file_2 << "guest_id,first_name,last_name,username,password,list_of_bookings";
		for (int i = 0, n = li_gu_ID.size(); i < n; i++) {
			file_2 	<< '\n' << li_guests[li_gu_ID[i]].guestID << ','
				 	<< li_guests[li_gu_ID[i]].first_name << ','
				 	<< li_guests[li_gu_ID[i]].last_name << ','
				 	<< li_guests[li_gu_ID[i]].username << ','
				 	<< li_guests[li_gu_ID[i]].password << ','
				 	<< "[";
			// dump the linked list
			li_guests[li_gu_ID[i]].list_of_bookings.dumpData(file_2);
			file_2 << "]";
		}
			file_2.close();
	}
	else cout << "Can't open Guests.txt" << endl;

	// save data into moviescreenings.txt
	ofstream file_3("MovieScreenings.txt");
	if (file_3.is_open()){
		file_3 << "movie_screening_id,movie_name,number_of_guests,maximum_capacity,screening_date,screening_time,hall_name,list_of_guests";
		for (int i = 0, n = li_mo_ID.size(); i < n; i++) {
			file_3 	<< '\n' << li_movies[li_mo_ID[i]].movieScreeningID << ','
				 	<< li_movies[li_mo_ID[i]].movie_name << ','
				 	<< li_movies[li_mo_ID[i]].number_guests << ','
				 	<< li_movies[li_mo_ID[i]].capacity << ','
				 	<< li_movies[li_mo_ID[i]].date << ','
				 	<< li_movies[li_mo_ID[i]].time << ','
				 	<< li_movies[li_mo_ID[i]].hall_name << ','
				 	<< "[";
			// dump the linked list
			li_movies[li_mo_ID[i]].list_of_guests.dumpData(file_3);
			file_3 << "]";
		}
			file_3.close();
	}
	else cout << "Can't open " << "MovieScreenings.txt" << endl;
}


void bookASeat(int ID_guest) {
	int tmp_ID;
	cout << "Please provide a Movie ID: " << endl;
	cin >> tmp_ID;
	cin.ignore();

	// check if movie ID exists
	if (find(li_mo_ID.begin(), li_mo_ID.end(), tmp_ID) != li_mo_ID.end()) {
		if (li_movies[tmp_ID].number_guests < li_movies[tmp_ID].capacity) {
			li_movies[tmp_ID].list_of_guests.addBack(ID_guest); // add guest to the list
			li_movies[tmp_ID].number_guests += 1;
			li_guests[ID_guest].list_of_bookings.addBack(tmp_ID); // add movie to the list
			cout << "You have successfully booked a seat to the " << li_movies[tmp_ID].movie_name << endl;
		}
		else cout << "Sorry there are no seats left for this movie." << endl;
	}
	else cout << "No movie with this ID is found" << endl;
	cout << "\n\n\n";
}

void cancelBooking(int ID_guest) {
	int tmp_ID;
	cout << "Please provide a Movie ID: " << endl;
	cin >> tmp_ID;
	cin.ignore();

	// check if movies ID exists
	if (find(li_mo_ID.begin(), li_mo_ID.end(), tmp_ID) != li_mo_ID.end()) {
		if (li_guests[ID_guest].list_of_bookings.find(tmp_ID) == 0) {
			li_movies[tmp_ID].list_of_guests.remove(ID_guest);
			li_movies[tmp_ID].number_guests -= 1;
			li_guests[ID_guest].list_of_bookings.remove(tmp_ID);
			cout << "You have successfully canceled booking from the " << li_movies[tmp_ID].movie_name << endl;
		}
		else cout << "You are not seated at this movie." << endl;
	}
	else cout << "No movie with this ID is found" << endl;
	cout << "\n\n\n";
}


void viewListOfGuests(){
	int tmp_ID;
	cout << "Please enter Movie ID:" << endl;
	cin >> tmp_ID;
	cin.ignore();

	if (find(li_mo_ID.begin(), li_mo_ID.end(), tmp_ID) != li_mo_ID.end()) {
		cout << "List of Guests: " << endl;
		li_movies[tmp_ID].list_of_guests.display();
	}
	else cout << "No movie with this ID is found" << endl;
	cout << "\n\n\n";
}

void viewListOfBookings(){
	int tmp_ID;
	cout << "Please enter Guest ID:" << endl;
	cin >> tmp_ID;
	cin.ignore();

	if (find(li_gu_ID.begin(), li_gu_ID.end(), tmp_ID) != li_gu_ID.end()) {
		cout << "List of Movies: " << endl;
		li_guests[tmp_ID].list_of_bookings.display_movies();
	}
	else cout << "No guest with this ID is found" << endl;
	cout << "\n\n\n";
}


void addMovieScreening(){ 
	int tmp_ID;
	
	// keep asking for valid ID
	do {
		cout << "Please enter a movie ID that doesn't exists yet: " << endl;
		cin >> tmp_ID;
	} while (find(li_mo_ID.begin(), li_mo_ID.end(), tmp_ID) != li_mo_ID.end());
	li_movies[tmp_ID].movieScreeningID = tmp_ID;
	cout << "Please provide movie name: " << endl;
	cin >> li_movies[tmp_ID].movie_name;

	// keep asking for valid capacity
	do {
		cout << "Please provide capacity(more than 0): " << endl;
		cin >> li_movies[tmp_ID].capacity;
	} while (li_movies[tmp_ID].capacity < 1);
	cout << "Please provide date in the following format dd-mm-yy: " << endl;
	cin >> li_movies[tmp_ID].date;
	cout << "Please provide time in the following format hh:mm: " << endl;
	cin >> li_movies[tmp_ID].time;
	cout << "Please provide hall name: " << endl;
	cin >> li_movies[tmp_ID].hall_name;
	cin.ignore();
	li_movies[tmp_ID].number_guests = 0;
	li_mo_ID.push_back(tmp_ID);

	cout << "Movie " << li_movies[tmp_ID].movie_name << " has been successfully registered!" << endl;
	cout << "\n\n\n";
}

void updateMovieScreening(){
	int tmp_ID;
	cout << "Please provide movie ID: " << endl;
	cin >> tmp_ID;
	cin.ignore();

	if (find(li_mo_ID.begin(), li_mo_ID.end(), tmp_ID) != li_mo_ID.end()) {
		cout << "Please provide new date in the following format dd-mm-yy: " << endl;
		cin >> li_movies[tmp_ID].date;
		cout << "Please provide new time in the following format hh:mm: " << endl;
		cin >> li_movies[tmp_ID].time;
		cout << "Please provide new hall name: " << endl;
		cin >> li_movies[tmp_ID].hall_name;
		cin.ignore();
		cout << "The movie has been successfully updated." << '\n'
		 << "ID: " << li_movies[tmp_ID].movieScreeningID << "\n"
		 << "Date: " << li_movies[tmp_ID].date << "\n"
		 << "Time: " << li_movies[tmp_ID].time << "\n"
		 << "Location: " << li_movies[tmp_ID].hall_name << endl;
	}
	else cout << "No movie with this ID is found" << endl;
	cout << "\n\n\n";
}

void deleteMovieScreening(){
	int tmp_ID;

	cout << "Please provide movie ID: " << endl;
	cin >> tmp_ID;
	cin.ignore();

	if (find(li_mo_ID.begin(), li_mo_ID.end(), tmp_ID) != li_mo_ID.end()) { 
		li_mo_ID.erase(remove(li_mo_ID.begin(), li_mo_ID.end(), tmp_ID), li_mo_ID.end()); // delete the movie from the vector of movie ID's
		for (int i = 0, n = li_gu_ID.size(); i < n; i++) {
			li_guests[li_gu_ID[i]].list_of_bookings.remove(tmp_ID); // remove the ID from the list of bookings of all guests
		}
		cout << "The movie with ID: " << tmp_ID << " has been successfully deleted!" << endl;
	}
	else cout << "No movie with this ID is found" << endl;
	cout << "\n\n\n";
}

void viewAvailableMovieScreenings() {
	sort(li_mo_ID);

	for (int i = 0; i < li_mo_ID.size(); i++) {
		cout << li_movies[li_mo_ID[i]].movieScreeningID << " "
			 << li_movies[li_mo_ID[i]].movie_name << " "
			 << li_movies[li_mo_ID[i]].number_guests << " "
			 << li_movies[li_mo_ID[i]].capacity << " "
			 << li_movies[li_mo_ID[i]].date << " "
			 << li_movies[li_mo_ID[i]].time << " "
			 << li_movies[li_mo_ID[i]].hall_name << "\n";
	}
	cout << "\n\n\n";
}


void viewMovieScreeningsWithSeats() {
	sort(li_mo_ID);

	for (int i = 0; i < li_mo_ID.size(); i++) {
		if (li_movies[li_mo_ID[i]].number_guests < li_movies[li_mo_ID[i]].capacity) {
			cout << li_movies[li_mo_ID[i]].movieScreeningID << " "
				 << li_movies[li_mo_ID[i]].movie_name << " "
				 << li_movies[li_mo_ID[i]].number_guests << " "
				 << li_movies[li_mo_ID[i]].capacity << " "
				 << li_movies[li_mo_ID[i]].date << " "
				 << li_movies[li_mo_ID[i]].time << " "
				 << li_movies[li_mo_ID[i]].hall_name << "\n";
				}
			}
	cout << "\n\n\n";
}

void viewMovieScreeningDetails() {
	int tmp_ID;
	cout << "Please enter the Movie ID" << endl;
	cin >> tmp_ID;
	cin.ignore();
	
	// check if the movie ID exists
	if (find(li_mo_ID.begin(), li_mo_ID.end(), tmp_ID) != li_mo_ID.end()) {
		cout << li_movies[tmp_ID].movieScreeningID << " "
				 << li_movies[tmp_ID].movie_name << " "
				 << li_movies[tmp_ID].number_guests << " "
				 << li_movies[tmp_ID].capacity << " "
				 << li_movies[tmp_ID].date << " "
				 << li_movies[tmp_ID].time << " "
				 << li_movies[tmp_ID].hall_name << "\n";
		}
	cout << "\n\n\n";
}

// convert the string to lowercase
string to_lowercase(string name) {
	int n = name.length();
	for (int i = 0; i < n; i++) {
		name[i] = char(tolower(name[i]));
	}
	return name;
}

string registerGuest(){
	srand(time(NULL));
	string guest_id, un, pw, first_name_1, last_name_1;
	int random, random_last;

	cout << "Please enter guest's first name and last name seperated by space" << endl;
	cin >> first_name_1 >> last_name_1;
	cin.ignore();
	
	// keep creating ID that doesn't exist yet
	do {
		random = rand() % 10000;
	} while (find(li_gu_ID.begin(), li_gu_ID.end(), random) != li_gu_ID.end());
	
	// convert the ID to string with front zeroes if nessecary
	if (random < 10)
		guest_id = "000" + to_string(random);
	else if (random < 100)
		guest_id = "00" + to_string(random);
	else if (random < 1000)
		guest_id = "0" + to_string(random);
	else
		guest_id = to_string(random);
	
	// create random ID for passwrord
	random_last = rand() % 10000;
	first_name_1 = to_lowercase(first_name_1);
	last_name_1 = to_lowercase(last_name_1);

	// create a password with 4 random numbers at the end
	if (random_last < 10)
		li_guests[random].password = last_name_1 + "000" + to_string(random_last);
	else if (random_last < 100)
		li_guests[random].password = last_name_1 + "00" + to_string(random_last);
	else if (random_last < 1000)
		li_guests[random].password = last_name_1 + "0" + to_string(random_last);
	else
		li_guests[random].password = last_name_1 + to_string(random_last);
	
	li_guests[random].username = first_name_1 + guest_id;
	li_guests[random].guestID = random;
	li_guests[random].first_name = char(toupper(first_name_1[0])) + first_name_1.substr(1);
	li_guests[random].last_name = char(toupper(last_name_1[0])) + last_name_1.substr(1);
	li_gu_ID.push_back(random); // add the ID to the vectors list

	cout << first_name_1 << " " << last_name_1 << " has been successfully registered!" << endl;
	cout << "\n\n\n";
	return li_guests[random].username;
}

// check if password and username are valid
bool login_check(string user, string username_1, string password_1) {
	cout << username_1 << password_1 << endl;
	if (user == "guest") {
		for (int i = 0; i < 10000; i++) {
			if (li_guests[i].username == username_1 && li_guests[i].password == password_1)
				return 0;
		}
	}
	else {
		for (int i = 0; i < 10000; i++) {
			if (li_admins[i].username == username_1 && li_admins[i].password == password_1)
				return 0;
			} 
	}
	return 1;
}

// convert the string of bookings and guests to LL
void str_to_linked_list(string s, LinkedList* L) {
	int n = s.length();
	int j = 0;
	int arr[n] = {0};
	
	// if it's not empty
	if (n != 2) {
		for(int i = 1; s[i] != '\0'; i++) {
			if (s[i] == ',' or s[i] == ']') {
				L->addBack(arr[j]); // add element to the LL
				j++;
			}
			else {
				arr[j] = arr[j] * 10 + (s[i] - 48); // convert the string to integer
			}
		}
	}
}

//load the data from the csv files
void loadData(Admin* li_admins, Guest* li_guests, MovieScreening* li_movies, string path_1, string path_2, string path_3) {
	int  ID_admin, ID_guest;
	ifstream file_1(path_1);
	if (file_1.is_open()){
		file_1.ignore(1000, '\n');
		string ID, FN, LN, UN, PW;
		while (file_1.good()) {
			getline(file_1, ID, ',');
			getline(file_1, FN, ',');
			getline(file_1, LN, ',');
			getline(file_1, UN, ',');
			getline(file_1, PW, '\n');
			
			ID_admin = stoi(ID);
			li_ad_ID.push_back(ID_admin); // add the ID to the vectors of ID's
			
			li_admins[ID_admin].adminID = ID_admin;
			li_admins[ID_admin].first_name = FN;
			li_admins[ID_admin].last_name = LN;
			li_admins[ID_admin].username = UN;
			li_admins[ID_admin].password = PW;
		}
		file_1.close();
	}
	else
		cout << "Can't open " << path_1 << endl;
	ifstream file_2(path_2);
	if (file_2.is_open()){
		file_2.ignore(1000, '\n');
		string ID, FN, LN, UN, PW, LB;
		while (file_2.good()) {
			getline(file_2, ID, ',');
			getline(file_2, FN, ',');
			getline(file_2, LN, ',');
			getline(file_2, UN, ',');
			getline(file_2, PW, ',');
			getline(file_2, LB, '\n');
			
			ID_guest = stoi(ID);
			li_gu_ID.push_back(ID_guest); // add the ID to the vectors of ID's
			
			li_guests[ID_guest].guestID = ID_guest;
			li_guests[ID_guest].first_name = FN;
			li_guests[ID_guest].last_name = LN;
			li_guests[ID_guest].username = UN;
			li_guests[ID_guest].password = PW;
			str_to_linked_list(LB, &li_guests[ID_guest].list_of_bookings);
		}
		file_2.close();
	}
	else
		cout << "Can't open " << path_2 << endl;

	ifstream file_3(path_3);
	if (file_3.is_open()){
		file_3.ignore(1000, '\n');
		string ID, MN, NG, MC, SD, ST, HN, LG;
		int movie_ID;
		while (file_3.good()) {
			getline(file_3, ID, ',');
			getline(file_3, MN, ',');
			getline(file_3, NG, ',');
			getline(file_3, MC, ',');
			getline(file_3, SD, ',');
			getline(file_3, ST, ',');
			getline(file_3, HN, ',');
			getline(file_3, LG, '\n');
			
			movie_ID = stoi(ID);
			li_mo_ID.push_back(movie_ID); // add the ID to the vectors of ID's

			li_movies[movie_ID].movieScreeningID = movie_ID;
			li_movies[movie_ID].movie_name = MN;
			li_movies[movie_ID].number_guests = stoi(NG);
			li_movies[movie_ID].capacity = stoi(MC);
			li_movies[movie_ID].date = SD;
			li_movies[movie_ID].time = ST;
			li_movies[movie_ID].hall_name = HN;
			str_to_linked_list(LG, &li_movies[movie_ID].list_of_guests);
		}
		file_3.close();
	}
	else
		cout << "Can't open " << path_3 << endl;
}

// return guest ID that just registered or loged in
int find_guest_id(string user_name) {
	for (int i = 0, n = li_gu_ID.size(); i < n; i++) {
		if (li_guests[li_gu_ID[i]].username == user_name) {
			return li_gu_ID[i];
		}
	}
	return 0;
}

int main() {
	int ID_guest;
	string user, login, username, password, user_input, command, parameter, parameter_2;

	loadData(li_admins, li_guests, li_movies, "Admins.txt", "Guests.txt", "MovieScreenings.txt");
	cout << "Welcome! Please identify yourself either as admin or guest: " <<endl;
	cin >> user;
	cin.ignore();
	if (user == "guest") {

		// keep asking while guest doesn't input valid info
		do {
			cout << "register or login?" << endl;
			cin >> login;
		} while (login != "login" and login != "register");
		
		if (login == "login"){
			cout << "Please enter your username: " << endl;
			cin >> username;
			cin.ignore();
			cout << "Please enter your password: " << endl;
			cin >> password;
			cin.ignore();
			if (login_check(user, username, password) == 0)
				user_listCommands();
			else {
				cout << "No such user found, come back when you remember your info!" << endl;
				return 1;
			}
 		}
 		
 		if (login == "register") { 
 			username = registerGuest();
 			user_listCommands();
 		}
 		ID_guest = find_guest_id(username);
 		
 		do
		{
			cout<<">";
			getline(cin,command);
			system("clear");
			
			if(command=="viewAvailableMovieScreenings" or command == "1") 		viewAvailableMovieScreenings(), user_listCommands();
			else if(command=="viewMovieScreeningsWithSeats" or command == "2")	viewMovieScreeningsWithSeats(), user_listCommands();
			else if(command=="bookASeat" or command == "3")						bookASeat(ID_guest), user_listCommands();
			else if(command=="cancelBooking" or command == "4")					cancelBooking(ID_guest), user_listCommands();
			else if(command == "help" or command == "5")						user_listCommands();
			else if(command == "exit" or command == "quitProgram" or command == "quit" or command == "6")			{quitProgram(); break;}
			else 																cout<<"Invalid Commad !!"<<endl;
		}while(!(command == "exit" or command == "quitProgram" or command == "quit"));
	}

	if (user == "admin") {
		cout << "Please enter your username: " << endl;
		cin >> username;
		cin.ignore();
		cout << "Please enter your password: " << endl;
		cin >> password;
		cin.ignore();
		
		if (login_check(user, username, password) == 0)
			admin_listCommands();
		else {
			cout << "No such user found, come back when you remember your info!" << endl;
			return 1;
		}
		
		do
		{
			cout<<">";
			getline(cin,command);
			system("clear");

			if(command=="registerGuest" or command == "1") 						registerGuest(), admin_listCommands();
			else if(command=="addMovieScreening" or command == "2")				addMovieScreening(), admin_listCommands();
			else if(command=="deleteMovieScreening" or command == "3")			deleteMovieScreening(), admin_listCommands();
			else if(command=="updateMovieScreening" or command == "4")			updateMovieScreening(), admin_listCommands();
			else if(command=="viewMovieScreeningDetails" or command == "5")		viewMovieScreeningDetails(), admin_listCommands();
			else if(command=="viewListOfGuests" or command == "6")				viewListOfGuests(), admin_listCommands();
			else if(command=="viewListOfBookings" or command == "7")			viewListOfBookings(), admin_listCommands();
			else if(command=="viewAvailableMovieScreenings" or command == "8")	viewAvailableMovieScreenings(), admin_listCommands();
			else if(command=="viewMovieScreeningsWithSeats" or command == "9")	viewMovieScreeningsWithSeats(), admin_listCommands();
			else if(command == "help" or command == "10")						admin_listCommands();
			else if(command == "exit" or command == "quitProgram" or command == "quit" or command == "11")			{quitProgram(); break;}
			else 																cout<<"Invalid Commad !!"<<endl;
		} while(command!="exit");

	}
	else cout << "Get out of here, you don't belong here!" << endl;
	return 0;
}
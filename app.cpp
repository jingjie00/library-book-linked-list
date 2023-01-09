#define _CRT_SECURE_NO_WARNINGS
#include	<iostream>
#include	<cstdlib>
#include	<cstdio>
#include    <fstream>
#include    <string>
#include	<Windows.h>
#include	"List.h"
#include    "LibStudent.h"
#include    "LibBook.h"

using namespace std;

bool ReadFile(string, List*);
bool DeleteRecord(List*, char*);
bool Display(List*, int, int);
bool InsertBook(string, List*);
bool SearchStudent(List*, char* id, LibStudent&);
bool computeAndDisplayStatistics(List*);
bool printStuWithSameBook(List*, char*);
bool displayWarnedStudent(List*, List*, List*);
int menu();
bool checklist(List*, int);
int daycount(LibBook);//return total borrowed day of a book
bool bookcheck(LibBook, LibBook);
void idcheck(List*, char[30]);//change student name to id,if already id remain
bool displayprint(List*, ostream&, int);//question 5 sub function

int main() {
	//design
	system("color E0"); cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t      Welcome\n\t\t\t\t\t\t  Just a moment..\n\t\t\t\t\t      Checking the program...";
	Beep(2000, 100); Beep(1500, 120); Beep(2000, 80); Beep(1500, 100); Sleep(2000); system("cls"); system("color 70");

	//check
	ifstream file1, file2, file3, file4;
	char test[100], t1, t2;
	file1.open("student.txt"); file2.open("book.txt"); file3.open("Layout_menu.txt"); file4.open("Layout_thanks.txt");
	file3 >> t1; file4 >> t2;
	if (!file1 || !file2 || !file3 || !file4 || !(file1 >> test) || !(file2 >> test) || t1 != '*' || t2 != '*') {
		system("color E0"); Beep(2000, 100); Beep(1500, 120); Beep(2000, 80); Beep(1500, 100);
		cout << "\n\n\n\n\n\n\n\n\t\t\t\t\tSystem detected missing / unable \n\t\t\t\t     to open some necesarry file as below" << endl << endl;
		if (!file1) cout << "\t\t\t\t\t\tstudent.txt" << endl;
		if (!file2) cout << "\t\t\t\t\t\tbook.txt" << endl;
		if (!file3) cout << "\t\t\t\t\t\tLayout_menu.txt" << endl;
		if (!file4) cout << "\t\t\t\t\t\tLayout_thanks.txt" << endl;
		else cout << "Other abnormal situation occured. Please contact 011-3810 0852 for help" << endl;//cause by system error or compiler error. Normally would no happen
		cout << "\n\n\t\t\t\t Please included it for program able to run.\n\t\t\t\t  The program will terminated after 10 second...    " << endl << endl;
		Sleep(10000);
		return 0;
	}
	else {
		file1.close(); file2.close(); file3.close(); file4.close();
	}

	string line;
	int choice, source, detail;
	char  idname[30], callNum[20], input[100], input2[100];
	bool error = true;
	List *allstudent = new List, *type1, *type2;
	LibStudent output, stu;
	ostream& screen = cout;
	ifstream file;

	do {
		choice = menu();//here started //Question 9
		switch (choice) {
		case 1://Question1
			cout << "\n\nREAD FILE\n\n";
			cout << "*Duplicate student: System will update the latest student detail(exp: course, phone number, etc) with the latest getted record" << endl;
			cout << "*Kindly procced to <4> in menu to get the latest updated book record. Please do every after this step" << endl << endl;//We do not update automatically, as some circumstances we would not need procced to this step
			if (ReadFile("student.txt", allstudent)) //function start here
				cout << "\n\nAll students in text file which not duplicate(If duplicate will be update the detail with latest one) is inserted(updated) successfully to student list.\n\nCurrenly list having total of " << allstudent->count << " records \n\n";
			else
				cout << "\n\nFailure to read students' information\n\nCurrenly list having total of " << allstudent->count << " records \n\n";
			break;
		case 2://Question2
			if (!checklist(allstudent, 0))//check and get student record if does not exist
				cout << "\n\nFailure to read students' information\n\nCurrenly list having total of " << allstudent->count << " records \n\n";
			cout << "\n\nDELETE RECORD\n\n";
			cout << "Please enter the id or name \nof the student that you want to delete its record\n (Or enter '0' to back to menu):";
			cin.ignore(); cin.getline(idname, 30, '\n');
			if (strcmp(idname, "0") == 0)//enter 0 to return menu
				break;
			system("cls"); cout << "\n\nDELETE RECORD\n\n";
			if (DeleteRecord(allstudent, idname)) //function start here
				cout << "The student record shown above have been successfully deleted.\n\n";
			else
				cout << "The student record cannot be found in the record.\n\n";
			break;
		case 3://Question3
			if (!checklist(allstudent, 0))//check and get student record if does not exist
				cout << "\n\nFailure to read students' information\n\nCurrenly list having total of " << allstudent->count << " records \n\n";
			cout << "\n\nSEARCH STUDENT\n\n";
			cout << "Please enter the id or name \nof the student that you want to search its record\n (Or enter '0' to back to menu):";
			cin.ignore(); cin.getline(idname, 30, '\n');
			if (strcmp(idname, "0") == 0)//enter 0 to return menu
				break;
			if (SearchStudent(allstudent, idname, stu)) //function start here
				stu.print(screen);
			else
				cout << "The student " << idname << " cannot be found in the record.\n\n";
			break;
		case 4://Question4
			if (!checklist(allstudent, 0))//check and get student record if does not exist
				cout << "\n\nFailure to read students' information\n\nCurrenly list having total of " << allstudent->count << " records \n\n";
			cout << "\n\nINSERT BOOK\n\n";
			cout << "*No related student: System will create a new student if no related record is found" << endl;
			cout << "*Duplicate book: System will update the latest book detail(exp: author, publisher, etc) with the latest getted record" << endl;
			cout << "*Total author: Total author is only 10. System will stop record other author if more than 10" << endl;
			cout << "*Total book: Total book for a student is only 15. System will stop recieve if exceed" << endl << endl;
			if (InsertBook("book.txt", allstudent)) //function start here
				cout << "\nAll Books in text file which not duplicate(If duplicate will be update the detail with latest one) is inserted(updated) successfully to student list.\n\n";
			else
				cout << "\nError occur in text file. Only some Insertion to student list may succeed.\n\n";
			break;
		case 5://Question5
			cout << "\n\nDISPLAY OUTPUT\n\n";
			do {
				if (error == false)
					cout << "\nInvalid input!!!Please try again\n\n";
				cout << "Where do you want to display the output (0 - back to menu/ 1 - File / 2 - Screen): " << endl;
				cin >> input;
				if (strlen(input) < 2 && input[0] >= '0' && input[0] <= '2') {
					source = input[0] - '0';//minus the ascii value of 0 to get the number of that character represent like ((int)input[0])-((int)'0')
					if (source == 0)//enter 0 to return menu
						break;
					cout << "Do you want to display book list for every student(0 - back to menu/ 1 - YES / 2 - NO): " << endl;
					cin >> input2;
					if (strlen(input2) < 2 && input2[0] >= '0' && input2[0] <= '2') {
						detail = input2[0] - '0';//minus the ascii value of 0 to get the number of that character represent like ((int)input2[0])-((int)'0')
						if (detail == 0)//enter 0 to return menu
							break;
						if (!Display(allstudent, source, detail)) {//function start here
							cout << "Error occur.Return to menu." << endl;
							break;
						}
					}else error = false;
				}else error = false;
			} while (!error);
			break;
		case 6://Question6
			cout << "\n\nCOMPUTE AND DISPLAY STATISTICS\n\n*UK=Unknown course\n";
			if (!computeAndDisplayStatistics(allstudent))
				cout << "\n\nThe list is empty\nPlease choose <?> in menu\n <1>-Read file\n And\n <4>-Insert book\nBefore performing this option\n\n";
			break;
		case 7://Question7
			cout << "\n\nSTUDENT WITH SAME BOOK\n\n";
			cout << "Please enter the call number of the book to show the student who borrowed that book (enter 0 to return menu):" << endl;
			cin >> callNum;
			if (strcmp(callNum, "0") == 0)//enter 0 to return menu
				break;
			if (!printStuWithSameBook(allstudent, callNum)) //function start here
				cout << "\n\nThe list is empty\nPlease choose <?> in menu\n <1>-Read file\n And\n <4>-Insert book\nBefore performing this option\n\n";
			break;
		case 8://Question8
			type1 = new List; type2 = new List;
			cout << "\n\nDISPLAY WARNED STUDENT\n\n";
			cout << "Type1 misdemeanor: If a student has more than 2 books that are overdue for more than 10 days." << endl;
			cout << "Type2 misdemeanor : If the total fine for a student is more than RM50.00 and every book in the students book list are overdue." << endl << endl;
			if (displayWarnedStudent(allstudent, type1, type2)) { //function start here
				if (type1->empty())
					cout << "\nNo student is violated the rules of type 1 misdemeanor...\n\n";
				else {
					cout << "Total student(s) who violated the rules of type 1 misdemeanor and being warned is " << type1->count << " people and is being shown as below:";
					for (int i = 1; i <= type1->size(); i++) {
						if (!type1->get(i, output))
							cout << "\n\nFailure to get student's information...\n";
						output.print(screen);
						for (int j = 0; j < output.totalbook; j++)
							output.book[j].print(screen);
						cout << "\n***************************************************************" << endl;
					}
				}
				if (type2->empty())
					cout << "\nNo student is violated the rules of type 2 misdemeanor...\n\n";
				else {
					cout << "Total student(s) who violated the rules of type 2 misdemeanor and being warned is " << type2->count << " people and is being shown as below:";
					for (int i = 1; i <= type2->size(); i++) {
						if (!type2->get(i, output))
							cout << "\n\nFailure to get student's information...\n";
						output.print(screen);
						for (int j = 0; j < output.totalbook; j++)
							output.book[j].print(screen);
						cout << "\n***************************************************************" << endl;
					}
				}
			}
			else
				cout << "\n\nThe list is empty\nPlease choose <?> in menu\n <1>-Read file\n And\n <4>-Insert book\nBefore performing this option\n\n";
			delete type1; delete type2; type1 = NULL; type2 = NULL;//free it
			break;
		case 9:
			//design
			file.open("Layout_thanks.txt");
			if (file.is_open())
				while (!file.eof()) {
					getline(file, line);
					cout << line << endl;
				}
			file.close();
			cout << "                    Contact us if have any enquiry" << endl << "                  ";
			system("color E0"); Beep(2000, 100); Beep(1500, 120); Beep(2000, 80); Beep(1500, 100);
			break;
		default:
			cout << "\n\nInvalid input!!Please try again\n\n";
		}
		system("pause");
	} while (choice != 9);
	return 0;
}

//Question 1
bool ReadFile(string filename, List* list)
{
	ifstream file(filename);
	LibStudent tempstudent, check;
	char temp[30];
	if (!file.is_open() || file.eof()) {//check if the file is not opening or the file is empty
		cout << "Failure to read file\n";
		return false;
	}

	//read from the file
	while (!file.eof())
		if (file >> temp >> temp >> temp >> tempstudent.id) { //ensure no format error in txt file
			if (!((file >> temp >> temp) && file.ignore() && file.getline(tempstudent.name, 30) && (file >> temp >> temp >> tempstudent.course >> temp >> temp >> temp >> tempstudent.phone_no)))
				return false; //ensure no format error in txt file
			for (int j = 1; j <= list->size(); j++) {
				if (!list->get(j, check))return false;
				if (strcmp(tempstudent.id, check.id) == 0) {//student id treated as primary key
					if (!list->remove(j)) return false;
					cout << "Duplicate Student found which name: " << tempstudent.name << " with id : " << tempstudent.id << " updated with the latest one." << endl;
					break;
				}
			}
			if (!list->insert(tempstudent)) return false;
			cout << "Student detail with id: " << tempstudent.id << " successfully inserted (or updated) in the list." << endl << endl;
		}
		else if (tempstudent.id[0] != NULL)
			return false;
	file.close();
	return true;
}

//Sub function for question 2 and question 3
int Search(List* list, char* id)
{
	idcheck(list, id);//idname changed to id
	LibStudent tempstudent;
	for (int position = 0; list->get(position, tempstudent); position++)
		if (strcmp(tempstudent.id, id) == 0)//use id to check
			return position;
	return 0;
}

// Sub function for question 2 and question 3
void idcheck(List* list, char check[30]) //convert name to id
{
	LibStudent temp;
	int record[100], r = 1;
	for (int i = 1; i <= list->size(); i++) {
		if (!list->get(i, temp))return;
		if (strcmp(check, temp.id) == 0)//if id match, save into record 1
			record[r++] = i;
		else if (strcmp(check, temp.name) == 0)//if name match, save into record 2
			record[r++] = i;
	}
	int choose = 1;//NO related is found
	if (r == 1)
		return;
	else if (r != 2) { //if have more than 1 record
		cout << "Following list are related to your search" << endl;
		for (int j = 1; j < r; j++) {
			cout << "Student: " << j << endl;//print all related student
			if (!list->get(record[j], temp))return;
			temp.print(cout); cout << endl << endl;
		}
		do {
			choose = 0;
			char cchoose[100];
			cout << "Please select the student who want to be take action:" << endl;//to select a student from all the related result searched
			cin >> cchoose;
			for (int i = 0; i < strlen(cchoose); i++)
				if (!(int(cchoose[i]) >= 48 && int(cchoose[i] <= 57))) {//ascii method to validate
					choose = 0;
					break;
				}
				else
					choose = choose + int(cchoose[i]) - 48;
		} while (choose < r && choose >2);//quit the loop is error checking is pass
	}
	//if only 1 record found will straight away proceed here. else it will proceed the else if program
	if (!list->get(record[choose], temp))return;
	strcpy(check, temp.id);//give back id(used in other function)
	return;
}

//Question 2
bool DeleteRecord(List* list, char* id) {
	idcheck(list, id);//idname changed to id
	int position = Search(list, id);
	if (position >= 1) {//show first before delete, if vice versa the node is less one and the display item is no accurate
		LibStudent temp;
		if (!list->get(position, temp))return false;
		temp.print(cout);
	}
	if (list->remove(position) && position >= 1)
		return true;
	return false;
}

//Question 3
bool SearchStudent(List* list, char* id, LibStudent& stu)
{
	int position = Search(list, id);
	if (list->get(position, stu) && position > 0)
		return true;
	return false;
}

//Question 4
bool InsertBook(string filename, List* list) //***The author cannot be saved large than 9 because it will overflow the checking in for loop which in function print() in LibBook.cpp when launched in question 5
{
	ifstream file(filename);
	if (!file.is_open() || file.eof()) {//check if the file is not opening or the file is empty
		cout << "Failure to read file\n";
		return false;
	}
	char id[1000];
	while (!file.eof())
		if (file >> id && id[9] != NULL) { //ensure no format error in txt file
			LibBook book;
			LibStudent check, addon;
			char temp[100], author[1000], authtemp[100];
			//set book author to null
			for (int p = 0; p < 1000; p++)
				author[p] = NULL;//all author name

			//keyin 
			if (!(file >> author >> book.title >> book.publisher >> book.ISBN >> book.yearPublished >> book.callNum >> book.borrow.day >> temp[1]
				>> book.borrow.month >> temp[1] >> book.borrow.year >> book.due.day >> temp[1] >> book.due.month >> temp[1] >> book.due.year))
				return false;  //ensure no format error in txt file

			//initialise
			for (int p = 0; p < 100; p++)
				authtemp[p] = NULL;

			//modify the data to the correct format
			int m = 0, n = 0;
			for (int j = 0; author[j] != NULL; j++)
				if (author[j] == '/') {
					book.author[m] = new char[100];
					strcpy(book.author[m], authtemp);
					for (int p = 0; p < 100; p++)
						authtemp[p] = NULL;
					n = 0;
					m++;//updated to prepare inserting the next author for the same book
					if (m == 9) { //already 9 people (prepare for 10th input)
						cout << "Book with call num: " << book.callNum << " exceed the maximum number of author." << endl << "First 9 author is saved and other is dropped." << endl << endl;
						break;
					}//only 9 author can be saved, if not the program will be overflow when selected question 5. 
				}// As the for loop terminate condition is detect NULL. If 10author is entered then NULL will not detected and cause overflow.
				else if (author[j] == '_')
					authtemp[n++] = ' ';
				else
					authtemp[n++] = author[j];

			//last author is key-ined, if not 9 people
			if (m != 9) {
				book.author[m] = new char[100];
				strcpy(book.author[m], authtemp);
			}
			for (int j = 0; book.title[j] != NULL; j++)
				if (book.title[j] == '_')//remove underscore
					book.title[j] = ' ';
			for (int j = 0; book.publisher[j] != NULL; j++)
				if (book.publisher[j] == '_')//remove underscore
					book.publisher[j] = ' ';

			//count money
			book.fine = double(daycount(book)) * 0.50;

			//update fine
			for (int m = 1; m <= list->size(); m++) {
				if (!list->get(m, check))return false;
				if (strcmp(id, check.id) == 0) {
					//We use call num and date of borrow as primary key.
					//There be a possibility that the book is borrowed and be borrow again.
					//The text file detail does not provide the condition(return ald) of book (is it returned by student?)

					//Duplicate check
					bool duplicateflag = false;
					for (int k = 0; k < check.totalbook; k++)
						if (bookcheck(check.book[k], book)) {
							cout << "Duplicate record found on the book with call num: " << book.callNum << " by student with id : " << id << ", Borrow date: ";
							book.borrow.print(cout); cout << endl;
							check.book[k] = book;//need increament
							if (!check.calculateTotalFine())return false;
							if (!list->set(m, check))return false;
							duplicateflag = true;
							break;
						}
					if (duplicateflag == true)
						break;
					//Book exceed check
					if (check.totalbook == 15) {
						cout << "Book with call num: " << book.callNum << " cannot be inserted.\nTotal book can be inserted to the student with id : " << id << " exceeded.\nNo insert action will be done" << endl << endl;
						break;
					}
					check.book[check.totalbook++] = book;//need increament
					if (!check.calculateTotalFine())return false;
					if (!list->set(m, check))return false;
					break;
				}
				else if (m == list->size()) { //cannot find any student related
					strcpy(addon.id, id);//create new record if there is a book borrowed by a student who not in student.txt
					cout << "ID: " << id << " cannot found in the list. Creating a new student" << endl;
					addon.book[addon.totalbook++] = book;//need increment after this line
					if (!addon.calculateTotalFine())return false;
					if (!list->insert(m + 1, addon))return false;
					break;
				}
			}
			cout << "Book with call num : " << book.callNum << " is successfully inserted(or updated) to student with id : " << id << endl << endl;
		}
		else if (id[0] != NULL)//if is null mean empty of file just extra line, if not null mean error occur in txt
			return false;
	file.close();
	return true;
}

//Sub function for Question 4
bool bookcheck(LibBook book1, LibBook book2)
{
	if (strcmp(book1.callNum, book2.callNum) == 0
		&& book1.borrow.day == book2.borrow.day && book1.borrow.month == book2.borrow.month && book1.borrow.year == book2.borrow.year
		&& book1.due.day == book2.due.day && book1.due.month == book2.due.month && book1.borrow.year == book2.due.year) //if date and call num is same, mean repeated
		return true;
	else
		return false;
}

//Sub function for question 4 and question 6
int daycount(LibBook book)
{
	int day = 29, month = 3, year = 2020;
	int totalday = 0;
	//loop to count how many day, loop until the due date to current date
	for (totalday = 0; book.due.year < year || (book.due.year == year && book.due.month < month) || (book.due.year == year && book.due.month == month && book.due.day < day); book.due.day++)
	{
		//each row of "if" indicate total day of the month is excceed and increase month
		if (((book.due.month == 1 || book.due.month == 3 || book.due.month == 5 || book.due.month == 7 || book.due.month == 8 || book.due.month == 10 || book.due.month == 12) && book.due.day == 32)
			|| ((book.due.month == 4 || book.due.month == 6 || book.due.month == 9 || book.due.month == 11) && book.due.day == 31)
			|| (book.due.month == 2 && ((book.due.year % 4 == 0 && book.due.year % 100 != 0) || (book.due.year % 4 == 0 && book.due.year % 400 == 0)) && book.due.day == 30)
			|| (book.due.month == 2 && ((book.due.year % 4 == 0 && book.due.year % 100 == 0) || book.due.year % 4 != 0) && book.due.day == 29)
			) {
			book.due.day = 1;
			book.due.month++;
		}
		//if a year exceed 12 month, set month to 1 and increase 1 to the year
		if (book.due.month == 13) {
			book.due.month = 1;
			book.due.year++;
		}
		totalday++;
	}
	return totalday;
}

//Question 5
bool Display(List* list, int source, int detail)
{
	ofstream file;
	string outputfile;
	if (detail == 1) {//check the student and book list before printing and extract necessary info only
		if (!checklist(list, 1)) {
			cout << "\n\nFailure to read student and its book information\n\nCurrenly list having total of " << list->count << " records \n\n";
			return false;
		}
	}
	else {//detail==2
		if (!checklist(list, 0)) {
			cout << "\n\nFailure to read students' information\n\nCurrenly list having total of " << list->count << " records \n\n";
			return false;
		}
	}

	if (source == 1) {
		if (detail == 1)//print all detail
			outputfile = "student_booklist.txt";
		else if (detail == 2)// print partial
			outputfile = "student_info.txt";

		file.open(outputfile);
		if (!displayprint(list, file, detail)) return false;
		cout << "\n\nSuccessfully display output to " << outputfile << endl;
		file.close();
	}
	else
		if (!displayprint(list, cout, detail)) return false;
	return true;
}

//question5 sub function
bool displayprint(List* list, ostream& outt, int detail)
{
	LibStudent stu;
	outt << "\n**********************************************************************************" << endl;
	for (int i = 1; i <= list->size(); i++) {
		if (!list->get(i, stu))return false;
		outt << "\nSTUDENT " << i;
		stu.print(outt);

		if (detail == 1) {//print detail if choosed
			outt << "\nBOOK LIST:\n";
			for (int j = 0; j < stu.totalbook; j++) {
				outt << "\nBook " << j + 1;
				stu.book[j].print(outt);
			}
			if (stu.totalbook == 0)
				outt << "No book record found." << endl;
		}
		outt << "\n**********************************************************************************" << endl;
	}
	return true;
}

//Question 6
bool computeAndDisplayStatistics(List* list)
{
	if (list->empty())return false;
	struct detail {
		char course[3] = "UK";//UK=unknown
		int numstu = 0, totalbook = 0, overduebook = 0;
		double totalfine = 0.00;
	}content[6];

	strcpy(content[0].course, "CS");
	strcpy(content[1].course, "IA");
	strcpy(content[2].course, "IB");
	strcpy(content[3].course, "CN");
	strcpy(content[4].course, "CT");//and one for unknown, didnt set here as default is already unknown

	for (int i = 1; i <= list->size(); i++) {
		LibStudent temp;
		int code;
		if (!list->get(i, temp)) return false;

		//label by number
		if (strcmp(temp.course, "CS") == 0) code = 0;
		else if (strcmp(temp.course, "IA") == 0) code = 1;
		else if (strcmp(temp.course, "IB") == 0) code = 2;
		else if (strcmp(temp.course, "CN") == 0) code = 3;
		else if (strcmp(temp.course, "CT") == 0) code = 4;
		else code = 5;

		//compute the statistics
		content[code].numstu++;
		content[code].totalbook += temp.totalbook;
		for (int j = 0; j < temp.totalbook; j++)
			if (daycount(temp.book[j]) > 0)
			{
				content[code].overduebook++;
				temp.book[j].fine = double(daycount(temp.book[j])) * 0.5;
				content[code].totalfine += temp.book[j].fine;
				if (!temp.calculateTotalFine())return false;
				if (!list->set(i, temp))return false;
			}
	}
	cout << "Course\tNumber of Student\tTotal Books Borrowed\tTotal Overdue Books\tTotal Overdue Fine(RM)" << endl;
	//add on the data into the struct array
	for (int i = 0; i < 6; i++)
		cout << content[i].course << "\t" << content[i].numstu << "\t\t\t" << content[i].totalbook << "\t\t\t" << content[i].overduebook << "\t\t\t" << content[i].totalfine << endl;
	return true;
}

//Question 7
bool printStuWithSameBook(List* list, char* callNum)
{
	if (list->empty())
		return false;
	struct detail {
		char name[30] = " ", id[10] = " ", course[3] = " ", phone_no[10] = " ";
		Date borrow, due;
		void print() {
			cout << "Student ID : " << id << endl;
			cout << "Name : " << name << endl;
			cout << "Course : " << course << endl;
			cout << "Phone Number : " << phone_no << endl;
			cout << "Borrow Date : "; borrow.print(cout);
			cout << endl << "Due Date : "; due.print(cout); cout << endl << endl;
		}
	}student[20];
	int totalstudent = 0;
	for (int i = 1; i <= list->size(); i++) {
		LibStudent temp;
		if (!list->get(i, temp))return false;
		for (int j = 0; j < temp.totalbook; j++) {
			if (strcmp(callNum, temp.book[j].callNum) == 0) {
				strcpy(student[totalstudent].id, temp.id);
				strcpy(student[totalstudent].name, temp.name);
				strcpy(student[totalstudent].course, temp.course);
				strcpy(student[totalstudent].phone_no, temp.phone_no);
				student[totalstudent].borrow = temp.book[j].borrow;
				student[totalstudent].due = temp.book[j].due;
				totalstudent++;
			}
		}
	}
	if (totalstudent == 0)// incase the call num is not found in the record
		cout << "\n\nNo student have borrowed the book with call number of " << callNum << ".\n\n";
	else {
		cout << "\nThere are " << totalstudent << " students that borrow the book with call number " << callNum << " as shown below :" << endl << endl;
		for (int i = 0; i < totalstudent; i++)
			student[i].print();
	}
	return true;
}

//Question 8
bool displayWarnedStudent(List* list, List* type1, List* type2) {
	if (list->empty())
		return false;
	LibStudent student;
	int book[15], j;
	for (int i = 1; i <= list->size(); i++) {
		if (!list->get(i, student))return false;
		int overdueten = 0, overdue = 0;
		for (j = 0; student.book[j].yearPublished != 0; j++) {
			book[j] = daycount(student.book[j]);//record the number of book student overdue for 10 days 
			if (book[j] >= 10) {
				overdueten++;
			}
			if (book[j] > 0)//record the number of book student overdue 
				overdue++;
		}
		if (overdueten > 2)
			if (!type1->insert(student))return false;
		if (student.total_fine > 50 && student.totalbook == overdue)
			if (!type2->insert(student))return false;
	}
	return true;
}

//Sub function for question 9
bool checklist(List* list, int checkbook) {
	if (list->empty()) {//the list is empty then insert the student
		cout << "\nThe student record is empty....\nReading the student.txt file....\n\n";
		if (!ReadFile("student.txt", list))return false;
		cout << "Returning..." << endl; Sleep(4000); system("cls");
	}
	if (checkbook == 1) {//determine if check the insertion of books
		LibStudent stu;
		int totalbook = 0;
		for (int i = 1; i <= list->size(); i++) {
			if (!list->get(i, stu))return false;
			totalbook += stu.totalbook;
		}
		if (totalbook == 0) {//if there is no book in all students' record, read the book from file
			cout << "\nThe book record of students is empty....\nReading the book.txt file....\n\n";
			if (!InsertBook("book.txt", list))return false;
			cout << "Returning..." << endl; Sleep(4000); system("cls");
		}
	}
	return true;
}

//Question 9
int menu() {
	string line;
	int choice;
	char input[100];
	system("cls");
	ifstream file("Layout_menu.txt");
	if (file.is_open())
		while (!file.eof()) {
			getline(file, line);
			cout << line << endl;
		}
	cout << "Input------->";
	cin >> input;
	if (strlen(input) < 2 && input[0] >= '0' && input[0] <= '9')//check if the input entered only one character and is a digit
		choice = input[0] - '0';//minus the ascii value of 0 to get the number of that character represent like ((int)input[0])-((int)'0')
	else
		choice = 0;
	file.close();
	system("cls");

	return choice;
}

//If the program have other issue please contact us, 011-3810 0852 !
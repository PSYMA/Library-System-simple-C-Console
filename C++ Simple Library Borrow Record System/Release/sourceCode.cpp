#include <iostream>
#include <iomanip>
#include <string>

constexpr unsigned int studentSize = 20;
constexpr unsigned int bookSize = 15;
constexpr unsigned int MAX_TO_BORROW = 5;

enum class Status {
	AVAILABLE = 0, BORROWED = 1
};
struct StudentsRec { // 20 students
	int studentID;
	float totalPriceOfBorrowedBooks;
	int numberOfBorrowedBooks;
	std::string booksBorrowed[MAX_TO_BORROW];
	std::string name;
	std::string courseYrLv;
	StudentsRec() : studentID(0), booksBorrowed{ "" }, totalPriceOfBorrowedBooks(0.0f), numberOfBorrowedBooks(0), name(""), courseYrLv("") { }
};
struct BooksRec { // 15 books
	int bookID;
	int bookDuration;
	float bookPrice;
	Status bookStatus;
	std::string bookBorrowedDate;
	std::string bookReturnedDate;
	std::string bookTitle;
	std::string bookAuthor;
	BooksRec() : bookID(0), bookDuration(0), bookPrice(0.0f), bookBorrowedDate(""), bookStatus(Status::AVAILABLE),
		bookReturnedDate(""), bookTitle(""), bookAuthor("") { }
};

int studentCount = -1;
StudentsRec students[studentSize];
BooksRec books[bookSize];

void addStudentsInfo(const int& studentID, const std::string& name, const std::string& courseYrLv) {
	if (studentCount != -1) {
		for (int i = 0; i <= studentCount; i++) {
			if (students[i].studentID == studentID) {
				std::cout << "This ID already added\n";
				return;
			}
		}
	}
	studentCount++;
	students[studentCount].studentID = studentID;
	students[studentCount].name = name;
	students[studentCount].courseYrLv = courseYrLv;
}
void borrowBook(const int& studentID, const int* bookID, const int& countBorrowBooks, const std::string* borrowDate, float& totalPrice) {
	int j = 0;
	for (int i = 0; i <= studentCount; i++) {
		if (students[i].studentID == studentID) {
			students[i].numberOfBorrowedBooks += countBorrowBooks + 1;
			j = i;
			break;
		}
	}
	int k = 0;
	for (int i = 0; i < bookSize; i++) {
		if (books[i].bookID == bookID[k]) {
			students[j].totalPriceOfBorrowedBooks += books[i].bookPrice;
			totalPrice += books[i].bookPrice;
			books[i].bookBorrowedDate = borrowDate[k];
			books[i].bookReturnedDate = borrowDate[k];
			books[i].bookStatus = Status::BORROWED;
			k++;
			i = 0;
		}
	}

}
void returnBook(const int& studentID, const int& bookID) {
	bool x = false;
	std::string bookTitle;
	for (int i = 0; i <= studentCount; i++) {
		if (students[i].studentID == studentID) {
			for (int j = 0; j < bookSize; j++) {
				if (books[j].bookID == bookID) {
					bookTitle = books[j].bookTitle;
					for (int p = 0; p < students[i].numberOfBorrowedBooks; p++) {
						if (students[i].booksBorrowed[students[i].numberOfBorrowedBooks - 1] == bookTitle) {
							break;
						}
						else if (students[i].booksBorrowed[p] == bookTitle && x == false) {
							x = true;
						}
						else if (x) {
							students[i].booksBorrowed[p - 1] = students[i].booksBorrowed[p];
						}
					}
					books[j].bookStatus = Status::AVAILABLE;
					books[j].bookBorrowedDate = "";
					books[j].bookReturnedDate = "";
					students[i].totalPriceOfBorrowedBooks -= books[j].bookPrice;
					students[i].numberOfBorrowedBooks--;
					break;
				}
			}
			break;
		}
	}
}
void viewRecord(const int& studentID) {
	int k = 0;
	for (int i = 0; i <= studentCount; i++) {
		if (students[i].studentID == studentID) {
			std::cout << "Student ID: " << std::setw(40) << students[i].studentID << '\n'
				      << "Student Name: " << std::setw(40) << students[i].name << '\n'
				      << "Student CourseYrLv: " << std::setw(30) << students[i].courseYrLv << '\n'
				      << "Student #'s books borrowed: " << std::setw(20) << students[i].numberOfBorrowedBooks << '\n'
				      << "Student Total price of borrowed books: " << std::setw(10) << students[i].totalPriceOfBorrowedBooks << '\n'
					  << "\n\n\t\t >> Books borrowed << \n\n";
			for (int j = 0; j < bookSize; j++) {
				if (books[j].bookTitle == students[i].booksBorrowed[k]) {
					std::cout << "Book ID: " << std::setw(30) << books[j].bookID << '\n'
						<< "Book Title: " << std::setw(30) << books[j].bookTitle << '\n'
						<< "Book Author: " << std::setw(30) << books[j].bookAuthor << '\n'
						<< "Book Price: " << std::setw(30) << books[j].bookPrice << '\n'
						<< "Book Duration: " << std::setw(20) << books[j].bookDuration << '\n'
						<< "Book Borrowed Date: " << std::setw(20) << books[j].bookBorrowedDate << '\n'
						<< "Book Returned Date: " << std::setw(20) << books[j].bookReturnedDate  << " + " << books[j].bookDuration << " days" << '\n'
						<< "Book Status: " << std::setw(30);
						if (books[j].bookStatus == Status::AVAILABLE) {
							std::cout << "AVAILABLE\n";
						}
						else if (books[j].bookStatus == Status::BORROWED) {
							std::cout << "BORROWED\n";
						}
						k++;
						j = 0;
						std::cout << "--------------------------------------------------\n";
				}
				if (k == students[i].numberOfBorrowedBooks) {
					return;
				}
			}
			break;
		}
	}
}

void Initialise() {
	const char* bookAuthor[15];
	const char* bookTitle[15];
	bookAuthor[0] = "A. Abraham";   bookTitle[0] = "Statistics";
	bookAuthor[1] = "B. Bob";		bookTitle[1] = "Calculus I";
	bookAuthor[2] = "C. Cathyrine";	bookTitle[2] = "Calculus II";
	bookAuthor[3] = "D. Clyde";		bookTitle[3] = "Calculus III";
	bookAuthor[4] = "E. Mike";		bookTitle[4] = "Science";
	bookAuthor[5] = "F. George";	bookTitle[5] = "Algorithms";
	bookAuthor[6] = "G. William";	bookTitle[6] = "Probabilty";
	bookAuthor[7] = "H. Karl";		bookTitle[7] = "Topology";
	bookAuthor[8] = "I. Bryan";		bookTitle[8] = "Pre-Calculus";
	bookAuthor[9] = "J. Kobe";		bookTitle[9] = "Geometry";
	bookAuthor[10] = "K. Cynthia";	bookTitle[10] = "Linear Algebra";
	bookAuthor[11] = "L. Paul";		bookTitle[11] = "Algebra";
	bookAuthor[12] = "M. Pacquiao";	bookTitle[12] = "Basic Algebra";
	bookAuthor[13] = "N. Jacob";	bookTitle[13] = "Trigonometry";
	bookAuthor[14] = "O. Muhammad";	bookTitle[14] = "English";
	float price = 13.22f;
	for (int i = 0; i < bookSize; i++) {
		books[i].bookID = 100100 + (i + 1);
		books[i].bookDuration = i + 1;
		books[i].bookPrice = ((price * (i + 1)) / 2);
		books[i].bookStatus = Status::AVAILABLE;
		books[i].bookBorrowedDate = " ";
		books[i].bookReturnedDate = " ";
		books[i].bookAuthor = bookAuthor[i];
		books[i].bookTitle = bookTitle[i];
	}
}
void displayBooks() {
	std::cout << "Book ID" << std::setw(20)
		<< "Title" << std::setw(20)
		<< "Author" << std::setw(20)
		<< "Price" << std::setw(20)
		<< "Duration(Days)" << std::setw(20)
		<< "Status\n\n";
	for (int i = 0; i < bookSize; i++) {
		std::cout << books[i].bookID << std::setw(20)
			<< books[i].bookTitle << std::setw(20)
			<< books[i].bookAuthor << std::setw(20)
			<< books[i].bookPrice << std::setw(20)
			<< books[i].bookDuration << std::setw(20);
		if (books[i].bookStatus == Status::AVAILABLE) {
			std::cout << "AVAILABLE\n";
		}
		else {
			std::cout << "BORROWED\n";
		}
	}
}
void displayStudents() {
	std::cout << "ID Number" << std::setw(30)
		<< "Name" << std::setw(40)
		<< "CourseYrLv" << std::setw(40)
		<< '\n';
	for (int i = 0; i <= studentCount; i++) {
		std::cout << students[i].studentID << std::setw(40)
			<< students[i].name << std::setw(30)
			<< students[i].courseYrLv << std::setw(30)
			<< '\n';
	}
}
void displayBorrowedBooks(const int* bookID, const int& studentID, const bool& borrowOrNot, const int& numberOfBorrowedBooks) {
	if (borrowOrNot) {
		int k = numberOfBorrowedBooks;
		int p = 0;
		for (int i = 0; i <= studentCount; i++) {
			if (students[i].studentID == studentID){
				for (int j = 0; j < bookSize; j++) {
					if (books[j].bookID == bookID[p]) {
						students[i].booksBorrowed[k] = books[j].bookTitle;
						k++;
						p++;
						j = 0;
					}
				}
				break;
			}
		}
	}
	else {
		int j = 0;
		for (int i = 0; i < bookSize; i++) {
			if (books[i].bookID == bookID[j]) {
				std::cout << books[i].bookTitle << ", ";
				j++;
				i = 0;
			}
		}
	}
}
void payment(const float& totalPrice) {
	while (true) {
		float pay = 0.0f;
		std::cout << "Total: " << totalPrice << '\n';
		std::cout << "Enter amount: ";
		std::cin >> pay;
		if (pay >= totalPrice) {
			std::cout << "Thank you! Change: " << pay - totalPrice << "\n\n";
			break;
		}
		else {
			std::cout << "Insufficient amount!\n";
		}
	}
}
bool checkIfStudentIDisValid(const int& studentID, const bool& ifViewRecord)  {
	if (ifViewRecord) {
		for (int i = 0; i <= studentCount; i++) {
			if (students[i].studentID == studentID) {
				return true;
			}
		}
		return false;
	}
	else {
		for (int i = 0; i <= studentCount; i++) {
			if (students[i].studentID == studentID && students[i].numberOfBorrowedBooks != MAX_TO_BORROW) {
				return true;
			}
		}
		return false;
	}
	
}
bool checkIfBookIDisValid(const int& bookID)  {
	for (int i = 0; i < bookSize; i++) {
		if (books[i].bookID == bookID && books[i].bookStatus == Status::AVAILABLE) {
			return true;
		}
	}
	return false;
}
bool checkIfBookIsBorrowed(const int& studentID, const int& bookID) {
	std::string bookTitle;
	for (int i = 0; i < bookSize; i++) {
		if (books[i].bookID == bookID) {
			bookTitle = books[i].bookTitle;
			break;
		}
	}
	for (int i = 0; i <= studentCount; i++) {
		if (students[i].studentID == studentID) {
			for (int j = 0; j < students[i].numberOfBorrowedBooks; j++) {
				if (students[i].booksBorrowed[j] == bookTitle) {
					return true;
				}
			}
		}
	}
	return false;
}
int getNumberOfBorrowedbooks(const int& studentID) {
	for (int i = 0; i <= studentCount; i++) {
		if (students[i].studentID == studentID) {
			return students[i].numberOfBorrowedBooks;
		}
	}
	return 0;
}

int main() {
	
	bool endProgram = false;
	char ch = ' ';
	Initialise();
	while (!endProgram) {
		system("cls");
		std::cout << "\n\n\t\t\t\t>> Simple Library Borrow Record System <<\n";
		std::cout << "\t\t\t\t\t\tWELCOME\n\n";
		std::cout << "\t\t\t\t1.Add Students information\n\t\t\t\t2.Borrow book\n\t\t\t\t3.Return book\n\t\t\t\t4.View record\n\t\t\t\t5.Exit\n";
		std::cout << "\n\n\t\t\t\tSelect from (1-5): ";
		std::cin >> ch;
		system("cls");
		{
			int studentID = 0;
			int bookID = 0;
			std::string date;
			std::string name;
			std::string courseYrLv;
			switch (ch) {
				case '1':
					if (studentCount != studentSize - 1) {
						std::cout << "\t\t\t\t >> ADD STUDENT INFORMATION SECTION <<\n\n\n";
						std::cout << "Enter student ID: ";
						std::cin >> studentID;
						std::cout << "Enter student name: ";
						std::getline(std::cin >> std::ws, name);
						std::cout << "Enter student courseYrLv: ";
						std::getline(std::cin >> std::ws, courseYrLv);
						addStudentsInfo(studentID, name, courseYrLv);
					}
					else {
						std::cout << "Has reach the maximum, only 20 students can be added!\n";
					}
					break;
				case '2':
					std::cout << "\t\t\t\t >> BORROW BOOK SECTION <<\n\n\n";
					displayStudents();
					std::cout << "Enter student ID: ";
					std::cin >> studentID;
					if (checkIfStudentIDisValid(studentID, false)) {
						system("cls");
						float totalPrice = 0.0f;
						int countBorrowBooks = 0;
						int tmpBookID[MAX_TO_BORROW] = { 0 };
						std::string tmpBorrowDate[MAX_TO_BORROW] = { };
						int numberOfBorrowedBooks = getNumberOfBorrowedbooks(studentID);
						while (countBorrowBooks != MAX_TO_BORROW && (numberOfBorrowedBooks + countBorrowBooks) != MAX_TO_BORROW) {
							displayBooks();
							std::cout << "Enter book ID: ";
							std::cin >> bookID;
							bool exist = false;
							for (int i = 0; i < MAX_TO_BORROW; i++) {
								if (bookID == tmpBookID[i]) {
									exist = true;
									break;
								}
							}
							if (exist) {
								std::cout << "You already selected this book!\n";
								system("PAUSE");
								system("cls");
								continue;
							}
							if (checkIfBookIDisValid(bookID)) {
								tmpBookID[countBorrowBooks] = bookID;
								std::cout << "Enter data(MM/DD/YY): ";
								std::getline(std::cin >> std::ws, tmpBorrowDate[countBorrowBooks]);
								char borrowAgain = ' ';
								std::cout << "Do you still want to borrow more books? <y/n>: ";
								std::cin >> borrowAgain;
								if (borrowAgain == 'Y' || borrowAgain == 'y') {
									system("cls");
									countBorrowBooks++;
								}
								else if (borrowAgain == 'N' || borrowAgain == 'n') {
									displayBorrowedBooks(tmpBookID, studentID, false, numberOfBorrowedBooks);
									char borrowOrNot = ' ';
									std::cout << "\n\nDo you want to borrow these books? <y/n>: ";
									std::cin >> borrowOrNot;
									if (borrowOrNot == 'Y' || borrowOrNot == 'y') {
										borrowBook(studentID, tmpBookID, countBorrowBooks, tmpBorrowDate, totalPrice);
										displayBorrowedBooks(tmpBookID, studentID, true, numberOfBorrowedBooks);
										payment(totalPrice);
										break;
									}
									else if (borrowOrNot == 'N' || borrowOrNot == 'n') {
										break;
									}
								}
							}
							else {
								std::cout << "Book ID is not valid! or Book is already borrowed\n";
								break;
							}
						}
						if (countBorrowBooks == MAX_TO_BORROW || (numberOfBorrowedBooks + countBorrowBooks) == MAX_TO_BORROW) {
							displayBorrowedBooks(tmpBookID, studentID, false, numberOfBorrowedBooks);
							std::cout << "\n\nYou have reach the maximum to borrow only 5 books per student\n";
							char borrowOrNot = ' ';
							std::cout << "\n\nDo you want to borrow these books? <y/n>: ";
							std::cin >> borrowOrNot;
							if (borrowOrNot == 'Y' || borrowOrNot == 'y') {
								borrowBook(studentID, tmpBookID, countBorrowBooks - 1, tmpBorrowDate, totalPrice);
								displayBorrowedBooks(tmpBookID, studentID, true, numberOfBorrowedBooks);
								payment(totalPrice);
							}
						}
					}
					else {
						std::cout << "Student ID is not valid! or Student has already borrowed 5 books\n";
					}
					break;
				case '3':
					std::cout << "\t\t\t\t >> RETURN BOOK SECTION <<\n\n\n";
					displayStudents();
					std::cout << "Enter student ID: ";
					std::cin >> studentID;
					system("cls");
					if (checkIfStudentIDisValid(studentID, false)) {
						viewRecord(studentID);
						std::cout << "Enter book ID: ";
						std::cin >> bookID;
						if (checkIfBookIsBorrowed(studentID, bookID)) {
							std::string date;
							std::cout << "Enter current date(MM/DD/YY): ";
							std::getline(std::cin >> std::ws, date);
							char returnOrNot = ' ';
							std::cout << "Do you want to return this book? <y/n>: ";
							std::cin >> returnOrNot;
							if (returnOrNot == 'Y' || returnOrNot == 'y') {
								returnBook(studentID, bookID);
								std::cout << "\nThank you for returning the book\n";
							}
						}
						else {
							std::cout << "!Invalid book ID\n";
						}
					}
					else {
						std::cout << "!Invalid student ID\n";
					}
					break;
				case '4':
					std::cout << "\t\t\t\t >> VIEW RECORD SECTION <<\n\n\n";
					displayStudents();
					std::cout << "Enter student ID: ";
					std::cin >> studentID;
					system("cls");
					if(checkIfStudentIDisValid(studentID, true)) {
						viewRecord(studentID);
					}
					else {
						std::cout << "Invalid student ID!\n";
					}
					break;
				case '5':
					endProgram = true;
					break;
				default:
					break;
				}
		}
		system("PAUSE");
	}

	return 0;
}
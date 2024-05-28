// ******************************************************** //
//                   CS222 - Final Project                  //
//                     Mar/24/2024 G.C                      //

//            Title: Book Shop Management System            //

//                      - Kidus Yosef -                     //

#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
using namespace std;

struct placeInfo
{
    string phoneNum;
    string email;
    string address;    
};

struct bookInfo 
{
    int id;
    string name;
    string author;
    int copies;
    double price;
    string status;
    int sold = 0;
};

struct employeeInfo
{
    int id;
    string fname;
    string lname;
    string fullName;
    char gender;
    int age;
    string nationality;
    string position;
    double salary;
};

struct salesInfo
{
    string employeeName;
    int saleSize;
    bookInfo receipt [100];
    string date;
    double sum;
};

void invalidInput ()
{
    cout << "Invalid Input!\n";
    string x;
    cin.ignore();
    getline (cin, x);
}

void enter ()
{
    string x;
    cin.ignore();
    cout << "Enter to continue: ";
    getline (cin, x);
}

char* time ()
{
    time_t now = time (0);
    return (ctime(&now));
}

placeInfo location ()
{
    system ("clear");
    ofstream out ("placeFile.txt", ios::app | ios::out);
    out.close();

    ifstream in ("placeFile.txt", ios::in);
    placeInfo x;

    out.open ("placeFile.txt", ios::app | ios::out);
    in >> x.email >> x.phoneNum >> x.address;

    if (x.email.empty())
    {
        cout << "*****************************************\n";
        cout << "             WELCOME TO YOUR\n";
        cout << "       BOOK SHOP MANAGEMENT SYSTEM\n";
        cout << "*****************************************\n\n";
        cout << "Enter the store's phone number: \n";
        cin >> x.phoneNum;
        cout << "\nEnter the address of the store: \n";
        cin.ignore();
        getline (cin, x.address);
        cout << "\nEnter work e-mail: \n";
        cin >> x.email;

        out << x.email << "\t" << x.phoneNum << "\t" << x.address;
    }
    in.close();
    out.close();

    return x;
}

bookInfo* start (int &size)
{
    bookInfo * bookArray = new bookInfo [100];
    ofstream out ("bookFile.txt", ios::app | ios::out);
    out.close();

    ifstream in ("bookFile.txt", ios::in);
    if (!in)
    {
        cout << "Error while opening books file!\n";
        return 0;
    }

    size = 0;
    in.seekg(0, ios::beg);
    while (getline (in, bookArray[size].name))
    {
        getline (in, bookArray[size].author);
        getline (in, bookArray[size].status);
        in >> bookArray[size].id;
        in >> bookArray[size].copies;
        in >> bookArray[size].price; 
        in >> bookArray[size].sold; 
        size++;
    }

    in.close(); 
    return bookArray;
}

employeeInfo * startEmployee (int &size)
{
    employeeInfo * employeeArray = new employeeInfo [100];
    ofstream out ("employeeFile.txt", ios::app | ios::out);
    out.close();

    ifstream in ("employeeFile.txt", ios::in);
    if (!in)
    {
        cout << "Error while opening employee's file!\n";
        return 0;
    }

    size = 0;
    in.seekg(0, ios::beg);
    while (getline (in, employeeArray[size].fullName))
    {
        getline (in, employeeArray[size].position);
        in >> employeeArray[size].id;
        in >> employeeArray[size].fname;
        in >> employeeArray[size].lname;
        in >> employeeArray[size].gender;
        in >> employeeArray[size].age;
        in >> employeeArray[size].nationality;
        in >> employeeArray[size].salary;
        size++;
    }
    
    in.close();
    return employeeArray;
}

salesInfo * startSales (int &size)
{
    salesInfo * salesArray = new salesInfo [100];
    ofstream out ("salesFile.txt", ios::app | ios::out);
    out.close();

    ifstream in ("salesFile.txt", ios::in);
    if (!in)
    {
        cout << "Error while opening sales file!\n";
        return 0;
    }

    in.seekg(0, ios::beg);
    size = 0;

    while (getline (in, salesArray[size].employeeName))
    {
        getline (in, salesArray[size].date);
        in >> salesArray[size].saleSize;
        for (int i = 0; i < salesArray[size].saleSize; i++) 
        {
            getline (in, salesArray[size].receipt[i].name);
            in >> salesArray[size].receipt[i].sold;
            in >> salesArray[size].receipt[i].price;
            in >> salesArray[size].sum;
        }
        size++;
    }

    in.close(); 
    return salesArray;
}

int menu ()
{
    cout << "***************************************" << endl;
    cout << "      Bookshop Management System" << endl;
    cout << "***************************************" << endl << endl;

    cout << "   1. Books" << endl;
    cout << "   2. Employees" << endl;
    cout << "   3. Sales" << endl;
    cout << "   4. Save" << endl;
    cout << "   5. Exit" << endl;

    cout << "Enter your choice: ";
    int choice;
    cin >> choice;

    return choice;
}

int bookMenu ()
{
    cout << "***************************************" << endl;
    cout << "                Book Menu" << endl;
    cout << "***************************************" << endl << endl;

    cout << "   1. Add" << endl;
    cout << "   2. Remove" << endl;
    cout << "   3. Display" << endl;
    cout << "   4. Search" << endl;
    cout << "   5. Update Price" << endl;
    cout << "   6. Update Status" << endl;
    cout << "   7. Save" << endl;
    cout << "   8. Return" << endl;
    cout << "   9. Exit" << endl;

    cout << "Enter your choice: ";
    int choice;
    cin >> choice;

    return choice;
}

void bookAdd (bookInfo *bookArray, int &size)
{
    system ("clear");
    cout << "**************************************\n";
    cout << "Enter the number of books to add: ";
    int num;
    cin >> num;
    
    for (int i = size; i<num+size; i++)
    {
        system ("clear");
        cout << "**************************************\n";
        cout << "Enter Informations for book number " << i+1 << endl;
        cout << "Enter Book ID: ";
        here:
        int id;
        cin >> id;
        for (int j = 0; j < i; j++)
        {
            if (bookArray[j].id == id)
            {
                cout << "ID already taken!\n";
                system ("clear");
                cout << "*********************\n";
                cout << "Enter a valid ID: ";
                goto here;
            }
        }
        bookArray[i].id = id;

        cin.ignore();
        cout << "\nEnter the name of the book: ";
        getline (cin, bookArray[i].name);
        cout << "\nEnter the author of the book: ";
        getline (cin, bookArray[i].author);
        cout << "\nEnter the number of copies: ";
        cin >> bookArray[i].copies;
        cout << "\nEnter the price for 1 copy: ";
        cin >> bookArray[i].price;
        cout << endl << endl;

        if (bookArray[i].copies == 0)
        {
            bookArray[i].status = "Sold out";
        }
        else
            bookArray[i].status = "Available";
    }
    size += num;
}

void booklist(bookInfo * bookArray, int i)
{
    cout << "Book ID = " << bookArray[i].id << endl;
    cout << "Name = " << bookArray[i].name << endl;
    cout << "Author = " << bookArray[i].author << endl;
    if (bookArray[i].copies != 0)
        cout << "Copies = " << bookArray[i].copies << endl;
    else
        cout << "Copies = Sold out!" << endl;
    cout << "Price = " << bookArray[i].price << endl;
}

void remove (bookInfo * bookArray, int &size)
{
    system ("clear");
    cout << "*************************************************\n";
    cout << "Enter the ID of the book you want to remove: ";
    int id;
    cin >> id;

    for (int i = 0; i<size; i++)
    {
        if (id == bookArray[i].id)
        {
            booklist (bookArray, i);
            cout << "\nAre you sure you want to remove this book from the system? ";
            char choice;
            cin >> choice;

            choice = tolower(choice);
            if (choice == 'y')
            {
                for (int j = i; j<size; j++)
                {
                    bookArray[j] = bookArray[j+1];
                }
                size--;
                return;
            }
        }
    }
}

void display (bookInfo *bookArray, int size)
{
    system ("clear");
    cout << left << setw(15) << "ID" << left << setw(25) << "Name" << left << setw(25) << "Author" << left
    << setw(15) << "Price" << left << setw(15) << "Status" << left << setw(15) << "Copies" << endl << endl;

    for (int i = 0; i<size; i++)
    {
        cout << left << setw(15) << bookArray[i].id << left << setw(25) << bookArray[i].name << left << setw(25) << bookArray[i].author << left
        << setw(15) << bookArray[i].price << left << setw(15) << bookArray[i].status << left << setw(15) << bookArray[i].copies << endl;
    }

    enter();
}

void search(bookInfo *bookArray, int size)
{
    system ("clear");
    cout << "*****************************\n";
    cout << "1. Search by ID\n";
    cout << "2. Search by Book name\n";
    cout << "3. Search by Author\n";
    cout << "4. Search by Price\n";
    cout << "5. Search by Availability\n\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;

    if (choice == 1)
    {
        system ("clear");
        cout << "\n\nEnter Book's ID: ";
        int id;
        cin >> id;

        for (int i = 0; i<size; i++)
        {
            if (id == bookArray[i].id)
            {
                system ("clear");
                cout << "************************\n";
                cout << "Book is registered!\n\n";
                booklist (bookArray, i);
            }
        }
        enter();
    }
    else if (choice == 2)
    {
        system ("clear");
        cout << "\n\nEnter Book's Name: ";
        string name;
        cin.ignore();
        getline (cin , name);

        for (int i = 0; i<size; i++)
        {
            if (name == bookArray[i].name)
            {
                system ("clear");
                cout << "************************\n";
                cout << "Book is registered!\n\n";
                booklist (bookArray, i);
            }
        }
        enter();
    }
    else if (choice == 3)
    {
        system ("clear");
        cout << "\n\nEnter Book's Author: ";
        string author;
        cin.ignore();
        getline (cin , author);

        for (int i = 0; i<size; i++)
        {
            if (author == bookArray[i].author)
            {
                system ("clear");
                cout << "************************\n";
                cout << "Book is registered!\n\n";
                booklist (bookArray, i);
            }
        }
        enter ();
    }
    else if (choice == 4)
    {
        system ("clear");
        cout << "******************************\n";
        cout << "\n\nEnter Book's Price: ";
        double price;
        cin >> price;

        system ("clear");
        cout << "***************************************\n";
        cout << left << setw(15) << "ID" << left << setw(15) << "Name" << left << setw(15) << "Price" << endl << endl;
        for (int i = 0; i<size; i++)
        {
            if (price == bookArray[i].price)
            {
                cout << left << setw(15) << bookArray[i].id << left << setw(15) << bookArray[i].name << left << setw(15) << bookArray[i].price << endl;
            }
        }
        cout << endl;
        enter();
    }
    else if (choice == 5)
    {
        system ("clear");
        cout << "*************************************************\n";
        cout << "The available books with their number of copies \n\n";
        cout << left << setw(15) << "ID" << left << setw(20) << "Name" << left << setw(20) << "Author" << left
        << setw(15) << "Price" << left << setw(15) << "Status" << left << setw(15) << "Copies" << endl;

        for (int i = 0; i<size; i++)
        {
            if (bookArray[i].copies >0)
            {
                cout << left << setw(15) << bookArray[i].id << left << setw(20) << bookArray[i].name << left << setw(20) << bookArray[i].author << left
                << setw(15) << bookArray[i].price << left << setw(15) << bookArray[i].status << left << setw(15) << bookArray[i].copies << endl;
            }
        }
        enter ();
    }
}

void updatePrice (bookInfo* bookArray, int size)
{
    system ("clear");
    cout << "**************************\n";
    cout << "Enter ID of the book: ";
    int id;
    cin >> id;
    for (int i = 0; i<size; i++)
    {
        if (id == bookArray[i].id)
        {
            system("clear");
            cout << "*********************************\n";
            cout << "Current Price of the Book: " << bookArray[i].price;
            cout << "\nEnter the new price: ";
            cin >> bookArray[i].price;

            system("clear");
            cout << "*********************************\n";
            cout << "Price updated successfully!\n\n";
            booklist(bookArray, i);

            enter();

            break;
        }
    }
}

void updateStatus (bookInfo *bookArray, int size)
{
    system ("clear");
    display (bookArray, size);
    string x;
    do
    {
        cout << "\n****************************************************\n";
        cout << "Enter the id of the book you want to update status: \n";
        int id;
        cin >> id;
        for (int i =0; i<size; i++)
        {
            if (id == bookArray[i].id)
            {
                cout << "Enter the number of additional copies: ";
                int additional;
                cin >> additional;
                bookArray[i].copies += additional;
                if (bookArray[i].copies > 0)
                    bookArray[i].status = "Available";
                else
                    bookArray[i].status = "Sold out";
            }
        }
        cin.ignore();
        getline(cin,x);
    } while (!x.empty());
}

int employeeMenu ()
{
    cout << "***************************************" << endl;
    cout << "             Employee Menu" << endl;
    cout << "***************************************" << endl << endl;

    cout << "   1. Add Employee" << endl;
    cout << "   2. Search Employee" << endl;
    cout << "   3. Display Employee" << endl;
    cout << "   4. Remove Employee" << endl;
    cout << "   5. Update Salary" << endl;
    cout << "   6. Save" << endl;
    cout << "   7. Return" << endl;
    cout << "   8. Exit" << endl;

    cout << "Enter your choice: ";
    int choice;
    cin >> choice;

    return choice;   
}

void employeeAdd (employeeInfo * employeeArray, int &size)
{
    system ("clear");
    cout << "******************************************\n";
    cout << "Enter the number of employees to add: ";
    int num;
    cin >> num;
    
    for (int i = size; i<num+size; i++)
    {
        system("clear");
        cout << "******************************************\n";
        cout << "Enter information for employee #" << i+1 << endl;
        employeeArray[i].id = i;
        cout << "Enter first name: ";
        cin >> employeeArray[i].fname;
        cout << "\nEnter last name: ";
        cin >> employeeArray[i].lname; 
        employeeArray[i].fullName = employeeArray[i].fname + " " + employeeArray[i].lname;
        cout << "\nEnter gender: ";
        cin >> employeeArray[i].gender;

        cout << "\nEnter age: ";
        cin >> employeeArray[i].age;
        cout << "\nEnter nationality: ";
        cin >> employeeArray[i].nationality;
        system ("clear");
        cout << "******************************************\n";
        cout << "Enter the employee's position: \n";
        cout << "1. Admin\n";
        cout << "2. Store keeper\n";
        cout << "3. Security\n";
        cout << "4. Janitor\n";
        cout << "5. IT Developer\n";
        cout << "\nEnter your choice: ";
        int x;
        string work;
        cin >> x;
        if (x == 1)
            work = "Admin";
        else if (x == 2)
            work = "Store Keeper";
        else if (x == 3)
            work = "Security";
        else if (x == 4)
            work = "Janitor";
        else if (x == 5)
            work = "IT Developer";
        employeeArray[i].position = work; 

        cout << "\nEnter salary: ";
        cin >> employeeArray[i].salary;
    }
    size += num;
}

void employeeList(employeeInfo * employeeArray, int i)
{
    cout << "Information of Employee \"" << employeeArray[i].fullName << "\"\n" << endl;
    cout << "ID = " << employeeArray[i].id << endl;
    cout << "First Name = " << employeeArray[i].fname << endl;
    cout << "Last Name = " << employeeArray[i].lname << endl;
    cout << "Gender = " << employeeArray[i].gender << endl;
    cout << "Nationality = " << employeeArray[i].nationality << endl;
    cout << "Position = " << employeeArray[i].position << endl;
    cout << "Salary = " << employeeArray[i].salary << endl;
}

void search (employeeInfo * employeeArray, int employeeSize)
{
    system ("clear");
    cout << "******************************************\n";
    cout << "1. Search by Name\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;

    string name;
    if (choice == 1)
    {
        system ("clear");
        cout << "******************************************\n";
        cout << "1. Search by First Name: \n";
        cout << "2. Search by Last Name: \n";
        cout << "3. Search by Full Name: \n";
        cout << "\nEnter your choice: ";
        int choiceNum;
        cin >> choiceNum;

        if (choiceNum == 1)
        {
            cout << "\nEnter first name of the employee: ";
            cin >> name;
        }
        else if (choiceNum == 2)
        {
            cout << "Enter the last name of the employee: ";
            cin >> name;
        }
        else if (choiceNum == 3)
        {
            cout << "Enter the full name of the employee: ";
            cin.ignore();
            getline (cin , name);
        }
        cout << endl;
        bool check = true;
        for (int i = 0; i<employeeSize; i++)
        {
            if (name == employeeArray[i].fname || name == employeeArray[i].lname || name == employeeArray[i].fullName)
            {
                system ("clear");
                cout << "******************************************\n";
                cout << "\nVerified employee/s by this name is/are: \n";
                employeeList(employeeArray, i);
                enter();
                check = false;
            }
        }
        if (check == true)
        {
            system ("clear");
            cout << "******************************************\n";
            cout << "There is no employee by this name!\n";
            enter();
        }
    }
}

void display (employeeInfo * employeeArray, int employeeSize)
{
    system ("clear");
    cout << left << setw(15) << "ID" << left << setw(25) << "First Name" << left << setw(25) << "Last Name" << left << setw(15) << "Gender" << left
    << setw(15) << "Age" << left << setw(15) << "Nationality" << left << setw(15) << "Position" << left << setw(15) << "Salary"  << endl << endl;

    for (int i = 0; i<employeeSize; i++)
    {
        cout << left << setw(15) << employeeArray[i].id << left << setw(25) << employeeArray[i].fname << left << setw(25) << employeeArray[i].lname << left << 
        setw(15) << employeeArray[i].gender << left << setw(15) << employeeArray[i].age << left << setw(15) << employeeArray[i].nationality << left << setw(15) 
        << employeeArray[i].position << left << setw(15) << employeeArray[i].salary  << endl;
    }

    enter();
}

void remove (employeeInfo * employeeArray, int &employeeSize)
{
    display (employeeArray, employeeSize);
    cout << "***************************************************\n";
    cout << "Enter the ID of the employee you want to remove: ";
    int id;
    cin >> id;

    if (id == employeeArray[id].id)
    {
        system ("clear");
        cout << "*****************************************\n";
        employeeList (employeeArray, id);
        cout << "\nAre you sure you want to delete this employee from the system? ";
        char choice;
        cin >> choice;

        choice = tolower(choice);
        if (choice == 'y')
        {
            for (int i = id; i<employeeSize; i++)
            {
                employeeArray[i] = employeeArray[i+1];
                employeeArray[i].id -= 1;
            }
            employeeSize--;
            return;
        }
    }
}

void updateSalary (employeeInfo * employeeArray, int employeeSize)
{
    display (employeeArray, employeeSize);
    cout << "******************************************************\n";
    cout << "Enter employeer's ID you want to update salary to: ";
    int id;
    cin >> id;

    for (int i = 0; i<employeeSize; i++)
    {
        if (id == employeeArray[i].id)
        {
            system ("clear");
            cout << "******************************\n";
            cout << "Current Salary = " << employeeArray[i].salary;
            cout << "\nEnter their new salary: ";
            double newSalary;
            cin >> newSalary;

            employeeArray[i].salary = newSalary;
            system ("clear");
            cout << "******************************\n";
            cout << "Salary updated successfully!\n";
            enter();
        }
    }
}

void addNewBill (employeeInfo * employeeArray, bookInfo * bookArray, salesInfo * salesArray, int employeeSize, int &salesSize, int size)
{
    system ("clear");
    cout << "**************************\n";
    cout << "Enter your ID: ";
    int id;
    here:

    cin >> id;

    bool flag = false;
    for (int i = 0; i<employeeSize; i++)
    {
        if (id == employeeArray[i].id && (employeeArray[i].position == "Admin" || employeeArray[i].position == "Store Keeper" || employeeArray[i].position == "IT Developer"))
        {
            salesArray[salesSize].employeeName = employeeArray[i].fullName;
            flag = true;
            break;
        }
    }
    if (flag == false)
    {
        system ("clear");
        cout << "**************************\n";
        cout << "Invalid employee ID!\n\n";
        cout << "Enter a valid ID: ";
        goto here;
    }

    system ("clear");
    cout << "*************************************************************\n";
    cout << "Enter the amount of books (Group the similar one's as 1): ";
    cin >> salesArray[salesSize].saleSize;
    int num = salesArray[salesSize].saleSize;

    for (int i = 0; i<num; i++)
    {
        system("clear");
        display (bookArray, size);
        cout << "\n*****************************************\n";
        cout << "Enter book type #" << i+1 << "'s ID: ";
        int bookID;
        cin >> bookID;
        cout << "\nEnter quantity: ";
        int bookCopies;
        cin >> bookCopies;

        for (int j = 0; j<size; j++)
        {
            if (bookID == bookArray[j].id)
            {
                system ("clear");
                if (bookArray[j].copies >= bookCopies)
                {
                    salesArray[salesSize].receipt[i].name = bookArray[j].name;
                    salesArray[salesSize].receipt[i].price = bookArray[j].price;
                    salesArray[salesSize].receipt[i].copies = bookArray[j].copies - bookCopies;
                    bookArray[j].copies = salesArray[salesSize].receipt[i].copies;
                    if (bookArray[j].copies == 0)
                    {
                        bookArray[j].status = "Sold out";
                    }
                    else
                        bookArray[j].status = "Available";
                    salesArray[salesSize].receipt[i].sold = bookCopies;

                    salesArray[salesSize].sum += salesArray[salesSize].receipt[i].price * salesArray[salesSize].receipt[i].sold;
                    break;
                }
                else if (bookArray[j].copies == 0)
                {
                    cout << "This book is all sold out!\n";
                }
                else if (bookArray[j].copies < bookCopies)
                {
                    cout << "Not enough copies!\n";
                    cout << "There are only " << bookArray[i].copies << " left!\n";
                }
            }
            system("clear");
        }
    }
    string date;
    date = time();
    salesArray[salesSize].date = date;
    
    salesSize++;
    cout << "*******************\n";
    cout << "Receipt added!\n";
    enter();
}

int salesMenu (int size)
{
    cout << "***************************************" << endl;
    cout << "               Sales Menu" << endl;
    cout << "***************************************" << endl << endl;

    cout << "    1. Add new bill" << endl;
    cout << "    2. Total sales" << endl;
    cout << "    3. Save" << endl;
    cout << "    4. Return" << endl;
    cout << "    5. Exit" << endl;

    cout << "Enter your choice: ";
    int choice;
    cin >> choice;

    return choice;       
}

void totalSales (salesInfo* salesArray, int salesSize, employeeInfo* employeeArray, bookInfo * bookArary, placeInfo x)
{
    system ("clear");
    for (int i = 0; i<salesSize; i++)
    {
        cout << "********************************************************\n";
        cout << left << "\nDate                   " << salesArray[i].date << endl << endl;
        cout << "RECEIVED FROM" << endl << endl;

        cout << left << setw(25) << "Name" << left << setw(25) << salesArray[i].employeeName << endl;
        cout << left << setw(25) << "Phone Number" << left << setw(25) << x.phoneNum << endl;
        cout << left << setw(25) << "Email" << left << setw(25) << x.email << endl;
        cout << left << setw(25) << "Address" << left << setw(25) << x.address << endl << endl;
        
        cout << "\nSales Detail" << endl << endl; 
        cout << left << setw(25) << "Description" << right << setw (16) << "Amount" << endl << endl << endl;

        
        for (int j = 0; j<salesArray[i].saleSize; j++)
        {
            cout << salesArray[i].receipt[j].name << endl << endl;
            cout << left << setw (3) << salesArray[i].receipt[j].sold << " *  " << "$" << left << setw (4) << salesArray[i].receipt[j].price << left << setw (23) << " " << right << setw(5) << salesArray[i].receipt[j].price * salesArray[i].receipt[j].sold << endl;
            cout << endl;
        }
        cout << endl << endl;
        cout << "Total" << setw(30) << " " << right << setw(5) << salesArray[i].sum << endl << endl << endl << endl << endl;
    }
    enter();
}

void saveAll (bookInfo* bookArray, employeeInfo* employeeArray, salesInfo* salesArray, int size, int employeeSize, int salesSize)
{
    ofstream out;
        out.open ("bookFile.txt", ios::out);
        if (!out)
        {
            cout << "Error while opening book file!\n";
            return;
        }
        for (int i = 0; i<size; i++)
        {
            out << bookArray[i].name << "\n" << bookArray[i].author << "\n" << bookArray[i].status << "\n" << bookArray[i].id << "\n" << bookArray[i].copies 
            << "\n" << bookArray[i].price << "\n" << bookArray[i].sold;
        }
        out.close ();
    
        out.open ("employeeFile.txt", ios::out);
        if (!out)
        {
            cout << "Error while opening employee file!\n";
            return;
        }
        for (int i = 0; i<employeeSize;i++)
        {
            out << employeeArray[i].fullName << "\n" << employeeArray[i].position << "\n" << employeeArray[i].id << "\n" << employeeArray[i].fname << "\n" << employeeArray[i].lname << "\n" << employeeArray[i].gender << "\n"
                << employeeArray[i].age << "\n" << employeeArray[i].nationality << "\n" << employeeArray[i].salary;
        }

        out.close();

        out.open ("salesFile.txt", ios::out);
        if (!out)
        {
            cout << "Error while opening sales file!\n";
            return;
        }
        for (int i = 0; i<salesSize; i++)
        {
            out << salesArray[i].employeeName << "\n" << salesArray[i].date << "\n" << salesArray[i].saleSize;
            for (int j = 0; j<salesArray[i].saleSize; j++)
            {
                out << salesArray[i].receipt[j].name << "\n" << salesArray[i].receipt[j].sold << "\n" << salesArray[i].receipt[j].price
                << "\n" << salesArray[i].sum;
            }
        }
        out.close();
        system ("clear");
        cout << "********************\n";
        cout << "Saved!\n";

        enter ();
}

void save (bookInfo* bookArray, int size)
{
    ofstream out;
        out.open ("bookFile.txt", ios::out);
        if (!out)
        {
            cout << "Error while opening book file!\n";
            return;
        }
        for (int i = 0; i<size; i++)
        {
            out << bookArray[i].name << "\n" << bookArray[i].author << "\n" << bookArray[i].status << "\n" << bookArray[i].id << "\n" << bookArray[i].copies 
            << "\n" << bookArray[i].price << "\n" << bookArray[i].sold;
        }
        out.close ();
        system ("clear");
        cout << "******************\n";
        cout << "Saved!\n";
        enter ();
}

void save (employeeInfo * employeeArray, int size)
{
    ofstream out;
        out.open ("employeeFile.txt", ios::out);
        if (!out)
        {
            cout << "Error while opening employee file!\n";
            return;
        }
        for (int i = 0; i<size;i++)
        {
            out << employeeArray[i].fullName << "\n" << employeeArray[i].position << "\n" << employeeArray[i].id << "\n" << employeeArray[i].fname << "\n" << employeeArray[i].lname << "\n" << employeeArray[i].gender << "\n"
                << employeeArray[i].age << "\n" << employeeArray[i].nationality << "\n" << employeeArray[i].salary;
        }
        out.close();   
        system ("clear");
        cout << "*******************\n";
        cout << "Saved!\n";

        enter ();
}

void save (salesInfo* salesArray, int size, bookInfo* bookArray, int bookSize)
{
    ofstream out;
        out.open ("salesFile.txt", ios::out);
        if (!out)
        {
            cout << "Error while opening sales file!\n";
            return;
        }
        for (int i = 0; i<size; i++)
        {
            out << salesArray[i].employeeName << "\n" << salesArray[i].date << "\n" << salesArray[i].saleSize;
            for (int j = 0; j<salesArray[i].saleSize; j++)
            {
                out << salesArray[i].receipt[j].name << "\n" << salesArray[i].receipt[j].sold << "\n" << salesArray[i].receipt[j].price
                << "\n" << salesArray[i].sum;
            }
        }
        out.close();

        out.open ("bookFile.txt", ios::out);
        if (!out)
        {
            cout << "Error while opening book file!\n";
            return;
        }
        for (int i = 0; i<bookSize; i++)
        {
            out << bookArray[i].name << "\n" << bookArray[i].author << "\n" << bookArray[i].status << "\n" << bookArray[i].id << "\n" << bookArray[i].copies 
            << "\n" << bookArray[i].price << "\n" << bookArray[i].sold;
        }
        out.close ();

        system ("clear");
        cout << "*******************\n";
        cout << "Saved!\n";
        enter ();
}

void exit (bookInfo* bookArray, employeeInfo* employeeArray, salesInfo* salesArray)
{
    delete [] bookArray;
    delete [] employeeArray;
    delete [] salesArray;
}

int main ()
{
    placeInfo x = location();
    bookInfo * bookArray;
    employeeInfo * employeeArray;
    salesInfo * salesArray;
    int size, employeeSize, salesSize;

    bookArray = start(size);
    employeeArray = startEmployee(employeeSize);
    salesArray = startSales(salesSize);

    int mainChoice;
    do
    {
        system ("clear");
        mainChoice = menu();
        if (mainChoice == 1)
        {
            int bookChoice;
            do 
            {
                system ("clear");
                bookChoice = bookMenu();
                if (bookChoice == 1)
                {
                    bookAdd(bookArray, size);
                }
                else if (bookChoice == 2)
                {
                    remove (bookArray, size);
                }
                else if (bookChoice == 3)
                {
                    display (bookArray, size);
                }
                else if (bookChoice == 4)
                {
                    search (bookArray, size);
                }
                else if (bookChoice == 5)
                {
                    updatePrice (bookArray, size);
                }
                else if (bookChoice == 6)
                {
                    updateStatus (bookArray, size);
                }
                else if (bookChoice == 7)
                {
                    save (bookArray, size);
                }
                else if (bookChoice == 8)
                {
                    system ("clear");
                }
                else if (bookChoice == 9)
                {
                    exit (bookArray, employeeArray, salesArray);
                    return 0;
                }
                else if (bookChoice > 9 || bookChoice < 1)
                {
                    system ("clear");
                    invalidInput ();
                }
            } while (bookChoice != 8);
        }
        else if (mainChoice == 2)
        {
            int employeeChoice;
            do
            {
                system ("clear");
                employeeChoice = employeeMenu();
                if (employeeChoice == 1)
                {
                    employeeAdd (employeeArray, employeeSize);
                }
                else if (employeeChoice == 2)
                {
                    search (employeeArray, employeeSize);
                }
                else if (employeeChoice == 3)
                {
                    display (employeeArray, employeeSize);
                }
                else if (employeeChoice == 4)
                {
                    remove (employeeArray, employeeSize);
                }
                else if (employeeChoice == 5)
                {
                    updateSalary (employeeArray, employeeSize);
                }
                else if (employeeChoice == 6)
                {
                    save (employeeArray, employeeSize);
                }
                else if (employeeChoice == 7)
                {
                    system ("clear");
                }
                else if (employeeChoice == 8)
                {
                    exit (bookArray, employeeArray, salesArray);
                    return 0;
                }
                else if (employeeChoice > 8 || employeeChoice < 1)
                {
                    invalidInput ();
                }
            } while (employeeChoice != 7);
        }
        else if (mainChoice == 3)
        {
            int salesChoice;
            do
            {
                system ("clear");
                salesChoice = salesMenu(salesSize);
                if (salesChoice == 1)
                {
                    addNewBill (employeeArray, bookArray, salesArray, employeeSize, salesSize, size);
                }
                else if (salesChoice == 2)
                {
                    totalSales (salesArray, salesSize, employeeArray, bookArray, x);
                }
                else if (salesChoice == 3)
                {
                    save (salesArray, salesSize, bookArray, size);
                }
                else if (salesChoice == 4)
                {
                    system ("clear");
                }
                else if (salesChoice == 5)
                {
                    exit (bookArray, employeeArray, salesArray);
                    return 0;
                }
                else if (salesChoice > 5 || salesChoice < 1)
                {
                    invalidInput ();
                }
            } while (salesChoice != 4);
        }
        else if (mainChoice == 4)
        {
            saveAll (bookArray, employeeArray, salesArray, size, employeeSize, salesSize);
        }
        else if (mainChoice == 5)
        {
            exit (bookArray, employeeArray, salesArray);
        }
        else if (mainChoice >= 6 || mainChoice <= 0)
        {
            invalidInput();
        }
    } while (mainChoice != 5);
    return 0;
}
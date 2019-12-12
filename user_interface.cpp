/*********************************************************************
//
//   Name:         Jennifer Hsu
//
//   Homework:     Project 1
//
//   Class:        ICS 212
//
//   Instructor:   Ravi Narayan
//
//   Date:         Oct. 28, 2019
//
//   File:         user_interface.c
//
//   Description:
//     This file contains the user interface for the software.
//
*******************************************************************/

#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "llist.h"
#include "record.h"
using namespace std;

/*******************************************************************
//
//   Function name:    main
//
//   Description:      Start of the program.
//
//   Parameters:       argc (int : Number of arguments passed in
//                     argv (char *) : Argument passed in
//
//   Return values:    0 : success
//
*******************************************************************/

int main(int argc, char* argv[])
{
    void getaddress(char[], int);
    int validate_number(char[]);
    int validate_name(string);
    char buffer[1000];
    char name[1000];
    char address[100];
    #ifdef DEBUGMODE
    char fname[15] = "dataCopy=.txt";
    #endif
    int accountnum = -1;
    int value = -1;
    int starting = 0;
    int nameValid = -1;
    int success = 0;
  
    llist mylist;

    #ifdef DEBUGMODE
    cout << "\nCreating empty llist 'listOperator' to test operator=....";
    llist listOperator (fname);
    cout << "\nCalling copy constructor for mylistCopy....";
    llist mylistCopy(mylist);

    cout << "\nAssigning 'listOperator = mylistCopy....";
    listOperator = mylistCopy;
    #endif
    
    if (starting == 0)
    {
        cout << endl << "Welcome to Xyro, the software that stores the customer's bank records for the bank 'Larkin'." << endl;
    }

    while (value == -1 && starting == 0)
    {
        cout << endl << endl << "===========================================================================================";
        cout << endl << "Menu" << endl;
        cout << "1: Add a new record in the database." << endl;
        cout << "2: Print information about a record using the account #." << endl;
        cout << "3: Print all records in the database." << endl;
        cout << "4: Modify the address field of a record specified by account #." << endl;
        cout << "5: Delete an existing record from the database." << endl;
        cout << "6: Reverse the list." << endl;
        cout << "7: Quit the program." << endl;
        cout << "============================================================================================" << endl;
        cout << "Please enter the respective number to select the option you want to use: ";

        cin >> buffer;
        value = validate_number(buffer);

        if (value > 7)
        {
            value = -1;
            cout << "\nInvalid menu option. Please try again.";
        }

        switch (value)
        {
        case 1:
            cout << "\nYou selected: 'Add a new record to the datebase.'\n";
            cout << "Please enter the account number. It must be greater than 0. Press enter when done: ";

            while (accountnum == -1)
            {
                cin >> buffer;
                accountnum = validate_number(buffer);
                cin.clear();
                cin.ignore(1000, '\n');
            }

            cout << "Please enter the name. Press enter when done: ";
            nameValid = -1;
            while (nameValid == -1)
            {
                nameValid = 0;
                cin.getline(name, 1000);
                nameValid = validate_name(name);
            }

            getaddress(address, 100);
            success = mylist.addRecord(accountnum, name, address);
            if (success != -1)
            {
                cout << "You have entered: \nAccount #: " << accountnum << "\nName: " << name << "\nAddress: " << address;
            }
            else
            {
                cout << "Sorry, an account with the number: '" << accountnum << "' already exists. Please try again.\n";
            }

            value = -1;
            nameValid = -1;
            accountnum = -1;
            break;
        case 2:
            cout << "\nYou selected: `Print information about a record using the account #.\n";
            cout << "Please enter the account number. It must be greater than 0. Press enter when done: ";
            while (accountnum == -1)
            {
                cin >> buffer;
                accountnum = validate_number(buffer);
                cin.clear();
                cin.ignore(1000, '\n');
            }
            value = -1;
            success = mylist.printRecord(accountnum);
            if (success != 0)
            {
                cout << "Invalid, there are no records in the database that match the account #: '" << accountnum << "' Please try again.\n";
            }
            success = 0;
            accountnum = -1;
            break;
        case 3:
            cout << "\nYou've selected: 'Print all records in the database'.\n";
            std::cout << mylist;
            
            #ifdef DEBUGMODE
            cout << endl << "[[ COPY CONSTRUCTOR LIST ]]" << endl;
            std::cout << mylistCopy;
            cout << endl << "[[ OPERATOR= LIST ]]" << endl;
            std::cout << listOperator;
            #endif
            
            value = -1;
            break;
        case 4:
            cout << "\nYou selected: 'Modify the address field of a record specified by account # as key.`\n";
            cout << "Please enter the account number. It must be greater than 0. Press enter when done: ";
            while (accountnum == -1)
            {
                cin >> buffer;
                accountnum = validate_number(buffer);
                cin.clear();
                cin.ignore(1000, '\n');
            }
            getaddress(address, 100);
            success = mylist.modifyRecord(accountnum, address);
            if (success != 0)
            {
                cout << "Invalid, there are no records in the database that match the account #: '" << accountnum << "' Please try again.\n";
            }
            else
            {
                cout << "Successfully changed the address for account #: '" << accountnum << "'" << endl;
            }
            success = 0;
            value = -1;
            accountnum = -1;
            break;
        case 5:
            cout << "You selected: 'Delete an existing record from the database using the account # as a key.`\n";
            cout << "Enter the account number you wish to delete. It must be greater than 0. Press enter when done: ";
            while (accountnum == -1)
            {
                cin >> buffer;
                accountnum = validate_number(buffer);
                cin.clear();
                cin.ignore(1000, '\n');
            }

            success = mylist.deleteRecord(accountnum);

            if (success != -1)
            {
                cout << "Account #: '" << accountnum << "' successfully deleted.\n";
            }
            else
            {
                cout << "Invalid, there are no records in the database that match the account #: '" << accountnum << "' Please try again.\n";
            }
            accountnum = -1;
            value = -1;
            break;
        case 6:
            cout << "You selected 'Reverse the list.'\n";
            mylist.reverse();
            value = -1;
            break;
        case 7:
            cout << "Closing program now.\n\n";
            value = 0;
            break;
        default:
            value = -1;
        }
    }

    return 0;
}

 
/***************************************************************************************
//
//   Function name:    getaddress
//
//   Description:      Obtains address information for the following fields:
//                     account number
//                     name
//                     mailing address
//
//   Parameters:       input (char []) : The address field
//                     size (int) : size of input
//
//   Return values:    None
//
***************************************************************************************/

void getaddress(char input[], int size)
{

    char line = '\n';
    int i;
    int count = 0;


    #ifdef DEBUGMODE
        cout << "\n=== Entering getaddress function ===\n";
        cout << "=== char input []: '" << input << "'\nInt size: '" << size << "'\n===\n\n";
    #endif

    cout << "\nPlease enter the new address. Signify that you are done inputting by adding a `@` at the end.";
    cout << "\nFor example: 1234 Dole Street, Honolulu, HI@";
    cout << "\nEnter here: ";

    cin.get(input, size, '@');

    count = strlen(input);

    for (i = 0; i <= count; i++)
    {
        if (input[i] == line)
        {
            input[i] = ' ';
        }

    }

    #ifdef DEBUGMODE
        cout << "=== At the end of getaddress (after code is ran). ===\n";
        cout << "=== char input []: '" << input << "'\nInt size: '" << size << "'\n===\n\n";
    #endif

    cin.clear();
    cin.ignore(10000, '\n');

}


/*******************************************************************
//
//   Function name:    validate_number
//
//   Description:      Validates account #.
//
//   Parameters:       buffer (char []): The number being passed in. 
//
//   Return values:    valid (int): Checks to see if number passed
//                     in is valid.
//                     -1 : invalid input
//
*******************************************************************/

int validate_number(char buffer [])
{
    int input;
    int size;
    int error = -1;

    #ifdef DEBUGMODE
        cout << "\n==== Entering validate_number function ===\n";
        cout << "Passing input: " << buffer << endl;
    #endif

    input = atoi(buffer);
    size = strlen(buffer);

    if (buffer[0] == '0')
    {
        input = -1;
        cout << "Invalid input. Please try again. ";
    }
    else
    {
        for (int counter = 0; counter < size; counter++)
        {

            if (buffer[counter] >= '0' && buffer[counter] <= '9')
            {
                ;
            }
            else
            {
                input = -1;
                if (error == -1)
                {
                    cout << "Invalid input. No characters or negative numbers allowed. ";
                    error = 0;
                }
            }
        }
    }

    return input;

}

/*******************************************************************
//
//   Function name:    validate_name
//
//   Description:      Validates name
//
//   Parameters:       name: The name being passed in. 
//
//   Return values:    valid: Checks to see if inputted name is valid.
//                     -1 : invalid input.
//
*******************************************************************/

int validate_name(string name)
{
    int error = -1;
    int valid = 0;
    int length = 0;
    
    length = name.length();

    #ifdef DEBUGMODE
        cout << "\n==== Entering validate_name function ===\n";
        cout << "Passing name: " << name << endl;
    #endif

    if (name.length() == 0)
    {
        cout << "Invalid. Input is empty. Please try again: ";
        valid = -1;
    }

    for (int counter = 0; counter < length; counter++) 
    {
        if (name[counter] >= '0' && name[counter] <= '9')
        {
            if (error == -1)
            {
                cout << "Invalid: no numbers allowed. Please try again: ";
                error = 0;
            }
            valid = -1;
        }
        else if ((name[counter] >= 'A' && name[counter] <= 'Z') ||
            (name[counter] >= 'a' && name[counter] <= 'z') ||
            (name[counter] == '.') || (name[counter] == ' '))
        {
            ;
        }
        else
        {
            if (error == -1)
            {
                cout << "Invalid: No special characters allowed. Please try again: ";
                error = 0;
            }
            valid = -1;
        }
            
    }

    return valid; 

}

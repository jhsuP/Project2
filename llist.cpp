/****************************************************************
//     
//     Name:       Jennifer Hsu
//
//     Homework:   Project 2
//
//     Class:      ICS 212
//
//     Instructor: Ravi Narayan
//
//     Date:       Oct. 28, 2019
//
//     File name:  llist.cpp
//
//     Description:
//       Contains the functions that allow us to create, view,
//       delete, and modify records.
//
*****************************************************************/

#include "llist.h"
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
using namespace std;

/****************************************************************
//    
//    Function name:    llist
//
//    Description:      Default constructor.
//
//    Parameters:       N/A
//
//    Return values:    N/A
//
*****************************************************************/

llist::llist()
{

    #ifdef DEBUGMODE
        cout << "\n=== Entering llist() ===";
    #endif

    this->start = NULL;
    strcpy(filename, "data.txt");
    this->readfile();

}

/****************************************************************
//    
//    Function name:     llist
//
//    Description:       Copy constructor
//
//    Parameters:        list (llist &): The list that we want
//                       to copy.
//
//    Return values:     N/A
//
****************************************************************/

llist::llist(const llist& list)
{

    #ifdef DEBUGMODE
        cout << "\n=== Entering llist(llist& list) ===";
    #endif

    this->start = NULL;
    record * head = list.start;
    record * prev = NULL;

    while(head != NULL)
    {
        prev = new record();
        addRecord(head->accountno, head->name, head->address);
        head = head->next;
        prev = prev->next;
    }
    
    strcpy(filename, "dataCopy.txt");
    this->readfile();

}

/*****************************************************************
//    
//    Function name:     operator=
//
//    Description:       Assignment overloading. Copies the data
//                       in llist A to llist B.
//
//    Parameters:        source (llist &): The list we want to copy
//
//    Return Values:     N/A
//
*****************************************************************/

llist& llist::operator= (const llist& source)
{

    #ifdef DEBUGMODE
        cout << "\n=== Entering llist (operator=) ===";
    #endif

    this->start = NULL;
    record * head = source.start;
    record * prev = NULL;

    while(head != NULL)
    {
        prev = new record();
        addRecord(head->accountno, head->name, head->address);
        head = head->next;
        prev = prev->next;
    }

    strcpy(filename, "dataCopy=.txt");
    this->readfile();

    return *this;
}

/*****************************************************************
//    
//    Function name:     llist
//
//    Description:       Constructor that takes in a char [] as
//                       a parameter.
//
//    Parameters:        fileName (char []): The file you want to 
//                       read in.
//
//    Return values:      N/A
//
******************************************************************/

llist::llist(char fileName [])
{

    #ifdef DEBUGMODE
        cout << "\n=== Entering llist(char []) ===\n";
    #endif

    this-> start = NULL;
    strcpy(filename, fileName);
    this->readfile();
}

/*****************************************************************
//    
//    Function name:     ~llist
//
//    Description:       The deconstructor; cleans up the heap.
//
//    Parameters:        N/A
//
//    Return Values:     N/A
//
*****************************************************************/

llist::~llist()
{

    #ifdef DEBUGMODE
        cout << "\n=== Entering ~llist() ===\n";
    #endif

    this->writefile();
    this->cleanup();
}

/****************************************************************
//   
//   Function name:      addRecord
//
//   Description:        Adds a new record into the database.
//
//   Parameters:         accountnum (int): contains the account #
//                       name (char []): name of the account owner
//                       address (char []): address of account owner
//
//   Return values:      0 : success
//
*****************************************************************/

int llist::addRecord (int accountnum, char name [], char address [])
{

    record * temp = NULL;
    record * input = NULL;
    int success = 0;
    int valid = 0;
    int counter = 0;

    temp = start;

    #ifdef DEBUGMODE
        cout << "\n=== Entering addRecord() ===\n";
        cout << "Passing in:\nAccount #: " << accountnum << endl;
        cout << "Name: " << name << endl;
        cout << "Address: " << address << endl;
        cout << "==============================\n";
    #endif


    while (temp != NULL && success == 0)
    {
        if (accountnum < temp->accountno)
        {
            counter++;
        }
        else if (accountnum == temp->accountno)
        {
            success = -1;
        }
        temp = temp->next;
    }

    if (success == 0)
    {
        input = new record();
 
        if (start == NULL)
        {
            start = input;
            input->next = NULL;
        }
        else
        {
            temp = start;
        
            if (counter == 0)
            {
                input->next = temp;
                start = input;
            }      
            else
            {
                while (valid < counter - 1)
                {
                    temp = temp->next;
                    valid++;
                }
             
                if (temp->next == NULL)
                {
                    temp->next = input;
                    input->next = NULL;
                }
                else
                {
                    input->next = temp->next;
                    temp->next = input;
                }
            }
        }
        
        input->accountno = accountnum;
        strcpy(input->name, name);
        strcpy(input->address, address);

    }

    return success;
}

/******************************************************************
//    
//   Function name:       printRecord
//
//   Description:         Prints out the account information.
//
//   Parameters:          accountnum (int): The account #
//
//   Return Values:       0 : success
//
********************************************************************/

int llist::printRecord (int accountnum)
{
    record * temp = NULL;
    int success = -1;

    temp = start;
  
    #ifdef DEBUGMODE
        cout << "\n=== Entering printRecord() ===\n";
        cout << "Passing in:\nAccount #: " << accountnum << endl;
        cout << "================================\n\n";
    #endif
 
    while (temp != NULL && success == -1)
    {
        if (accountnum == temp->accountno)
        {
            success = -0;
            cout << "Account #: " << temp->accountno << endl;
            cout << "Name: " << temp->name << endl;
            cout << "Address: " << temp->address << endl;
        }
        
        temp = temp->next;
    }

    return success;
}

/*******************************************************************
//   
//   Function name:        modifyRecord
//
//   Description:          Changes the address of an account.
//
//   Parameters:           accountnum (int): The account #.
//                         address (char []): The modified address.
//
//   Return values:        0 : success
//
********************************************************************/

int llist::modifyRecord (int accountnum, char address [])
{
    record * temp = NULL;
    int success = -1;

    #ifdef DEBUGMODE
        cout << "\n=== Entering modifyRecord ===\n";
        cout << "Passing in:\nAccount #: " << accountnum << endl;
        cout << "Address: " << address << endl;
        cout << "=============================\n\n";
    #endif

    temp = start;

    while (temp != NULL && success == -1)
    {
        if (accountnum == temp->accountno)
        {
            success = 0;
            strcpy(temp->address, address);
        }
        temp = temp->next;
    }

    return success;
}

/*******************************************************************
//   
//   Function name:        deleteRecord
//
//   Description:          Deletes a record from the database.
//
//   Parameters:           accountnum (int): The account #.
//
//   Return Values:        0 : success
//
********************************************************************/

int llist::deleteRecord (int accountnum)
{
    record * temp = NULL;
    record * remove = NULL;
    record * prev = NULL;
    int success = -1;
    int counter = 0;

    #ifdef DEBUGMODE
        cout << "\n=== Entering deleteRecord() ===\n";
        cout << "Passing in:\nAccount #: " << accountnum << endl;
        cout << "=============================\n\n";
    #endif

    temp = start;

    while (temp !=NULL && success == -1)
    {
        if (accountnum < temp->accountno)
        {
            counter++;
            temp = temp->next;
        }
        else if (accountnum == temp->accountno)
        {
            success = 0;
        }
        else 
        {
            temp = temp->next;
        }
    }

    if (success == 0)
    {
        if (counter == 0)
        {
            if (temp->next == NULL)
            {
                delete temp;
                start = NULL;
            }
            else
            {
                start = temp->next;
                delete temp;
            }
        }
        else
        {
            temp = start;

            while (success <= counter - 1)
            {
                prev = temp;
                temp = temp->next;
                success++;
            }

            if (temp->next == NULL)
            {
                prev->next = NULL;
                delete temp;
            }
            else
            {
                remove = temp;
                temp = temp->next;
                prev->next = temp;
                delete remove;
            }
        }
        success = 0;
    }

    return success;
}

/********************************************************************
//   
//   Function name:        reverse
//
//   Description:          Reverses the list
//
//   Parameters:           N/A
//
//   Return Values:        N/A
//
*********************************************************************/

void llist::reverse()
{
    #ifdef DEBUGMODE
        cout << "=== Entering reverse() ===\n";
    #endif

    start = reverse(start);
}

/********************************************************************
//   
//   Function name:        readfile
//
//   Description:          Reads the database.
//
//   Parameters:           N/A
//
//   Return Values:        0 : success
//                         -1 : failed
//
*********************************************************************/

int llist::readfile()
{
    ifstream file (filename);
    int success = 0;
    int accountno = 0;
    char name [1000];
    char address [1000];
    string line;   

    #ifdef DEBUGMODE
        cout << "\n=== Entering readfile() ===\n";
    #endif
 
    if (!file.is_open())
    {
        success = -1;
    }
    else
    {
        while ( getline (file, line) )
        {
            accountno = atoi( line.c_str() );
            getline (file, line);
            strcpy(name, line.c_str());
            getline (file, line);
            strcpy(address, line.c_str());

            this->addRecord(accountno, name, address);
        }

        file.close();
    }

    return success;
}

/********************************************************************
//   
//   Function name:        writefile
//
//   Description:          Writes to the database.
//
//   Parameters:           N/A
//
//   Return Values:        0 : success
//                         -1 : failed
********************************************************************/

int llist::writefile()
{
    ofstream inputFile (filename);
    record * temp;
    temp = start;
    int success = 0;
    
    #ifdef DEBUGMODE
        cout << "=== Entering writefile function ===";
    #endif

    if (!inputFile.is_open())
    {
        success = -1;
    }
    else
    {
        while (temp != NULL)
        {
            inputFile << temp->accountno << endl;
            inputFile << temp-> name << endl;
            inputFile << temp->address << endl;
            temp = temp->next;
        }

    inputFile.close();

    }

    return success;
}

/*******************************************************************
//  
//  Function name:         reverse
//
//  Description:           Reverses the list.
//
//  Parameters:            start (record *): start of the linked list
//
//  Return values:         Returns a record *
//
********************************************************************/

record * llist::reverse(record * head)
{
    #ifdef DEBUGMODE
        cout << "=== Entering reverse(record *) function ===\n";
    #endif

    if (head == NULL || head->next == NULL)
    { 
        return head;
    }

    record * temp = reverse(head->next);
    head->next->next = head;
    head->next = NULL;

    return temp;
}

/*******************************************************************
//   
//   Function name:        cleanup
//
//   Description:          Releases all the heap space.
//
//   Parameters:           N/A
//
//   Return values:        N/A
//
*******************************************************************/

void llist::cleanup()
{

    record * temp = NULL;
    record * prev = NULL;
    temp = start;

    #ifdef DEBUGMODE
        cout << "\n=== Entering cleanup function ===\n";
    #endif


    while (temp != NULL)
    {
        #ifdef DEBUGMODE
            cout << "Clean Up!\n";
        #endif

        prev = temp;
        temp = temp->next;
        delete prev;
    }

    if (start != NULL)
    {
        start = NULL;
    }
}

/******************************************************************
//    
//    Function name:      operator<<
//
//    Description:        Operator overloading "<<". Prints out all
//                        the records.
//
//    Parameters:         stream (ostream&): ostream object
//                        list (llist &): llist class being overloaded
//
//    Return values:      ostream&
//
********************************************************************/

ostream& operator << (ostream& stream, llist& list)
{

    #ifdef DEBUGMODE
        cout << "=== Entering operator << function ===\n";
    #endif

    record * temp = NULL;

    temp = list.start;

    while (temp != NULL)
    {
        stream << "============================" << endl;
        stream << "Account #: " << temp->accountno << endl;
        stream << "Name: " << temp->name << endl;
        stream << "Address: " << temp->address << endl;
        stream << "============================" << endl;

        temp = temp->next;
    }
    
    return stream;
}


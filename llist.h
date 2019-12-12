/***************************************************************
//     
//     Name:          Jennifer Hsu
//
//     Class:         ICS 212
//
//     Instructor:    Ravi Narayan
//
//     Date:          Nov. 22, 2019
//
//     File name:     llist.h
//
//     Description:
//       Containing the definitions for the llist class.
//
****************************************************************/

#ifndef LLIST_H
#define LLIST_H
#include "record.h"
#include <iostream>

class llist
{
private:
    record *    start;
    char        filename[16];
    int         readfile();
    int         writefile();
    record *    reverse(record * );
    void        cleanup();

public:
    llist();
    llist(char[]);
    llist(const llist&);
    llist& operator =(const llist&);
    ~llist();
    int addRecord(int, char [ ],char [ ]);
    int printRecord(int);
    int modifyRecord(int, char [ ]);
    int deleteRecord(int);
    void reverse();
    friend std::ostream& operator<<(std::ostream&, llist&);
};

#endif

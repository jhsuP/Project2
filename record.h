/******************************************************************
//
//  Name:          Jennifer Hsu
//
//  Homework:      3b
//
//  Class:         ICS 212
//
//  Instructor:    Ravi Narayan
//
//  Date:          Sept. 23, 2019
//
//  File:          record.h
//
//  Description:
//   This file contains the structure for record.
// 
*******************************************************************/

#ifndef RECORD_H
#define RECORD_H

struct record
{
    int                accountno;
    char               name[25];
    char               address[80];
    struct record*     next;
}; 

#endif

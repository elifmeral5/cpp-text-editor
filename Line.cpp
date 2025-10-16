/*                                                                                                                                                                                                       
  File: Line.cpp                                                                                                                                                                                           
                                                                                                                                                                                                           
  Project: CMSC 202 Project 3, Spring 2025  
                                                                                                                                                                                                           
  Author: Elif Meral                                                                                                                                                                                       
                                                                                                                                                                                                           
  Date: 03/29/25                                                                                                                                                                                           
                                                                                                                                                                                                           
  Section: 10/14                                                                                                                                                                                           
                                                                                                                                                                                                          
  E-mail: elifm1@umbc.edu                                                                                                                                                                               
                                                                                                                                                                                                       
  Description: This file contains the Line class function definitions                                                                                                                                   
               Which represents a node in a linked list used for storing text.                                                                                                                            
*/
#include "Line.h"
#include <iostream>
#include <string>
using namespace std;

//CONSTRUCTORS

//Line()
//Default Constructor - Creates an empty line (acts as linked list node)
Line::Line(){
  m_text = "";
  m_next = nullptr;
}

//Line(string text)
//Overloaded Constructor - Creates a line with the passed value and a nullptr (acts as linked list node)
Line::Line(string text){
  m_text = text;
  m_next = nullptr;
}

//GETTERS

//GetText()
//Returns the text stored in this node
string Line::GetText(){return m_text;}

//GetNext()
//Returns next line in the document
Line* Line::GetNext(){return m_next;}

//SETTERS

//SetText(string text)
//Sets the text in this node
void Line::SetText(string text){m_text = text;}

//SetNext(Line* next)
//Sets next line in document
void Line::SetNext(Line* next){m_next = next;}


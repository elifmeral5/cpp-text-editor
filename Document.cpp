/*                                                                                                                                                                                        
  File: Document.cpp                                                                                                                                                                                        
                                                                                                                                                                                                           
  Project: CMSC 202 Project 3, Spring 2025                                                                                                                                                                
                                                                                                                                                                                                           
  Author: Elif Meral                                                                                                                                                                                       
                                                                                                                                                                                                           
  Date: 03/29/25                                                                                                                                                                                          
                                                                                                                                                                                                           
  Section: 10/14                                                                                                                                                                                           
                                                                                                                                                                                                           
  E-mail: elifm1@umbc.edu                                                                                                                                                                                  
                                                                                                                                                                                                           
  Description: This file contains the Document class function definitions                                                                                                                                 
                 This includes...                                                                                                             
*/
#include "Document.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Document()
//Default Constructor - sets m_head to nulptr and m_lineCount to 0
Document::Document(){
  m_head = nullptr;
  m_lineCount = 0;
}

//~Document()
//Destructor - Removes all lines and sets m_head to nullptr and m_lineCount to 0
Document::~Document(){
  Line* curr;

  //Continues to delete lines as long as lines existt
  while(m_head){

    //Sets pointer to the beginning
    curr = m_head;
    //sets head to the next line
    m_head = m_head->GetNext();
    //deletes current line
    delete curr;
  }
  
  m_head = nullptr;  //sets head to nullptr
  m_lineCount = 0;   //resets line count
}

//FUNCTIONS

//InsertLine(string text, int position)
//Inserts a new line at chosen position
void Document::InsertLine(string text, int position){
  Line* newLine = new Line(text);   // Create a new Line object

  position -= 1;     //Sets position to be 1 less than the users choice to properly insert new line

  //If the new line is at the beginning
  if(position == 0){
    newLine->SetNext(m_head);
    m_head = newLine;
  }
  //If the new line is not at the beginning
  else{

    //sets the pointer to the beginning
    Line* curr = m_head;

    //Traverses through to get to the right line
    for(int i = 0; i < position - 1; i++){
      curr = curr->GetNext();
    }

    //sets the next pointer of newLine to point to the node after curr
    newLine->SetNext(curr->GetNext());

    //sets next pointer of curr to point to newLine
    curr->SetNext(newLine);
  }

  //increases number of lines
  m_lineCount++;
}

//DeleteLine(int position)
//Deletes a line at the chosen position
void Document::DeleteLine(int position){
  Line* curr = m_head;  //Sets pointer to the first line 

  position -= 1;   //Sets position to be 1 less than users choice to access correct line

  //If the first line is deleted the pointer is set to the next line
  if(position == 0){
    m_head = curr->GetNext();
    delete curr;
  }
  
  //If the first line is not being deleted
  else{

    //Traverses to specific line
    for(int i = 0; i < position - 1; i++){
      curr = curr->GetNext();
    }

    //Temporary pointer for the current line to be set to the next line
    Line* temp = curr->GetNext();
    curr->SetNext(temp->GetNext());

    //Deletes line
    delete temp;
  }
  
  //Reduces the number of lines count  by 1
  m_lineCount--;
}

//EditLine(int position, string newText)
//Edits the line at given position
void Document::EditLine(int position, string newText){
  Line* curr = m_head; //sets pointer to the first line

  //Traverses to the specfic line
   for (int i = 0; i < position - 1; i++) {
        curr = curr->GetNext();
   }

   //Changes text of the current line
   curr->SetText(newText);
}

//DisplayDocument()
//Displays all the lines in the document
void Document::DisplayDocument(){
  int count = 1;  //first line number to be displayed
  Line* curr = m_head; //sets pointer to the first line 

  //continues to display lines as long as there are remaining lines
  while(curr){
    cout << count << ". " << curr->GetText() << endl;
    //Pointer is set to next line
    curr = curr->GetNext();
    //Line number is increased
    count++;
  }

}

//SearchWord(string word)
//Indicates whether or not the searched work is found 
void Document::SearchWord(string word){

  Line* curr = m_head;  //Sets pointer to the first line 
  int count = 1;        //sets first line number

  //continues to look through lines as long as there are remaining lines
  while(curr){

    //if the word is found, it gets printed
    if (curr->GetText().find(word) != string::npos) {
      cout << "Word found in Line " << count << ": " << curr->GetText() <<  endl;
    }
    //pointer is set to the next line
    curr = curr->GetNext();
    //increases line number for the next line
    count++;
  }
}

//SaveToFile(string filename)
//Writes all the lines from the document to the fie
void Document::SaveToFile(string filename){
  //creates an output file stream
  ofstream file(filename);
  
  //lets user know if the file is not saved properly
  if (!file.is_open()) {
    cout << "File was not saved successfully." << endl;
    return;
  }

  Line* curr = m_head;  //Create a new Line object

  //Continues as long as the linked list has lines
  while (curr != nullptr) {
    file << curr->GetText() << endl;
    //Moves pointer to the next line
    curr = curr->GetNext();  
  }
  
  file.close();
  cout << "File saved successfully! "<< endl;
}

//LoadFromFile(string filename)
//loads all the lines from the file to the document
void Document::LoadFromFile(string filename){
  //opens file
  ifstream file(filename);

  //lets user know if the file is not loaded properly
  if (!file.is_open()) {
    cout << "File was not loaded successfully." << endl;
    return;
  }

  string text;     //Will hold each line from the file as it is read

  //reads file line by line until there are no more lines
  while (getline(file, text)) {
    
    Line* newLine = new Line(text);  // Create a new Line object

    //If the list is empty, set new line as the head
    if (m_head == nullptr) {
      m_head = newLine; 
    }
    
    //If the list is not emmpty 
    else {
      Line* curr = m_head;

      //Traverses the listt
      while (curr->GetNext() != nullptr) {
	curr = curr->GetNext();  // Traverse to the end of the list
      }

      //Appends the new line at the end
      curr->SetNext(newLine);
    }

    //Increases the line count each time a line is loaded
    m_lineCount++;
  }
  
  file.close();
  cout << "File loaded successfully!" << endl;

  
}

//GetLineCount()
//Gets the number of lines in the file
int Document::GetLineCount(){return m_lineCount;}

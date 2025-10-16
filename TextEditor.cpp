/*                                                                                                                                                                                                        
  File: TextEditor.cpp

  Project: CMSC 202 Project 3, Spring 2025                                                                                                                                                                 
                                                                                                                                                                                                           
  Author: Elif Meral                                                                                                                                                                                       
                                                                                                                                                                                                           
  Date: 03/29/25                                                                                                                                                                                           
                                                                                                                                                                                                           
  Section: 10/14                                                                                                                                                                                           
                                                                                                                                                                                                           
  E-mail: elifm1@umbc.edu                                                                                                                                                                                  
                                                                                                                                                                                                           
  Description: This file contains the Document class function definitions                                                                                                                                  
                 This includes...                                                                                                                                                                         
*/
#include "TextEditor.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//TextEditor()
//Default Constructor - Sets the file name to be empty
TextEditor::TextEditor(){
  m_fileName = "";
}

//MainMedu()
//Displays options
int TextEditor::MainMenu(){
  int choice = 0;     //Users choice of action

  //Continues to display main menu as long as choice is not  between 1 and 8
  while (choice < 1 || choice > 8){
    cout << "\n\n--- Simple Text Editor --" << endl;
    cout << "1. Insert Line" << endl;
    cout << "2. Delete Line" << endl;
    cout << "3. Edit Line" << endl;
    cout << "4. Display Document" << endl;
    cout << "5. Search Word" << endl;
    cout << "6. Save to File" << endl;
    cout << "7. Load From File" << endl;
    cout << "8. Exit" << endl;
    cout << "Enter your choice: ";

    //Sets users choice
    cin >> choice;

    //ignores any leftover input
    cin.ignore();
  }

  return choice;
}

//GetLineNumber
//Allows the user to choose a specific line
int TextEditor::GetLineNumber(bool isExact){
  int lineNumber = 0;     //Users chosen line number
  cout << "Enter line number: " << endl;

  //sets line number
  cin >> lineNumber;

  //ignores any leftover input
  cin.ignore();

  //If statement used for DeleteLine() and EditLine() function 
  if (isExact){

    //Continues as long as user has chosen a number between 1 and existing amont of lines
    while (lineNumber < 1 || lineNumber > m_editor.GetLineCount()){
      cout << "\n\nMust be between 1 and " << m_editor.GetLineCount() << endl;
      m_editor.DisplayDocument();
      cout << "Enter line number: " << endl;
      cin >> lineNumber;
      cin.ignore();
    }
  }
  
  //Used for InsertLine() functioon
  else{

    //Continues as long as user has chosen a number between 1 and existing amont of lines + 1
    while (lineNumber < 1 || lineNumber > m_editor.GetLineCount() + 1){
      cout << "\n\nMust be between 1 and " << m_editor.GetLineCount() + 1 << endl;
      m_editor.DisplayDocument();
      cout << "Enter line number: " << endl;
      cin >> lineNumber;
      cin.ignore();
    }
  }
  
  return lineNumber;
}

//GetFileName
//Gets the file name
string TextEditor::GetFileName(){
  cout << "Enter the file name:" << endl;
  getline(cin,m_fileName);

  return m_fileName;
}

//Start
//Runs the main program
void TextEditor::Start(){
  int choice = 0;     //Sets user choice to 0

  //Runs as long as user does not choose 8
  while (choice != 8){

    //choice is set by the mainMenu function
    choice = MainMenu();
    
    switch (choice){
      //Insert line case
    case 1:
      InsertLine();
      break;
      
      //Delete line case
    case 2:
      DeleteLine();
      break;

      //Edit line case
    case 3:
      EditLine();
      break;

      //Displays document
    case 4:
      cout << "\n\n**Display Document**" << endl;
      m_editor.DisplayDocument();
      break;

      //Search document case
    case 5:
      SearchDocument();
      break;

      //Saves file
    case 6:
      SaveFile();
      break;

      //Loads file
    case 7:
      LoadFile();
      break;

      //Thanks and exists
    case 8:
      cout << "\n\nThank you for using the UMBC Text Editor" << endl;
      break;
      
    default:
      cout << "Error" << endl;
    }
  }
}

//InsertLine
//inserts new line into the document
void TextEditor::InsertLine(){
  cout << "\n\n**Insert Line**" << endl;

  //if there are no existing lines, the user can just add text
  if (m_editor.GetLineCount() == 0){
    string text = "";   //users chosen text
    cout << "Enter text: ";
    getline(cin, text);
    m_editor.InsertLine(text,1);
  }

  //if there are existing lines
  else{
    cout << "Inserts line before chosen number" << endl;
    m_editor.DisplayDocument();
    int lineNum = 0;       //Users chosen line number to insert
    lineNum = GetLineNumber(false);
    string text = "";     //users chosen text
    
    cout << "\n\nEnter text: ";
    getline(cin, text);
    m_editor.InsertLine(text,lineNum);
  }
}

//DeleteLine                                                                                                                                                                 
//Deletes a chosen line from the document
void TextEditor::DeleteLine(){
  cout << "\n\n**Delete Line**" << endl;
  m_editor.DisplayDocument();

  //If there are not lines in the document
  if (m_editor.GetLineCount() == 0){
    cout << "empty document" << endl;
  }

  //If there are existing lines in the document
  else{
    int lineNum = 0;     //Users chosen line number
    lineNum = GetLineNumber(true);
    m_editor.DeleteLine(lineNum);
  }
}

//EditLine
//Edits a chosen line from the document
void TextEditor::EditLine(){
  cout << "\n\n**Edit Line**" << endl;
  m_editor.DisplayDocument();

  //If there are no lines 
  if (m_editor.GetLineCount() == 0){
    cout << "empty document" << endl;
  }

  //If there are existing lines in the document
  else{
    int lineNum = 0;     //users chosen line number to edit
    lineNum = GetLineNumber(true);
    
    string text = "";   //User chosen new text
    cout << "\n\nEnter new text: " ;
    getline(cin, text);
    m_editor.EditLine(lineNum, text);
  }
}

//SearchDocument
//Checks document for chosen word or character
void TextEditor::SearchDocument(){
  cout << "\n\n**Search Document**" << endl;

  //If there are no lines
  if (m_editor.GetLineCount() == 0){
     cout << "empty document" << endl;
   }

  //If there are existing lines in the document
  else{
    cout << "Enter word to search:" << endl;
    string word = "";     //Users chosen word to search
    cin.ignore();
    getline(cin, word);
    m_editor.SearchWord(word);
  }
}


//LoadFile
//Loads File
void TextEditor::LoadFile(){
  string fileName = "";    //Users chosen file name

  //ignores any leftover input
  cin.ignore();     
  
  cout << "Enter the file name: " << endl;
  getline(cin, fileName);

  //Loads from file
  m_editor.LoadFromFile(fileName);
}

//SaveFile
//Saves File
void TextEditor::SaveFile(){
  string fileName = "";    //Users chosen file name

  //ignores any leftover input
  cin.ignore();
  
  cout << "Enter the file name: " << endl;
  getline(cin, fileName);

  //Saves to file
  m_editor.SaveToFile(fileName);
}

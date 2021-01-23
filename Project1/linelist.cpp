
#include <iostream>
#include "linelist.h"

LineList::LineList()
{
	LineNode *line = new LineNode;
	LineNode *line2 = new LineNode;

	line -> info = topMessage;
	currLine = line;
	currLineNum = 1;
	length = 0;
	line2 -> info = bottomMessage;
	currLine -> back = NULL;
	currLine -> next = line2;
	line2 -> back = line;
	line2 -> next = NULL;
}

void LineList::goToTop() 
{
	// Post : Advances currLine to line 1
	while(currLine -> info != topMessage){
	  currLine = currLine -> back;
	}
        currLine = currLine -> next;
	currLineNum = 1;
}

void LineList::goToBottom() 
{
	// Post : Advances currLine to last line
	while(currLine -> next -> info != bottomMessage){
	  currLine = currLine -> next;
	}
}

void LineList::insertLine(string newLine)
{
	// post : newLine has been inserted after the current line
	if (currLine -> info == bottomMessage){
	  //start out w/ currline pointing to top
	  movePrevLine();
	}	
  //create and fill line pointer
  LineNode *line = new LineNode;
  line -> info = newLine; 
  line -> back = currLine;
  line -> next = currLine -> next;

  //insert line into list
  currLine -> next -> back = line;
  currLine -> next = line;
  //points to new line
  currLine = currLine -> next;

  //handle the private variables of LineNode
  length++;
  currLineNum++;

}

void LineList::deleteLine()
{
	// post : deletes the current line leaving currentLine
	//	  pointing to line following line
	if(currLine == NULL){
	  return;
	}  

	  currLine -> next -> back = currLine -> back;
	  currLine -> back -> next = currLine -> next;
	  currLine = currLine -> back;
}

void LineList::printList() 
{
  //make new LineNode so we don't have to modify the original, then set it to the top of the list
  int LineNum = 1;
  LineNode* pLine = currLine;
  int pLineNum = currLineNum;
  goToTop();

  LineNode *line = currLine;
  //print out until 
  while(line -> info != bottomMessage){
    cout << LineNum << "> " << line -> info << endl;
    line = line -> next;
    LineNum++;
  }
 
  currLine = pLine;
  currLineNum = pLineNum;
 
}

string LineList::getCurrLine() const
{
  return (currLine -> info);   

}

void LineList::moveNextLine()
{
	// Post : Advances currLine (unless already at last line)
  if((currLine -> next != NULL) && (currLine -> info != bottomMessage)){
  	currLine = currLine -> next;
	currLineNum++;
  }
}

void LineList::movePrevLine()
{
	// Post : Advances currLine (unless already at last line)
  if(currLine -> back -> info != topMessage){
    currLine = currLine -> back;
    currLineNum--;
  }
}

int LineList::getCurrLineNum() const
{
  return(currLineNum);

}

int LineList::getLength() const
{
  return(length);
}

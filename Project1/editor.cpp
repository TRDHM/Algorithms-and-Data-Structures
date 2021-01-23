#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "linelist.h"
#include <sstream>


namespace fscope{
	ifstream infile; //input file pointer
	string filename; //input filename
}

using namespace fscope; //global directive
using namespace std;
void OpenFile(char *filename, LineList &l);
bool Editor(LineList &l);
void CleanUp(LineList &l, char *filename);


int main(int argc, char *argv[1]){
	if(argv[1] == NULL){
		cout << "Error: No file entered" << endl;
		exit(1);
	}
	char* arg = argv[1];
	LineList l;	
	OpenFile(arg, l);
	l.printList();
	Editor(l);	
	CleanUp(l, arg);
  return 0;
}


void OpenFile(char *filename, LineList &l){
	ifstream infile(filename); 
	string line;
	while (infile){
		getline(infile, line);
		l.insertLine(line); 
	}
	infile.close();
}

bool Editor(LineList &l){
  char arg;
  do{    
 	cout << l.getCurrLineNum() << ">";	
	cin >> arg;
	    
	    if(arg == 'I') {
		string str;
		getline(cin, str);
		l.insertLine(str);
	    }
	    else if(arg == 'D')  {
		l.deleteLine();
	    }
	    else if(arg == 'L')  {
		l.printList();
	    }
	    else if(arg == 'P') {
		l.movePrevLine();
	    }
	    else if(arg == 'N'){
  		l.moveNextLine();
	    }
  }while (arg != 'E');
}

void CleanUp(LineList &l, char *filename){
	string s;
	int i = 1;
	ofstream outfile(filename);
	l.goToTop();
	while (i != l.getLength()){
	  outfile << l.getCurrLine() << endl;
	  i++;
	  l.moveNextLine();
	}	
	outfile.close();
}

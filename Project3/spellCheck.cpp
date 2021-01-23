#include<fstream>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<algorithm>



using namespace std;
#include"HashTable.h"
#include"BinarySearchTree.h"


struct BNode{
	string word;
	int lineNum;
	bool operator < (BNode otherStruct) const{
		return (word < otherStruct.word);
	}
};

typedef BinarySearchTree<BNode> BST;
ostream & operator << (ostream & out, BNode & temp) {
	out << temp.word << " " << temp.lineNum;
	return out;

}





void insertDict(HashTable HT);
void fileInput(char* file, HashTable HT, HashTable ADD, BST BT, string misspelled[500], int lineNums[500]);
void suggestSpelling(string word, HashTable HT);
void  handleMenu(HashTable HT, BST BT, HashTable ADD, string misspelled[500], int lineNums[500]);
bool checkAdded(string word, HashTable HT, HashTable ADD);



int main(int argc, char *argv[1]){
  BNode nf = {"ZZZ", -1};
  BST BT(nf);
  HashTable HT(5000);
  HashTable ADD(1000);
  string misspelled[500];
  int lineNums[500];


  //string dict(argv[1]);
  insertDict(HT);
  char* file = argv[1];
  fileInput(file, HT, ADD, BT, misspelled, lineNums);  
  handleMenu( HT, BT, ADD, misspelled, lineNums);
 


  return 0;
}



bool checkAdded(string word, HashTable HT, HashTable ADD){
  if(HT.find(word) || ADD.find(word)){
	return true;
  }

  else{
    return false;
  }
}




void handleMenu(HashTable HT, BST BT, HashTable ADD, string misspelled[500], int lineNums[500]) {
  string cIn;
  int i = 0;
  while(true){
    

    //placeholder; will hold the string passed from BT that is the next mispelled word
    string currWord = misspelled[i];
    int currLine = lineNums[i]; 
    
    if(!checkAdded(currWord, HT, ADD)){
    /*   i++;
       currLine = lineNums[i];
       currWord = misspelled[i];
       cout << currWord << " found in dictionary or ignored" << endl;
    */

 
    cout<<"	    Spell Checker Program"<<endl;
      
    cout << currWord << " was not found in dictionary on line " << currLine << endl;
    cout << "A) Add Word to Dictionary" << endl;
    cout << "I) Ignore Word, Skip in the Future" << endl;
    cout << "G) Go to Next Word" << endl;
    cout << "S) Search For Suggested Spelling" << endl;
    cout << "Q) Quit Spell Checker" << endl;

    cin >> cIn;
    //make sure command is lower case before handling 
	tolower(cIn[0]);

     /* if(cIn != "a" || cIn != "i" || cIn != "g" || cIn != "s" || cIn != "q"){
  	  cout << "Selection error - Please try again" << endl;
      }*/

 
      if(cIn == "a"){
  	  HT.insert(currWord);
 	  ofstream add;
	  add.open("dict.txt", fstream::app);
	  add << currWord << endl;
	  add.close(); 
      }

      if(cIn == "i"){
 	  ADD.insert(currWord);	
	  if(ADD.find(currWord)){
	  	  cout << currWord << " added to Ignored list" << endl;
	  }
      }

      if(cIn == "g"){
	  cout << "\033[2J\033[1;1H";
      }

      if(cIn == "s"){
	  suggestSpelling(currWord, HT);
      }

      if(cIn == "q"){
 	  cout << "Now Exiting" << endl;
	  break;
      }
    
      //increment counter for BNode arrays

      //clears screen after every selection;
      cout <<"Press Enter to Continue" << endl;
      cin.get();
      cout << "\033[2J\033[1;1H";
    }
   i++;
  }
}


void suggestSpelling(string word, HashTable HT){
  //switch every adjacent set of letters up until length - 1 of the word
   string wCopy;
   bool isFound = false;
   
   for(int i = 0; i < (word.length() - 1); i++){
   //create a fresh copy of word every time
        wCopy = word;
	char curr;
	//switch the adjacent letters
  	curr = wCopy[i];
	wCopy[i] = wCopy[i+1];
	wCopy[i+1] = curr;	

	if(HT.find(wCopy) == true){
	  isFound = true;
	  cout << "Suggested Spelling: " << wCopy << endl;
	  cin.get();
	  break;
	}
  }
   if (isFound != true){
	cout << "No recommended spelling could be found, sorry" << endl;
	cin.get();
   }
 
   
}






void fileInput(char* file, HashTable HT, HashTable ADD, BST BT, string misspelled[500], int lineNums[500]) {
  //takes input filename and reads it into the BST


  ifstream infile(file);
  string word;
  string currWord;
  int lineNum = 1;
  int x = 0; 
  while(!infile.is_open()){
	cout << file << " could not be found" << endl;

  }

  //reads in word by word
  while(infile >> word){
    //makes all letters lowercase and removes non letters
   
    
    for(int l = 0; l < word.length(); l++){
      word[l] = tolower(word[l]);
    }
   
    string tempWord = "";
    
   
    for(int j = 0; j < word.size(); j++){
      if(isalpha(word[j])){
 	tempWord += word[j];
      }
    }
    
   
    word = tempWord;
 

    if(word != ""){
    //makes sure word hasn't been ADD to ignored or dict
      if(!HT.find(word) || !ADD.find(word)){
  	  BNode bN = {word, lineNum }; 
	  BT.insert(bN);
	
	  misspelled[x] = word;
          lineNums[x] = lineNum;
      }
    }
    x++; 
    lineNum++;
  

  ofstream out;
  out.open("notfound.txt");
  BT.printTree(out);
  out.close();

 }
}


void insertDict(HashTable HT){
 //takes the input file name for the dictionary and then populates the hash table 

 ifstream inFile;
 inFile.open("dict.txt");
 string word; 

  while(inFile >> word){
   HT.insert(word);
  }
}


/* Daniel Mitchell PostFix calculator */

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include "dsexceptions.h"
#include "stack.h"

class Underflow;
class Overflow;
class OutOfMemory;
class BadIterator;
class DivisionByZero;
class DataError;
class float_exception{};
class InvalidOperator{};


void runCalc(Stack<int>& s);
string parseInput(string& input);
void handleInput(Stack<int>& s, string input);
bool isNum( char c);
bool isOperator(string o);
bool isCommand(const string& input);
int toInt(string& input);


int main(){
  Stack<int> s;
  
  runCalc(s);

  return 0;
}

void runCalc(Stack<int>& s) {
  
    string input, parsed;
    while(getline(cin,input)){

     while(!input.empty()){
      parsed = parseInput(input); 
      handleInput(s, parsed);
      }
    }
}

string parseInput(string& input){
 try{
  string s = "";

  if(input[0] == '_'){
    s +="-";
    input.erase(0,1);
  }
  
  while( isNum(input[0]) && isNum(input[1])){
  	s += input[0];
	input.erase(0,1);
  }

  while(isCommand(input.substr(0,0)) && isCommand(input.substr(1,1))){
	s += input.substr(0,0);
	input.erase(0,1);
  }

    s += input[0];
    input.erase(0,1);
    return s;

 }

 catch(DataError exc){
	cerr << "Invalid Input" << endl;
 }
}

void handleInput (Stack<int>& s, string input){
 try{
  int num;

  //Pre: takes the parsed input, determines what it is, then acts accordingly
  
  if(isOperator(input)){

	int num1;
	int num2;
	int num3;
	num2 = s.top();
	s.pop();
	num1 = s.top();
	s.pop();
 
	if(input == "+"){ 
		num3 = num1 + num2;
		s.push(num3);
	}

	else if(input == "-"){
                 
		num3 = num1 - num2;
		s.push(num3);
	}

	else if(input == "*"){
                 
		num3 = num1 * num2;
                s.push(num3);
        }

	else if(input == "/"){
             if ( num2 == 0){
		throw DivisionByZero( );
 	     } 
		num3 = num1 / num2;
                s.push(num3);
	     

        }

	else if(input == "%"){                 
		num3 = num1 % num2;
                s.push(num3);
   	  
	}

   }
    

  else if (isCommand(input)) {
    
    Stack<int> s2;

    	if( input == "p"){
		cout << s.top() << endl;	
	}

	else if( input == "n"){
		cout << s.top();
		s.pop();
	}

	else if( input == "f"){

		while(!s.isEmpty()){
			s2.push(s.top());
			s.pop();
			cout << s2.top() << endl;
		} 
	
		while (s2.top() ){
			s.push(s2.top());
			s.pop();
		}
	}

	else if(input == "c"){
		while(!s.isEmpty()){
			s.pop();
		}
        }

	else if(input == "d") {
	 	int d; 
		d = s.top();
		s.pop();
		s.push(d * d);	
        }		

	else if(input == "r"){
		int n; 
		n = s.top();
		s.pop();

		int r; 
		r = s.top();
		s.pop();

		s.push(r);
		s.push(n);
	}
  }
  else if (isNum(input[0])){
 
     int s1;
     s1 = toInt(input);
     s.push(s1);
   }

  else {
	throw InvalidOperator ( );
  }
  
}

   catch (DataError exc){
	cerr << "Invalid data \n";
   }

   catch (DivisionByZero exc){
    	cerr << "Division by zero not allowed :( \n";
   }

   catch (Underflow exc){
	cerr << "Not enough numbers on stack \n";
   }

   catch (Overflow exc){
	cerr << "Sorry that's too much stuff \n";
   }

   catch (float_exception exc){
 	cerr << "Result not an integer, sorry \n";
   }

   catch (InvalidOperator exc){
	cerr << "Invalid Input \n";
   }
   
 }
 


bool isNum( char c){
  
  return (c >= '0' && c <= '9');
}

int toInt(string& input){

  return atoi(input.c_str());
}

bool isOperator(string o){
 
  if(o == "+" || o == "-" || o == "*" || o == "/" || o == "%"){ 
    return true;
  }
 
  return false;
}

bool isCommand(const string& input){
 
  if(input == "p" || input == "n" || input == "f" || input == "c" || input == "d" || input == "r" || input == " "){
    
     return true;
  }
  return false;
}


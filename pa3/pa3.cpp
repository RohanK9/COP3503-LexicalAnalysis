#include "pa3.h"
using namespace std;

//method to get the depth of nester for loops
int getDepth(stack findDepth);

//method to find the number of for statements in the .txt file
int forCount(stack findForCount);

//method to find the number of begin statements in the .txt file
int beginCount(stack findForCount);

//method to find the number of end statements in the .txt file
int endCount(stack findEndCount);

int main(){

	//user inputs the name of the .txt file that is supposed to be opened
	cout << "Please enter the name of the input file:" << endl;
	string fileName;
	cin>>fileName;

	fstream file;

	//string into which .txt while will be read
	string inputTxt;

	const char * fileNameToString = fileName.c_str();
	file.open(fileNameToString);

	//opens .txt file and reads it into string inputTxt
	if(file.is_open()){
		while(file.good()){
			string temp;
			file >> temp;
			inputTxt = inputTxt + temp + " ";
		}
	}

	//if the file can not be found
	else{
		cout << endl << "Could not find " << fileName << endl;
		return 0;
	}

	file.close();

	//inputLength is the lenght of the inputTxt string
	int inputLength = inputTxt.length();

	//stack to keep track of parentheses
	stack parenthesisStack;

	//stack to keep track of syntax errors
	stack errorStack;

	//stack to keep track of delimiters 
	stack delemiterStack;

	//booleans to ensure each delimiter only appears once in delimiter stack
	bool commaFirstInstance = true;
	bool semiFirstInstance = true;

	//stack to keep track of operators
	stack operatorStack;

	//booleans to ensure each operator only appears once in operator stack
	bool plusFirstInstance = true;
	bool minusFirstInstance = true;
	bool multiplyFirstInstance = true;
	bool divideFirstInstance = true;
	bool equalFirstInstance = true;
	bool incrementFirstInstance = true;

	//stack to keep track of constants
	stack constantStack;

	//stack to keep track of keywords
	stack keywordStack;
	
	//stack to keep track of idenitifiers
	stack idenitifierStack;

	//stack to keep track of keywords without removing duplicates
	stack loopStack;

	//this is the main for loop used to iterate over string inputTxt
	for(int i = 0; i < inputLength; i++){

		//start of check for uneven parentheses
		if(inputTxt.at(i) == '('){
			parenthesisStack.push("(");
		}
		else if(inputTxt.at(i) == ')'){
			if(parenthesisStack.isEmpty()){
				if(!errorStack.contains(")")){
					errorStack.push(")");
				}
				//errorStack.push(")");
			}
			else{
				parenthesisStack.pop();
			}
		}
		//end of check for uneven parentheses

		//start of check for delimiters
		if(inputTxt.at(i) == ',' && commaFirstInstance){
			delemiterStack.push(",");
			commaFirstInstance = false;
		}
		else if(inputTxt.at(i) == ';' && semiFirstInstance){
			delemiterStack.push(";");
			semiFirstInstance = false;
		}
		//end of check for delimiters

		//start of check for operators
		if(inputTxt.at(i) == '+' && plusFirstInstance){
			operatorStack.push("+");
			plusFirstInstance = false;
		}
		 else if(inputTxt.at(i) == '-' && minusFirstInstance){
		 	operatorStack.push("-");
		 	minusFirstInstance = false;
		 }
		 else if(inputTxt.at(i) == '*' && multiplyFirstInstance){
		 	operatorStack.push("*");
		 	multiplyFirstInstance = false;
		 }
		 else if(inputTxt.at(i) == '/' && divideFirstInstance){
		 	operatorStack.push("/");
		 	divideFirstInstance = false;
		 }
		 else if(inputTxt.at(i) == '=' && equalFirstInstance){
		 	operatorStack.push("=");
		 	equalFirstInstance = false;
		 }
		 else if(inputTxt.at(i) == '+' && inputTxt.at(i+1) == '+' && incrementFirstInstance){
		 	operatorStack.push("++");
		 	incrementFirstInstance = false;
		 }
		 //end of check for operators

		 //start of check for constants
		 if(isdigit(inputTxt.at(i))){
		 	string temp;
		 	while(isdigit(inputTxt.at(i))){
		 		temp = temp + inputTxt.at(i);
		 		++i;
		 	}
		 	if(!constantStack.contains(temp)){
		 		constantStack.push(temp);
		 	}
		 }
		 //end of check for constants

		 //check for keywords by first checking for uppercase letters
		 if(isupper(inputTxt.at(i))){

		 	//check if "FOR" character by character
		 	if(inputTxt.at(i) == 'F' && inputTxt.at(i+1) == 'O' && inputTxt.at(i+2) == 'R'){
		 		if(!keywordStack.contains("FOR")){
		 			keywordStack.push("FOR");
		 		}
		 		loopStack.push("FOR");
		 	}

		 	//check if "BEGIN" character by character
		 	else if(inputTxt.at(i) == 'B' && inputTxt.at(i+1) == 'E' && inputTxt.at(i+2) == 'G' && inputTxt.at(i+3) == 'I' && inputTxt.at(i+4) == 'N'){
		 		if(!keywordStack.contains("BEGIN")){
		 			keywordStack.push("BEGIN");
		 		}
		 		loopStack.push("BEGIN");
		 	}

		 	//check if "END" character by character
		 	else if(inputTxt.at(i) == 'E' && inputTxt.at(i+1) == 'N' && inputTxt.at(i+2) == 'D'){
		 		if(!keywordStack.contains("END")){
		 			keywordStack.push("END");
		 		}
		 		loopStack.push("END");
		 	}

		 	//check if the uppercase characters are anything besides "FOR", "BEGIN" or "END"
		 	//eg: "BEGAN"
		 	string temp1;
		 	for(int j = i; inputTxt.at(j) != ' '; ++j){
		 		temp1 = temp1 + inputTxt.at(j);
		 		i = j;
		 	}

		 	if(temp1 != "FOR" && temp1 != "BEGIN" && temp1 != "END"){
		 		if(!errorStack.contains(temp1)){
		 		errorStack.push(temp1);
		 		}
		 	}

		}

		//check for idenitifiers by first checking for lowercase letters
		if(islower(inputTxt.at(i))){
			string temp2;
			for(int j = i; islower(inputTxt.at(j)); ++j){
				temp2 = temp2 + inputTxt.at(j);
				i = j;
			}
			if(!idenitifierStack.contains(temp2)){
			idenitifierStack.push(temp2);
			}

		}
	//this is then end of the main for loop
	}

	//if parenthesis stack is empty and error stack does not already contain "(" then "(" is added to error stack
	if(!parenthesisStack.isEmpty()){
		if(!errorStack.contains("(")){
			errorStack.push("(");
		}
	}

	//integer to store the number of for statements
	int fCount = forCount(loopStack);

	//integer to store the number of begin statements
	int bCount = beginCount(loopStack);

	//integer to store the number of end statements
	int eCount = endCount(loopStack);

	//if end statement count is not equal to for statement count then "END" is added to error stack
	if(eCount != fCount){
		if(!errorStack.contains("END")){
			errorStack.push("END");
		}
	}

	//if begin statement count is not equal to for statement count then "BEGIN" is added to error stack
	if(bCount != fCount){
		if(!errorStack.contains("BEGIN")){
			errorStack.push("BEGIN");
		}
	}

	//prints the depth of for loops
	cout << endl << "The depth of nested loop(s) is " << getDepth(loopStack) << endl << endl;
	
	//prints the keywords
	cout << "Keywords: ";
	keywordStack.print();

	//prints identifiers
	cout << "Idenitifier: ";
	idenitifierStack.print();

	//prints constants
	cout << "Constant: ";
	constantStack.print();

	//prints operators 
	cout << "Operators: ";
	operatorStack.print();

	//prints delimiters
	cout << "Delimiter: ";
	delemiterStack.print();

	//prints syntax errors
	cout << endl;
	cout << "Syntax Error(s): ";
	errorStack.print();
	cout << endl;

	return 0;
	//end of main method
} 

//constructor for node class
node::node(){
	data = "";
	next = NULL;
}

//constructor for stack class
stack::stack(){
	head = NULL;
}

//pushes into stack
void stack::push(string toPush){
	node* temp = new node;
	temp->data = toPush;

	if(head == NULL){
		head = temp;
	}

	else{
		temp->next = head;
		head = temp;
	}
}

//pops the top element and returns its value
string stack::pop(){
	string topData;

	if(head == NULL){
		return "Empty stack";
	}

	else{
		topData = head->data;
		head = head->next;
		return topData;
	}
}

//prints the stack
void stack::print(){
	node* curr = new node;
	if(head == NULL){
		cout<<"NA"<<endl;
	}
	else{
	curr = head;
		while(curr->next != NULL){
			cout<<curr->data + " ";
			curr = curr->next;
		}
		cout<<curr->data + " ";
	}
	cout<<endl;
}

//checks to see if the stack is empty
bool stack::isEmpty(){
	if(head == NULL){
		return true;
	}
	else{
		return false;
	}
}

//checks to see if a node in the stack has the value that is being searched for
bool stack::contains(string toCheck){
	node* curr = new node;
	
	if(head != NULL){
		curr = head;
		while(curr->next != NULL){
			if(curr->data == toCheck){
				return true;
			}
			curr = curr->next;
		}
		if(curr->data == toCheck){
			return true;
		}
		return false;
	}
	return false;
}

int getDepth(stack findDepth){
	node* curr = findDepth.getHead();
	int count = 0;
	while(curr->next != NULL){
		if(curr->data == "FOR" && curr->next->data == "BEGIN"){
			++count;
		}
		curr = curr->next;
	}
	return count;
}

//getter method for stack class
node* stack::getHead(){
	return head;
}

int forCount(stack findForCount){
	node* curr = findForCount.getHead();
	int forCount = 0;
	while(curr != NULL){
		if(curr->data == "FOR"){
			++forCount;
		}
		curr = curr->next;
	}
	return forCount;
}

int beginCount(stack findBeginCount){
	node* curr = findBeginCount.getHead();
	int beginCount = 0;
	while(curr != NULL){
		if(curr->data == "BEGIN"){
			++beginCount;
		}
		curr = curr->next;
	}
	return beginCount;
}

int endCount(stack findEndCount){
	node* curr = findEndCount.getHead();
	int endCount = 0;
	while(curr != NULL){
		if(curr->data == "END"){
			++endCount;
		}
		curr = curr->next;
	}
	return endCount;
}



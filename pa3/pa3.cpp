#include "pa3.h"
using namespace std;

//did this commit make it

int main(){

	//user inputs the name of the .txt file that is supposed to be opened
	cout << "Please enter the name of the input file:" << endl;
	string fileName;
	cin>>fileName;

	fstream file;
	string inputTxt;

	const char * fileNameToString = fileName.c_str();
	file.open(fileNameToString);

	if(file.is_open()){
		while(file.good()){
			string temp;
			file >> temp;
			inputTxt = inputTxt + temp;
		}
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
	bool eqaulFirstInstance = true;
	bool incrementFirstInstance = true;

	for(int i = 0; i < inputLength; i++){

		if(inputTxt.at(i) == '('){
			parenthesisStack.push("(");
		}
		else if(inputTxt.at(i) == ')'){
			if(parenthesisStack.isEmpty()){
				errorStack.push(")");
			}
			else{
				parenthesisStack.pop();
			}
		}

		if(inputTxt.at(i) == ',' && commaFirstInstance){
			delemiterStack.push(",");
			commaFirstInstance = false;
		}
		else if(inputTxt.at(i) == ';' && semiFirstInstance){
			delemiterStack.push(";");
			semiFirstInstance = false;
		}

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
		 else if(inputTxt.at(i) == '=' && eqaulFirstInstance){
		 	operatorStack.push("=");
		 	eqaulFirstInstance = false;
		 }
		 else if(inputTxt.at(i) == '+' && inputTxt.at(i+1) == '+' && incrementFirstInstance){
		 	operatorStack.push("++");
		 	incrementFirstInstance = false;
		 }

	}

	if(!parenthesisStack.isEmpty()){
		errorStack.push("(");
	}
	errorStack.print();
	delemiterStack.print();
	operatorStack.print();

	

	return 0;
} 

node::node(){
	data = "";
	next = NULL;
}

stack::stack(){
	head = NULL;
}

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

void stack::print(){
	node* curr = new node;
	if(head == NULL){
		cout<<"empty stack"<<endl;
	}
	else{
	curr = head;
		while(curr->next != NULL){
			cout<<curr->data<<endl;
			curr = curr->next;
		}
		cout<<curr->data<<endl;
	}
}

string stack::peek(){
	if(head == NULL){
		return "Empty stack";
	}

	else{
		return head->data;
	}
}

bool stack::isEmpty(){
	if(head == NULL){
		return true;
	}

	else{
		return false;
	}

}
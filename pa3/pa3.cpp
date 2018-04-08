#include "pa3.h"
using namespace std;



int main(){

	//user inputs the name of the .txt file that is supposed to be opened
	cout << "Please enter the name of the input file:" << endl;
	string fileName;
	cin>>fileName;

	//contents of the .txt file is saved into inputTxt string
	string inputTxt;
	ifstream myfile(fileName);
	if(!myfile){
		return -1;
	}

	while(getline(myfile, inputTxt)){
		//cout << inputTxt << endl;
	}
	myfile.close();

	//inputLength is the lenght of the inputTxt string
	int inputLength = inputTxt.length();

	//stack to keep track of parentheses
	stack parenthesisStack;

	//stack to keep track of syntax errors
	stack errorStack;

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

	}

	if(!parenthesisStack.isEmpty()){
		errorStack.push("(");
	}
	errorStack.print();

	

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
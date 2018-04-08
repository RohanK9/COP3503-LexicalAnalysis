#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class node{
public:
	string data;
	node* next;
	node();
};

class stack{
private:
	node* head;

public:
	stack();
	void push(string toPush);
	string pop();
	string peek();
	void print();
	bool isEmpty();
};

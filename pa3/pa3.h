#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
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
	void print();
	bool isEmpty();
	bool contains(string toCheck);
	node* getHead();
};



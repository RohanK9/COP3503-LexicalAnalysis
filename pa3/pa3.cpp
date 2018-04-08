#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int main(){


	cout << "Please enter the name of the input file:" << endl;
	string fileName;
	cin>>fileName;

	string inputTxt;
	ifstream myfile(fileName);
	if(!myfile){
		return -1;
	}
	while(getline(myfile, inputTxt)){
		cout << inputTxt << endl;
	}
	myfile.close();

	int inputLength = inputTxt.length();

	for(int i = 0; i < inputLength; i++){
		if (inputTxt.at(i) == 'F' && inputTxt.at(i+1) == 'O' && inputTxt.at(i+2) == 'R'){
			cout << "wow a for loop" << endl;
		}
	}

	return 0;
} 
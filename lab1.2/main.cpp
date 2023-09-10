#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

#define BUFFER 30

using namespace std;

void user_input(string &inputDataFilename, string &outputDataFilename, string &firstWord, string &secondWord);

int file_handling(string inputDataFilename, string outputDataFilename, string firstWord, string secondWord);
int get_file_data(string inputDataFilename, string firstWord, string secondWord);
int put_file_data(string outputDataFilename, string firstWord, string secondWord);

int main() {

	string inputDataFilename;
	string outputDataFilename;
	string firstWord;
	string secondWord;

	user_input(inputDataFilename, outputDataFilename, firstWord, secondWord);

	if (file_handling(inputDataFilename, outputDataFilename, firstWord, secondWord)) {
		return -1;
	}

	return 0;

}

void user_input(string &inputDataFilename, string &outputDataFilename, string &firstWord, string &secondWord) {

	printf("Enter input data filename:>>"); cin >> inputDataFilename;
	printf("Enter output data filename:>>"); cin >> outputDataFilename;
	printf("Enter first word:>>"); cin >> firstWord;
	printf("Enter second word:>>"); cin >> secondWord;
	
}

void replace_all(string &line, string firstWord, string secondWord) {
	size_t startPos = 0;
	while ((startPos = line.find(firstWord, startPos)) != string::npos) {
		line.replace(startPos, firstWord.length(), secondWord);
		startPos += secondWord.length();
	}
}

int file_handling(string inputDataFilename, string outputDataFilename, string firstWord, string secondWord) {

	ifstream ftIn (inputDataFilename);
	ofstream ftOut (outputDataFilename);


	if (ftIn.is_open() && ftOut.is_open()) {
		string line;
		while(getline(ftIn, line)) {
			replace_all(line, firstWord, secondWord);	
			ftOut << line << endl;
		}
	}
	else {
		printf("INCORRECT: file doesn't exist!");
		ftIn.close();
		ftOut.close();
		return -1;
	}

	ftIn.close();
	ftOut.close();

	return 0;

}

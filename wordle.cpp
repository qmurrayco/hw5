#ifndef RECCHECK
// For debugging

// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <vector>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void blankCount(string givenCopy, int gIdx, vector<int>& blanks, int& blankC, string& floatString);
void binsert(string& givenCopy, vector<int>& blanks, int& blankC, int idx, string permString);
void permuteFloat(string& floatString, set<string>& floatsSet, int begin, int end);
void swap(char& a, char& b);
void floatHelper(string givenCopy, set<string>& permutedStrings, string floatString);

void abc(string givenWord, int wordIdx, set<string>& solutions, const set<string>& dict);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
	//given to me
	const string word = "-dd-d-";
	const string floatLetters = "xy";
	const set<string> beep = dict;

	//what I will generate in given function before beginning to recurse in the first helper
	string wordCopy = in;
	string floatCopy = floating;
	int floatIdx = 0;
	int floatLen = floatCopy.length();
	set<string> generatedSet;
	int wordIdx = 0;
	set<int> excludeIdx;
	int count = 0;
	set<string> solSet;

	if(floating != ""){
		floatHelper(in, generatedSet, floating);
	}
	else{
		generatedSet.insert(wordCopy);
	}
	

	set<string>::iterator iter = generatedSet.begin();
	for(; iter != generatedSet.end(); ++iter){
		//cout << *iter << endl;
		abc(*iter, 0, solSet, dict);
	}

	return solSet;
}


void abc(string givenWord, int wordIdx, set<string>& solutions, const set<string>& dict){
	
	if(wordIdx == givenWord.length()){
		//cout << givenWord << endl;
		if(dict.find(givenWord) != dict.end()){
			solutions.insert(givenWord);
		}
	}
	
	else if(givenWord[wordIdx] != '-'){
		abc(givenWord, wordIdx + 1, solutions, dict);
	}

	else if(givenWord[wordIdx] == '-'){
		for(int i = 97; i < 123; i++){
			char letter = i;
			givenWord[wordIdx] = letter;
			abc(givenWord, wordIdx + 1, solutions, dict);
			givenWord[wordIdx] = '-';
		}
	}
}

void blankCount(string givenCopy, int gIdx, vector<int>& blanks, int& blankC, string& floatString){
	if(gIdx == givenCopy.length()){
		return;
	}

	else{
		if(givenCopy[gIdx] == '-'){
			blanks.push_back(gIdx);
			blankC++;
			if(blankC > floatString.length()){
				floatString += "-";
			}
		}
		blankCount(givenCopy, gIdx+1, blanks, blankC, floatString);
	}
}


void binsert(string& givenCopy, vector<int>& blanks, int& blankC, int idx, string permString){
	for(int i = blankC; i > 0; i--){
		givenCopy[blanks[idx]] = permString[idx];
		idx = idx + 1;
	}
}

void floatHelper(string givenWord, set<string>& permutedStrings, string floatString){
	int gIdx = 0;
	vector<int> blankIdx;
	int blankC = 0;
	set<string> floatSet;
	int idx = 0;
	// string givenCopy = givenWord;
	string newFloat = floatString;
	string gWord = givenWord;

	blankCount(gWord, 0, blankIdx, blankC, newFloat);

	permuteFloat(newFloat, floatSet, 0, newFloat.length()-1);


	set<string>::iterator floatSetIter = floatSet.begin();
	for(; floatSetIter != floatSet.end(); ++floatSetIter){
		string pString = *floatSetIter;
		string givenC = givenWord;
		binsert(givenC, blankIdx, blankC, idx, pString);
		permutedStrings.insert(givenC);
	}
}

void permuteFloat(string& floatString, set<string>& floatsSet, int begin, int end){
	//when begin equals end, we have completed permutation
	if(begin == end){
		floatsSet.insert(floatString);
	}
	else {
		for(int i = begin; i <= end; i++){

			swap(floatString[begin], floatString[i]);

			permuteFloat(floatString, floatsSet, begin + 1, end);

			swap(floatString[i], floatString[begin]);
		}
	}
}

void swap(char& a, char& b){
	char temp = a;
	a = b;
	b = temp;
}
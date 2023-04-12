#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
#include <vector>
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

	//display set
	// set<string>::iterator iter = generatedSet.begin();
	// for(; iter != generatedSet.end(); ++iter){
	// 	cout << *iter << endl;
	// }
	// cout << "count: " << count << " length: " << generatedSet.size() << endl;

	return solSet;
}

// void distributeFloat(string givenWord, string floatLetters, int wordIdx,
// 	set<int> excludeIdx, set<string>& generatedSet, int& count)
// {
// 	int floatRemain = floatLetters.length() - excludeIdx.size();
	

// 	if(floatLetters.length() - excludeIdx.size() == 0){
// 		//cout << givenWord << endl;
// 		count++;
// 		generatedSet.insert(givenWord);
// 	}
// 	else{
// 		for(int i = wordIdx; i < givenWord.length(); i++){
// 			//int wordRemain = givenWord.length() - i - 1;
// 			if(givenWord[i] == '-'){
// 				for(int j = 0; j < floatLetters.length(); j++){
// 					if(excludeIdx.find(j) == excludeIdx.end()){
// 						givenWord[i] = floatLetters[j];
// 						set<int> nextExcluded; 
// 						nextExcluded = excludeIdx;
// 						nextExcluded.insert(j);
// 						distributeFloat(givenWord, floatLetters, wordIdx + 1, nextExcluded, generatedSet, count);
// 						givenWord[i] = '-';
// 					}
// 				}
// 			}
// 		}
// 	}
// }

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
			//cout << givenWord << endl;
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
			//if we have more blanks than float, add blanks to permute
			if(blankC > floatString.length()){
				floatString += "-";
			}
		}
		blankCount(givenCopy, gIdx+1, blanks, blankC, floatString);
	}
}

//function to zip permutation into givenWord
// void binsert(string& givenCopy, vector<int>& blanks, int& blankC, int idx, string permString){
// 	if(blankC == -1){
// 		return;
// 	}

// 	else{
// 		givenCopy[blanks[idx]] = permString[idx];
// 		binsert(givenCopy, blanks, blankC - 1, idx + 1, permString);
// 	}
// }

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
	//cout << newFloat << endl;
	// for(int i = 0; i < blankIdx.size(); i++){
	// 	//cout << blankIdx[i] << " ";
	// }
	permuteFloat(newFloat, floatSet, 0, newFloat.length()-1);
	// string test = "wxyz";
	// permuteFloat(test, floatSet, 0, test.length()-1);
	// for(auto it= floatSet.begin(); it != floatSet.end(); ++it){
	// 	cout << *it << endl;
	// }

	// string var1 =  "string";
	// vector<int> var2;
	// var2.push_back(2);
	// int var3 = 2;
	// int var4 = 0;
	// string var5 = "dumbass";
	// binsert(var1, var2, var3, var4, var5);

	set<string>::iterator floatSetIter = floatSet.begin();
	for(; floatSetIter != floatSet.end(); ++floatSetIter){
		string pString = *floatSetIter;
		string givenC = givenWord;
		binsert(givenC, blankIdx, blankC, idx, pString);
		permutedStrings.insert(givenC);
		//cout << givenC << endl;
	}
}

void permuteFloat(string& floatString, set<string>& floatsSet, int begin, int end){
	//when begin equals end, we have completed permutation
	if(begin == end){
		floatsSet.insert(floatString);
	}
	else {
		for(int i = begin; i <= end; i++){
			// cout << "1 " << floatString << endl;

			swap(floatString[begin], floatString[i]);

			// cout << "2 " << floatString << endl;

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
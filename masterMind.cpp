#include <iostream>
#include "masterMind.h"
using namespace masterMindSpace;

//direction 0 parse self generated code, direction 1 parse guessed code from player
masterMind::Color masterMind::parseCode(int direction, int index){
	int count = 0;
	string code = "";
	
	while(count < RETRY_NUMBER){
		if(direction == 0){
			cout << "Generate color " <<(index+1)<< endl;
		}else{
			cout << "Guess color " <<(index+1)<< endl;
		}
		getline(cin, code);

		if(code.compare("Red") == 0){
			return masterMind::Color::RED;
		}else if(code.compare("Blue") == 0){
			return masterMind::Color::BLUE;
		}else if(code.compare("Yellow") == 0){
			return masterMind::Color::YELLOW;
		}else if(code.compare("White") == 0){
			return masterMind::Color::WHITE;
		}else if(code.compare("Brown") == 0){
			return masterMind::Color::BROWN;
		}else if(code.compare("Green") == 0){
			return masterMind::Color::GREEN;
		}else{
			cout << "Cannot recognize your input, please try again" << endl;
			count ++;	
			continue;
		}
	}
	return masterMind::Color::NO_MATCH;
}

int masterMind::generateReply(){
	int i=0;
	int whiteCount = 0;
	int blackCount = 0;
	unordered_map<Color, int, EnumClassHash> tmpMap = codeMap;
	Color tmpGuessArray[4];

	for(i=0; i<4; i++){
		tmpGuessArray[i] = guessArray[i];
	}
	//find if any code in correct color and position
	for(i=0; i<4; i++){
		if(codeArray[i] == tmpGuessArray[i]){
			blackCount++;
#ifdef DEBUG
			cout << "guess index: " << i << " guess color: " << (int)tmpGuessArray[i] << " code color: "<< (int)codeArray[i] <<" blackCount ++" << endl;
#endif	
			if(tmpMap.count(tmpGuessArray[i]) && tmpMap[tmpGuessArray[i]] > 0){
				tmpMap[tmpGuessArray[i]]--;
			}else{
				cout << "number of color is not consistent, game stopped" << endl;
				return -1;
			}
			//matched color in guess array don't need to be examined again.
			tmpGuessArray[i] = masterMind::Color::MATCHED;
		}
	}
	//find if any code in correct color but wrong position
	for(i=0; i<4; i++){
		if((codeArray[0] == tmpGuessArray[i] && tmpMap.count(tmpGuessArray[i]) && tmpMap[tmpGuessArray[i]]  > 0) || (codeArray[1] == tmpGuessArray[i] && tmpMap.count(tmpGuessArray[i]) && tmpMap[tmpGuessArray[i]] > 0)
			   || (codeArray[2] == tmpGuessArray[i] && tmpMap.count(tmpGuessArray[i]) && tmpMap[tmpGuessArray[i]] > 0) 
			   || (codeArray[3] == tmpGuessArray[i] && tmpMap.count(tmpGuessArray[i]) && tmpMap[tmpGuessArray[i]] > 0)){
			whiteCount++;
#ifdef DEBUG
			cout << "guess index: " << i << " guess color: " << (int)tmpGuessArray[i] << " code color: "<< (int)codeArray[i] <<" whiteCount ++" << endl;
#endif	
			tmpMap[tmpGuessArray[i]]--;
		}	
	}

	cout << "White: " << whiteCount << " Black: " << blackCount << endl;
	if(whiteCount == 0 && blackCount == 4)
		return 0;
	else
		return 1;
}

int masterMind::guessCode(){
	int i=0;
	for(i=0; i<4; i++){
		guessArray[i] = parseCode(1, i);
		if((int)guessArray[i] == 0){
			cout << "You enter unrecognized color 3 times, game stopped" << endl;
			return -1;
		}
#ifdef DEBUG
		cout << "input guess color is " << (int)guessArray[i] << endl;
#endif
	}
	return generateReply();
}

int masterMind::generateCode(){
	int i = 0;
	//unordered_map<Color, int, EnumClassHash>::iterator it;
	for(i=0; i<4; i++){
		codeArray[i] = parseCode(0, i);
		if((int)codeArray[i] == 0){
			cout << "You input unrecognized color more than 3 times, game finished" << endl;
			return -1;
		}
		codeMap[codeArray[i]]++;
#ifdef DEBUG
		cout << "input color is " << (int)codeArray[i] << endl;
		for(auto it : codeMap){
			cout << "key " << (int)it.first << " value " << (int)it.second << endl;
		}
#endif
	}
	return 0;
}

int masterMind::showGameInfo(){
	cout << "Welcome to gamemaster! Please choose 4 colors from colors \"Red, Blue, Yellow, White, Brown and Green.\"" << endl;
	cout << "You could choose duplicate color and get the response like \"White: 2 Black: 2\"." << endl;
	cout << "The number of Black in response means number of your choosen code is in the right color and position." << endl;
	cout << "The number of White in response means number of your choosen code is in the right color but wrong position." << endl;
	cout << "Once you got four black response, you crack the code and game is finished." << endl;
	cout << "You have 12 chances to crack the code. After 12 times trying, you fail and game is over" << endl;
	cout << endl <<"Press enter to continue." << endl;
	return 0;
}

#include <iostream>
#include "masterMind.h"

using namespace masterMindSpace;

int main(void){
	int count = 0;
	int retryNumber = 0;
	int ret = 0;
	string tmp = "";
	int option = 0;
	masterMind game;
	while(retryNumber <= RETRY_NUMBER){
		system("clear");
		cout << "Please choose from following options" << endl;
		cout << "\"0\". run the game" << endl;
		cout << "\"1\". see the instruction" << endl;
		cout << "\"2\". leave the game" << endl;
		getline(cin, tmp);
		option = stoi(tmp);
		if(option == 1){
			system("clear");
			game.showGameInfo();
			getchar();
		}else if(option == 2){
			cout << "Bye" << endl;
			break;
		}else if(option == 0){
			system("clear");
			if(game.generateCode() <0){
				return -1;
			}
			while(count < MAX_FAIL_NUMBER){
				cout << "=================== round " << count <<" ===================" << endl;
				ret = game.guessCode();
				if(ret == 0 ){
					cout << "You pass the game" << endl;
					break;
				}else if(ret <0){
					cout << "Unexpected error, game stopped" << endl;
					break;
				}
				count++;
			}
			cout << "You tried " << MAX_FAIL_NUMBER << " times, game over" << endl;
			break;
		}else{
			cout << "wrong option" << endl;
			retryNumber ++ ;
		}	
	}
	return 0;
}

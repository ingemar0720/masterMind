#ifndef MASTERMIND_H
#include <string>
#include <unordered_map>

#define MASTERMIND_H
//#define DEBUG 
#define RETRY_NUMBER 3
#define MAX_FAIL_NUMBER 12

using namespace std;
namespace masterMindSpace{
	struct EnumClassHash
	{
		template <typename T>
			std::size_t operator()(T t) const
			{
				return static_cast<std::size_t>(t);
			}
	};

	class masterMind{
		public: int guessCode();
				int generateCode();
				int showGameInfo();
		private: enum class Color {NO_MATCH = 0, RED, BLUE, YELLOW, WHITE, BROWN, GREEN};
				 Color codeArray[4];
				 Color guessArray[4];
				 unordered_map<Color, int, EnumClassHash> codeMap;

				 Color parseCode(int direction, int index);
				 int generateReply();
	};
}
#endif

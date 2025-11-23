#include <clocale>
#include <iostream>

int main(){
	std::setlocale(LC_ALL, "");
	
	int user_input;
	do {
		std::cout << "Обучайка приветствует тебя, мой юный ученик!" << std::endl;
		std::cout << "1 - Хочу учиться математике!" << std:endl;
		std::cout << "0 - лучше пойду полежу..." << std::endl;
		std::cout << "Обучайка > ";
		
		std::cin >> user_input;
		
		if (user_input == 1) {
		}
		else if (user_input == 0) {
			exit(0);
		}
		
		std::cout << std::endl;
	} while (true);
	
	return 0;
}
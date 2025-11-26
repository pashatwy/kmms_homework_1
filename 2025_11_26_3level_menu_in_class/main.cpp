#include <clocale>
#include <iostream>

#include "menu_item.hpp"
#include "menu.hpp"
#include "menu_function.hpp"

int main(){
	std::setlocale(LC_ALL, "");
	
	const gpi::MenuItem* current = &gpi::MAIN;
	do {
		current = current->func(current);
	} while (true);
	
	return 0;
}
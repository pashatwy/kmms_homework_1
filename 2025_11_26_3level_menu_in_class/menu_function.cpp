#include "menu_function.hpp"

#include <cstdlib>
#include <iostream>

namespace {
	const gpi::MenuItem* print_items(const gpi::MenuItem* current){
		for (int i = 1; i < current->children_count; i++){
			std::cout << current->children[i]->title << std::endl;
		}
		std::cout << current->children[0]->title << std::endl;
	
		int user_input;
		std::cin >> user_input;
		std::cout << std::endl;
		return current->children[user_input];
	}
}

const gpi::MenuItem* gpi::show_menu(const MenuItem* current){
	std::cout << "Главное меню: " << std::endl;
	return print_items(current);
}

const gpi::MenuItem* gpi::go_exit(const MenuItem* current){
	std::exit(0);
}

const gpi::MenuItem* gpi::itmo(const MenuItem* current){
	
	std::cout << current->title << std::endl << std::endl;
	return current->parent;
}

const gpi::MenuItem* gpi::politeh(const MenuItem* current){
	
	std::cout << current->title << std::endl << std::endl;
	return current->parent;
}

const gpi::MenuItem* gpi::leti(const MenuItem* current){
	
	std::cout << current->title << std::endl << std::endl;
	return current->parent;
}

const gpi::MenuItem* gpi::go_back(const MenuItem* current){
	
	std::cout << current->title << std::endl << std::endl;
	return current->parent->parent;
}

const gpi::MenuItem* gpi::university(const MenuItem* current){
	std::cout << "Выберите нужный университет:" << std::endl;
	return print_items(current);
}

const gpi::MenuItem* gpi::spbgu(const MenuItem* current){
	std::cout << "Выберите нужный факультет:" << std::endl;
	return print_items(current);
}

const gpi::MenuItem* gpi::pm_py(const MenuItem* current){
	
	std::cout << current->title << std::endl << std::endl;
	return current->parent;
}

const gpi::MenuItem* gpi::matmeh(const MenuItem* current){
	
	std::cout << current->title << std::endl << std::endl;
	return current->parent;
}

const gpi::MenuItem* gpi::language(const MenuItem* current){
	
	std::cout << current->title << std::endl << std::endl;
	return current->parent;
}

const gpi::MenuItem* gpi::go_univer(const MenuItem* current){
	
	std::cout << current->title << std::endl << std::endl;
	return current->parent->parent;
}
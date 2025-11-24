#include "menu_function.hpp"

#include <cstdlib>
#include <iostream>

const gpi::MenuItem* gpi::show_menu(const MenuItem* current){
	std::cout << "Обучайка приветствует тебя, мой ученик!" << std::endl;
	for (int i = 1; i < current->children_count; i++){
		std::cout << current->children[i]->title << std::endl;
	}
	std::cout << current->children[0]->title << std::endl;
	std::cout << "Обучайка > ";
	
	int user_input;
	std::cin >> user_input;
	std::cout << std::endl;
	
	return current->children[user_input];
}
	
const gpi::MenuItem* gpi::exit(const MenuItem* current){
	std::exit(0);
}

const gpi::MenuItem* gpi::study_summ(const MenuItem* current){
	
	std::cout << current->title << std::endl <<std::endl;
	return current->parent;
}

const gpi::MenuItem* gpi::study_substract(const MenuItem* current){
	
	std::cout << current->title << std::endl <<std::endl;
	return current->parent;
}

const gpi::MenuItem* gpi::study_multiply(const MenuItem* current){
	
	std::cout << current->title << std::endl <<std::endl;
	return current->parent;
}

const gpi::MenuItem* gpi::study_divide(const MenuItem* current){
	
	std::cout << current->title << std::endl <<std::endl;
	return current->parent;
}

const gpi::MenuItem* gpi::study_go_back(const MenuItem* current){
	
	std::cout << current->title << std::endl <<std::endl;
	return current->parent->parent;
}
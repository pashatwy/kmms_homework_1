#include <clocale>
#include <iostream>

#include "menu.hpp"
#include "menu_function.hpp"

int main(){
	std::setlocale(LC_ALL, "");
	
	gpi::MenuItem study_summ = { "1 - Хочу научиться складывать!", gpi::study_summ};
	gpi::MenuItem study_substract = { "2 - Хочу научиться вычитать!", gpi::study_substract};
	gpi::MenuItem study_multiply = { "3 - Хочу научиться умножать!", gpi::study_multiply};
	gpi::MenuItem study_divide = { "4 - Хочу научиться делить!", gpi::study_divide};
	gpi::MenuItem study_go_back = { "0 - Выйти в главное меню", gpi::study_go_back};

	gpi::MenuItem* study_children[]{
		&study_go_back,
		&study_summ,
		&study_substract,
		&study_multiply,
		&study_divide
	};
	const int study_size = sizeof(study_children)/sizeof(study_children[0]);
	
	gpi::MenuItem study = { "1 - Хочу учиться математике!", gpi::show_menu, study_children, study_size };
	gpi::MenuItem exit = { "0 - Я лучше пойду полежу...", gpi::exit};
	
	gpi::MenuItem* main_children[] = { &exit, &study };
	const int main_size = sizeof(main_children) / sizeof(main_children[0]);
	
	gpi::MenuItem main = { nullptr, gpi::show_menu, main_children, main_size };
	
	study_summ.parent = &study;
	study_substract.parent = &study;
	study_multiply.parent = &study;
	study_divide.parent = &study;
	study_go_back.parent = &study;
	
	study.parent = &main;
	exit.parent = &main;
	
	const gpi::MenuItem* current = &main;
	do {
		current = current->func(current);
	} while (true);
	
	return 0;
}
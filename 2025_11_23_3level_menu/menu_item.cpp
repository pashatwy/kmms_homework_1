#include "menu_item.hpp"

#include <cstddef>

#include "menu_function.hpp"

const gpi::MenuItem gpi::STUDY_SUMM = { 
	"1 - Хочу научиться складывать!", gpi::study_summ, &gpi::STUDY
};
const gpi::MenuItem gpi::STUDY_SUBSTRACT = {
	"2 - Хочу научиться вычитать!", gpi::study_substract, &gpi::STUDY
};
const gpi::MenuItem gpi::STUDY_MULTIPLY = {
	"3 - Хочу научиться умножать!", gpi::study_multiply, &gpi::STUDY
};
const gpi::MenuItem gpi::STUDY_DIVIDE = {
	"4 - Хочу научиться делить!", gpi::study_divide, &gpi::STUDY
};
const gpi::MenuItem gpi::STUDY_GO_BACK = {
	"0 - Выйти в главное меню", gpi::study_go_back, &gpi::STUDY
};

namespace {
	const gpi::MenuItem* const study_children[]{
		&gpi::STUDY_GO_BACK,
		&gpi::STUDY_SUMM,
		&gpi::STUDY_SUBSTRACT,
		&gpi::STUDY_MULTIPLY,
		&gpi::STUDY_DIVIDE
	};
	const int study_size = sizeof(study_children)/sizeof(study_children[0]);
}

const gpi::MenuItem gpi::STUDY = {
	"1 - Хочу учиться математике!", gpi::show_menu, &gpi::MAIN, study_children, study_size 
};
const gpi::MenuItem gpi::EXIT = {
	"0 - Я лучше пойду полежу...", gpi::exit, &gpi::MAIN
};

namespace{
	const gpi::MenuItem* const main_children[] = {
		&gpi::EXIT,
		&gpi::STUDY	
	};
	const int main_size = sizeof(main_children) / sizeof(main_children[0]);
}
	
const gpi::MenuItem gpi::MAIN = {
	nullptr, gpi::show_menu, nullptr, main_children, main_size
};

#include "menu_item.hpp"

#include <cstddef>

#include "menu_function.hpp"

const gpi::MenuItem gpi::LESSON_SUBJECT = {
	"0 - Вернуться к выбору предметов.", gpi::lesson_object, &MATHAN
};

const gpi::MenuItem gpi::ALGEBRA_SUMM = { 
	"1 - Хочу научиться складывать!", gpi::algebra_summ, &gpi::ALGEBRA
};
const gpi::MenuItem gpi::ALGEBRA_SUBSTRACT = {
	"2 - Хочу научиться вычитать!", gpi::algebra_substract, &gpi::ALGEBRA
};
const gpi::MenuItem gpi::ALGEBRA_MULTIPLY = {
	"3 - Хочу научиться умножать!", gpi::algebra_multiply, &gpi::ALGEBRA
};
const gpi::MenuItem gpi::ALGEBRA_DIVIDE = {
	"4 - Хочу научиться делить!", gpi::algebra_divide, &gpi::ALGEBRA
};

namespace {
	const gpi::MenuItem* const algebra_children[]{
		&gpi::LESSON_SUBJECT,
		&gpi::ALGEBRA_SUMM,
		&gpi::ALGEBRA_SUBSTRACT,
		&gpi::ALGEBRA_MULTIPLY,
		&gpi::ALGEBRA_DIVIDE
	};
	const int algebra_size = sizeof(algebra_children)/sizeof(algebra_children[0]);
}

const gpi::MenuItem gpi::MATHAN_DIF = {
	"1 - Хочу изучить дифферинциальное исчисление!", gpi::mathan_dif, &MATHAN
};
const gpi::MenuItem gpi::MATHAN_INTEGRALS = {
	"2 - Хочу изучить интегральное исчисление!", gpi::mathan_integrals, &MATHAN
};

namespace {
	const gpi::MenuItem* const mathan_children[] {
		&gpi::LESSON_SUBJECT,
		&gpi::MATHAN_DIF,
		&gpi::MATHAN_INTEGRALS
	};
	const int mathan_size = sizeof(mathan_children) / sizeof(mathan_children[0]);
}

const gpi::MenuItem gpi::ALGEBRA = {
	"1 - Хочу изучать алгебру!", gpi::show_menu, &gpi::STUDY, algebra_children, algebra_size,  "Утешев Алексей Юрьевич приветствует вас"
};
const gpi::MenuItem gpi::MATHAN = {
	"2 - Хочу изучать математический анализ!", gpi::show_menu, &gpi::STUDY, mathan_children, mathan_size, "Бочкарев Анатолий Олегович"
};
const gpi::MenuItem gpi::STUDY_GO_BACK = {
	"0 - Выйти в главное меню!", gpi::study_go_back, &gpi::STUDY,
};

namespace {
	const gpi::MenuItem* const study_children[] = {
		&gpi::STUDY_GO_BACK,
		&gpi::ALGEBRA,
		&gpi::MATHAN
	};
	const int study_size = sizeof(study_children) / sizeof (study_children[0]);
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

#include "menu_item.hpp"
#include <cstddef>
#include "menu_function.hpp"

const gpi::MenuItem gpi::PM_PY{
    " 1 - Факультет ПМ-ПУ ", gpi::pm_py, &gpi::SPBGU 
};
const gpi::MenuItem gpi::MAT_MEH{
    " 2 - Факультет МатМех", gpi::matmeh, &gpi::SPBGU 
};
const gpi::MenuItem gpi::LANGUAGE{
    " 3 - Лингвистический факультет", gpi::language, &gpi::SPBGU
};
const gpi::MenuItem gpi::GO_UNIVER{
    " 0 - Выйти в предыдущее меню ", gpi::go_univer, &gpi::SPBGU
};

namespace {
    const gpi::MenuItem* const spbgu_children[]{
        &gpi::GO_UNIVER,
        &gpi::PM_PY,
        &gpi::MAT_MEH,
        &gpi::LANGUAGE
    };
    const int spbgu_size = sizeof(spbgu_children) / sizeof(spbgu_children[0]);
}

const gpi::MenuItem gpi::SPBGU{
    " 1 - СПБГУ ", gpi::spbgu, &gpi::UNIVERSITY, spbgu_children, spbgu_size
};
const gpi::MenuItem gpi::ITMO{
    " 2 - ИТМО ", gpi::itmo, &gpi::UNIVERSITY
};
const gpi::MenuItem gpi::POLITEH{
    " 3 - Политех ", gpi::politeh, &gpi::UNIVERSITY
};
const gpi::MenuItem gpi::LETI{
    " 4 - ЛЭТИ ", gpi::leti, &gpi::UNIVERSITY
};
const gpi::MenuItem gpi::GO_BACK{
    " 0 - Выйти в главное меню ", gpi::go_back, &gpi::UNIVERSITY
};

namespace {
    const gpi::MenuItem* const university_children[]{
        &gpi::GO_BACK,
        &gpi::SPBGU,
        &gpi::ITMO,
        &gpi::POLITEH,
        &gpi::LETI
    };
    const int university_size = sizeof(university_children) / sizeof(university_children[0]);
}

const gpi::MenuItem gpi::UNIVERSITY{
    " 1 - Посмотреть университеты Санкт-Петербургa ", gpi::university, &gpi::MAIN, university_children, university_size 
};
const gpi::MenuItem gpi::GO_EXIT{
    " 0 - Я уже студент ", gpi::go_exit, &gpi::MAIN 
};

namespace {
    const gpi::MenuItem* const main_children[]{
        &gpi::GO_EXIT,
        &gpi::UNIVERSITY
    };
    const int main_size = sizeof(main_children) / sizeof (main_children[0]);
}

const gpi::MenuItem gpi::MAIN{
    nullptr, gpi::show_menu, nullptr, main_children, main_size
};
	
#pragma once

#include "menu.hpp"

namespace gpi {
	const MenuItem* show_menu(const MenuItem* current);
	
	const MenuItem* go_exit(const MenuItem* current);
	
	const MenuItem* university(const MenuItem* current);
	
	const MenuItem* spbgu(const MenuItem* current);
	const MenuItem* itmo(const MenuItem* current);
	const MenuItem* politeh(const MenuItem* current);
	const MenuItem* leti(const MenuItem* current);
	const MenuItem* go_back(const MenuItem* current);
	
	const MenuItem* pm_py(const MenuItem* current);
	const MenuItem* matmeh(const MenuItem* current);
	const MenuItem* language(const MenuItem* current);
	const MenuItem* go_univer(const MenuItem* current);
}
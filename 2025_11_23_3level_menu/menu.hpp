#pragma once

namespace gpi{
	struct MenuItem {
		const char* const title;
		void (*func)();
	};
}
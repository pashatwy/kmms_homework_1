target_sources(${LIBRARY}
	PRIVATE
		shell_sorting.cpp
	PUBLIC
		shell_sorting.hpp
)

target_include_directories(${LIBRARY} PUBLIC
	"${PROJECT_SOURCE_DIR}/src"
)
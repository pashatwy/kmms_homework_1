set(SOURCES 
	test_shell.cpp
)

add_executable(test_shell ${SOURCES})
target_link_libraries(test_shell 
	${LIBRARY}
	gtest_main 
	gmock_main 
)

add_test(ShellSortTest test_shell)
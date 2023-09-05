
CXX= @g++
CXXFLAGS= -std=c++17 -g -Wall -Werror -Wextra
CXXFLAGS_DEV= -std=c++17 -g
# GTESTFLAGS = -lgtest -lgmock -pthread -lstdc++
GTESTFLAGS = -lgtest -pthread -lstdc++

VGRND= CK_FORK=no valgrind --vgdb=no\
				--leak-check=full --show-leak-kinds=all\
				--trace-children=yes --track-origins=yes\
				-v --verbose -q --quiet -s

EXECUTABLE= s21_containers
TEST_EXEC = tests_containters
GCOV = gcov_report
SRC_GCOV_TEST = $(GCOV)/$(TEST_EXEC)

ALLFILE = $(wildcard tests/*.cc *.cc tests/*.h *.h *tpp)
SRC_MAIN= $(wildcard main.cc)
SRC_TESTS= $(wildcard tests/*.cc)
SRC_HEADERS= $(wildcard *.h)

TARGET_TESTS = array list map set multiset queue tree stack vector test
FILTER_TESTS_FLAG = $(if $(filter test,$@),*,$@)

$(TARGET_TESTS): clean $(TEST_EXEC)
	@echo "======= TESTS ======="
	@./$(TEST_EXEC) --gtest_filter=$(FILTER_TESTS_FLAG).*
	@rm $(TEST_EXEC)

$(TEST_EXEC): clean
	$(CXX) $(SRC_TESTS) -o $(TEST_EXEC) $(CXXFLAGS)  $(GTESTFLAGS) 

all: clean gcov_report

build_gcov_report: clean
build_gcov_report:
	@echo "======= MAKE GCOV REPORT ======="
	@mkdir -p -- $(GCOV)
	$(CXX) --coverage $(SRC_TESTS) -o $(SRC_GCOV_TEST) $(CXXFLAGS)  $(GTESTFLAGS)
	@./$(SRC_GCOV_TEST)
	lcov -t "test" -o ./$(GCOV)/test.info -c -d . --no-external
	genhtml -o ./$(GCOV)/report ./$(GCOV)/test.info

$(GCOV): build_gcov_report
	open ./$(GCOV)/report/index.html

clean:
	@rm -rf $(EXECUTABLE) $(TEST_EXEC)
	@rm -rf *.gcda *.gcno report test.info
	@rm -rf -- $(GCOV)
	@rm -rf tests_containters.dSYM

check_style:
	@cp ../materials/linters/.clang-format .
	@echo "======= CHECK GOOGLE CODE STYLE ======="
	clang-format -n $(ALLFILE)

do_style:
	@cp ../materials/linters/.clang-format .
	@echo "======= DO GOOGLE CODE STYLE ======="
	clang-format -i $(ALLFILE)

leak: main
	leaks -atExit -- ./$(EXECUTABLE)

leak_tests: clean $(TEST_EXEC)
	leaks -atExit -- ./$(TEST_EXEC)

main: clean
	$(CXX) $(CXXFLAGS_DEV) $(SRC_MAIN) -o $(EXECUTABLE)
	./$(EXECUTABLE)

VG: clean
	$(CXX) -g $(CXXFLAGS_DEV) $(SRC_MAIN) -o $(EXECUTABLE)
	$(VGRND) ./$(EXECUTABLE)

testVG: clean $(TEST_EXEC)
	$(VGRND) ./$(TEST_EXEC)
	rm $(TEST_EXEC)

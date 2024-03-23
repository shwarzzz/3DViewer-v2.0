CC = g++
CFLAGS = -std=c++17 -Wall -Werror -Wextra
SRC = ./model/*.cc ./modules/*.cc
TEST_SRC = ./tests/viewer_tests.cc
OBJ = *.o
LFLAGS = -lgtest
TARGET = 3D_Viewer_v2
GCOV_FLAGS = --no-external

ifeq ($(shell uname), Linux) 
	LFLAGS += -lpthread
endif

ifeq ($(shell uname), Darwin)
	TARGET = 3D_Viewer_v2.app
	GCOV_FLAGS += --ignore-errors mismatch 
endif

all: install

install:
	@echo "Installation of 3D Viewer v2.0:"
	@mkdir -p ../build
	@cd view && qmake && make && make clean && rm -rf Makefile && mv $(TARGET) ../../build/$(TARGET)
	@echo "Installation completed! You can find the app in the ../build/ folder!"
	
uninstall:
	@rm -rf ../build
	@echo "Uninstall completed!"
	
dist: 
	@mkdir -p ../dist
	@cp -R ../build/$(TARGET) ../dist
	@cd ../dist && tar cvzf $(TARGET).tgz *
	@echo "Archive creation completed successfully!"

tests: 3d_viewer.a
	@$(CC) $(CFLAGS) -c $(TEST_SRC)
	@$(CC) viewer_tests.o $(CFLAGS) $(LFLAGS) -L. 3d_viewer.a -o test
	./test

3d_viewer.a:
	$(CC) $(CFLAGS) -c $(SRC)
	ar rcs 3d_viewer.a $(OBJ)
	ranlib 3d_viewer.a
	rm -rf *.o

add_coverage:
	$(eval CFLAGS += --coverage)

gcov_report: clean add_coverage tests
	-./test
	lcov -t "test" -o test.info -c -d . $(GCOV_FLAGS)
	genhtml -o report test.info
	open report/index.html

check_format:
	clang-format -n -style=Google -verbose model/*.cc model/*.h 
	clang-format -n -style=Google -verbose controller/*.cc controller/*.h
	clang-format -n -style=Google -verbose view/*.cc view/*.h
	clang-format -n -style=Google -verbose modules/*.cc modules/*.h

formatting:
	clang-format -i -style=Google -verbose model/*.cc model/*.h 
	clang-format -i -style=Google -verbose controller/*.cc controller/*.h
	clang-format -i -style=Google -verbose view/*.cc view/*.h
	clang-format -i -style=Google -verbose modules/*.cc modules/*.h

valgrind: clean tests
	valgrind --tool=memcheck --leak-check=full --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./test

clean:
	rm -rf *.o *.a *.gcno *.gcda test test.info report

PHONY: all tests clean valgrind
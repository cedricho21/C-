CC = g++

all: install

install: uninstall
	mkdir build
	cd build && qmake ../3D_Viewer/frontend && make
	cd build && open 3D_Viewer.app

uninstall: clean
	rm -rf build

dvi_install:
	brew install doxygen

dvi:
	doxygen Doxyfile
	open html/index.html

dist: install
	tar cvzf 3D_Viewer.tgz build/

test: clean
	g++ tests/tests.cc 3D_Viewer/model.cc -o test -lgtest -pthread
	./test

gcov_report: clean
	$(CC) tests/tests.cc 3D_Viewer/model.cc -o tests/testing -lgtest -pthread --coverage
	./tests/testing
	lcov -d ./ --capture --output-file snake.info --ignore-errors mismatch --ignore-errors inconsistent
	genhtml snake.info --output-directory report
	open report/index.html

clang-check:
	cp ../materials/linters/.clang-format .
	clang-format -n 3D_Viewer/backend/*.cc 3D_Viewer/backend/*.h 3D_Viewer/frontend/*.cpp 3D_Viewer/frontend/*.h 
	rm ./.clang-format

clang-formatting:
	cp ../materials/linters/.clang-format .
	clang-format -i 3D_Viewer/backend/*.cc 3D_Viewer/backend/*.h 3D_Viewer/frontend/*.cpp 3D_Viewer/frontend/*.h
	rm ./.clang-format

clean:
	rm -rf *.a *.out *.o test *.html *.css
	rm -rf 3D_Viewer.tgz
	rm -rf *.g* *.info report
	rm -rf tests/testing*
	rm -rf html latex

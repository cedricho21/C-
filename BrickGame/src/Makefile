CC = g++

all: install

install: uninstall
	mkdir Game
	mkdir Game/console
	mkdir Game/desktop
	touch Game/console/high_score_tetris.txt
	touch Game/desktop/high_score_tetris.txt
	echo "0" >> Game/console/high_score_tetris.txt
	echo "0" >> Game/desktop/high_score_tetris.txt
	cd Game/desktop/ && qmake ../../gui/desktop && make
	g++ brick_game/tetris/s21_tetris.c brick_game/snake/controller.cpp brick_game/snake/model.cpp gui/console/s21_interface.cc -o Game/console/BrickGame -lncurses
	
open_desk:
	open Game/desktop/brickgame.app/Contents/MacOS/brickgame
	
open_console:
	./Game/console/BrickGame

uninstall:
	rm -rf Game

test: clean
	$(CC) tests/test_snake.cc brick_game/snake/controller.cpp brick_game/snake/model.cpp -o tests/testing -lgtest -pthread
	./tests/testing


gcov_report: clean
	$(CC) tests/test_snake.cc brick_game/snake/controller.cpp brick_game/snake/model.cpp -o tests/testing -lgtest -pthread --coverage
	./tests/testing
	lcov -d ./ --capture --output-file snake.info --ignore-errors mismatch --ignore-errors inconsistent
	genhtml snake.info --output-directory report
	open report/index.html
	
dist: uninstall install
	tar cvzf Snake.tgz Game/

dvi:
	open instruction.md

clean:
	rm -rf *.a *.out *.o test *.html *.css
	rm -rf *.g* *.info report *.txt *.tgz
	rm -rf tests/testing tests/*.gcda tests/*.gcno snake.info report

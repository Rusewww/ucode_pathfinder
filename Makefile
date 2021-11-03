all: pathfinder

pathfinder: libmx.a obj
	@clang -std=c11 -Wall -Wextra -Werror -Wpedantic obj/*.o libmx/libmx.a -o pathfinder -I inc

libmx.a: libmx/src/*.c libmx/inc/*.h
	@make -C libmx

obj: src/*.c inc/*.h
	@mkdir -p obj
	@clang -std=c11 -Wall -Wextra -Werror -Wpedantic -c src/*.c -I inc
	@mv *.o obj

clean:
	@rm -rf obj

uninstall: clean
	@rm -f pathfinder
	@make -C libmx uninstall

reinstall: uninstall all
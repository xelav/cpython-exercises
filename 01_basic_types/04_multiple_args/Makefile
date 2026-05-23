PYTEST = /workspaces/cpython_exercies/.venv/bin/pytest
CFLAGS = -shared -fPIC -Wall -Wuninitialized -Werror $(shell python3.13-config --includes --ldflags)

py_args.so: py_args.c
	gcc $(CFLAGS) -o $@ $<

test: py_args.so
	$(PYTEST) test_args.py -v

clean:
	rm -f py_args.so

test-valgrind: py_args.so
	valgrind --error-exitcode=1 --leak-check=full \
        $(PYTEST) test_args.py -v
 
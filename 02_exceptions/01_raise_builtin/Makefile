PYTEST = /workspaces/cpython_exercies/.venv/bin/pytest
CFLAGS = -shared -fPIC -Wall -Wuninitialized -Werror $(shell python3.13-config --includes --ldflags)

py_exceptions.so: py_exceptions.c
	gcc $(CFLAGS) -o $@ $<

test: py_exceptions.so
	$(PYTEST) test_exceptions.py -v

clean:
	rm -f py_exceptions.so

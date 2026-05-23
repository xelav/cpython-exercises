PYTEST = /workspaces/cpython_exercies/.venv/bin/pytest
CFLAGS = -shared -fPIC $(shell python3.13-config --includes --ldflags)

py_integers.so: py_integers.c
	gcc $(CFLAGS) -o $@ $<

test: py_integers.so
	$(PYTEST) test_integers.py -v

clean:
	rm -f py_integers.so

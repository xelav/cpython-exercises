PYTEST = /workspaces/cpython_exercies/.venv/bin/pytest
CFLAGS = -shared -fPIC -Wall -Wuninitialized -Werror $(shell python3.13-config --includes --ldflags)

py_exc_chain.so: py_exc_chain.c
	gcc $(CFLAGS) -o $@ $<

test: py_exc_chain.so
	$(PYTEST) test_exc_chain.py -v

clean:
	rm -f py_exc_chain.so

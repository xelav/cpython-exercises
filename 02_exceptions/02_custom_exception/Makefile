PYTEST = /workspaces/cpython_exercies/.venv/bin/pytest
CFLAGS = -shared -fPIC -Wall -Wuninitialized -Werror $(shell python3.13-config --includes --ldflags)

py_custom_exc.so: py_custom_exc.c
	gcc $(CFLAGS) -o $@ $<

test: py_custom_exc.so
	$(PYTEST) test_custom_exc.py -v

clean:
	rm -f py_custom_exc.so

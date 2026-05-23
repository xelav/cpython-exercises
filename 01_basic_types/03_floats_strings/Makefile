PYTEST = /workspaces/cpython_exercies/.venv/bin/pytest
CFLAGS = -shared -fPIC $(shell python3.13-config --includes --ldflags)

py_types.so: py_types.c
	gcc $(CFLAGS) -o $@ $<

test: py_types.so
	$(PYTEST) test_types.py -v

clean:
	rm -f py_types.so

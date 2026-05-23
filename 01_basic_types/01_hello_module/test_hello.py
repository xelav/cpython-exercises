import py_hello


def test_hello_returns_string():
    result = py_hello.hello()
    assert isinstance(result, str)
    print("OK!")


def test_hello_returns_correct_message():
    assert py_hello.hello() == "Hello World!"
    print("OK!")

if __name__ == "__main__":
    # py_hello.hello()
    test_hello_returns_string()
    test_hello_returns_correct_message()
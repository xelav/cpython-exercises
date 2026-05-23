import py_args
import pytest


def test_greet_default():
    assert py_args.greet("Alice") == "Hello, Alice!"

def test_greet_custom():
    assert py_args.greet("Bob", greeting="Hi") == "Hi, Bob!"

def test_greet_returns_str():
    assert isinstance(py_args.greet("X"), str)

def test_sum_all_multiple():
    assert py_args.sum_all(1, 2, 3) == 6

def test_sum_all_single():
    assert py_args.sum_all(42) == 42

def test_sum_all_empty():
    assert py_args.sum_all() == 0

def test_sum_all_negative():
    assert py_args.sum_all(-1, -2, 3) == 0

def test_greet_missing_name():
    with pytest.raises(TypeError):
        py_args.greet()

def test_greet_wrong_name_type():
    with pytest.raises(TypeError):
        py_args.greet(123)

def test_greet_wrong_greeting_type():
    with pytest.raises(TypeError):
        py_args.greet("Alice", greeting=42)

def test_greet_unknown_kwarg():
    with pytest.raises(TypeError):
        py_args.greet("Alice", typo="Hi")

def test_sum_all_wrong_type():
    with pytest.raises(TypeError):
        py_args.sum_all(1, "two", 3)

def test_sum_all_float_rejected():
    with pytest.raises(TypeError):
        py_args.sum_all(1.5, 2)

if __name__ == "__main__":
    test_greet_default()
    test_greet_custom()
    test_greet_returns_str()
    test_sum_all_multiple()
    test_sum_all_single()
    test_sum_all_empty()
    test_sum_all_negative()
    print("OK!")

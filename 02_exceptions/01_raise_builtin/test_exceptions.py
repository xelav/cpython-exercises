import pytest
import py_exceptions


def test_must_be_positive_valid():
    assert py_exceptions.must_be_positive(5) == 5

def test_must_be_positive_zero():
    with pytest.raises(ValueError):
        py_exceptions.must_be_positive(0)

def test_must_be_positive_negative():
    with pytest.raises(ValueError):
        py_exceptions.must_be_positive(-10)

def test_must_be_positive_message():
    with pytest.raises(ValueError, match="positive"):
        py_exceptions.must_be_positive(-1)


def test_safe_divide_valid():
    assert py_exceptions.safe_divide(10.0, 2.0) == pytest.approx(5.0)

def test_safe_divide_zero():
    with pytest.raises(ZeroDivisionError):
        py_exceptions.safe_divide(1.0, 0.0)

def test_safe_divide_negative_divisor():
    assert py_exceptions.safe_divide(-6.0, 2.0) == pytest.approx(-3.0)


def test_string_length_valid():
    assert py_exceptions.string_length("hello") == 5

def test_string_length_empty():
    assert py_exceptions.string_length("") == 0

def test_string_length_wrong_type_int():
    with pytest.raises(TypeError):
        py_exceptions.string_length(42)

def test_string_length_wrong_type_list():
    with pytest.raises(TypeError):
        py_exceptions.string_length([1, 2, 3])

def test_string_length_error_mentions_type():
    with pytest.raises(TypeError, match="int"):
        py_exceptions.string_length(42)

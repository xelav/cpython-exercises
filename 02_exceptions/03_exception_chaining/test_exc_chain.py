import pytest
import py_exc_chain


def test_parse_int_valid():
    assert py_exc_chain.parse_int("42") == 42

def test_parse_int_negative():
    assert py_exc_chain.parse_int("-7") == -7

def test_parse_int_invalid_raises():
    with pytest.raises(ValueError):
        py_exc_chain.parse_int("abc")

def test_parse_int_chained_cause():
    with pytest.raises(ValueError) as exc_info:
        py_exc_chain.parse_int("abc")
    assert exc_info.value.__cause__ is not None

def test_parse_int_cause_is_valueerror():
    with pytest.raises(ValueError) as exc_info:
        py_exc_chain.parse_int("abc")
    assert isinstance(exc_info.value.__cause__, ValueError)


def test_load_value_valid():
    assert py_exc_chain.load_value({"x": 10}, "x") == 10

def test_load_value_missing_key():
    with pytest.raises(KeyError):
        py_exc_chain.load_value({}, "x")

def test_load_value_wrong_type():
    with pytest.raises(TypeError):
        py_exc_chain.load_value({"x": "not_an_int"}, "x")

def test_load_value_missing_chained():
    with pytest.raises(KeyError) as exc_info:
        py_exc_chain.load_value({}, "x")
    assert exc_info.value.__cause__ is not None

def test_load_value_wrong_type_chained():
    with pytest.raises(TypeError) as exc_info:
        py_exc_chain.load_value({"x": "oops"}, "x")
    assert exc_info.value.__cause__ is not None

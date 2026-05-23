import math
import py_types


def test_circle_area_unit():
    assert math.isclose(py_types.circle_area(1.0), math.pi)

def test_circle_area_zero():
    assert py_types.circle_area(0.0) == 0.0

def test_circle_area_precision():
    assert math.isclose(py_types.circle_area(2.5), math.pi * 6.25)

def test_repeat_basic():
    assert py_types.repeat("ab", 3) == "ababab"

def test_repeat_once():
    assert py_types.repeat("hello", 1) == "hello"

def test_repeat_zero():
    assert py_types.repeat("x", 0) == ""

if __name__ == "__main__":
    test_circle_area_unit()
    test_circle_area_zero()
    test_circle_area_precision()
    test_repeat_basic()
    test_repeat_once()
    test_repeat_zero()
    print("OK!")

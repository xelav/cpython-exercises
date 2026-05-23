import py_integers


def test_add_positive():
    assert py_integers.add(2, 3) == 5

def test_add_negative():
    assert py_integers.add(-4, 4) == 0

def test_add_large():
    assert py_integers.add(1000000, 2000000) == 3000000

def test_absolute_positive():
    assert py_integers.absolute(7) == 7

def test_absolute_negative():
    assert py_integers.absolute(-7) == 7

def test_absolute_zero():
    assert py_integers.absolute(0) == 0

if __name__ == "__main__":
    test_add_positive()
    test_add_negative()
    test_add_large()
    test_absolute_positive()
    test_absolute_negative()
    test_absolute_zero()
    print("OK!")

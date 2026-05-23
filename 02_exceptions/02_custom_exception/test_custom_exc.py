import pytest
import py_custom_exc


def test_module_error_exists():
    assert hasattr(py_custom_exc, "ModuleError")

def test_module_error_is_exception():
    assert issubclass(py_custom_exc.ModuleError, Exception)

def test_validate_range_valid():
    assert py_custom_exc.validate_range(5, 1, 10) == 5

def test_validate_range_boundary_lo():
    assert py_custom_exc.validate_range(1, 1, 10) == 1

def test_validate_range_boundary_hi():
    assert py_custom_exc.validate_range(10, 1, 10) == 10

def test_validate_range_below():
    with pytest.raises(py_custom_exc.ModuleError):
        py_custom_exc.validate_range(0, 1, 10)

def test_validate_range_above():
    with pytest.raises(py_custom_exc.ModuleError):
        py_custom_exc.validate_range(11, 1, 10)

def test_validate_range_not_builtin():
    with pytest.raises(py_custom_exc.ModuleError):
        py_custom_exc.validate_range(0, 1, 10)
    # must NOT be a plain ValueError or Exception
    try:
        py_custom_exc.validate_range(0, 1, 10)
    except py_custom_exc.ModuleError:
        pass
    except Exception as e:
        pytest.fail(f"Expected ModuleError, got {type(e)}")


def test_parse_version_valid():
    assert py_custom_exc.parse_version("1.2.3") == (1, 2, 3)

def test_parse_version_zeros():
    assert py_custom_exc.parse_version("0.0.0") == (0, 0, 0)

def test_parse_version_too_few_parts():
    with pytest.raises(py_custom_exc.ModuleError):
        py_custom_exc.parse_version("1.2")

def test_parse_version_too_many_parts():
    with pytest.raises(py_custom_exc.ModuleError):
        py_custom_exc.parse_version("1.2.3.4")

def test_parse_version_non_integer():
    with pytest.raises(py_custom_exc.ModuleError):
        py_custom_exc.parse_version("1.x.3")

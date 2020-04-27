# Python interface for the Reflexxes Motion Libraries

The `setup.py` script will invoke CMake to build the module. The module can thus
be built and installed with e.g.
``` bash
    pip3 install --user . # or replace pip3 with pip
```
This library depends on
- python-dev
- pybind11 (Build from [source](https://github.com/pybind/pybind11/releases))
- libReflexxesTypeII (included in the source code)

#ifndef PYRMLVECTOR_H
#define PYRMLVECTOR_H

#include <RMLVector.h>

#include <boost/python.hpp>

template<typename T>
struct RMLVectorName {};

template<>
struct RMLVectorName<RMLVector<double>>
{
    static const char* value() { return "RMLDoubleVector"; }
};

template<>
struct RMLVectorName<RMLVector<int>>
{
    static const char* value() { return "RMLIntVector"; }
};

template<>
struct RMLVectorName<RMLVector<bool>>
{
    static const char* value() { return "RMLBoolVector"; }
};

// Print RMLVector to output steam (used by __repr__ / __str__)
template<typename T>
std::ostream& operator<<(std::ostream& os, const RMLVector<T>& v)
{
    os << RMLVectorName<RMLVector<T>>::value() << "([";

    for (unsigned i = 0; i < v.VectorDimension - 1; ++i) {
        os << v.VecData[i] << ", ";
    }

    os << v.VecData[v.VectorDimension - 1] << "])";
    return os;
}

// Copy RMLVector elements to Python list
template<typename T>
inline auto make_list(const RMLVector<T>& v)
{
    boost::python::list list;

    for (unsigned i = 0; i < v.VectorDimension; ++i) {
        list.append(v.VecData[i]);
    }

    return list;
}

// Create an RMLVector from a Python iterable
template<typename T>
std::shared_ptr<RMLVector<T>> make_vector(const boost::python::object& iterable)
{
    auto n = static_cast<unsigned>(len(iterable));

    if (n == 0)
        throw std::invalid_argument("RMLVector does not support being empty");

    auto v = std::make_shared<RMLVector<T>>(n);

    for (unsigned i = 0; i < n; ++i) {
        v->VecData[i] = boost::python::extract<T>(iterable[i]);
    }

    return v;
}

// Expose a template instantiation of RMLVector
template<typename T>
void expose_RMLVector()
{
    boost::python::class_<RMLVector<T>>(RMLVectorName<RMLVector<T>>::value(), boost::python::no_init)
        .def("__init__", boost::python::make_constructor(make_vector<T>))
        .def("__len__", &RMLVector<T>::GetVecDim)
        .def("__getitem__",
             +[](const RMLVector<T>& self, unsigned idx) {
                 if (idx >= self.VectorDimension)
                     throw std::out_of_range("RMLVector index out of range");
                 return self.VecData[idx];
             })
        .def("__setitem__",
             +[](RMLVector<T>& self, unsigned idx, const T& val) {
                 if (idx >= self.VectorDimension)
                     throw std::out_of_range("RMLVector index out of range");
                 self.VecData[idx] = val;
             })
        .def("__iter__", boost::python::range(+[](RMLVector<T>& self) { return self.VecData; }, +[](RMLVector<T>& self) { return self.VecData + self.VectorDimension; }))
        .def("__eq__", &RMLVector<T>::operator==)
        .def("__ne__", &RMLVector<T>::operator!=)
        .def("Set", &RMLVector<T>::Set)
        .def("tolist", +[](const RMLVector<T>& self) { return make_list(self); })
        .def(repr(boost::python::self))
    ;
}

#endif // PYRMLVECTOR_H
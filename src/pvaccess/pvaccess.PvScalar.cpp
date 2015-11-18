//
// PV Scalar class
//
class_<PvScalar, bases<PvObject> >("PvScalar", 
    "PvScalar is a base class for all scalar PV types. It cannot be instantiated directly from python.\n\n", 
    no_init)

    // use __int__ instead of .def(int_(self)) which requires operator::long()
    // use __float__ instead of .def(float_(self)) 
    .def("__int__", &PvScalar::toInt)

    .def("__long__", &PvScalar::toLongLong)

    .def("__float__", &PvScalar::toDouble)

    .def("__str__", &PvScalar::toString)
;

//
// PV UInt class
//
class_<PvUInt, bases<PvScalar> >("PvUInt", 
    "PvUInt represents PV unsigned int type.\n\n"
    "**PvUInt([value=0])**\n\n"
    "\t:Parameter: *value* (int) - unsigned integer value\n\n"
    "\t::\n\n"
    "\t\tpv = PvUInt(1000)\n\n", 
    init<>())

    .def(init<unsigned int>())

    .def("get", 
        &PvUInt::get, 
        "Retrieves unsigned integer PV value.\n\n"
        ":Returns: unsigned integer value\n\n"
        "::\n\n"
        "    value = pv.get()\n\n")

    .def("set", 
        &PvUInt::set, 
        args("value"), 
        "Sets unsigned integer PV value.\n\n"
        ":Parameter: *value* (int) - unsigned integer value\n\n"
        "::\n\n"
        "    pv.set(1000)\n\n")
;

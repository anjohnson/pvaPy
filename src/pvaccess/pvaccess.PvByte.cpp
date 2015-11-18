//
// PV Byte class
//
class_<PvByte, bases<PvScalar> >("PvByte", 
    "PvByte represents PV byte type.\n\n"
    "**PvByte([value=''])**\n\n"
    "\t:Parameter: *value* (str) - byte value\n\n"
    "\t::\n\n"
    "\t\tpv = PvByte('a')\n\n", 
    init<>())

    .def(init<char>())
    
    .def("get", 
        &PvByte::get, 
        "Retrieves byte PV value.\n\n"
        ":Returns: byte value\n\n::\n\n"
        "    value = pv.get()\n\n")

    .def("set", 
        &PvByte::set, 
        args("value"), 
        "Sets byte PV value.\n\n"
        ":Parameter: *value* (str) - byte value\n\n"
        "::\n\n"
        "    pv.set('a')\n\n")
;

// Here come typedefs and macros used for easier code writing

#pragma once

/* custom extendable enum class */
#define ExtendableEnum(enumname, operations) class enumname {private: int i; public: enumname(int newI = 0) { i = newI; } operator int() { return i; } operations }
#define ExtendableEnumElement(name, var) static const int name = var


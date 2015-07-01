// Here come typedefs and macros used for easier code writing

/* custom extendable enum class */
#define exEnum(enumname, operations) class enumname {private: int i; public: enumname(int newI = 0) { i = newI; } operator int() { return i; } operations }
#define enumElement(name, var) static const int name = var


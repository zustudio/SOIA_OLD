

#define MDLVECTOR gIA_RegisteredDataModules

#define registerM(module) MDLVECTOR.push_back(std::string(#module));

#define checkM(module) (std::find(MDLVECTOR.begin(), MDLVECTOR.end(), std::string(#module)) != MDLVECTOR.end())

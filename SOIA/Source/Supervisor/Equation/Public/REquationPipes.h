//
//#pragma once
//
//#include "RElement.h"
//
//namespace Supervisor
//{
//	RCLASS(REquationPipes, Environment::RElement);
//	class LIBIMPEXP REquationPipes : public REquationPipes_Base
//	{
//		RCLASS_BEGIN();
//
//		REquationPipes();
//
//		RFUNCTION(pipe_)
//			bool pipe_1DoubleTo2Double(const double& In, double& Out1, double& Out2);
//
//		RFUNCTION(pipe_IntToString)
//			bool pipe_IntToString(const int& In, std::string& Out);
//
//		RCLASS_END();
//	};
//}
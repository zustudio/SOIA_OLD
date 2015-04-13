
#include "Supervisor/Core/Classes/PrivateDefinitions.h"

#include "Supervisor/Logica/Public/SchroedingerApplication.h"
using namespace Supervisor;

#include "Environment/Mathematics/Runtime/Public/MathContainer.h"
#include "Environment/Mathematics/Runtime/Public/OP_Add.h"
#include "Environment/Mathematics/Runtime/Public/OP_Substract.h"
#include "Environment/Mathematics/Runtime/Public/OP_Multiply.h"
#include "Environment/Mathematics/Runtime/Public/OP_If.h"
#include "Environment/Mathematics/Runtime/Public/OP_CalculateFunction.h"
#include "Environment/Mathematics/Runtime/Public/Constant.h"
#include "Environment/Mathematics/Runtime/Public/Variable.h"
using namespace Environment;

#include "Graphics/Core/Public/Window.h"
#include "Graphics/ControlElements/Public/CGraph.h"
using namespace SO;
using namespace Graphics;

#define d(arguments) (runtime.DefineValue(arguments))

void SchroedingerApplication::Execute()
{
	MathContainer runtime = MathContainer();

	//create constants
	auto MinusC = runtime.DefineValue(new Constant(-1.6382e38));
	auto W = d(new Constant(95e-18));
	auto DeltaX = d(new Constant(5e-12));

	Value_ID &Psi = d(new Constant(0));
	Value_ID &PsiDot d(new Constant(0));

	auto PsiDotDot =
		d(new OP_Multiply(std::vector<Value_ID>({
			d(new OP_Multiply(std::vector<Value_ID>({
				MinusC,
				W }))),
			d(new OP_CalculateFunction(&runtime.FuncCache, std::vector<Value_ID>({
				Psi,
				d(new OP_Substract(std::vector<Value_ID>({
					d(new Variable(0, 0)),
					DeltaX }))) }))) })));

	runtime.RedefineValue(PsiDot, new OP_If(std::vector<Value_ID>({
		d(new Variable(0, 0)),
		d(new Constant(1)),
		d(new OP_Add(std::vector<Value_ID>({
			d(new OP_CalculateFunction(&runtime.FuncCache, std::vector<Value_ID>({
				PsiDot,
				d(new OP_Substract(std::vector<Value_ID>({
					d(new Variable(0, 0)),
					DeltaX }))) }))),
			d(new OP_Multiply(std::vector<Value_ID>({
				DeltaX,
				d(new OP_CalculateFunction(&runtime.FuncCache, std::vector<Value_ID>({
					PsiDotDot,
					d(new OP_Substract(std::vector<Value_ID>({
						d(new Variable(0, 0)),
						d(new Constant(0)) }))) }))) }))) }))) })));

	runtime.RedefineValue(Psi, new OP_If(std::vector<Value_ID>({
		d(new Variable(0,0)),
		d(new Constant(0)),
		d(new OP_Add(std::vector<Value_ID>({
			d(new OP_CalculateFunction(&runtime.FuncCache, std::vector<Value_ID>({
				Psi,
				d(new OP_Substract(std::vector<Value_ID>({
					d(new Variable(0, 0)),
					DeltaX }))) }))),
			d(new OP_Multiply(std::vector<Value_ID>({
				DeltaX,
				d(new OP_CalculateFunction(&runtime.FuncCache, std::vector<Value_ID>({
					PsiDot,
					d(new OP_Substract(std::vector<Value_ID>({
						d(new Variable(0, 0)),
						d(new Constant(0)) }))) }))) }))) }))) })));

	runtime.SetValueName(Psi, "Psi");
	runtime.SetValueName(PsiDot, "PsiDot");
	runtime.SetValueName(PsiDotDot, "PsiDotDot");


	Window* mainWindow = new Window("SchroedingerApplication");
	CGraph* mainGraph = mainWindow->AddControl<CGraph>();
	mainGraph->SizeMin = fPoint(0, -1e-10);
	mainGraph->SizeMax = fPoint(1e-10, 1e-10);
	mainGraph->DeltaX = 5e-12;

	FunctionObject functionObject = FunctionObject(&runtime, Psi);

	mainGraph->AddFunction(functionObject);

	mainWindow->Open();
}

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

#include "Environment/Reflection/ID/Public/RFunction.h"

#include "Graphics/Core/Public/Window.h"
#include "Graphics/ControlElements/Public/CGraph.h"
#include "Graphics/ControlElements/Public/CTable.h"
#include "Graphics/ControlElements/Public/CTextBox.h"
using namespace SO;
using namespace Graphics;

#define d(arguments) (runtime.Register(arguments))

SchroedingerApplication::SchroedingerApplication(Environment::RContainer &InServiceContainer) : RApplication(InServiceContainer)
{

}

void SchroedingerApplication::Main()
{
	MathContainer runtime = MathContainer();

	double XMax = 5e-11;
	double val_DeltaX = 5e-12;

	//create constants
	auto MinusC = runtime.Register(new Constant(-1.6382e38));
	auto W = d(new Constant(-12.9e-18));
	auto DeltaX = d(new Constant(val_DeltaX));

	auto &Psi = d(new Constant(0));
	auto &PsiDot d(new Constant(0));

	auto W_pot = d(new OP_If(std::vector<Element_ID>({
		d(new OP_Substract(std::vector<Element_ID>({
			d(new Variable(0, 0)),
			d(new Constant(XMax)) }))),
		d(new Constant(-16e-18)),
		d(new Constant(0)) })));

	auto PsiDotDot =
		d(new OP_Multiply(std::vector<Element_ID>({
			d(new OP_Multiply(std::vector<Element_ID>({
				MinusC,
				d(new OP_Substract(std::vector<Element_ID>({
					W,
					d(new OP_CalculateFunction(&runtime.FuncCache, std::vector<Element_ID>({
						W_pot,
						d(new Variable(0, 0)) }))) }))) }))),
			d(new OP_CalculateFunction(&runtime.FuncCache, std::vector<Element_ID>({
				Psi,
				d(new OP_Substract(std::vector<Element_ID>({
					d(new Variable(0, 0)),
					DeltaX }))) }))) })));

	runtime.ReRegister(PsiDot, new OP_If(std::vector<Element_ID>({
		d(new Variable(0, 0)),
		d(new Constant(0)),
		d(new OP_Add(std::vector<Element_ID>({
			d(new OP_CalculateFunction(&runtime.FuncCache, std::vector<Element_ID>({
				PsiDot,
				d(new OP_Substract(std::vector<Element_ID>({
					d(new Variable(0, 0)),
					DeltaX }))) }))),
			d(new OP_Multiply(std::vector<Element_ID>({
				DeltaX,
				d(new OP_CalculateFunction(&runtime.FuncCache, std::vector<Element_ID>({
					PsiDotDot,
					d(new OP_Substract(std::vector<Element_ID>({
						d(new Variable(0, 0)),
						d(new Constant(0)) }))) }))) }))) }))) })));

	runtime.ReRegister(Psi, new OP_If(std::vector<Element_ID>({
		d(new Variable(0,0)),
		d(new Constant(1)),
		d(new OP_Add(std::vector<Element_ID>({
			d(new OP_CalculateFunction(&runtime.FuncCache, std::vector<Element_ID>({
				Psi,
				d(new OP_Substract(std::vector<Element_ID>({
					d(new Variable(0, 0)),
					DeltaX }))) }))),
			d(new OP_Multiply(std::vector<Element_ID>({
				DeltaX,
				d(new OP_CalculateFunction(&runtime.FuncCache, std::vector<Element_ID>({
					PsiDot,
					d(new OP_Substract(std::vector<Element_ID>({
						d(new Variable(0, 0)),
						d(new Constant(0)) }))) }))) }))) }))) })));

	runtime.SetValueName(Psi, "Psi");
	runtime.SetValueName(PsiDot, "PsiDot");
	runtime.SetValueName(PsiDotDot, "PsiDotDot");

	auto P = d(new OP_Multiply(std::vector<Element_ID>({
		DeltaX,
		d(new OP_Multiply(std::vector<Element_ID>({
			d(new OP_CalculateFunction(&runtime.FuncCache, std::vector<Element_ID>({
				Psi,
				d(new Variable(0, 0)) }))),
			d(new OP_CalculateFunction(&runtime.FuncCache, std::vector<Element_ID>({
				Psi,
				d(new Variable(0, 0)) }))) }))) })));
	
	auto CumP = d(new Constant(0));

	runtime.ReRegister(CumP, 
		new OP_If(std::vector<Element_ID>({
			d(new Variable(0,0)),
			d(new Constant(0)),
			d(new OP_Add(std::vector<Element_ID>({
				d(new OP_CalculateFunction(&runtime.FuncCache, std::vector<Element_ID>({
					CumP,
					d(new OP_Substract(std::vector<Element_ID>({
						d(new Variable(0, 0)),
						DeltaX }))) }))),
				d(new OP_CalculateFunction(&runtime.FuncCache, std::vector<Element_ID>({
					P,
					d(new Variable(0, 0)) }))) }))) })));

	runtime.SetValueName(P, "Propability");
	runtime.SetValueName(CumP, "Commulated Propability");

	double CumPAtXMax = runtime.CalculateValue(d(new OP_CalculateFunction(&runtime.FuncCache, {
		CumP,
		d(new Constant(XMax)) })));

	double Multiplier = 1 / CumPAtXMax;
	std::cout << "CumP@XMax= " << CumPAtXMax << std::endl;
	std::string t;
	std::getline(std::cin, t);

	auto ScaledP = d(new OP_Multiply(std::vector<Element_ID>({
		d(new Constant(Multiplier)),
		d(new OP_CalculateFunction(&runtime.FuncCache, {
			P,
			d(new Variable(0, 0)) })) })));

	auto ScaledCumP = d(new OP_Multiply(std::vector<Element_ID>({
		d(new Constant(Multiplier)),
		d(new OP_CalculateFunction(&runtime.FuncCache, {
			CumP,
			d(new Variable(0, 0)) })) })));

	auto ScaledW_pot = d(new OP_Multiply(std::vector<Element_ID>({
		d(new Constant(1e17)),
		d(new OP_CalculateFunction(&runtime.FuncCache, {
			W_pot,
			d(new Variable(0, 0)) })) })));



	GenericMathFunction PObject = GenericMathFunction(&runtime, ScaledP);
	GenericMathFunction PsiObject = GenericMathFunction(&runtime, Psi);
	GenericMathFunction W_pot_Object = GenericMathFunction(&runtime, ScaledW_pot);

	// prepare window drawing:

	double WMax = 20e-18;
	double WStep = 2e-18;
	int WTimes = WMax / WStep;

	ZABS::Math::Matrix2D<double> results;
	results.Resize(2, WTimes, 0);
	std::vector<fPoint> dataPoints;

	for (int i = 0; i < WTimes; i++)
	{
		double WTrial = WStep * i;
		runtime.ReRegister(W, new Constant(-WTrial));
		runtime.FuncCache.Clear();
		double result = PObject.get(XMax * 3);
		results.set(0, i, WTrial);
		results.set(1, i, result);
		dataPoints.push_back(fPoint(WTrial, result));
	}

	Window* subWindowWDep = new Window("W->Psi(W)");

	CGraph* GraphWDep = subWindowWDep->AddControl<CGraph>();
	GraphWDep->SizeMin = fPoint(0, 0);
	GraphWDep->SizeMax = fPoint(WMax, 100);
	GraphWDep->DeltaX = WStep;
	GraphWDep->SetDataPoints(dataPoints);

	CTable* TableWDep = subWindowWDep->AddControl<CTable>();
	TableWDep->Matrix = results;

	subWindowWDep->Open();

	/*Window* mainWindow = new Window("SchroedingerApplication");
	CGraph* mainGraph = mainWindow->AddControl<CGraph>();
	mainGraph->SizeMin = fPoint(0, -2);
	mainGraph->SizeMax = fPoint(XMax*3, 2);
	mainGraph->DeltaX = val_DeltaX;


	mainGraph->AddFunction(PsiObject, fColor(0.1,0.1,0.9));
	mainGraph->AddFunction(PObject, fColor(0.1,0.9,0.1));
	mainGraph->AddFunction(W_pot_Object, fColor(0.4,0.4,0.4));

	mainWindow->Open();*/
}

bool SchroedingerApplication::eventhandler_ButtonPressed(Environment::EventDetails*)
{
	std::cout << "something pressed" << std::endl;
	return true;
}
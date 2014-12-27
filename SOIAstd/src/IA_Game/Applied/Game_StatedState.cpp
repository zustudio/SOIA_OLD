
#include "Data_StatedState.h"
#include "Game_StatedState.h"

using namespace IA;

Data_StatedState* Game_StatedState::CalculateResult(Data_StatedState* Input)
{
	Data_StatedState* result = new Data_StatedState();
	result->Data::Content = Input->Data::Content + 1;
	return result;
}

Data_StatedState* Game_StatedState::IFuncResultOfAction(Data_StatedState* Input)
{
	return CalculateResult(Input);
}
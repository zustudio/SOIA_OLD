
#include "stdafx.h"

#include "DEGraph.h"
#include "DataExplorer.h"

#include "Draw_2D.h"

using namespace SO::UI;
using namespace SO::Com;
using namespace SO::Drawing;

SDL_Modules_Init

DataExplorer::DataExplorer(IA::Engine* NewEngine, ComService* NewUp, SO::MeaningStream::MeaningService* MSrvc) : Window(std::string("DataExplorer")), IIComIO(NewUp)
{
	//init vars
	CurrentEngine = NewEngine;
	Drawable = new Draw_2D(Up);
	MeaningSrvc = MSrvc;
	DrawnSet = /*"standard";*/ "SDLcreated";
	SelectedData = nullptr;

	//create window
	TopTextBox = new CTextBox(this, cPoint(0, 0, 0, 0), cPoint(1, 0, 0, 50));
	TextBox_SelectedDataInfo = new CTextBox(this, cPoint(), cPoint());
	Canvas = new CCanvas(this, cPoint(0, 0, 0, 50), cPoint(1, 1, 0, -50));
	myControls.push_back(TopTextBox);
	myControls.push_back(TextBox_SelectedDataInfo);
	myControls.push_back(Canvas);

	//initial drawing
	cmd_redraw(Handle<ICom>(this, ""), std::vector<VoidPointer>());
	
}

void DataExplorer::Tick()
{
	Window::Tick();
}


//////////////////////////////////////////////////////////////////////
// ICom
Handle<ICom>& DataExplorer::cGetHandle()
{
	TryCreateHandle("DataExplorer");
	return IIComIO::cGetHandle();
}
void DataExplorer::cGetCommands(std::vector<Handle<ICmd> > &Commands)
{
	ICom_RegisterCmd(Commands, DataExplorer, cmd_redraw, "redraw");
	ICom_RegisterCmd(Commands, DataExplorer, cmd_setset, "setset");
	ICom_RegisterCmd(Commands, DataExplorer, cmd_select, "select");
	ICom_RegisterCmd(Commands, DataExplorer, cmd_deselect, "deselect");

}
//////////////////////////////////////////////////////////////////////
// commands
bool DataExplorer::cmd_redraw(const Handle<ICom> &Caller, const std::vector<VoidPointer> &Args)
{
	// set control sizes
	//  TextBox_MainInfo
	int pxSizeCanvas = 0;
	TopTextBox->SetTrans(cPoint(0, 0, 0, 0), cPoint(1, 0, 0, 50));
	pxSizeCanvas -= 50;
	//  TextBox_SelectedDataInfo
	if (SelectedData)
	{
		TextBox_SelectedDataInfo->SetTrans(cPoint(0, 1, 0, -100), cPoint(1, 0, 0, 100));
		pxSizeCanvas -= 100;
	}
	//  Canvas
	Canvas->SetTrans(cPoint(0, 0, 0, 50), cPoint(1, 1, 0, pxSizeCanvas));

	// draw Canvas & TextBox_MainInfo
	bool result = false;
	Handle<ExDSet> set = MeaningSrvc->GetSetByName(DrawnSet);
	if (set.getObj())
	{
		Drawable->Draw(Canvas, set.getObj()->GetGroups());
		TopTextBox->Text = "Currently drawn data set: " + set.getName() + "\n    - Number of groups: " + std::to_string(set.getObj()->GetGroups()->size()) + '\n';
		result = true;
	}

	// draw TextBox_SelectedDataInfo
	if (SelectedData)
	{
		std::string* temp_text = &TextBox_SelectedDataInfo->Text;
		*temp_text = *SelectedData->getText() + '\n';
		*temp_text += " - value: " + std::to_string(SelectedData->CurrentSource->get()) + '\n';

		if (checkM(MNET_Base))
		{
			*temp_text += " - directly connected data: ";

			MNET_Base<IData>* temp_data = (MNET_Base<IData>*)SelectedData->CurrentSource;

			for (int i_data = 0; i_data < temp_data->MNET_Base<IData>::getConnectedNum(); i_data++)
			{
				*temp_text += std::to_string(temp_data->MNET_Base<IData>::getConnected(i_data)->get());

				if (checkM(MSimDec))
				{
					cIA_Data* temp2_data = (cIA_Data*)SelectedData->CurrentSource;
					if (temp2_data)
						*temp_text += " (" + *((cIA_Data*)temp2_data->getConnected(i_data, IA::LinkType::M_GreatesMatch))->Text + ")";
				}

				*temp_text += "  |  ";
			}
			*temp_text += "\n";
		}



		
	}

//	// refresh window
//	TopTextBox->Draw();
//	Canvas->Draw();
//	TextBox_SelectedDataInfo->Draw();
	Refresh();

	return result;
}
bool DataExplorer::cmd_setset(const Handle<ICom> &Caller, const std::vector<VoidPointer> &Args)
{
	bool result = false;

	if (Args.size() > 0)
	{
		std::string* setName = Args[0].CastTo<std::string>();
		if (setName)
		{
			delete Drawable;
			Drawable = new Draw_2D(Up);
			DrawnSet = *setName;
			result = true;
		}
	}
	return result;
}
bool DataExplorer::cmd_select(const Handle<ICom> &Caller, const std::vector<VoidPointer> &Args)
{
	Handle<ExDSet> set = MeaningSrvc->GetSetByName(DrawnSet);

	if (SelectedData)
	{
		Canvas->HighlightObject(SelectedData, false);
	}
	else
	{
		if (set.getObj())
		{
			auto groups = set.getObj()->GetGroups();
			if (groups->size() > 0)
			{
				SelectedData = (*groups)[0]->GetBaseData();
			}
		}
	}

	if (Args.size() == 1)
	{
		std::string* p_text = Args[0].CastTo<std::string>();
		if (p_text)
		{
			if (*p_text == "down")
			{
				if (SelectedData->Children.size() > 0)
					SelectedData = SelectedData->Children[0];
			}
			if (*p_text == "up")
			{
				if (SelectedData->Parent)
					SelectedData = SelectedData->Parent;
			}
			if (*p_text == "right")
			{
				ExData* parent = SelectedData->Parent;
				if (parent)
				{
					int i;
					for (i = 0; i < parent->Children.size(); i++)
					{
						if (SelectedData == parent->Children[i])
						{
							break;
						}
					}
					SelectedData = parent->Children[(i + 1) % parent->Children.size()];
				}
			}
		}
	}

	if (SelectedData)
	{
		Canvas->HighlightObject(SelectedData, true);
		cmd_redraw(Handle<ICom>(this, ""), std::vector<VoidPointer>());
	}

	return true;
}
bool DataExplorer::cmd_deselect(const Handle<ICom> &Caller, const std::vector<VoidPointer> &Args)
{
	Canvas->HighlightObject(SelectedData, false);
	cmd_redraw(Handle<ICom>(this, ""), std::vector<VoidPointer>());
	return true;
}

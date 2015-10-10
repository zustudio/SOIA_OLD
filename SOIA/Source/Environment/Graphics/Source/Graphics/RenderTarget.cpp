
#include "Definitions.h"
#include "OpenGL.h"

#include "RenderTarget.h"
using namespace Environment;

#include "GraphicsWindow.h"
#include "TextLayer.h"
#include "FilledGeometryLayer.h"
#include "UnfilledGeometryLayer.h"

RenderTarget::RenderTarget(MBoundaries * InBoundaries, pxMargins InMargins, StyleSheet InStyle)
	: MBoundaries(InBoundaries, InMargins),
	Style(InStyle),
	Layer_Background(Layers, std::make_unique<FilledGeometryLayer>()),
	Layer_FilledGeometry(Layers, std::make_unique<FilledGeometryLayer>()),
	Layer_UnfilledGeometry(Layers, std::make_unique<UnfilledGeometryLayer>()),
	Layer_Heading(Layers, std::make_unique<TextLayer>(InStyle.Heading)),
	Layer_Content(Layers, std::make_unique<TextLayer>(InStyle.Content))
{
	GetWindow()->AddRenderTarget(this);
}

RenderTarget::~RenderTarget()
{
	GetWindow()->RemoveRenderTarget(this);
}

void RenderTarget::SetStencilValue(int InValue)
{
	StencilValue = InValue;
}

GraphicsLayer* RenderTarget::GetLayer(LayerItem InLayer)
{
	return Layers.GetNamed(InLayer).get();
}

void RenderTarget::AddObject(GraphicsObject * InObject, LayerItem InTargetLayer)
{
	LayerMutex.lock();
	Layers.GetNamed(InTargetLayer)->AddObject(InObject);
	LayerMutex.unlock();

	this->RequestUpdate();
}

void RenderTarget::Initialize()
{
	for (auto& layer : Layers)
	{
		layer->Initialize();
	}
}

void RenderTarget::Draw()
{
	//glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

	glStencilFunc(GL_ALWAYS, StencilValue, 0xFF);
	glStencilMask(StencilValue);

	LayerMutex.lock();
	Layers.GetNamed(Layer_Background)->BeginDraw();

	glStencilFunc(GL_EQUAL, StencilValue, 0xFF);
	glStencilMask(0x00);
	for (int i = Layer_FilledGeometry.ItemIndex; i < Layers.size(); ++i)
	{
		Layers[i]->BeginDraw();
	}
	LayerMutex.unlock();
	glStencilMask(0xFF);
}



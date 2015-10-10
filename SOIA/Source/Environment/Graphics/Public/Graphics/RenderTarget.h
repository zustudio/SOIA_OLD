
#pragma once

#include "MBoundaries.h"

#include "StyleSheet.h"
#include "GraphicsLayer.h"

#include <memory>
#include <mutex>

namespace Environment
{
	class GraphicsWindow;
}


namespace Environment
{
	template<typename T>
	struct NamedVector;

	template<typename T>
	struct NamedVectorItem
	{
		NamedVectorItem(NamedVector<T> & InVector, T&& InItem)
			:
			ItemIndex(InVector.AddNamed(std::move(InItem)))
		{}
		int ItemIndex;
	};

	template<typename T>
	struct NamedVector : std::vector<T>
	{	
		NamedVector()
			: std::vector<T>()
		{}

		int AddNamed(T&& InItem)
		{
			push_back(std::move(InItem));
			return size() - 1;
		}

		T& GetNamed(NamedVectorItem<T> const & InItem)
		{
			return (*this)[InItem.ItemIndex];
		}
	};

	/// Provides GraphicsLayers for GraphicsObjects to draw to. Every RenderTarget has individual Layers 
	///  and clips the drawn objects to it's specified Boundaries.
	class LIBIMPEXP RenderTarget : public MBoundaries
	{
		friend GraphicsWindow;

	public:
		using LayerItem = NamedVectorItem<std::unique_ptr<GraphicsLayer>>;

	public:
		RenderTarget(MBoundaries* InBoundaries, pxMargins InMargins, StyleSheet InStyle);
		virtual ~RenderTarget();

		void SetStencilValue(int InValue);

		GraphicsLayer* GetLayer(LayerItem InLayer);
		void AddObject(GraphicsObject* InObject, LayerItem InTargetLayer);
		
	private:
		NamedVector<std::unique_ptr<GraphicsLayer>> Layers;
	public:
		LayerItem Layer_Background;
		LayerItem Layer_FilledGeometry;
		LayerItem Layer_UnfilledGeometry;
		LayerItem Layer_Heading;
		LayerItem Layer_Content;

	protected:
		void Initialize();
		virtual void Draw();

	private:
		StyleSheet Style;
		int StencilValue;
		std::mutex LayerMutex;
	};
}
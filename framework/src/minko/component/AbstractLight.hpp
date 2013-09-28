/*
Copyright (c) 2013 Aerys

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

#include "minko/Common.hpp"

#include "minko/Signal.hpp"
#include "minko/component/AbstractRootDataComponent.hpp"
#include "minko/data/ArrayProvider.hpp"
#include "minko/math/Vector3.hpp"

namespace minko
{
	namespace component
	{
		class AbstractLight :
			public AbstractRootDataComponent<data::ArrayProvider>
		{
			friend LightManager;

		public:
			typedef std::shared_ptr<AbstractLight> 					Ptr;

		private:
			typedef	std::shared_ptr<scene::Node>					NodePtr;
			typedef std::shared_ptr<AbstractComponent>				AbsCmpPtr;
			typedef Signal<NodePtr, NodePtr, NodePtr>::Slot 		SceneSignalSlot;
			typedef std::unordered_map<NodePtr, SceneSignalSlot> 	NodeToSceneSignalSlotMap;

		private:
			std::shared_ptr<math::Vector3>			_color;

			Signal<AbsCmpPtr, NodePtr>::Slot 		_targetAddedSlot;
			Signal<AbsCmpPtr, NodePtr>::Slot 		_targetRemovedSlot;
			NodeToSceneSignalSlotMap 				_addedSlots;
			NodeToSceneSignalSlotMap				_removedSlots;

		public:
			inline
			std::shared_ptr<math::Vector3>
			color()
			{
				return _color;
			}

		protected:
			AbstractLight(const std::string& arrayName);
		};
	}
}

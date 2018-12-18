#pragma once

namespace HopStep
{
	inline namespace Internal
	{
		class ITickObject;

		class TickObjectList
		{
		public:

			TickObjectList();
			~TickObjectList();

			Result AddObject(ITickObject* object);
			Result DeleteObject(ITickObject* object);

			void ProcessTick(const float deltaTime);

		private :

			std::vector<ITickObject*> m_TickObjectList;
		};

		static TickObjectList* thisGameTickObjects = nullptr;
	}
}

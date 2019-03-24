#pragma once

namespace HopStep
{
	inline namespace Internal
	{
		class TickObject;

		class TickObjectList
		{
		public:

			static std::shared_ptr<TickObjectList> Get();

			TickObjectList() = default;
			~TickObjectList();

			Result AddObject(TickObject* object);
			Result DeleteObject(TickObject* object);

			void ProcessTick(const float deltaTime);

		private :

			std::vector<TickObject*> m_TickObjects;
			static std::shared_ptr<TickObjectList> instance;
		};
	}
}

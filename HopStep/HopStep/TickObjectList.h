#pragma once

namespace HopStep
{
	inline namespace Internal
	{
		class ITickObject;

		class TickObjectList
		{
		public:

			static std::shared_ptr<TickObjectList> Get();

			TickObjectList() = default;
			~TickObjectList();

			Result AddObject(ITickObject* object);
			Result DeleteObject(ITickObject* object);

			void ProcessTick(const float deltaTime);

		private :

			std::vector<ITickObject*> m_TickObjectList;
			static std::shared_ptr<TickObjectList> instance;
		};
	}
}

#pragma once

namespace HopStep
{
	using ObjectId = long long;

	class GameObject
	{
	public :

		GameObject();
		virtual ~GameObject();

		void SetObjectId(ObjectId id) { m_Id = id; }
		ObjectId GetId() const { return m_Id; }

	protected :

		ObjectId m_Id = 0L;

	};
}

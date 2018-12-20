#include "stdafx.h"
#include "RenderQueue.h"
#include "IRenderCommandProducer.h"
#include "RenderProducerList.h"

namespace HopStep
{
	std::shared_ptr<RenderProducerList> RenderProducerList::instance = nullptr;

	std::shared_ptr<RenderProducerList> Internal::RenderProducerList::Get()
	{
		if (instance == nullptr)
			instance = std::make_shared<RenderProducerList>();

		return instance;
	}

	RenderProducerList::~RenderProducerList()
	{
		instance = nullptr;

		m_RenderProducers.clear();
	}

	Result RenderProducerList::AddProducer(IRenderCommandProducer * producer)
	{
		if (m_IsGathering)
			return Result::InvalidParameter;

		if (producer == nullptr)
			return Result::NullParameter;

		if (std::find(m_RenderProducers.begin(), m_RenderProducers.end(), producer) != m_RenderProducers.end())
			return Result::DuplicatedObject;

		m_RenderProducers.push_back(producer);

		return Result::None;
	}

	Result RenderProducerList::DeleteProducer(IRenderCommandProducer * producer)
	{
		if (m_IsGathering)
			return Result::InvalidParameter;

		if (producer == nullptr)
			return Result::NullParameter;

		std::remove_if(m_RenderProducers.begin(), m_RenderProducers.end(), [=](IRenderCommandProducer* currentProducer)
		{
			if (currentProducer == producer)
				return true;

			return false;
		});

		return Result::None;
	}

	void RenderProducerList::GatherCommand(FrameInfo* frameInfo)
	{
		if (frameInfo == nullptr)
			return;

		m_IsGathering = true;
		for (int i = 0; i < m_RenderProducers.size(); ++i)
		{
			if (m_RenderProducers[i] == nullptr)
				continue;

			m_RenderProducers[i]->Produce(frameInfo);
		}
		//for (const auto& producer : m_RenderProducers)
		//{
		//	if (producer == nullptr)
		//		continue;

		//	producer->Produce(frameInfo);
		//}
		m_IsGathering = false;
	}
}

#include "stdafx.h"
#include "RenderQueue.h"
#include "IRenderCommandProducer.h"
#include "RenderProducerList.h"

namespace HopStep
{
	RenderProducerList::RenderProducerList()
	{
		if (thisGameRendererList != nullptr)
			return;

		thisGameRendererList = this;
	}

	RenderProducerList::~RenderProducerList()
	{
		thisGameRendererList = nullptr;

		m_RenderProducers.clear();
	}

	Result RenderProducerList::AddProducer(IRenderCommandProducer * producer)
	{
		if (producer == nullptr)
			return Result::NullParameter;

		if (std::find(m_RenderProducers.begin(), m_RenderProducers.end(), producer) == m_RenderProducers.end())
			return Result::DuplicatedObject;

		m_RenderProducers.push_back(producer);

		return Result::None;
	}

	Result RenderProducerList::DeleteProducer(IRenderCommandProducer * producer)
	{
		if (producer == nullptr)
			return Result::NullParameter;

		std::remove(m_RenderProducers.begin(), m_RenderProducers.end(), producer);

		return Result::None;
	}

	void RenderProducerList::GatherCommand(RenderQueue * queue)
	{
		if (queue == nullptr)
			return;

		for (const auto& producer : m_RenderProducers)
		{
			if (producer == nullptr)
				continue;

			producer->Produce(queue);
		}
	}
}

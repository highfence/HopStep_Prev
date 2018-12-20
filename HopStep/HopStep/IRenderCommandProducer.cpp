#include "stdafx.h"
#include "RenderProducerList.h"
#include "IRenderCommandProducer.h"

namespace HopStep
{
	void Internal::IRenderCommandProducer::SetVisible(bool visivility)
	{
		if (visivility)
			RegistMe();
		else
			UnregistMe();
	}

	void Internal::IRenderCommandProducer::RegistMe()
	{
		auto producerList = RenderProducerList::Get();
		if (producerList == nullptr)
		{
			HSDebug::CheckResult(Result::GetSingletonFailed);
			return;
		}
		producerList->AddProducer(this);
	}

	void Internal::IRenderCommandProducer::UnregistMe()
	{
		auto producerList = RenderProducerList::Get();
		if (producerList == nullptr)
		{
			HSDebug::CheckResult(Result::GetSingletonFailed);
			return;
		}
		producerList->DeleteProducer(this);
	}
}

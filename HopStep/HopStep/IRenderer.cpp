#include "stdafx.h"
#include "HopStep.h"
#include "IRenderer.h"

namespace HopStep
{
	IRenderer* IRenderer::Factory::GetRenderer()
	{
		return nullptr;
	}
}

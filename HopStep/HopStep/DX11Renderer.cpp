#include "stdafx.h"
#include "Result.h"
#include "HSConsoleLogger.h"
#include "DX11Renderer.h"

namespace HopStep
{
	Result DX11Renderer::SetRenderQueue(RenderQueue* renderQueue)
	{
		return Result::None;
	}

	Result Internal::DX11Renderer::InitRenderer(HWND windowHandle, HSConsoleLogger* logger)
	{
		return Result::None;
	}

	Result Internal::DX11Renderer::ReleaseRenderer()
	{
		return Result();
	}

	void Internal::DX11Renderer::Render()
	{

	}
}

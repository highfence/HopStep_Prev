#pragma once
#include "RenderCommandProcessor.h"
#include "IRenderer.h"

namespace HopStep
{
    inline namespace Internal
    {
        class DX2DRenderer final : public IRenderer
        {
        public :

			virtual Result SetRenderQueue(RenderQueue* renderQueue) override;

            virtual Result InitRenderer(HWND windowHandle, HSConsoleLogger* logger) override;

			virtual Result ReleaseRenderer() override;

            virtual void Render() override;

        private :

			Result CreateDeviceResources();
			Result RegistRenderFunctions();

			RenderQueue* m_RenderQueue = nullptr;
			HSConsoleLogger* m_Logger = nullptr;

			HWND m_Hwnd;
			ID2D1Factory* m_Direct2DFactory = nullptr;
			ID2D1HwndRenderTarget* m_RenderTarget = nullptr;
			ID2D1SolidColorBrush* m_BackGroundColorBrush = nullptr;
			ID2D1SolidColorBrush* m_pLightSlateGrayBrush = nullptr;
			ID2D1SolidColorBrush* m_pCornflowerBlueBrush = nullptr;

			std::unique_ptr<RenderCommandProcessor> m_Processor;

		private :

			void ClearScreen(std::shared_ptr<RenderCommand> renderCommand);
			void DrawRect(std::shared_ptr<RenderCommand> renderCommand);
        };
    }
}
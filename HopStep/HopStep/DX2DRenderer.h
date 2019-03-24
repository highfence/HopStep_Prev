#pragma once
#include "RenderCommandProcessor.h"
#include "RenderCommand.h"
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

			void ClearScreen(ClearScreenCommand* renderCommand);
			void DrawRect(DrawRectCommand* renderCommand);
			void DrawSprite(DrawSpriteCommand* renderCommand);

			RenderQueue* m_RenderQueue = nullptr;

			Result CreateDeviceResources();

			HSConsoleLogger* m_Logger = nullptr;

			HWND m_Hwnd;
			ID2D1Factory* m_Direct2DFactory = nullptr;
			ID2D1HwndRenderTarget* m_RenderTarget = nullptr;
			ID2D1SolidColorBrush* m_BackGroundColorBrush = nullptr;

        };
    }
}
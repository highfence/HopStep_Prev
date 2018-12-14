#pragma once
#include "IRenderer.h"

namespace HopStep
{
    inline namespace Internal
    {
        class DX2DRenderer final : public IRenderer
        {
        public :

            virtual Result SetRenderQueue(std::shared_ptr<RenderQueue> renderQueue) override;

            virtual Result InitRenderer(HWND windowHandle) override;

			virtual Result ReleaseRenderer() override;

            virtual void Render() override;

        private :

			Result CreateDeviceResources();

			std::shared_ptr<RenderQueue> m_RenderQueue;

			HWND m_Hwnd;
			ID2D1Factory* m_Direct2DFactory = nullptr;
			ID2D1HwndRenderTarget* m_RenderTarget = nullptr;
			ID2D1SolidColorBrush* m_BackGroundColorBrush = nullptr;
			ID2D1SolidColorBrush* m_pLightSlateGrayBrush = nullptr;
			ID2D1SolidColorBrush* m_pCornflowerBlueBrush = nullptr;
        };
    }
}
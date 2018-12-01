#pragma once
#include "IRenderer.h"

namespace HopStep
{
    inline namespace Internal
    {
        class DX2DRenderer : public IRenderer
        {
        public :

            virtual Result SetRenderQueue(RenderQueue* renderQueue) override;

            virtual Result InitRenderer() override;

            virtual void Render() override;

        private :

            RenderQueue* m_RenderQueue = nullptr;
        };
    }
}
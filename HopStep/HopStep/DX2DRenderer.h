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

            virtual Result InitRenderer() override;

            virtual void Render() override;

        private :

			std::shared_ptr<RenderQueue> m_RenderQueue;
        };
    }
}
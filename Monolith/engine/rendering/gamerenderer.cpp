#include <precomp.h>
#include <engine/rendering/gamerenderer.h>

#include <engine/rendering/renderingcontext.h>

namespace Monolith
{
    void GameRenderer::OnInit()
    {
        RegisterInstance(this);
    }

    void GameRenderer::OnShutdown()
    {
        UnregisterInstance(this);
    }

    void GameRenderer::StartFrame(RenderingContext& renderingContext)
    {
        //TODO
    }

    void GameRenderer::EndFrame(RenderingContext& renderingContext)
    {
        //TODO
    }

    namespace RenderingHelper
    {
        void StartFrame(RenderingContext& renderingContext)
        {
            GameRenderer* gameRenderer{ GameRenderer::Get() };
            if (gameRenderer != nullptr)
            {
                gameRenderer->StartFrame(renderingContext);
            }
        }

        void EndFrame(RenderingContext& renderingContext)
        {
            GameRenderer* gameRenderer{ GameRenderer::Get() };
            if (gameRenderer != nullptr)
            {
                gameRenderer->EndFrame(renderingContext);
            }
        }
    }
}
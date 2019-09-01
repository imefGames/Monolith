#pragma once

namespace Monolith
{
    class RenderingContext;

    class GameSystem
    {
    public:
        virtual ~GameSystem() = default;

        void Init();
        void Shutdown();
        void Update(f32 deltaTime);
        void Render(RenderingContext& renderingContext);

    protected:
        virtual void OnInit() {}
        virtual void OnShutdown() {}
        virtual void OnUpdate(f32 deltaTime) {}
        virtual void OnRender(RenderingContext& renderingContext) {}
    };
}
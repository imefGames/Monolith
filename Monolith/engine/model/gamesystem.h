#pragma once

namespace Monolith
{
    class RenderingContext;

    class GameSystem
    {
    public:
        void Init();
        void Shutdown();
        void Update(f32 deltaTime);
        void Render(RenderingContext& renderingContext);

    protected:
        virtual void OnInit() {}
        virtual void OnShutdown() {}
    };
}
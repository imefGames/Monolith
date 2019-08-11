#pragma once

namespace Monolith
{
    class GameSystem
    {
    public:
        void Init();
        void Shutdown();
        void Update(f32 deltaTime);

    protected:
        virtual void OnInit() {}
        virtual void OnShutdown() {}
    };
}
#pragma once

#include <engine/model/object.h>

namespace Monolith
{
    class GameSystem;

#pragma region GeneratedCodeHeader
    class GameSystemInitData : public Object
    {
    public:
        GameSystemInitData();
        ~GameSystemInitData();

        void LoadObject(const ObjectSerializer& serializer) override;


        virtual GameSystem* InstanciateGameSystem() const;

    private:
        using super = Object;

    };
#pragma endregion //GeneratedCodeHeader
}

#include <precomp.h>
#include <engine/input/inputprocessorinitdata.h>

#include <core/serialization/objectserializer.h>
#include <engine/input/inputprocessor.h>

namespace Monolith
{
#pragma region GeneratedCodeSource
    InputProcessorInitData::InputProcessorInitData()
        : super{}
    {
    }

    InputProcessorInitData::~InputProcessorInitData()
    {
    }

    void InputProcessorInitData::LoadObject(const ObjectSerializer& serializer)
    {
        super::LoadObject(serializer);
    }
#pragma endregion //GeneratedCodeSource

    GameSystem* InputProcessorInitData::InstanciateGameSystem() const
    {
        return new InputProcessor();
    }
}

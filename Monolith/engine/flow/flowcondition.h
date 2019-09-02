#pragma once

#include <engine/model/object.h>

namespace Monolith
{
    class FlowCondition;

#pragma region GeneratedCodeHeader
    class FlowConditionData : public Object
    {
    public:
        FlowConditionData();
        ~FlowConditionData();

        void LoadObject(const ObjectSerializer& serializer) override;


        virtual FlowCondition* InstantiateFlowCondition() const;

    private:
        using super = Object;

    };
#pragma endregion //GeneratedCodeHeader

    class FlowCondition
    {
    public:
        FlowCondition(const FlowConditionData& flowConditionData);
        virtual ~FlowCondition() = default;

        virtual bool IsSatisfied() const { return false; }
    };
}

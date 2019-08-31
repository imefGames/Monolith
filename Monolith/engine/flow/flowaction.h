#pragma once

#include <engine/model/object.h>

namespace Monolith
{
    class FlowAction;

#pragma region GeneratedCodeHeader
    class FlowActionData : public Object
    {
    public:
        FlowActionData();
        ~FlowActionData();

        void LoadObject(const ObjectSerializer& serializer) override;


        virtual FlowAction* InstanciateFlowAction() const;

    private:
        using super = Object;

    };
#pragma endregion //GeneratedCodeHeader

    class FlowAction
    {
    public:
        FlowAction(const FlowActionData& flowActionData);
        virtual ~FlowAction() = default;

        virtual void Execute() const {}
    };
}

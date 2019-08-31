#pragma once

namespace Monolith
{
    class FlowStateContext
    {
    public:
        FlowStateContext();

        inline u32 GetNextStateID() const { return m_NextStateID; }
        inline void SetNextStateID(u32 nextStateID) { m_NextStateID = nextStateID; }

    private:
        u32 m_NextStateID;
    };
}

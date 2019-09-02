#include <precomp.h>
#include <engine/model/entity.h>

#include <engine/model/data/entityinitdata.h>

namespace Monolith
{
    Entity::Entity(const EntityInitData& entityInitData)
        : m_Position{ entityInitData.GetPosition() }
    {
    }

    void Entity::Init()
    {
    }

    void Entity::Shutdown()
    {
    }

    void Entity::Update(f32 deltaTime)
    {
    }

    void Entity::Render(RenderingContext& renderingContext)
    {
    }
}
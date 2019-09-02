#pragma once

#include <engine/model/entity.h>
#include <engine/model/data/entityinitdata.h>
#include <string>

namespace Monolith
{
    enum class EMinesweeperGameState;
    enum class EMouseButton;

#pragma region GeneratedCodeHeader
    class GameStateButtonEntityInitData : public EntityInitData
    {
    public:
        GameStateButtonEntityInitData();
        ~GameStateButtonEntityInitData();

        void LoadObject(const ObjectSerializer& serializer) override;

        std::string GetButtonText() const { return m_ButtonText; }
        void SetButtonText(std::string newValue) { m_ButtonText = newValue; }
        u32 GetGameStateID() const { return m_GameStateID; }
        void SetGameStateID(u32 newValue) { m_GameStateID = newValue; }

        Entity* InstantiateEntity() const override;

    private:
        using super = EntityInitData;

        std::string m_ButtonText;
        u32 m_GameStateID;
    };
#pragma endregion //GeneratedCodeHeader

    class GameStateButtonEntity : public Entity
    {
    public:
        GameStateButtonEntity(const GameStateButtonEntityInitData& gameStateButtonEntityInitData);

        void Init() override;
        void Shutdown() override;
        void Update(f32 deltaTime) override;
        void Render(RenderingContext& renderingContext) override;

    private:
        void OnMouseClick(EMouseButton mouseButton, Vec2 clickPosition);

        std::string m_ButtonText;
        EMinesweeperGameState m_GameStateID;
        u32 m_MouseClickSlotID;
    };
}

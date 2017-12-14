#pragma once

#include "slot__action.h"
#include "atexture.h"
#include "widget.h"

namespace gui {

class ActPanel : public Widget
{
    static constexpr int slWidth  = 48;
    static constexpr int slHeight = 48;
    static constexpr int lMargin  = 5;
    static constexpr int tMargin  = 5;
    static constexpr int margin   = 4;
    static constexpr int size     = 10;

    using SlotVec = std::vector<ActSlot>;

public:
    explicit ActPanel(Widget* parent = nullptr);

    void init(Json& node, ResourceManager& resManager) override;

    SlotVec& getSlots();

    bool handle(SDL_Event& event, Vec2i coordStart = { 0, 0 }) override;
    void render(RenderSubsystem& rendSubsystem, ResourceManager& resManager, Vec2i coordStart = { 0, 0 }) const override;

private:
    SlotVec     m_slots;
};

} /* gui namespace. */
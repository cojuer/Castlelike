#pragma once

#include <map>
#include <memory>

#include "menu_state.h"
#include "init_object.h"

class Options;
class RenderSubsystem;
class ResourceSystem;
union SDL_Event;

namespace gui {

class CreationUI;
class Widget;

class MenuGUI : public InitObject
{
public:
    MenuGUI();

    bool             init(const Options& opts, RenderSubsystem& rendSubsys, ResourceSystem& resSystem);

    bool             initMMPanel();
    bool             initOptions();
    bool             initCredits();

    void             render();
    void             renderCursor() const;

    void             handle(SDL_Event& event);

    void             setState(MenuState state);
    MenuState        getState() const;

private:
    const Options*   m_opts;

    RenderSubsystem* m_rendSubsys;
    ResourceSystem* m_resSystem;

    MenuState        m_state;
    std::map<MenuState, std::unique_ptr<Widget>> m_pages;
};

} /* gui namespace. */
#pragma once

#include <map>
#include <vector>

#include <SDL.h>

#include "object.h"
#include "json_aliases.h"
#include "vec2.h"
#include "widget_state.h"
#include "framed_transform.h"
#include "gui_text.h"

class Options;
class Renderable;
class RenderSubsystem;
class ResourceSystem;

namespace gui {

class Bhvr;
class Trigger;

class Widget : public Object
{
protected:
    using Children = std::map<std::string, std::unique_ptr<Widget>>;
    using WdgOpts  = std::map<std::string, int>;

public:
    explicit Widget(Widget* parent = nullptr);

    explicit Widget(std::string name, 
                    Widget* parent, 
                    SDL_Rect geometry, 
                    bool visible = true, 
                    Renderable* rendered = nullptr, 
                    WState state = WState::MOUSE_OUT);
    
    explicit Widget(std::string name, 
                    Widget* parent, 
                    int x, 
                    int y, 
                    bool visible, 
                    Renderable* rendered);

    Widget(const Widget&) = delete;
    Widget(Widget&&) = default;
    Widget& operator=(const Widget&) = delete;
    Widget& operator=(Widget&&) = default;

    virtual ~Widget();

    void             resize(int width, int height);
    void             setName(const std::string& name);
    void             setGeometry(const SDL_Rect& geometry);
    void             setTransform(FramedTransform transform);
    void             setGeometry(SDL_Rect&& geometry);
    virtual void     setGraphics(Renderable* rendered);
    void             setBhvr(std::vector<Trigger*>&& trigs);
    void             setOpt(std::string name, int value);
    virtual void     addChild(Widget&);
    virtual void     addChild(std::string, Widget&);
    virtual void     setParent(Widget*);
    virtual void     setPosition(Vec2i pos);
    virtual void     setVisible(bool visible);
    virtual void     setState(WState state);
    virtual void     setGUIText(GUIText text);
    virtual void     setText(std::string text);
    virtual void     setTextStyle(TextStyle style);

    const std::string& getName() const;
    Widget*          getParent() const;
    Widget*          getChild(std::string name);
    int              getOpt(std::string name) const;
    const Renderable* getGraphics() const;
    Vec2i            getCoordStart() const;
    Vec2i            getPos() const;
    int              getWidth() const;
    int              getHeight() const;
    SDL_Rect         getRect() const;
    SDL_Rect         getRenderRect() const;
    const WState&    getState() const;
    Children&        getChildren();
    GUIText          getGUIText() const;
    std::string      getText() const;
    TextStyle        getTextStyle() const;

    void             freeGraphics();

    bool             isVisible() const;
    bool             isPointOn(Vec2i point, Vec2i coordStart = { 0, 0 }) const;

    void virtual     render(RenderSubsystem& rendSubsystem, ResourceSystem& resSystem, Vec2i coordStart = { 0, 0 }) const;
    virtual bool     handle(SDL_Event& event, Vec2i coordStart = { 0, 0 });

    virtual void     load(Json& node, ResourceSystem& resSystem, const Options& opts);

protected:
    virtual void     loadOptions(Json& node);
    virtual void     loadGeometry(Json& node, const Options& opts);
    virtual void     loadGraphics(Json& node, ResourceSystem& resSystem);

    virtual void     handleSelf(SDL_Event& event, Vec2i coordStart = { 0, 0 });
    virtual void     handleChildren(SDL_Event& event, Vec2i coordStart = { 0, 0 });

    virtual void     renderSelf(RenderSubsystem& rendSubsystem, ResourceSystem& resSystem, Vec2i coordStart = { 0, 0 }) const;
    virtual void     renderText(RenderSubsystem& rendSubsystem, ResourceSystem& resSystem, Vec2i coordStart = { 0, 0 }) const;
    virtual void     renderChildren(RenderSubsystem& rendSubsystem, ResourceSystem& resSystem, Vec2i coordStart = { 0, 0 }) const;

protected:
    Widget*          m_parent;
    Children         m_children;
    WdgOpts          m_opts;
    Renderable*      m_rendered;
    std::unique_ptr<FramedTransform> m_transform;

    std::string      m_name;
    SDL_Rect         m_geometry;

    std::string      m_text;
    TextStyle        m_textStyle;
    std::unique_ptr<Bhvr> m_bhvr;
    WState           m_state;

    bool             m_visible;
};

} /* gui namespace. */
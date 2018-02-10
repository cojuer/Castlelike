#include "widget.h"

#include "renderable.h"
#include "atexture.h"

#include "GUI/Behaviour/behaviour.h"

#include "subsystem__render.h"
#include "system__resource.h"
#include "utils.h"
#include "text_renderer.h"

namespace gui {

Widget::Widget(Widget* parent) :
    m_parent(parent), 
    m_rendered(nullptr), 
    m_transform(nullptr),
    m_bhvr(nullptr), 
    m_state(WState::MOUSE_OUT), 
    m_visible(false)
{}

void Widget::setTransform(FramedTransform transform)
{
    m_transform.reset(new FramedTransform(std::move(transform)));
}

Widget::Widget(std::string name, Widget* parent, SDL_Rect geometry, bool visible, Renderable* rendered, WState state) :
    m_parent(parent),
    m_rendered(rendered),
    m_transform(nullptr),
    m_name(std::move(name)),
    m_geometry(geometry),
    m_bhvr(nullptr),
    m_state(state),
    m_visible(visible)
{}

Widget::Widget(std::string name, Widget* parent, int x, int y, bool visible, Renderable* rendered) :
    m_parent(parent),
    m_rendered(rendered),
    m_transform(nullptr),
    m_name(std::move(name)),
    m_geometry({x, y,
        rendered->getTexture()->getWidth(),
        rendered->getTexture()->getHeight()}), 
    m_bhvr(nullptr), 
    m_state(),
    m_visible(visible)
{}

void Widget::resize(int width, int height)
{
    m_geometry.w = width;
    m_geometry.h = height;
}

void Widget::setName(const std::string& name)
{
    m_name = name;
}

void Widget::setGeometry(const SDL_Rect& geometry)
{
    m_geometry = geometry;
}

void Widget::setGeometry(SDL_Rect&& geometry)
{
    m_geometry = geometry;
}

void Widget::setGraphics(Renderable* rendered)
{
    m_rendered = rendered;
}

void Widget::setBhvr(std::vector<Trigger*>&& trigs)
{
    m_bhvr.reset(new Bhvr(*this, std::move(trigs)));
}

void Widget::setOpt(std::string name, int value)
{
    m_opts[name] = value;
}

void Widget::addChild(Widget& child)
{
    auto childName = child.getName();
    utils::logassert(!m_children.count(childName),
                     m_name + ":" + childName);
    m_children[childName] = std::unique_ptr<Widget>(&child);
    child.m_parent = this;
}

void Widget::addChild(std::string name, Widget& child)
{
    utils::logassert(!m_children.count(name), 
                     m_name + ":" + name);
    m_children[name] = std::unique_ptr<Widget>(&child);
    child.m_parent = this;
}

void Widget::setParent(Widget* parent)
{
    m_parent = parent;
}

void Widget::setPosition(Vec2i pos)
{
    m_geometry.x = pos.x;
    m_geometry.y = pos.y;
}

Widget* Widget::getParent() const
{
    return m_parent;
}

Widget* Widget::getChild(std::string name)
{
    return m_children.at(name).get();
}

int Widget::getOpt(std::string name) const
{
    return m_opts.at(name);
}

Vec2i Widget::getCoordStart() const
{
    if (m_parent)
    {
        return m_parent->getPos() +
               m_parent->getCoordStart();
    }
    else return {0, 0};
}

Vec2i Widget::getPos() const
{
    return{ m_geometry.x, m_geometry.y };
}

bool Widget::handle(SDL_Event& event, Vec2i coordStart)
{
    if (!m_visible) return false;

    handleSelf(event, coordStart);
    handleChildren(event, coordStart);
    
    return true;
}

Widget::~Widget() = default;

void Widget::loadOptions(Json& node)
{
    auto opts = node["options"];
    if (opts.is_null()) return;

    for (auto it = opts.begin(); it != opts.end(); ++it)
    {
        setOpt(it.key(), it.value());
    }
}

void Widget::loadGeometry(Json& node, const Options& opts)
{
    auto geom = node["geom"];
    if (geom.is_null())
    {
        setGeometry({ 0, 0, opts.get<int>(OptType::WIDTH), opts.get<int>(OptType::HEIGHT) });
        return;
    }

    int x = geom["x"].is_null() ? 0 : geom["x"].get<int32_t>();
    int y = geom["y"].is_null() ? 0 : geom["y"].get<int32_t>();
    int w = geom["w"].is_null() ? opts.get<int>(OptType::WIDTH) : geom["w"].get<int32_t>();
    int h = geom["h"].is_null() ? opts.get<int>(OptType::HEIGHT) : geom["h"].get<int32_t>();
    auto halign = geom["halign"].is_null() ? std::string{} : geom["halign"].get<std::string>();
    auto valign = geom["valign"].is_null() ? std::string{} : geom["valign"].get<std::string>();

    auto parentX = m_parent ? m_parent->getPos().x : 0;
    auto parentY = m_parent ? m_parent->getPos().y : 0;
    auto parentW = m_parent ? m_parent->getWidth() : opts.get<int>(OptType::WIDTH);
    auto parentH = m_parent ? m_parent->getHeight() : opts.get<int>(OptType::HEIGHT);
    
    if (halign == std::string{ 'l' })
        x = parentX;
    else if (halign == std::string{ 'c' })
        x = parentX + (parentW - w) / 2;
    else if (halign == std::string{ 'r' })
        x = parentW - w;

    if (valign == std::string{ 'l' })
        y = parentY;
    else if (valign == std::string{ 'c' })
        y = parentY + (parentH - h) / 2;
    else if (valign == std::string{ 'r' })
        y = parentH - h;

    setGeometry({ x, y, w, h });
}

void Widget::loadGraphics(Json& node, ResourceSystem& resSystem)
{
    auto graphics = node["graphics"];
    if (graphics.is_null()) return;

    setGraphics(resSystem.get<Renderable>(graphics["res"]));
}

void Widget::handleSelf(SDL_Event& event, Vec2i coordStart)
{
    if (m_bhvr)
    {
        m_bhvr->behave(event, coordStart);
    }
}

void Widget::handleChildren(SDL_Event& event, Vec2i coordStart)
{
    coordStart += getPos();
    for (auto&[name, child] : m_children)
    {
        child->handle(event, coordStart);
    }
}

int Widget::getWidth() const
{
    return m_geometry.w;
}

int Widget::getHeight() const
{
    return m_geometry.h;
}

SDL_Rect Widget::getRect() const
{
    return m_geometry;
}

const WState& Widget::getState() const
{
    return m_state;
}

Widget::Children& Widget::getChildren()
{
    return m_children;
}

GUIText Widget::getGUIText() const
{
    return GUIText{ m_textStyle, m_text };
}

std::string Widget::getText() const
{
    return m_text;
}

TextStyle Widget::getTextStyle() const
{
    return m_textStyle;
}

bool Widget::isVisible() const
{
    return m_visible;
}

void Widget::setVisible(bool visible)
{
    m_visible = visible;
}

bool Widget::isPointOn(Vec2i point, Vec2i coordStart) const
{
    return m_visible 
           and point.x > m_geometry.x + coordStart.x
           and point.x < m_geometry.x + coordStart.x + m_geometry.w
           and point.y > m_geometry.y + coordStart.y
           and point.y < m_geometry.y + coordStart.y + m_geometry.h;
}

void Widget::render(RenderSubsystem& rendSubsystem, ResourceSystem& resSystem,
                    Vec2i coordStart) const
{
    if (!m_visible) return;

    renderSelf(rendSubsystem, resSystem, coordStart);
    renderText(rendSubsystem, resSystem, coordStart);
    renderChildren(rendSubsystem, resSystem, coordStart);
}

void Widget::setState(WState state)
{
    m_state = state;
}

void Widget::setGUIText(GUIText text)
{
    m_text = text.m_text;
    m_textStyle = text.m_style;
}

void Widget::setText(std::string text)
{
    m_text = std::move(text);
}

void Widget::setTextStyle(TextStyle style)
{
    m_textStyle = std::move(style);
}

void Widget::freeGraphics()
{
    delete(m_rendered);
    m_rendered = nullptr;
}

const std::string& Widget::getName() const
{
    return m_name;
}

SDL_Rect Widget::getRenderRect() const
{
    SDL_Rect result = m_geometry;
    auto tempParent = m_parent;
    while (tempParent != nullptr)
    {
        result.x += m_parent->getRect().x;
        result.y += m_parent->getRect().y;
        tempParent = tempParent->getParent();
    }
    return result;
}

const Renderable* Widget::getGraphics() const
{
    return m_rendered;
}

void Widget::load(Json& node, 
                  ResourceSystem& resSystem,
                  const Options& opts)
{
    loadGeometry(node, opts);
    loadOptions(node);
    loadGraphics(node, resSystem);
}

void Widget::renderSelf(RenderSubsystem& rendSubsystem, ResourceSystem& resSystem, Vec2i coordStart) const
{
    auto dstRect = m_geometry;
    dstRect.x += coordStart.x;
    dstRect.y += coordStart.y;
    rendSubsystem.render(m_rendered, m_transform.get(), dstRect);
}

void Widget::renderText(RenderSubsystem& rendSubsystem, ResourceSystem& resSystem, Vec2i coordStart) const
{
    if (m_text.empty()) return;

    coordStart += getPos();

    auto font = resSystem.textRenderer->getFont(m_textStyle.m_font, m_textStyle.m_fontSize);
    
    auto texture = new ATexture();
    texture->loadFromText(rendSubsystem, 
                          m_text, 
                          font, 
                          m_textStyle.m_color, 
                          m_textStyle.m_width);
    SDL_Rect dstRect;
    dstRect.x = coordStart.x;
    dstRect.y = coordStart.y;
    dstRect.w = texture->getWidth();
    dstRect.h = texture->getHeight();
    rendSubsystem.render(texture, m_transform.get(), dstRect);
    SDL_DestroyTexture(texture->getSDLTexture());
    delete(texture);
}

void Widget::renderChildren(RenderSubsystem& rendSubsystem, ResourceSystem& resSystem, Vec2i coordStart) const
{
    coordStart += getPos();
    for (auto&[name, child] : m_children)
    {
        child->render(rendSubsystem, resSystem, coordStart);
    }
}

} /* gui namespace. */
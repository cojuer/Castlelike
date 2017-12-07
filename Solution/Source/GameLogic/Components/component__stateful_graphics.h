#pragma once
//
//#include "component.h"
//#include "component__graphics_interface.h"
//#include "actor.h"
//
//class ResourceManager;
//
//class StatefulGraphicsComponent final : public GraphicsInterfaceComponent
//{
//public:
//    static const std::string stringID;
//
//    explicit StatefulGraphicsComponent(Actor* parent = nullptr);
//    StatefulGraphicsComponent(Layer layer, std::vector<std::string> renderableIds, Actor* parent = nullptr);
//
//    void fromJSON(Json& node, ResourceManager& resManager) override;
//    std::string getStringID() const override;
//
//    void setState(const std::string& state);
//    const std::string& getState() const;
//
//    std::string get() const override;
//
//    ~StatefulGraphicsComponent();
//
//private:
//    std::string m_state;
//    std::map<std::string, std::string> m_renderableIds;
//};
#include "component__mdfr.h"

#include <iostream>

#include "actor.h"

#include "item.h"

#include "component__attr.h"
#include "component__equipment.h"

const std::string MdfrComponent::stringID = "modifiers";

MdfrComponent::MdfrComponent(Actor* parent) :
    ActorComponent(parent)
{}

MdfrComponent::MdfrComponent(const Modifiers& base, Actor* parent) :
	ActorComponent(parent),
	m_base(base),
	m_current(base)
{}

void MdfrComponent::load(Json& node, ResourceSystem& resSystem)
{
	for (auto& type : Modifiers::types)
	{
        auto modifier = node[type];
        if (!modifier.is_null())
        {
            m_base[type] = modifier;
        }
        else
        {
            m_base[type] = 0;
        }
	}
}

void MdfrComponent::postLoad(ResourceSystem& resSystem)
{
    refresh();
}

Json MdfrComponent::save() const
{
    Json node;
    for (auto&[type, value] : m_base.data())
    {
        node[type] = value;
    }
    return { { getStringID(), node } };
}

std::string MdfrComponent::getStringID() const
{
    return "modifiers";
}

const Modifiers& MdfrComponent::getBase() const
{
	return m_base;
}

const Modifiers& MdfrComponent::get() const
{
	return m_current;
}

void MdfrComponent::refresh()
{
    m_current = m_base;
    m_current["dmg_ph"] = m_base.weak_at("dmg_ph");

    auto equipmentComponent = m_parent->getComponent<EquipmentComponent>();
    if (equipmentComponent)
    {
        auto& equipment = equipmentComponent->get();

        for (auto& slotType : Equipment::types)
        {
            auto item = equipment.getItem(slotType);
            if (item)
            {
                auto& mdfrs = item->getMdfrs();
                m_current["arm_ph"] += mdfrs.weak_at("arm_ph");
            }
        }
        
        auto lhWeapon = equipment.getItem("lhand");
        if (lhWeapon && !lhWeapon->isWeapon())
        {
            lhWeapon = nullptr;
        }
        auto rhWeapon = equipment.getItem("rhand");
        if (lhWeapon)
        {
            const auto& lhMdfrs = lhWeapon->getMdfrs();
            for (const auto& type : Modifiers::types)
            {
                m_current[type] += lhMdfrs.weak_at(type);
            }
        }
        if (rhWeapon && rhWeapon != lhWeapon)
        {
            const auto& rhMdfrs = rhWeapon->getMdfrs();
            for (const auto& type : Modifiers::types)
            {
                m_current[type] += rhMdfrs.weak_at(type);
            }
        }
        if (!lhWeapon && !rhWeapon)
        {
            m_current["dmg_ph"] += m_base["dmg_ph"];
        }
    }
    m_current[Mdfr("off_rating")] = m_base.weak_at(Mdfr("off_rating"));
    m_current[Mdfr("def_rating")] = m_base.weak_at(Mdfr("def_rating"));

    auto attrComp = m_parent->getComponent<AttrComponent>();
    if (attrComp)
    {
        auto& attributes = attrComp->get();
        m_current["dodge"] += attributes.at(Attr("dex")) * 3 +
            attributes.at(Attr("per")) +
            attributes.at(Attr("chr"));
        m_current["accuracy"] += attributes.at(Attr("dex")) * 3 +
            attributes.at(Attr("per")) * 2;
    }
}

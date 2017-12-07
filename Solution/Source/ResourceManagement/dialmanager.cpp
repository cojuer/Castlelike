#include "dialmanager.h"

#include "event_bus.h"
#include "event__gui.h"

DialManager::DialManager(DialFactory& dlFactory) :
    dlFactory(dlFactory), 
    dial(nullptr), 
    state(0), 
    phrase(0), 
    curState(nullptr), 
    curPhrase(nullptr)
{}

void DialManager::startDial(int id)
{
    dial = dlFactory.get(std::to_string(id));
    state = 0;
    phrase = 0;
    refresh();

    GUIEvent guiEv(EventId::START_DIALOG);
    EventBus::FireEvent(guiEv);
}

const Dialogue* DialManager::getDial() const
{
    return dial;
}

const int& DialManager::getState() const
{
    return state;
}

const int& DialManager::getPhrase() const
{
    return phrase;
}

const DialState* DialManager::getCurState() const
{
    return curState;
}

const DialPhrase* DialManager::getCurPhrase() const
{
    return curPhrase;
}

const std::string& DialManager::getCurText() const
{
    return curText;
}

void DialManager::nextState(int answer)
{
    state = dial->states[state].answers[answer].nextState;
    phrase = 0;
    refresh();
}

void DialManager::nextPhrase()
{
    if (phrase + 1 < dial->states[state].phrases.size())
    {
        ++phrase;
    }
    else
    {
        state = -1;
        phrase = 0;
    }
    refresh();
}

void DialManager::refresh()
{
    if (state != -1)
    {
        curState = &(dial->states[state]);
        curPhrase = &(curState->phrases[phrase]);
        curText = curPhrase->text;
    }
    GUIEvent ev(EventId::REFRESH_DIALOG);
    EventBus::FireEvent(ev);
}
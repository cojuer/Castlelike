#pragma once

#include "factory__dialogue.h"

class Actor;

class DialManager
{
private:
    std::vector<Actor*> actors;
    DialFactory&        dlFactory;
    const Dialogue*     dial;
    int                 state;
    int                 phrase;

    const DialState*    curState;
    const DialPhrase*   curPhrase;
    std::string         curText;
public:
    explicit DialManager(DialFactory& dlFactory);

    void                startDial(int id);
    void                nextState(int answer);
    void                nextPhrase();

    const Dialogue*     getDial() const;
    const int&          getState() const;
    const int&          getPhrase() const;
    const DialState*    getCurState() const;
    const DialPhrase*   getCurPhrase() const;
    const std::string&  getCurText() const;
private:
    void             refresh();
};
#pragma once

struct Cutscene;

class CutsceneSystem final
{
public:
    CutsceneSystem();
    ~CutsceneSystem();

    void startCutscene(Cutscene& cutscene);
    void updateCutscene();
    void finishCutscene();

    bool onCutscene() const;

private:
    Cutscene* m_currentCutscene;
};

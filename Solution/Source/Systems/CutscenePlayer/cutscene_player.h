#pragma once

struct Cutscene;

class CutscenePlayer final
{
public:
    CutscenePlayer();
    ~CutscenePlayer();

    void startCutscene(Cutscene& cutscene);
    void updateCutscene();
    void finishCutscene();

    bool onCutscene() const;

private:
    Cutscene* m_currentCutscene;
};

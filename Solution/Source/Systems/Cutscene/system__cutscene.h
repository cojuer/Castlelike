#pragma once

class Cutscene;

class CutsceneSystem final
{
public:
    void startCutscene(Cutscene& cutscene);
    void updateCutscene();
    void finishCutscene();

    bool onCutscene() const;

private:
    Cutscene* m_currentCutscene { nullptr };
};

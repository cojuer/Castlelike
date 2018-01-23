#pragma once

#include "app.h"

class App;

class AppState
{
public:
    AppState() : m_initialized(false) {}
    AppState(const AppState& another) = delete;
    AppState(AppState&& another) = delete;
    virtual ~AppState() = default;

    AppState& operator=(const AppState& another) = delete;
    AppState& operator=(AppState&& another) = delete;

    virtual void init(App& app) = 0;

    virtual void clean() = 0;

    virtual void start() = 0;
    virtual void pause() = 0;
    virtual void resume() = 0;

    virtual void handle() = 0;
    virtual void update() = 0;
    virtual void render() = 0;

    virtual bool isInited()
    {
        return m_initialized;
    }

protected:
    bool m_initialized;
};

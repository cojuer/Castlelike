#pragma once

// FIXME: ON_QUIT is not valid state
enum class MenuState
{
    ON_MAIN,
    ON_CONTINUE,
    ON_NEW_GAME,
    ON_OPTIONS,
    ON_LOAD_MENU,
    ON_LOAD,
    ON_CREDITS,
    ON_QUIT
};
#include <ctime>

#include "app.h"
#include "app_state__menu.h"

int main(int, char**)
{
    srand(unsigned int(time(nullptr)));

    App app;
    if (!app.init())
    {
        return -1;
    }
    app.changeState(*MenuAppState::instance());
    app.run();

    return 0;
}

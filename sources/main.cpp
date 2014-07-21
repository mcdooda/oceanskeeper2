#include "game/game.h"
#include "engine/exception.h"

int main(int argc, char* argv[])
{
    try {
        game::init();
        game::loop();
        game::free();
    } catch (engine::Exception& e) {
        e.print();
    }
    return 0;
}

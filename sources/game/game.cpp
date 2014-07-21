#include "../engine/engine.h"
#include "../engine/graphics/graphics.h"
#include "../engine/graphics/texture.h"
#include "../engine/sounds/sounds.h"
#include "../engine/sounds/sample.h"
#include "../engine/time.h"
#include "../engine/lua/lua.h"
#include "../engine/singleton.h"

#include "game.h"
#include "statemachine.h"
#include "states/game.h"
#include "field.h"

namespace game
{

    void init()
    {
        initEngine();
        preloadSamples();
        S(StateMachine)->setState(new states::Game());
    }

    void initEngine()
    {
        engine::init();
        engine::graphics::init(
            engine::graphics::ColorRGBA(0, 0, 0, 0),
            S(Field)->getScreenMinX(), S(Field)->getScreenMaxX(),
            S(Field)->getScreenMaxY(), S(Field)->getScreenMinY()
        );
        engine::sounds::init(engine::Vector2d(S(Field)->getCenterX(), S(Field)->getCenterY()));
        engine::time::setFrameRate(60);
        engine::lua::init();
    }

    void preloadSamples()
    {
        engine::sounds::getSample("lvlup.ogg");
    }

    void free()
    {
        freeEngine();
        engine::lua::dbg();
    }

    void freeEngine()
    {
        engine::graphics::freeTextures();
        engine::sounds::freeSamples();
        engine::free();
    }

    void loop()
    {
        S(StateMachine)->loop();
    }

}

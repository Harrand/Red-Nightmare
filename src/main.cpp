#include "core/window.hpp"
#include "core/topaz.hpp"
#include "utility/time.hpp"
#include "entity_manager.hpp"

void init();

int main()
{
    tz::initialise();
    init();
    tz::terminate();
    return 0;
}

void init()
{
    Window wnd("Red Nightmare", 0, 30, 800, 600);
    wnd.set_swap_interval_type(Window::SwapIntervalType::LATE_SWAP_TEARING);
    Font font{"../res/fonts/comfortaa.ttf", 24};
    Shader gui_shader{"../src/shaders/gui"};
    Shader render_shader{"../src/shaders/3D"};
    EntityManager manager{wnd};
    manager.enable_screen_wrapping({wnd.get_width(), wnd.get_height()});
    Cursor& cursor = manager.spawn_cursor();
    manager.spawn_fireball({wnd.get_width() / 2.0f, wnd.get_height() / 2.0f}, 0.0f, {40, 40});
    Player& player = manager.spawn_player({10, 10}, 0.0f, {100, 100});
    Ghost& ghost = manager.spawn_ghost({200, 10}, 0.0f, {100, 100});
    Camera camera;
    Timer tick_timer;
    constexpr int tps = 60;
    LocalRandom rand;
    while(!wnd.is_close_requested())
    {
        tick_timer.update();
        using namespace tz::graphics;
        wnd.clear(BufferBit::COLOUR_AND_DEPTH);
        if(tick_timer.millis_passed(1000.0f / tps))
        {
            manager.update(tick_timer.get_range() / 1000.0f);
            tick_timer.reload();
            manager.enable_screen_wrapping({wnd.get_width(), wnd.get_height()});
            if(rand.next_int(0, 60) == 5)
                manager.spawn_ghost({rand.next_float(0.0f, wnd.get_width()), rand.next_float(0.0f, wnd.get_height())}, 0.0f, {100, 100});
        }
        manager.render(render_shader, &gui_shader, camera, {wnd.get_width(), wnd.get_height()});
        wnd.update(gui_shader, nullptr);
    }
}
#include "central_engine.h"

int main()
{
    central_engine::instantiate();
    central_engine::get_instance().run();
    central_engine::destroy();
    return 0;
}

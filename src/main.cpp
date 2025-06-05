
#include "App.hpp"

int main() {
    App app(core::utils::Config::load());
    app.run();
}
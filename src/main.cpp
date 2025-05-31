
#include "App.hpp"

int main() {
    App app(Config::load());
    app.run();
}
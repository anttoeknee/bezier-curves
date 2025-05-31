
#include "App.h"

int main() {
    App app(Config::load());
    app.run();
}
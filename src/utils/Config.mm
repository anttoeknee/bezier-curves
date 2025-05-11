
#pragma once

#include "../../includes/utils/Config.h"

Config Config::load() {
    return {
        1920u,
        1080u,
        false,
        "/System/Library/Fonts/SFNS.ttf"
    };
}



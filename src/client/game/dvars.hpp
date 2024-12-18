#pragma once

#include "game.hpp"
#include "structs.hpp"
#include <string>

namespace dvars
{
    std::string dvar_get_domain(const game::dvar_type type, const game::dvar_limits& domain);
}
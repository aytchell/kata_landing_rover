#pragma once

#include "planet.h"
#include "position.h"
#include <list>
#include <string>

rover::StatusAndPose read_rover(int argc, char* argv[]);
std::list<rover::Movement> read_commands(int argc, char* argv[]);
rover::Planet read_planet(int argc, char* argv[]);
std::string read_outfile(int argc, char* argv[]);

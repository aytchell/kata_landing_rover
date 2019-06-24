#include "read_input.h"
#include <iostream>

void print_rover(const std::tuple<rover::Status, rover::Pose>& rover)
{
    const rover::Status& status = std::get<0>(rover);
    const rover::Pose& pose = std::get<1>(rover);

    std::cout << status << ' ' << pose.x << " " << pose.y
        << " " << pose.dir << std::endl;
}

int main(int argc, char* argv[])
{
    try
    {
        std::tuple<rover::Status, rover::Pose> rover = read_rover(argc, argv);
        const std::list<rover::Movement>& cmds = read_commands(argc, argv);
        const rover::Planet& planet = read_planet(argc, argv);

        std::cout << "Read this planet map:\n";
        planet.print_map(std::cout, "   ");

        for (auto c : cmds)
        {
            rover = planet.move(rover, c);
        }

        print_rover(rover);
        return (std::get<0>(rover) == rover::Status::Alive) ? 0 : 1;
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 2;
    }
}

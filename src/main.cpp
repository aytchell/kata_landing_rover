#include "read_input.h"
#include "map_printer.h"
#include <iostream>

void print_rover(const rover::StatusAndPose& snp)
{
    const rover::Status& status = std::get<0>(snp);
    const rover::Pose& pose = std::get<1>(snp);

    std::cout << status << ' ' << pose.x << " " << pose.y
        << " " << pose.dir << std::endl;
}

int main(int argc, char* argv[])
{
    try
    {
        rover::StatusAndPose snp = read_rover(argc, argv);
        const std::list<rover::Movement>& cmds = read_commands(argc, argv);
        const rover::Planet& planet = read_planet(argc, argv);
        rover::MapPrinter printer(planet);

        std::cout << "Read this planet map:\n";
        printer.set_start_field(snp);
        printer.print(std::cout);

        for (auto c : cmds)
        {
            snp = planet.move(snp, c);
            printer.add_visited_field(snp);
        }

        printer.set_end_field(snp);

        std::cout << "Final map:\n";
        printer.print(std::cout);

        print_rover(snp);
        return (std::get<0>(snp) == rover::Status::Alive) ? 0 : 1;
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 2;
    }
}

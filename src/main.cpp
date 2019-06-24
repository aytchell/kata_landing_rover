#include "read_input.h"
#include "map_printer.h"
#include <iostream>
#include <fstream>

void print_rover(const rover::StatusAndPose& snp)
{
    const rover::Status& status = std::get<0>(snp);
    const rover::Pose& pose = std::get<1>(snp);

    std::cout << status << ' ' << pose.x << " " << pose.y
        << " " << pose.dir << std::endl;
}

void print_mapfile(const std::string& filename,
        const rover::MapPrinter& printer)
{
    if (filename.empty())
        return;

    std::fstream out_file(filename, std::ios_base::out);
    if (!out_file)
    {
        std::cerr << "Failed to open '" << filename << "' for writing\n";
        return;
    }

    printer.print(out_file, "");
}

int main(int argc, char* argv[])
{
    try
    {
        rover::StatusAndPose snp = read_rover(argc, argv);
        const std::list<rover::Movement>& cmds = read_commands(argc, argv);
        const rover::Planet& planet = read_planet(argc, argv);
        rover::MapPrinter printer(planet);
        printer.set_start_field(snp);
        const std::string& out_filename = read_outfile(argc, argv);

#ifndef NDEBUG
        std::cout << "Read this planet map:\n";
        printer.print(std::cout, "   ");
#endif

        for (auto c : cmds)
        {
            snp = planet.move(snp, c);
            printer.add_visited_field(snp);
        }

        printer.set_end_field(snp);

#ifndef NDEBUG
        std::cout << "Final map:\n";
        printer.print(std::cout, "  ");
#endif

        print_rover(snp);
        print_mapfile(out_filename, printer);

        return (std::get<0>(snp) == rover::Status::Alive) ? 0 : 1;
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 2;
    }
}

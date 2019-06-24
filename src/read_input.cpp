#include "read_input.h"
#include <fstream>
#include <string>
#include <iostream>

void print_usage(char* argv[])
{
    std::cerr <<
        " Usage:\n"
        "        " << argv[0] << " X Y DIRECTION COMMAND_FILE PLANET_FILE\n"
        "\n"
        " Output:\n"
        "        DONE X Y DIRECTION\n"
        "  -or-  OBSTACLE X Y DIRECTION\n"
        "\n"
        " Info on coordinates:\n"
        "  - top, left is 0,0\n"
        "  - left <-> right is x-direction\n"
        "  - top <-> down is y-direction\n" << std::endl;
}

void assert_argc(int argc, char* argv[], int num, const char* msg)
{
    if (argc < num) {
        print_usage(argv);
        throw std::underflow_error(msg);
    }
}

rover::StatusAndPose read_rover(int argc, char* argv[])
{
    unsigned long x, y;

    assert_argc(argc, argv, 2, "Argument 'X' is missing");
    try {
        x = std::stoul(argv[1]);
    } catch (std::exception& e) {
        print_usage(argv);
        std::cerr << "ERROR: Argument 'X' is malformed\n";
        throw;
    }

    assert_argc(argc, argv, 3, "Argument 'Y' is missing");
    try {
        y = std::stoul(argv[2]);
    } catch (std::exception& e) {
        print_usage(argv);
        std::cerr << "ERROR: Argument 'X' is malformed\n";
        throw;
    }

    assert_argc(argc, argv, 4, "Argument 'DIRECTION' is missing");
    if (argv[3][1] != '\0')
    {
        print_usage(argv);
        throw std::invalid_argument(
                "DIRECTION has to be one of 'N', 'E', 'S' or 'W'");
    }

    const char dir = argv[3][0];
    rover::Direction enum_dir;
    switch (dir)
    {
        case 'N': enum_dir = rover::Direction::North; break;
        case 'E': enum_dir = rover::Direction::East; break;
        case 'S': enum_dir = rover::Direction::South; break;
        case 'W': enum_dir = rover::Direction::West; break;
        default:
            print_usage(argv);
            throw std::invalid_argument(
                "DIRECTION has to be one of 'N', 'E', 'S' or 'W'");
    }

    rover::StatusAndPose snp = alive_at(x, y, enum_dir);
    return snp;
}

std::list<rover::Movement> read_commands(int argc, char* argv[])
{
    assert_argc(argc, argv, 5, "Argument 'COMMAND_FILE' is missing");

    std::fstream cmd_file(argv[4], std::ios_base::in);
    if (!cmd_file)
        throw std::invalid_argument("Failed to open COMMAND_FILE");
    std::list<rover::Movement> moves;
    
    for (std::string line; std::getline(cmd_file, line); ) {
        moves.push_back(rover::convert_movement(line));
    }

    return moves;
}

rover::Planet read_planet(int argc, char* argv[])
{
    assert_argc(argc, argv, 6, "Argument 'PLANET_FILE' is missing");

    std::fstream planet_file(argv[5], std::ios_base::in);
    if (!planet_file)
        throw std::invalid_argument("Failed to open PLANET_FILE");

    rover::Planet planet(planet_file);

    return planet;
}

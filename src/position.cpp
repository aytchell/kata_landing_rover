#include "position.h"

rover::Movement rover::convert_movement(const std::string& m)
{
    if (m == "MF") return Movement::MoveForward;
    if (m == "MB") return Movement::MoveBackwards;
    if (m == "TL") return Movement::TurnLeft;
    if (m == "TR") return Movement::TurnRight;

    std::string msg("Unknown command '");
    msg.append(m);
    msg.append("' encountered");

    throw std::invalid_argument(msg.c_str());
}

rover::Direction rover::left(const Direction& old)
{
    switch (old)
    {
        case Direction::North:  return Direction::West;
        case Direction::East:   return Direction::North;
        case Direction::South:  return Direction::East;
        case Direction::West:   return Direction::South;
    }

    throw std::invalid_argument("Invalid direction given");
}

rover::Direction rover::right(const Direction& old)
{
    switch (old)
    {
        case Direction::North:  return Direction::East;
        case Direction::East:   return Direction::South;
        case Direction::South:  return Direction::West;
        case Direction::West:   return Direction::North;
    }

    throw std::invalid_argument("Invalid direction given");
}

std::ostream& rover::operator<<(std::ostream& out, Status status)
{
    switch (status)
    {
        case rover::Status::Alive:      out << "DONE "; break;
        case rover::Status::Wrecked:    out << "OBSTACLE "; break;
        default:
            throw std::invalid_argument("Unknown Status of Rover encountered");
    }

    return out;
}

std::ostream& rover::operator<<(std::ostream& out, Direction dir)
{
    switch (dir)
    {
        case Direction::North: out << "N"; break;
        case Direction::East:  out << "E"; break;
        case Direction::South: out << "S"; break;
        case Direction::West:  out << "W"; break;
        default:
             throw std::invalid_argument("Unknown direction encountered");
    }

    return out;
}

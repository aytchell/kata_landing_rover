#pragma once

#include <ostream>

namespace rover
{
    enum class Direction
    {
        North,
        East,
        South,
        West
    };

    enum class Status
    {
        Alive,
        Wrecked
    };

    enum class Movement
    {
        MoveForward,
        MoveBackwards,
        TurnLeft,
        TurnRight
    };

    struct Pose
    {
        unsigned long x;
        unsigned long y;
        Direction dir;
    };

    Movement convert_movement(const std::string& m);
    Direction left(const Direction& old);
    Direction right(const Direction& old);
    std::ostream& operator<<(std::ostream& out, Status status);
    std::ostream& operator<<(std::ostream& out, Direction dir);
}

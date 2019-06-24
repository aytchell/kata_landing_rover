#pragma once

#include <ostream>
#include <tuple>

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

    typedef std::tuple<rover::Status, rover::Pose> StatusAndPose;

    inline StatusAndPose wrecked_at(const Pose& pose)
    {
        return std::make_tuple(Status::Wrecked, pose);
    }

    inline StatusAndPose alive_at(const Pose& pose)
    {
        return std::make_tuple(Status::Alive, pose);
    }

    inline StatusAndPose alive_at(unsigned int x, unsigned int y, Direction dir)
    {
        return std::make_tuple(Status::Alive, Pose{x, y, dir});
    }

    Movement convert_movement(const std::string& m);
    Direction left(const Direction& old);
    Direction right(const Direction& old);
    std::ostream& operator<<(std::ostream& out, Status status);
    std::ostream& operator<<(std::ostream& out, Direction dir);
}

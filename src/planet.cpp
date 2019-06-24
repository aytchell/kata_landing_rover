#include "planet.h"
#include <string>

void assert_eq_or_set(unsigned long& num, size_t len)
{
    if (num == 0) {
        num = len;
        return;
    }

    if (num == len)
        return;

    throw std::invalid_argument("Different line lengths in planet file");
}

rover::Planet::Planet(std::istream& in)
{
    unsigned long num_cols = 0;

    for (std::string line; ! std::getline(in, line).eof(); )
    {
        assert_eq_or_set(num_cols, line.length());
        m_fields.push_back(std::vector<FieldContent>());
        std::vector<FieldContent>& row = *m_fields.rbegin();

        for (char field : line)
        {
            switch (field)
            {
                case '.': row.push_back(FieldContent::Free); break;
                case 'x': row.push_back(FieldContent::Obstacle); break;
                default: throw std::invalid_argument(
                                 "Illegal character found in planet map");
            }
        }
    }

    if (m_fields.size() != num_cols)
        throw std::invalid_argument("#Cols and #Rows differ in planet map");
}

void rover::Planet::print_map(
        std::ostream& out, const std::string& indent) const
{
    for (const auto& row : m_fields)
    {
        out << indent;
        for (FieldContent content : row)
        {
            switch (content)
            {
                case FieldContent::Free: out << '.'; break;
                case FieldContent::Obstacle: out << 'x'; break;
            }
        }
        out << '\n';
    }
}

std::tuple<rover::Status, rover::Pose> rover::Planet::move(
        const std::tuple<Status, Pose>& context,
        Movement cmd) const
{
    if (std::get<0>(context) == Status::Wrecked)
        return context;

    const Pose& old_pose = std::get<1>(context);
    const Pose& new_pose = move(old_pose, cmd);

    if (has_obstacle(new_pose.x, new_pose.y))
    {
        std::tuple<rover::Status, rover::Pose> new_context =
            std::make_tuple(Status::Wrecked, old_pose);
        return new_context;
    }

    std::tuple<rover::Status, rover::Pose> new_context =
        std::make_tuple(Status::Alive, new_pose);
    return new_context;
}


rover::Pose rover::Planet::move_fwd(const Pose& old_pose) const
{
    Pose new_pose = old_pose;
    size_t num_rows = m_fields.size();

    switch (old_pose.dir)
    {
        case Direction::North:
            new_pose.y = (old_pose.y + num_rows - 1) % num_rows;
            break;
        case Direction::East:
            new_pose.x = (old_pose.x + 1) % num_rows;
            break;
        case Direction::South:
            new_pose.y = (old_pose.y + 1) % num_rows;
            break;
        case Direction::West:
            new_pose.x = (old_pose.x + num_rows - 1) % num_rows;
            break;
    }

    return new_pose;
}

rover::Pose rover::Planet::move_back(const Pose& old_pose) const
{
    Pose new_pose = old_pose;
    size_t num_rows = m_fields.size();

    switch (old_pose.dir)
    {
        case Direction::North:
            new_pose.y = (old_pose.y + 1) % num_rows;
            break;
        case Direction::East:
            new_pose.x = (old_pose.x + num_rows - 1) % num_rows;
            break;
        case Direction::South:
            new_pose.y = (old_pose.y + num_rows - 1) % num_rows;
            break;
        case Direction::West:
            new_pose.x = (old_pose.x + 1) % num_rows;
            break;
    }

    return new_pose;
}

rover::Pose rover::Planet::turn_left(const Pose& old_pose) const
{
    Pose new_pose = old_pose;
    new_pose.dir = left(old_pose.dir);

    return new_pose;
}

rover::Pose rover::Planet::turn_right(const Pose& old_pose) const
{
    Pose new_pose = old_pose;
    new_pose.dir = right(old_pose.dir);

    return new_pose;
}

rover::Pose rover::Planet::move(const Pose& old_pose, Movement cmd) const
{
    switch (cmd)
    {
        case Movement::MoveForward:     return move_fwd(old_pose);
        case Movement::MoveBackwards:   return move_back(old_pose);
        case Movement::TurnLeft:        return turn_left(old_pose);
        case Movement::TurnRight:       return turn_right(old_pose);
    }

    throw std::invalid_argument("Invalid movement given");
}

bool rover::Planet::has_obstacle(unsigned long x, unsigned long y) const
{
    return m_fields[y][x] == FieldContent::Obstacle;
}

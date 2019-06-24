#include "map_printer.h"
#include "planet.h"

rover::MapPrinter::MapPrinter(const Planet& planet)
    :
        m_map()
{
    const size_t dim = planet.side_length();

    for (size_t y = 0; y < dim; ++y)
    {
        std::vector<MapCellInfo> row;

        for (size_t x = 0; x < dim; ++x)
        {
            if (planet.has_obstacle(x, y))
            {
                row.push_back(MapCellInfo::Obstacle);
            } else {
                row.push_back(MapCellInfo::Free);
            }
        }

        m_map.push_back(std::move(row));
    }
}

void rover::MapPrinter::set_start_field(const StatusAndPose& snp)
{
    const Pose& pose = std::get<1>(snp);
    m_map[pose.y][pose.x] = MapCellInfo::StartField;
}

void rover::MapPrinter::add_visited_field(const StatusAndPose& snp)
{
    const Pose& pose = std::get<1>(snp);
    if (m_map[pose.y][pose.x] != MapCellInfo::StartField)
    {
        m_map[pose.y][pose.x] = MapCellInfo::VisitedField;
    }
}

void rover::MapPrinter::set_end_field(const StatusAndPose& snp)
{
    const Pose& pose = std::get<1>(snp);
    m_map[pose.y][pose.x] = MapCellInfo::EndField;
}

void rover::MapPrinter::print(
        std::ostream& out, const std::string& indent) const
{
    for (const auto& row : m_map)
    {
        out << indent;
        for (MapCellInfo mci : row)
        {
            switch (mci)
            {
                case MapCellInfo::Free: out << '.'; break;
                case MapCellInfo::Obstacle: out << 'x'; break;
                case MapCellInfo::StartField: out << 'S'; break;
                case MapCellInfo::EndField: out << 'E'; break;
                case MapCellInfo::VisitedField: out << 'o'; break;
            }
        }
        out << '\n';
    }
}

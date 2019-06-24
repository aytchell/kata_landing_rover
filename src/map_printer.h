#pragma once

#include "position.h"
#include <ostream>
#include <vector>

namespace rover
{
    class Planet;

    class MapPrinter
    {
        public:
            MapPrinter(const Planet& planet);

            void set_start_field(const StatusAndPose& snp);
            void add_visited_field(const StatusAndPose& snp);
            void set_end_field(const StatusAndPose& snp);

            void print(std::ostream& out, const std::string& indent) const;

        private:
            enum class MapCellInfo
            {
                Free,
                Obstacle,
                StartField,
                EndField,
                VisitedField
            };

            std::vector<std::vector<MapCellInfo>> m_map;
    };
}

#pragma once

#include "position.h"
#include <iostream>
#include <vector>

namespace rover
{
    class Planet
    {
        public:
            Planet(std::istream& in);

            void print_map(std::ostream& out, const std::string& indent) const;

            StatusAndPose move(
                    const StatusAndPose& snp, Movement cmd) const;

        private:
            Pose move_fwd(const Pose& old_pose) const;
            Pose move_back(const Pose& old_pose) const;
            Pose turn_left(const Pose& old_pose) const;
            Pose turn_right(const Pose& old_pose) const;
            Pose move(const Pose& old_pose, Movement cmd) const;
            bool has_obstacle(unsigned long x, unsigned long y) const;

            enum class FieldContent
            {
                Free,
                Obstacle
            };

            std::vector<std::vector<FieldContent>> m_fields;
    };
}

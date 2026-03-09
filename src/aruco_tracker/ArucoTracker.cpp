#include "ArucoTracker.hpp"
#include <sstream>

ArucoTrackerNode::ArucoTrackerNode() : Node("aruco_tracker") {
    RCLCPP_INFO(this->get_logger(), "ArUco Tracker Node initialized");
}

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ArucoTrackerNode>());
    rclcpp::shutdown();
    return 0;
}
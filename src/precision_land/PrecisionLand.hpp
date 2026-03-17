#pragma once

#include <px4_ros2/components/mode.hpp>
#include <px4_ros2/odometry/local_position.hpp>
#include <px4_ros2/odometry/attitude.hpp>
#include <px4_msgs/msg/trajectory_setpoint.hpp>
#include <px4_msgs/msg/vehicle_land_detected.hpp>
#include <px4_ros2/control/setpoint_types/experimental/trajectory.hpp>

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <cmath>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <geometry_msgs/msg/pose.hpp>
#include <geometry_msgs/msg/quaternion.h>
#include <vector>

class PrecisionLand : public px4_ros2::ModeBase {
public:
    explicit PrecisionLand(rclcpp::Node& node);

    void targetPoseCallback(const geometry_msgs::msg::PoseStamped::SharedPtr msg);
    void vehicleLandDetectedCallback(const px4_msgs::msg::VehicleLandDetected::SharedPtr msg);

    // See ModeBase https://auterion.github.io/px4-ros2-interface-lib/classpx4__ros2_1_1ModeBase.html
    void onActivate() override;
    void onDeactivate() override;
    void updateSetpoint(float dt_s) override;
private:
    struct ArucoTag {
        // Init poisition with NaN values
        Eigen::Vector3d position = Eigen::Vector3d::Constant(std::numeric_limits<double>::quiet_NaN());
    };

};

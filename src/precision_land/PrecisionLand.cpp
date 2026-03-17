#include "PrecisionLand.hpp"

#include <px4_ros2/components/node_with_mode.hpp>
#include <px4_ros2/utils/geometry.hpp>
#include <Eigen/Core>
#include <Eigen/Geometry>

static const std::string kModeName = "PrecisionLand";
static const bool kEnableDebugOutput = true;

using namespace px4_ros2::literals;

PrecisionLand::PrecisionLand(rclcpp::Node& node) : ModeBase(node, kModeName), _node(node) {
    // Load in the shared pointers

    // Load in the parameters
    loadParameters();

    modeRequirements().manual_control = false;
}

void PrecisionLand::loadParameters() {
    _node.declare_parameter<float>("descent_vel", 1.0);
    _node.declare_parameter<float>("vel_p_gain", 1.5);
    _node.declare_parameter<float>("vel_i_gain", 0.0);
    _node.declare_parameter<float>("max_velocity", 3.0);
    _node.declare_parameter<float>("target_timeout", 3.0);
    _node.declare_parameter<float>("delta_position", 0.25);
    _node.declare_parameter<float>("delta_velocity", 0.25);

    _node.get_parameter("descent_vel", _param_descent_vel);
    _node.get_parameter("vel_p_gain", _param_vel_p_gain);
    _node.get_parameter("vel_i_gain", _param_vel_i_gain);
    _node.get_parameter("max_velocity", _param_max_velocity);
    _node.get_parameter("target_timeout", _param_target_timeout);
    _node.get_parameter("delta_position", _param_delta_position);
    _node.get_parameter("delta_velocity", _param_delta_velocity);

    RCLCPP_INFO(_node.get_logger(), "descent_vel: %f", _param_descent_vel);
    RCLCPP_INFO(_node.get_logger(), "vel_p_gain: %f", _param_vel_p_gain);
    // ...
}

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<px4_ros2::NodeWithMode<PrecisionLand>>(kModeName, kEnableDebugOutput));
    rclcpp::shutdown();
    return 0;
}
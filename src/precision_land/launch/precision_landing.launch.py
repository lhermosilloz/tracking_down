from launch import LaunchDescription
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from launch.substitutions import PathJoinSubstitution, LaunchConfiguration
from launch.actions import DeclareLaunchArgument
from launch.conditions import IfCondition

def generate_launch_description():
    enable_viz_arg = DeclareLaunchArgument(
        'enable_gazebo_viz',
        default_value='true',
        description='Enable Gazebo marker visualization (simulation only)'
    )

    return LaunchDescription([
        # For VOXL2-Based stacks, we need to run the voxl_mpa_to_ros2_node to conver the MPA output to ROS2 messages
        # Node(
        #     package='voxl_mpa_to_ros2',
        #     executable='voxl_mpa_to_ros2_node',
        #     name='voxl_mpa',
        #     output='screen'
        # ),
        # Bridge camera image from Gazebo to ROS2
        Node(
            package='ros_gz_bridge',
            executable='parameter_bridge',
            name='image_bridge',
            arguments=[
                '/world/aruco/model/x500_mono_cam_down_0/link/camera_link/sensor/imager/image@sensor_msgs/msg/Image@gz.msgs.Image'
            ],
            remappings=[
                ('/world/aruco/model/x500_mono_cam_down_0/link/camera_link/sensor/imager/image', '/camera')
            ],
            output='screen',
        ),
        # Bridge camera info from Gazebo to ROS2
        Node(
            package='ros_gz_bridge',
            executable='parameter_bridge',
            name='camera_info_bridge',
            arguments=[
                '/world/aruco/model/x500_mono_cam_down_0/link/camera_link/sensor/imager/camera_info@sensor_msgs/msg/CameraInfo@gz.msgs.CameraInfo'
            ],
            remappings=[
                ('/world/aruco/model/x500_mono_cam_down_0/link/camera_link/sensor/imager/camera_info', '/camera_info')
            ],
            output='screen',
        ),
        # Aruco tracker node
        Node(
            package='aruco_tracker',
            executable='aruco_tracker_node',
            name='aruco_tracker',
            output='screen'
            # parameters=[
            #     PathJoinSubstitution([FindPackageShare('aruco_tracker'), 'cfg', 'params.yaml'])
            # ]
        ),
        # Precision landing node
        Node(
            package='precision_land',
            executable='precision_land',
            name='precision_land',
            output='screen',
            parameters=[
                PathJoinSubstitution([FindPackageShare('precision_land'), 'cfg', 'params.yaml'])
            ]
        ),
    ])

# tracking_down

A ROS2 workspace containing px4_msgs package for PX4 message definitions.

## Building the Workspace

### Prerequisites
- ROS2 Humble installed
- OpenCV (can be installed using the provided `install_opencv.sh` script)

### Build Instructions
1. Source ROS2 environment:
   ```bash
   source /opt/ros/humble/setup.bash
   ```

2. Initialize and update submodules:
   ```bash
   git submodule update --init --recursive
   ```

3. Build the workspace:
   ```bash
   colcon build
   ```

4. Source the workspace:
   ```bash
   source install/setup.bash
   ```

## VSCode Setup for ROS2 Development

This workspace is pre-configured for VSCode with ROS2 support. The following files are included:

- `.vscode/c_cpp_properties.json` - C++ IntelliSense configuration with ROS2 include paths
- `.vscode/tasks.json` - Build tasks for colcon
- `.vscode/settings.json` - ROS2 environment configuration

### Required VSCode Extensions
- **C/C++ Extension Pack** (`ms-vscode.cpptools-extension-pack`)
- **CMake Tools** (`ms-vscode.cmake-tools`)
- **Python** (`ms-python.python`)

### First-time Setup
1. Open this workspace in VSCode
2. Install the recommended extensions when prompted
3. Run **Terminal > Run Task > colcon: build** to generate compile commands
4. Press `Ctrl+Shift+P` and run **C/C++: Reload IntelliSense Database**

The `#include <rclcpp/rclcpp.hpp>` should now be recognized by VSCode's IntelliSense.

## Troubleshooting

### Build Error: `canonicalize_version() TypeError`

If you encounter this error during `colcon build`:

```
TypeError: canonicalize_version() got an unexpected keyword argument 'strip_trailing_zero'
```

**Root Cause:** Version incompatibility between setuptools and packaging library. The colcon-core package requires setuptools < 80, but newer setuptools versions expect a newer packaging API.

**Solution:**

1. Upgrade the packaging library:
   ```bash
   pip install --upgrade --force-reinstall packaging
   ```

2. Downgrade setuptools to a compatible version:
   ```bash
   pip install setuptools==78.1.1
   ```

3. Clean and rebuild the workspace:
   ```bash
   rm -rf build/ && colcon build
   ```

**Verified Compatible Versions:**
- packaging: 26.0+
- setuptools: 78.1.1 (compatible with colcon-core requirement < 80)
- wheel: 0.37.1+

This issue typically occurs when your Python environment has been updated with newer packages that don't maintain backward compatibility with ROS2's colcon build system.

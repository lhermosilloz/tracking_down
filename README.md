# tracking_down

A ROS2 workspace containing px4_msgs package for PX4 message definitions.

## Building the Workspace

To build this workspace:

```bash
colcon build
```

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

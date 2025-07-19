using UnityEngine;

/// <summary>
/// Smooth camera follow script that tracks a target transform with configurable offset and smoothing
/// </summary>
public class CameraFollow : MonoBehaviour
{
    [Header("Camera Follow Settings")]
    public Transform target;  // The target object to follow (usually the player or bot)
    public Vector3 offset = new Vector3(0, 0, -10);  // Camera offset from target position
    public float smoothSpeed = 0.125f;  // How smoothly the camera follows (0-1, lower = smoother)

    /// <summary>
    /// LateUpdate ensures camera movement happens after all other object movements in the frame
    /// This prevents jittery camera behavior when following moving objects
    /// </summary>
    void LateUpdate()
    {
        // Exit early if no target is assigned
        if (target == null) return;

        // Calculate desired camera position based on target position and offset
        Vector3 desiredPosition = target.position + offset;

        // Smoothly interpolate between current position and desired position
        Vector3 smoothed = Vector3.Lerp(transform.position, desiredPosition, smoothSpeed);

        // Apply the smoothed position to the camera
        transform.position = smoothed;
    }
}
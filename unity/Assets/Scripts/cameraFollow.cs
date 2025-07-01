using UnityEngine;

public class CameraFollow : MonoBehaviour
{
    public Transform target;  
    public Vector3 offset = new Vector3(0, 0, -10); 
    public float smoothSpeed = 0.125f;

    void LateUpdate()
    {
        if (target == null) return;

        Vector3 desiredPosition = target.position + offset;
        Vector3 smoothed = Vector3.Lerp(transform.position, desiredPosition, smoothSpeed);
        transform.position = smoothed;
    }
}

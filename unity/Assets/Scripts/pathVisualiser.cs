using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;

/// <summary>
/// Visualizes GPS path data by moving a bot along waypoints and revealing obstacles dynamically
/// Loads GPS coordinates from CSV files and converts them to Unity world coordinates
/// </summary>
public class pathVisualiser : MonoBehaviour
{
    [Header("Prefab References")]
    public GameObject botPrefab;           // Bot object that will follow the path
    public GameObject headingArrowPrefab;  // Arrow prefab to show obstacle directions

    [Header("Runtime Objects")]
    private GameObject bot;                // Instance of the bot in the scene

    [Header("Path Data")]
    private List<Vector2> pathPoints = new List<Vector2>();  // Converted path coordinates
    private List<Vector2> obsPoints = new List<Vector2>();   // Converted obstacle coordinates
    private List<float> headings = new List<float>();        // Heading angles for each path point
    private int currentIndex = 0;                            // Current position along the path

    [Header("Coordinate Conversion")]
    private Vector2 referencePoint;  // First GPS coordinate used as origin
    private float scale = 1e5f;      // Scale factor to convert GPS degrees to Unity units

    [Header("Obstacle Management")]
    private List<GameObject> obstacleArrows = new List<GameObject>();  // Instantiated arrow objects
    private List<bool> arrowRevealed = new List<bool>();              // Track which arrows are visible

    [Header("Visual Effects")]
    LineRenderer dynamicLine;  // Draws the trail behind the moving bot

    /// <summary>
    /// Initialize the scene: create bot, setup camera, load data, configure visuals
    /// </summary>
    void Start()
    {
        Debug.Log("Starting Script...");

        // Create bot instance in the scene
        bot = Instantiate(botPrefab);

        // Configure camera to follow the bot
        CameraFollow camFollow = Camera.main.GetComponent<CameraFollow>();
        if (camFollow != null)
        {
            camFollow.target = bot.transform;
        }

        // Load path and obstacle data from CSV files
        loadPathCSV("path_data");
        loadObsCSV("obs_data");

        // Setup dynamic trail line renderer
        setupTrailRenderer();

        // Begin bot movement animation
        StartCoroutine(MoveBotAlongPath());
    }

    /// <summary>
    /// Configure the LineRenderer component for drawing the bot's trail
    /// </summary>
    void setupTrailRenderer()
    {
        dynamicLine = bot.AddComponent<LineRenderer>();
        dynamicLine.positionCount = 0;
        dynamicLine.startWidth = 0.05f;
        dynamicLine.endWidth = 0.05f;
        dynamicLine.material = new Material(Shader.Find("Sprites/Default"));

        // Create gradient from green to cyan for the trail
        Gradient gradient = new Gradient();
        gradient.SetKeys(
            new GradientColorKey[] {
                new GradientColorKey(Color.green, 0.0f),
                new GradientColorKey(Color.cyan, 1.0f)
            },
            new GradientAlphaKey[] {
                new GradientAlphaKey(1.0f, 0.0f),
                new GradientAlphaKey(1.0f, 1.0f)
            }
        );
        dynamicLine.colorGradient = gradient;
        dynamicLine.numCornerVertices = 5;
        dynamicLine.numCapVertices = 5;
    }

    /// <summary>
    /// Load GPS path data from CSV file and convert to Unity coordinates
    /// Expected CSV format: latitude, longitude, heading
    /// </summary>
    /// <param name="fileName">Name of CSV file in Resources folder (without extension)</param>
    void loadPathCSV(string fileName)
    {
        TextAsset csvData = Resources.Load<TextAsset>(fileName);
        string[] line = csvData.text.Split('\n');

        // Skip header row, process data rows
        for (int i = 1; i < line.Length; i++)
        {
            string[] values = line[i].Trim().Split(',');
            if (values.Length < 3) continue;  // Skip incomplete rows

            float lat = float.Parse(values[0]);
            float lon = float.Parse(values[1]);
            float heading = float.Parse(values[2]);

            // Use first coordinate as reference point (origin)
            if (i == 1)
            {
                referencePoint = new Vector2(lon, lat);
            }

            // Convert GPS coordinates to Unity world coordinates
            float x = (lon - referencePoint.x) * scale;
            float y = (lat - referencePoint.y) * scale;

            pathPoints.Add(new Vector2(x, y));
            headings.Add(heading);
        }
    }

    /// <summary>
    /// Load obstacle data from CSV file and create arrow markers
    /// Expected CSV format: latitude, longitude, heading, [additional columns]
    /// </summary>
    /// <param name="fileName">Name of CSV file in Resources folder (without extension)</param>
    void loadObsCSV(string fileName)
    {
        TextAsset csvData = Resources.Load<TextAsset>(fileName);
        string[] line = csvData.text.Split('\n');

        // Skip header row, process data rows
        for (int i = 1; i < line.Length; i++)
        {
            string[] values = line[i].Trim().Split(',');
            if (values.Length < 4) continue;  // Skip incomplete rows

            float lat = float.Parse(values[0]);
            float lon = float.Parse(values[1]);
            float heading = float.Parse(values[2]);

            Debug.Log($"OBS Parsed: lat={lat}, lon={lon}, heading={heading}");

            // Convert GPS coordinates to Unity world coordinates
            float x = (lon - referencePoint.x) * scale;
            float y = (lat - referencePoint.y) * scale;
            Vector2 obsPoint = new Vector2(x, y);
            obsPoints.Add(obsPoint);

            // Create arrow marker for obstacle (initially hidden)
            GameObject arrow = Instantiate(headingArrowPrefab, obsPoint, Quaternion.identity);
            arrow.transform.rotation = Quaternion.Euler(0, 0, heading);
            arrow.transform.localScale = new Vector3(0.4f, 0.4f, 1f);

            // Hide arrow until bot gets close
            arrow.SetActive(false);
            obstacleArrows.Add(arrow);
            arrowRevealed.Add(false);
        }
    }

    /// <summary>
    /// Animate bot movement along the loaded path points
    /// Reveals obstacle arrows when bot gets close to them
    /// </summary>
    IEnumerator MoveBotAlongPath()
    {
        float speed = 5f;  // Movement speed multiplier

        // Move through each segment of the path
        while (currentIndex < pathPoints.Count - 1)
        {
            Vector2 start = pathPoints[currentIndex];
            Vector2 end = pathPoints[currentIndex + 1];
            float t = 0;  // Interpolation parameter (0 to 1)

            // Smoothly interpolate between current and next waypoint
            while (t < 1f)
            {
                Vector2 currentPos = Vector2.Lerp(start, end, t);

                // Update bot position, scale, and rotation
                bot.transform.localScale = new Vector3(2.5f, 2.5f, 1f);
                bot.transform.position = currentPos;
                bot.transform.rotation = Quaternion.Euler(0, 0, -headings[currentIndex]);

                // Add current position to trail
                dynamicLine.positionCount++;
                dynamicLine.SetPosition(dynamicLine.positionCount - 1, currentPos);

                // Check proximity to obstacles and reveal arrows
                checkObstacleProximity();

                // Advance interpolation based on time and speed
                t += Time.deltaTime * speed;
                yield return null;  // Wait for next frame
            }

            currentIndex++;  // Move to next path segment
        }
    }

    /// <summary>
    /// Check if bot is close to any unrevealed obstacles and show their arrows
    /// </summary>
    void checkObstacleProximity()
    {
        for (int i = 0; i < obsPoints.Count; i++)
        {
            if (!arrowRevealed[i])  // Only check unrevealed obstacles
            {
                float distance = Vector2.Distance(bot.transform.position, obsPoints[i]);
                if (distance < 0.05f)  // Proximity threshold
                {
                    obstacleArrows[i].SetActive(true);
                    arrowRevealed[i] = true;
                }
            }
        }
    }
}
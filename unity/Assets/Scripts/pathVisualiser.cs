using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;

public class pathVisualiser : MonoBehaviour
{
    public GameObject botPrefab;
    public GameObject headingArrowPrefab;
    private GameObject bot;

    private List<Vector2> pathPoints = new List<Vector2>();
    private List<Vector2> obsPoints = new List<Vector2>();
    private int currentIndex = 0;

    private List<float> headings = new List<float>();
    private Vector2 referencePoint;
    private float scale = 1e5f;
    LineRenderer dynamicLine;
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        Debug.Log("Starting Script...");
        bot = Instantiate(botPrefab);

        CameraFollow camFollow = Camera.main.GetComponent<CameraFollow>();
        if (camFollow != null)
        {
            camFollow.target = bot.transform;
        }

        loadPathCSV("path_data");
        loadObsCSV("estimated_data");

        dynamicLine = bot.AddComponent<LineRenderer>();
        dynamicLine.positionCount = 0;
        dynamicLine.startWidth = 0.05f;
        dynamicLine.endWidth = 0.05f;
        dynamicLine.material = new Material(Shader.Find("Sprites/Default"));
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

        StartCoroutine(MoveBotAlongPath());
    }

    // Update is called once per frame
    void Update()
    {

    }

    void loadPathCSV(string fileName)
    {
        TextAsset csvData = Resources.Load<TextAsset>(fileName);
        string[] line = csvData.text.Split('\n');

        for (int i = 1; i < line.Length; i++)
        {
            string[] values = line[i].Split(',');
            if (values.Length < 3)
            {
                continue;
            }

            float lat = float.Parse(values[0]);
            float lon = float.Parse(values[1]);
            float heading = 90.0f - float.Parse(values[2]);

            if (i == 1)
            {
                referencePoint = new Vector2(lat, lon);
            }

            float x = (lat - referencePoint.x) * scale;
            float y = (lon - referencePoint.y) * scale;

            pathPoints.Add(new Vector2(x, y));
            headings.Add(heading);
        }
    }

    void loadObsCSV(string fileName)
    {
        TextAsset csvData = Resources.Load<TextAsset>(fileName);
        string[] line = csvData.text.Split('\n');

        for (int i = 1; i < line.Length; i++)
        {
            string[] values = line[i].Split(',');
            if (values.Length < 4)
            {
                continue;
            }

            float lat = float.Parse(values[0]);
            float lon = float.Parse(values[1]);
            float heading = float.Parse(values[2]);

            float x = (lat - referencePoint.x) * scale;
            float y = (lon - referencePoint.y) * scale;
            Vector2 obsPoint = new Vector2(x, y);
            obsPoints.Add(obsPoint);

            GameObject arrow = Instantiate(headingArrowPrefab, obsPoint, Quaternion.identity);
            arrow.transform.rotation = Quaternion.Euler(0, 0, heading);
            arrow.transform.localScale = new Vector3(0.4f, 0.4f, 1f);

        }
    }
    IEnumerator MoveBotAlongPath()
    {
        float speed = 2f;

        while (currentIndex < pathPoints.Count - 1)
        {
            Vector2 start = pathPoints[currentIndex];
            Vector2 end = pathPoints[currentIndex + 1];
            float t = 0;

            while (t < 1f)
            {
                Vector2 currentPos = Vector2.Lerp(start, end, t);
                bot.transform.position = currentPos;
                bot.transform.rotation = Quaternion.Euler(0, 0, -headings[currentIndex]);

                // Dynamic line draw
                dynamicLine.positionCount++;
                dynamicLine.SetPosition(dynamicLine.positionCount - 1, currentPos);

                t += Time.deltaTime * speed;
                yield return null;
            }

            currentIndex++;
        }
    }
 }

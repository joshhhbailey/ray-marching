// The following code is from:
// The Art of Code, 2018. Ray Marching for Dummies! [video, online]. YouTube.
// Available from: https://youtu.be/PGtv-dBi2wE
// Accessed [25 July 2021]

#define MAX_STEPS 100
#define MAX_DISTANCE 100.0
#define SURFACE_DISTANCE 0.01

float sdUnion(float _a, float _b)
{
   return min(_a, _b);
}

float sdBox(vec3 _p, vec3 _pos, vec3 _size)
{
    vec3 p = _p - _pos;
    return length(max(abs(p) - _size, 0.0));
}

float sdSphere(vec3 _p, vec3 _pos, float _r)
{
    vec4 sphere = vec4(_pos, _r);
    return length(_p - sphere.xyz) - sphere.w;
}

float sdPlane(vec3 _p, float _y)
{
    return _p.y - _y;
}

vec2 GetDistance(vec3 _p)
{
    float distance = 1000;

    float plane0 = sdPlane(_p, -1);
    float box0 = sdBox(_p, vec3(0, 0, 10), vec3(1, 1, 1));
    distance = sdUnion(plane0, box0);
    float sphere0 = sdSphere(_p, vec3(2, 0, 10), 1);
    distance = sdUnion(distance, sphere0);

    int material = 0;

    if (distance == plane0)
    {
        material = 0;
    }
    if (distance == box0)
    {
        material = 1;
    }
    if (distance == sphere0)
    {
        material = 2;
    }
    return vec2(distance, material);
}

vec2 RayMarch(vec3 _rayOrigin, vec3 _rayDirection)
{
    float originDistance = 0.0;
    vec2 sceneDistance = vec2(0.0);

    for (int i = 0; i < MAX_STEPS; i++)
    {
        // Marching point
        vec3 p = _rayOrigin + (originDistance * _rayDirection);

        // Calculate distance from current point (p) to scene object
        sceneDistance = GetDistance(p);
        originDistance += sceneDistance.x;

        // Scene has been hit, or surpassed MAX_DISTANCE
        if (abs(sceneDistance.x) < SURFACE_DISTANCE || originDistance > MAX_DISTANCE)
        {
            break;
        }
    }
    return vec2(originDistance, sceneDistance.y);
}

vec3 GetNormal(vec3 _p)
{
    // Distance from point _p to surface
    float surfaceDistance = GetDistance(_p).x;

    // Distance to sample surrounding points
    vec2 threshold = vec2(0.01, 0);

    // Sample points
    vec3 normal = surfaceDistance - vec3(GetDistance(_p - threshold.xyy).x,
                                         GetDistance(_p - threshold.yxy).x,
                                         GetDistance(_p - threshold.yyx).x);

    return normalize(normal);
}

float GetLight(vec3 _p)
{
    // Define light
    vec3 lightPosition = vec3(0, 5, 6);
    lightPosition.xz += vec2(sin(iTime), cos(iTime)) * 2;
    vec3 lightVector = normalize(lightPosition - _p);

    // Calculate normal of intersection point
    vec3 normal = GetNormal(_p);

    // Clamp diffuse value from -1 to 1, -> 0 to 1
    float diffuse = clamp(dot(normal, lightVector), 0.0, 1.0);

    // Calculate distance between _p and light source
    float lightDistance = RayMarch(_p + (normal * SURFACE_DISTANCE * 2.0), lightVector).x;

    // Hit something
    if (lightDistance < length(lightPosition - _p))
    {
        diffuse *= 0.1;
    }

    return diffuse;
}

void main()
{
    // Normalize pixel coordinates (from -0.5 to 0.5), flip y
    vec2 uv = vec2(iUV.x - 0.5, (iUV.y - 0.5) * -1);

    // Default black
    vec3 colour = vec3(0);

    // Camera setup
    vec3 rayOrigin = vec3(0, 1, 0);
    vec3 rayDirection = normalize(vec3(uv.x, uv.y, 1));

    // Fire rays, return distance to intersection
    vec2 rayDistance = RayMarch(rayOrigin, rayDirection);

    if (rayDistance.x < MAX_DISTANCE)
    {
        // Get point of intersection
        vec3 p = rayOrigin + (rayDirection * rayDistance.x);

        // Calculate lighting and shadows
        float diffuse = GetLight(p);
        colour = vec3(diffuse);

        int material = int(rayDistance.y);

        if (material == 0)
        {
            colour *= vec3(0.0, 1.0, 0.0);
        }
        else if (material == 1)
        {
            colour *= vec3(1.0, 0.0, 0.0);
        }
        else if (material == 2)
        {
            colour *= vec3(0.0, 0.0, 1.0);
        }
    }

    fragColour = vec4(colour, 1.0);
}
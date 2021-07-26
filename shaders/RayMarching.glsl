// The following code is from:
// The Art of Code, 2018. Ray Marching for Dummies! [video, online]. YouTube.
// Available from: https://youtu.be/PGtv-dBi2wE
// Accessed [25 July 2021]

#define MAX_STEPS 100
#define MAX_DISTANCE 100.0
#define SURFACE_DISTANCE 0.01

float sdSphere(vec3 _p, vec3 _pos, float _r)
{
    vec4 sphere = vec4(_pos, _r);
    return length(_p - sphere.xyz) - sphere.w;
}

float sdPlane(vec3 _p, float _y)
{
    return _p.y - _y;
}

float GetDistance(vec3 _p)
{
    float plane = sdPlane(_p, 0);
    float sphere = sdSphere(_p, vec3(0, 1, 6), 1.0);
    //float capsule = sdCapsule(_p, vec3(0, 1, 6), vec3(1, 2, 6), 0.2);
    


    // Return distance of closest scene object
    float closestDistance = min(sphere, plane);
    //closestDistance = min(closestDistance, capsule);

    return closestDistance;
}

float RayMarch(vec3 _rayOrigin, vec3 _rayDirection)
{
    float originDistance = 0.0;
    for (int i = 0; i < MAX_STEPS; i++)
    {
        // Marching point
        vec3 p = _rayOrigin + (originDistance * _rayDirection);

        // Calculate distance from current point (p) to scene object
        float sceneDistance = GetDistance(p);
        originDistance += sceneDistance;

        // Scene has been hit, or surpassed MAX_DISTANCE
        if (sceneDistance < SURFACE_DISTANCE || originDistance > MAX_DISTANCE)
        {
            break;
        }
    }
    return originDistance;
}

vec3 GetNormal(vec3 _p)
{
    // Distance from point _p to surface
    float surfaceDistance = GetDistance(_p);

    // Distance to sample surrounding points
    vec2 threshold = vec2(0.01, 0);

    // Sample points
    vec3 normal = surfaceDistance - vec3(GetDistance(_p - threshold.xyy),
                                         GetDistance(_p - threshold.yxy),
                                         GetDistance(_p - threshold.yyx));

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
    float lightDistance = RayMarch(_p + (normal * SURFACE_DISTANCE * 2.0), lightVector);

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
    float rayDistance = RayMarch(rayOrigin, rayDirection);

    // Get point of intersection
    vec3 p = rayOrigin + (rayDirection * rayDistance);

    // Calculate lighting and shadows
    float diffuse = GetLight(p);
    colour = vec3(diffuse);

    fragColour = vec4(colour, 1.0);
}
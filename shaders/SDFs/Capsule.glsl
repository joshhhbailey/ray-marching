float sdCapsule(vec3 _p, vec3 _a, vec3 _b, float _r)
{
    vec3 ab = _b - _a;
    vec3 ap = _p - _a;

    float t = dot(ab, ap) / dot(ab, ab);
    t = clamp(t, 0.0, 1.0);

    vec3 c = _a + (t * ab);

    return length(_p - c) - _r;
}
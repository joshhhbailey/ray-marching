float sdSphere(vec3 _p, vec3 _pos, float _r)
{
    vec4 sphere = vec4(_pos, _r);
    return length(_p - sphere.xyz) - sphere.w;
}
#version 410

in vec3 vNormal;

uniform vec3 LightDirection;

out vec4 FragColour;

void main() 
{
	vec3 N = normalize(vNormal);
	vec3 L = normalize(LightDirection);
	
	float lambertTerm = max(0, min(1, dot(N, -L)));
	
	FragColour = vec4(lambertTerm, lambertTerm, lambertTerm, 1);
}
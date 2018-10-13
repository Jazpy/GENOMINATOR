#version 400 core

out vec4 FragColor;
in vec3 gFacetNormal;
in vec4 gPatchDistance;

uniform vec3 AmbientMaterial;
uniform vec3 DiffuseMaterial;
uniform vec4 LightPos;
uniform mat4 Modelview;

const vec3 line_color = vec3(0.7, 0.7, 0.7);
const bool draw_lines = true;

float amplify(float d, float scale, float offset)
{
	d = scale * d + offset;
	d = clamp(d, 0, 1);
	d = 1 - exp2(-2 * d * d);
	return d;
}

void main()
{
	vec3 N = normalize(gFacetNormal);

	// Transform LightPos into eye coordinates
	vec4 eye_pos = LightPos * Modelview;
	vec3 L = vec3(eye_pos.x, eye_pos.y, eye_pos.z);

	float df = abs(dot(N, L));
	vec3 color = AmbientMaterial + df * DiffuseMaterial;

	if (draw_lines) {
		float d = min(min(min(gPatchDistance.x, gPatchDistance.y), gPatchDistance.z), gPatchDistance.w);
		d = 1 - amplify(d, 120, -0.1);
		color = color + d * line_color;
	}

	FragColor = vec4(color, 1.0);
}

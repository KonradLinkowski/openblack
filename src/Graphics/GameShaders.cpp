#include "GameShaders.h"

using namespace OpenBlack::Shaders;

const char* WorldObject::VertexShader = R"(
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 tex;
layout(location = 2) in vec3 normal;

out vec3 v_norm;
out vec2 TexCoord;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vec4(position, 1.0);
	v_norm = normal;
	TexCoord = tex;
}
)";

const char* WorldObject::FragmentShader = R"(
#version 150 core

in vec3 v_norm;
in vec2 TexCoord;

out vec4 outColor;

uniform sampler2D tex;

void main()
{
	//vec3 col = 0.5 + 0.5 * v_norm;
    //outColor = vec4(col, 1.0);

	outColor = texture(tex, TexCoord);
}
)";

const char* Terrain::VertexShader = R"(
#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texcoord;
layout(location = 2) in vec3 weights;
layout(location = 3) in uvec3 firstMaterialID;
layout(location = 4) in uvec3 secondMaterialID;
layout(location = 5) in uvec3 materialBlendCoefficient;
layout(location = 6) in float waterAlpha;

out vec2 Texcoord;
out vec3 Weights;
flat out uvec3 FirstMaterialID;
flat out uvec3 SecondMaterialID;
flat out uvec3 MaterialBlendCoefficient;
out float WaterAlpha;

uniform mat4 viewProj;

void main()
{
	Texcoord = texcoord;
	Weights = weights;
	FirstMaterialID = firstMaterialID;
	SecondMaterialID = secondMaterialID;
	MaterialBlendCoefficient = materialBlendCoefficient;
	WaterAlpha = waterAlpha;

    gl_Position = viewProj * vec4(position, 1.0);
}
)";

const char* Terrain::FragmentShader = R"(
#version 330 core

in vec2 Texcoord;
in vec3 Weights;
flat in uvec3 FirstMaterialID;
flat in uvec3 SecondMaterialID;
flat in uvec3 MaterialBlendCoefficient;
in float WaterAlpha;

uniform sampler2DArray sMaterials;

out vec4 FragColor;

void main()
{
	// do each vert with both materials
	vec4 colOne = mix(
		texture(sMaterials, vec3(Texcoord, FirstMaterialID.r)),
		texture(sMaterials, vec3(Texcoord, SecondMaterialID.r)),
		float(MaterialBlendCoefficient.r) / 255.0f
	) * Weights.r;
	vec4 colTwo = mix(
		texture(sMaterials, vec3(Texcoord, FirstMaterialID.g)),
		texture(sMaterials, vec3(Texcoord, SecondMaterialID.g)),
		float(MaterialBlendCoefficient.g) / 255.0f
	) * Weights.g;
	vec4 colThree = mix(
		texture(sMaterials, vec3(Texcoord, FirstMaterialID.b)),
		texture(sMaterials, vec3(Texcoord, SecondMaterialID.b)),
		float(MaterialBlendCoefficient.b) / 255.0f
	) * Weights.b;

	FragColor = colOne + colTwo + colThree;
	FragColor.a = WaterAlpha;

	//FragColor = vec4(1, 1, 1, 1);

	//uvec4 lookup = texelFetch(sCountryLookup, ivec2(Country, Altitude), 0);

	//vec4 colOne = texture(sMaterials, vec3(Texcoord, lookup.r));
	//vec4 colTwo = texture(sMaterials, vec3(Texcoord, lookup.g));
	//float coeff = float(lookup.b)/255;

	//FragColor = mix(colOne, colTwo, coeff); // lookup.b

	//FragColor = texture(sMaterials, vec3(Texcoord, 6));

    //FragColor = vec4(vec3(Altitude/255), 1);
	//FragColor = vec4(vec3(Country/10), 1);
	//FragColor = vec4(vec3(lookup.r/14), 1);
}
)";
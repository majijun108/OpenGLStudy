# version 330 core
out vec4 fragColor;

struct Material{
	//vec3 ambient;
	//vec3 diffuse;
	sampler2D texture_diffuse1;
	//vec3 specular;
	sampler2D texture_specular1;
	float shininess;
};
uniform Material material;

//点光源
struct Light{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 position;
	float constant;
	float linear;
	float quadratic;
};
uniform Light light;

//uniform sampler2D mainTexture;
//uniform sampler2D smileTexture;
//uniform float mixValue;
uniform vec3 objColor;
uniform vec3 viewWorldPos;
//uniform sampler2D emissionTexture;

in GS_OUT
{
	vec3 normal;
	vec2 ourUV;
	vec3 vertWorldPos;
}fs_in;
/*in vec3 normal;
in vec2 ourUV;
in vec3 vertWorldPos;*/
void main()
{
	//vec4 mainColor = texture(mainTexture, ourUV);
	/*float ambientStrength = 0.1f;
	vec3 ambient = lightColor * ambientStrength;

	vec3 lightWroldDir = normalize(lightWorldPos - vertWorldPos);
	vec3 worldNormal = normalize(normal);
	vec3 diffuse = max(dot(lightWroldDir,worldNormal),0) * lightColor;

	vec3 reflectDir = normalize(reflect(-lightWroldDir,normal));
	vec3 viewDir = normalize(viewWorldPos-vertWorldPos);
	float specularStrength = 0.5;
	float spec = pow(max(dot(reflectDir,viewDir),0),16);
	vec3 specular = specularStrength * spec * lightColor;

	vec4 mainColor = vec4((ambient + diffuse + specular)*objColor,1.0f);

	fragColor = mainColor;*/

	//vec4 sColor = texture(smileTexture, ourUV);
	//fragColor = mix(mainColor, sColor, mixValue); //* vec4(ourColor,1.0f);
	//fragColor = vec4(ourColor, 1.0f);

	vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1,fs_in.ourUV));

	vec3 lightWroldDir = normalize(light.position - fs_in.vertWorldPos);
	vec3 worldNormal = normalize(fs_in.normal);
	float diff = max(dot(lightWroldDir,worldNormal),0);
	vec3 diffuse = light.diffuse * vec3(texture(material.texture_diffuse1,fs_in.ourUV)) * diff;

	vec3 reflectDir = normalize(reflect(-lightWroldDir,fs_in.normal));
	vec3 viewDir = normalize(viewWorldPos - fs_in.vertWorldPos);
	float spec = pow(max(dot(reflectDir,viewDir),0),material.shininess);
	vec3 specular = light.specular * vec3(texture(material.texture_specular1,fs_in.ourUV)) * spec;

	vec3 result = ambient + diffuse + specular;

	//计算点光源的强度
	//float distance = length(light.position - vertWorldPos);
	//float attenuation = 1/(light.constant + light.linear * distance + light.quadratic * distance * distance);
	//result = result * attenuation;
	/*vec3 emission = vec3(texture(emissionTexture,ourUV));
	if(emission.x > 0)
	{
		result = emission;
	}*/
	fragColor = vec4(result,1);
	//屏幕坐标
	/*if(gl_FragCoord.x < 960){
		fragColor = vec4(1.0, 0.0, 0.0, 1.0);
	}else{
		fragColor = vec4(0.0, 1.0, 0.0, 1.0);
	}*/
}
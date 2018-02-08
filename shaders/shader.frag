#version 330 core 

in vec3 vNormal;
in vec2 vTexCoord;

out vec4 color;

uniform vec3 camPos;
uniform mat3 vars;

uniform sampler2D grass;
uniform sampler2D grassstone;
uniform sampler2D stone;
uniform sampler2D snow;
uniform sampler2D noise;

vec3 sunDir = vars[0];
float a = vars[1].x;
float b = vars[1].y;
float c = vars[1].z;

/////////////////
struct SHC{
    vec3 L00, L1m1, L10, L11, L2m2, L2m1, L20, L21, L22;
};

SHC groove = SHC(
    vec3( 0.3783264,  0.4260425,  0.4504587),
    vec3( 0.2887813,  0.3586803,  0.4147053),
    vec3( 0.0379030,  0.0295216,  0.0098567),
    vec3(-0.1033028, -0.1031690, -0.0884924),
    vec3(-0.0621750, -0.0554432, -0.0396779),
    vec3( 0.0077820, -0.0148312, -0.0471301),
    vec3(-0.0935561, -0.1254260, -0.1525629),
    vec3(-0.0572703, -0.0502192, -0.0363410),
    vec3( 0.0203348, -0.0044201, -0.0452180)
);

SHC beach = SHC(
    vec3( 0.6841148,  0.6929004,  0.7069543),
    vec3( 0.3173355,  0.3694407,  0.4406839),
    vec3(-0.1747193, -0.1737154, -0.1657420),
    vec3(-0.4496467, -0.4155184, -0.3416573),
    vec3(-0.1690202, -0.1703022, -0.1525870),
    vec3(-0.0837808, -0.0940454, -0.1027518),
    vec3(-0.0319670, -0.0214051, -0.0147691),
    vec3( 0.1641816,  0.1377558,  0.1010403),
    vec3( 0.3697189,  0.3097930,  0.2029923)
);

//SHC tomb = SHC(
//    vec3( 1.0351604,  0.7603549,  0.7074635),
//    vec3( 0.4442150,  0.3430402,  0.3403777),
//    vec3(-0.2247797, -0.1828517, -0.1705181),
//    vec3( 0.7110400,  0.5423169,  0.5587956),
//    vec3( 0.6430452,  0.4971454,  0.5156357),
//    vec3(-0.1150112, -0.0936603, -0.0839287),
//    vec3(-0.3742487, -0.2755962, -0.2875017),
//    vec3(-0.1694954, -0.1343096, -0.1335315),
//    vec3( 0.5515260,  0.4222179,  0.4162488)
//);

vec3 sh_light(vec3 normal, SHC l){
    float x = normal.x;
    float y = normal.y; 
    float z = normal.z; 

    const float C1 = 0.429043;
    const float C2 = 0.511664;
    const float C3 = 0.743125;
    const float C4 = 0.886227;
    const float C5 = 0.247708;
    
    return (
        C1 * l.L22 * (x * x - y * y) +
        C3 * l.L20 * z * z +
        C4 * l.L00 -
        C5 * l.L20 +
        2.0 * C1 * l.L2m2 * x * y +
        2.0 * C1 * l.L21  * x * z +
        2.0 * C1 * l.L2m1 * y * z +
        2.0 * C2 * l.L11  * x +
        2.0 * C2 * l.L1m1 * y +
        2.0 * C2 * l.L10  * z
    );
}

vec4 gamma(vec4 color){
    return pow(color, vec4(1.0f/2.0f));
}

float sum( vec3 v ) { return v.x+v.y+v.z; }

vec3 textureNoTile(sampler2D samp, vec2 x){
    float k = texture( noise, 0.005*x ).x; // cheap (cache friendly) lookup
    
    vec2 duvdx = dFdx(x);
    vec2 duvdy = dFdx(x);
    
    float l = k*8.0;
    float i = floor(l);
    float f = fract(l);
    
    vec2 offa = sin(vec2(3.0,7.0)*(i+0.0)); // can replace with any other hash
    vec2 offb = sin(vec2(3.0,7.0)*(i+1.0)); // can replace with any other hash

    vec3 cola = textureGrad(samp, x + offa, duvdx, duvdy).xyz;
    vec3 colb = textureGrad(samp, x + offb, duvdx, duvdy).xyz;
    
    return mix(cola, colb, smoothstep(0.2,0.8,f-0.1*sum(cola-colb)));
}

///////////////

const vec4 lightColor = vec4(1, 1, 0.8, 1);
//const vec3 materialColor = vec3(0);
//const vec3 materialColor = vec3(0.36f, 0.36f, 0.36f);//rock

const vec3 occlusion = vec3(0.5);

//vec2 vTexCoord = vec2(-1, 1);
//vec2 vTexCoord = vec2(-0.1, 0.1);

void main(void) {
    //vec3 outside = sh_light(vNormal, beach);
    //vec3 inside = sh_light(vNormal, groove);
    //vec4 light = vec4(mix(outside, inside, occlusion), 1);

    vec4 light = vec4(sh_light(vNormal, beach) * occlusion, 1);

    //vec3 result = materialColor * ambient * lightColor;
    float slope = 1 - vNormal.y;
    float blendAmount;
    vec3 result;

    if(slope < a){
        blendAmount = slope / 0.2f;
        //result = mix(texture(grass, vTexCoord), texture(grassstone, vTexCoord), blendAmount);
        result = mix(textureNoTile(grass, vTexCoord), textureNoTile(grassstone, vTexCoord), blendAmount);
    } else if(slope < b){
        blendAmount = (slope - 0.2f) * (1.0f / (0.7f - 0.2f));
        //result = mix(texture(grassstone, vTexCoord), texture(stone, vTexCoord), blendAmount);
        result = mix(textureNoTile(grassstone, vTexCoord), textureNoTile(stone, vTexCoord), blendAmount);
    } else if(slope > b){
        //result = texture(stone, vTexCoord);
        result = textureNoTile(stone, vTexCoord);
    }
    //result = texture(grass, vTexCoord).xyz;

    //vec4 col = vec4(result, 1);
    color = vec4(result, 1);
    color *= light * lightColor;

    color = gamma(color);
}

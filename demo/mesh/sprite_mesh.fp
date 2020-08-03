varying highp vec4 var_position;
varying mediump vec2 var_texcoord0;
varying mediump vec4 var_color1;
varying mediump vec4 var_color2;

uniform lowp sampler2D tex0;

void main()
{
    vec4 color = texture2D(tex0, var_texcoord0.xy);
    vec4 gradient = mix(var_color1, var_color2, 1.0 - var_texcoord0.y);

    gl_FragColor = vec4(gradient.rgb * color.a, color.a);
}

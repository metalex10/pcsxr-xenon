sampler tex0;

struct _IN
{
    float2 uv: TEXCOORD0;
    float4 col : COLOR;
};

float4 psG(_IN data): COLOR {
    float4 Color;

    Color = tex2D( tex0, data.uv) * data.col;

    return  Color;
}

float4 psF(_IN data): COLOR {
    float4 Color;

    Color = tex2D( tex0, data.uv) + data.col;

    return  Color;
}

float4 psC(_IN data): COLOR {
    float4 Color;

    Color = data.col;

    return  Color;
}

float4 main(_IN data): COLOR {
    return psF(data);
}
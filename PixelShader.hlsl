// PixelShader.hlsl
struct PS_INPUT {
    float3 fragColor : COLOR; // Входящий цвет из вершинного шейдера
};

float4 main(PS_INPUT input) : SV_TARGET {
    return float4(input.fragColor, 1.0); // Возвращаем цвет с альфа-каналом 1.0
}

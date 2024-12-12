// PixelShader.hlsl
struct PS_INPUT {
    float3 fragColor : COLOR; // �������� ���� �� ���������� �������
};

float4 main(PS_INPUT input) : SV_TARGET {
    return float4(input.fragColor, 1.0); // ���������� ���� � �����-������� 1.0
}

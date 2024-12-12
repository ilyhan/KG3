// VertexShader.hlsl
struct VS_OUTPUT {
    float4 position : SV_POSITION; // ���������� SV_POSITION ��� �������
    float3 fragColor : COLOR;       // ���������� COLOR ��������� ��� �������� �����
};

VS_OUTPUT main(float3 position : POSITION, float3 color : COLOR) {
    VS_OUTPUT output;
    output.position = float4(position, 1.0);
    output.fragColor = color;
    return output;
}

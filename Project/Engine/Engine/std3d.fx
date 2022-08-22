#ifndef _STD3D
#define _STD3D

#include "value.fx"

struct VTX_IN
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;
    
    float3 vTangent : TANGENT;
    float3 vNormal : NORMAL;
    float3 vBinormal : BINORMAL;
};

struct VTX_OUT
{
    float4 vPosition : SV_Position;   
    float2 vUV : TEXCOORD;
    
    float3 vViewPos : POSITION;        
    float3 vViewNormal : NORMAL1;    
};


// =========================
// Std3D Shader
// g_int_0 : Shader Type
// g_tex_0 : Output Texture
//
// DOMAIN : Masked
// Rasterizer : CULL_BACK
// DepthStencilState : LESS
// BlendState : DEFAULT
// =========================
VTX_OUT VS_Std3D(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f;
    
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vUV = _in.vUV;
    output.vViewPos = mul(float4(_in.vPos, 1.f), g_matWV).xyz;
    output.vViewNormal = normalize(mul(float4(_in.vNormal, 0.f), g_matWV)).xyz;
    
    return output;
}

float4 PS_Std3D(VTX_OUT _in) : SV_Target
{
    float4 vObjectColor = (float4) float4(1.f, 0.f, 0.1f, 1.f);    
    float4 vOutColor = (float4) float4(0.f, 0.f, 0.f, 1.f);
             
    if(g_btex_0)
    {
        vObjectColor = g_tex_0.Sample(g_sam_0, _in.vUV);
    }    
    
    if (0 < iLight3DCount)
    {
        tLightColor lightColor = (tLightColor) 0.f;
        
        for (int i = 0; i < iLight3DCount; ++i)
        {
            CalculateLight3D(_in.vViewPos, _in.vViewNormal, i, lightColor);
        }
                    
        // Diffuse, Specular, Ambient 로 최종 색상을 구한다.
        vOutColor.rgb = (vObjectColor.rgb * lightColor.vDiff.rgb)
                        + (lightColor.vSpec.rgb) 
                        + (vObjectColor.rgb * lightColor.vAmb.rgb);
    }
    
    return vOutColor;
}




#endif
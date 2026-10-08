
#define USES_COLOR
#define USES_TEXCOORD0
#define USES_TEXCOORD1
#define USES_SHADERCOLORSCALE
#define USES_OBJECTCOLORSCALE
#define USES_FOG

#include "360_Globals.h"

VS_OUTPUT vs_main( VS_INPUT IN )
{
   return GenerateVertexShaderOutput( IN );
}

float4 ps_main( VS_OUTPUT IN ) : COLOR
{
   float4 texDiffuse0 = tex2D( TexMap0, IN.TexCoord0 );
   float4 texAO = tex2D( TexMap1, IN.TexCoord1 );
   float4 texBlend = 0.25f * (texDiffuse0.rgba * texAO.brga);
   
   float4 color = texBlend * IN.Color;
   
   return CalculateFinalColor( IN, color );
}

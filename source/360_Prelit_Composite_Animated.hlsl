
#define USES_COLOR
#define USES_TEXCOORD0
#define USES_TEXGEN1
#define USES_FOG

#include "360_Globals.h"

VS_OUTPUT vs_main( VS_INPUT IN )
{
   return GenerateVertexShaderOutput( IN );
}

float4 ps_main( VS_OUTPUT IN ) : COLOR
{
   float4 texDiffuse0 = tex2D( TexMap0, IN.TexCoord0 );
   float4 texDiffuse1 = tex2D( TexMap1, IN.TexGen1   );
   
   float4 color = ( texDiffuse0 + texDiffuse1 * texDiffuse0.a ) * IN.Color ;
   
   return CalculateFinalColor( IN, color );
}

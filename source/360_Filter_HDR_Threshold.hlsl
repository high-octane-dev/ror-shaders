
#define USES_TEXCOORD0

#include "360_Globals.h"
#include "360_HDR.h"

VS_OUTPUT vs_main( VS_INPUT IN )
{
    VS_OUTPUT OUT;
    
    OUT.Position  = IN.Position;
    OUT.TexCoord0 = IN.TexCoord0;
    
    return OUT;
}

float4 ps_main( VS_OUTPUT IN ) : COLOR
{
   float3 texDiffuse0 = tex2D( TexMap0, IN.TexCoord0 );
   
   float luminance = dot( texDiffuse0, float3( 0.2125, 0.7154, 0.0721 ) );
   
   return float4( texDiffuse0 * max( luminance - PS_HDR_Threshold, 0 ) * 2, 1 );
}

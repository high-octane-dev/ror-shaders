
#define USES_TEXCOORD0
#define USES_TEXCOORD1
#define USES_TEXCOORD2
#define USES_TEXCOORD3
#define USES_TEXCOORD4
#define USES_TEXCOORD5
// #define USES_TEXCOORD6
// #define USES_TEXCOORD7

#include "360_Globals.h"

float PS_BlurAmount : register( c16 );

VS_OUTPUT vs_main( VS_INPUT IN )
{
    VS_OUTPUT OUT;

    OUT.Position  = IN.Position;

    OUT.TexCoord0 = IN.TexCoord0;
    OUT.TexCoord1 = IN.TexCoord1 - IN.TexCoord0;
    OUT.TexCoord2 = IN.TexCoord2 - IN.TexCoord0;
    OUT.TexCoord3 = IN.TexCoord3 - IN.TexCoord0;
    OUT.TexCoord4 = IN.TexCoord4 - IN.TexCoord0;
    OUT.TexCoord5 = IN.TexCoord5 - IN.TexCoord0;
    return OUT;
}

float4 ps_main( VS_OUTPUT IN ) : COLOR
{
   float depth = tex2D( TexMap6, IN.TexCoord0 ).r;
   float blur  = smoothstep( 0.0001, 0.05, depth );

   float3 texDiffuse0 =
      tex2D( TexMap1, IN.TexCoord0 + IN.TexCoord1 * blur ) +
      tex2D( TexMap2, IN.TexCoord0 + IN.TexCoord2 * blur ) +
      tex2D( TexMap3, IN.TexCoord0 + IN.TexCoord3 * blur ) +
      tex2D( TexMap4, IN.TexCoord0 + IN.TexCoord4 * blur ) +
      tex2D( TexMap5, IN.TexCoord0 + IN.TexCoord5 * blur );

   float alpha = tex2D( TexMap0, IN.TexCoord0 ).g * PS_BlurAmount;

   return float4( texDiffuse0 * 0.21, alpha );
}

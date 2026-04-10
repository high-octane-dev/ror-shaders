
#define USES_TEXCOORD0
#define USES_TEXCOORD1
#define USES_TEXCOORD2
#define USES_TEXCOORD3
#define USES_TEXCOORD4

#include "360_Globals.h"
#include "360_HDR.h"

struct VSOut {
   float4 Position : SV_POSITION;
   float2 TexCoord0 : TEXCOORD0;
   float4 TexCoord1 : TEXCOORD1;
   float4 TexCoord2 : TEXCOORD2;
   float4 TexCoord3 : TEXCOORD3;
   float4 TexCoord4 : TEXCOORD4;
};

VSOut vs_main( VS_INPUT IN )
{
   VSOut OUT;
   OUT.Position = IN.Position;
   OUT.TexCoord0 = IN.TexCoord0;
   OUT.TexCoord1 = float4( IN.TexCoord0 + VS_HDR_BlurDirection, IN.TexCoord0 + VS_HDR_BlurDirection * 2.0 );
   OUT.TexCoord2 = float4( IN.TexCoord0 + VS_HDR_BlurDirection * 3.0, IN.TexCoord0 + VS_HDR_BlurDirection * 4.0 );
   OUT.TexCoord3 = float4( IN.TexCoord0 - VS_HDR_BlurDirection, IN.TexCoord0 - VS_HDR_BlurDirection * 2.0 );
   OUT.TexCoord4 = float4( IN.TexCoord0 - VS_HDR_BlurDirection * 3.0, IN.TexCoord0 - VS_HDR_BlurDirection * 4.0 );
   return OUT;
}

float4 ps_main( VSOut IN ) : COLOR
{
   float3 centerColor = tex2D( TexMap7, IN.TexCoord0 );
   
   float3 blurredColor =
   
      centerColor * PS_HDR_BlurKernel[ 7 ].x +
      
      tex2D( TexMap0,  IN.TexCoord0 + PS_HDR_BlurOffset[  0 ] ) * PS_HDR_BlurKernel[  0 ] +
      tex2D( TexMap1,  IN.TexCoord0 + PS_HDR_BlurOffset[  1 ] ) * PS_HDR_BlurKernel[  1 ] +
      tex2D( TexMap2,  IN.TexCoord0 + PS_HDR_BlurOffset[  2 ] ) * PS_HDR_BlurKernel[  2 ] +
      tex2D( TexMap3,  IN.TexCoord0 + PS_HDR_BlurOffset[  3 ] ) * PS_HDR_BlurKernel[  3 ] +
      tex2D( TexMap4,  IN.TexCoord0 + PS_HDR_BlurOffset[  4 ] ) * PS_HDR_BlurKernel[  4 ] +
      tex2D( TexMap5,  IN.TexCoord0 + PS_HDR_BlurOffset[  5 ] ) * PS_HDR_BlurKernel[  5 ] +
      tex2D( TexMap6,  IN.TexCoord0 + PS_HDR_BlurOffset[  6 ] ) * PS_HDR_BlurKernel[  6 ] +
      tex2D( TexMap8,  IN.TexCoord0 + PS_HDR_BlurOffset[  8 ] ) * PS_HDR_BlurKernel[  8 ] +
      tex2D( TexMap9,  IN.TexCoord0 + PS_HDR_BlurOffset[  9 ] ) * PS_HDR_BlurKernel[  9 ] +
      tex2D( TexMap10, IN.TexCoord0 + PS_HDR_BlurOffset[ 10 ] ) * PS_HDR_BlurKernel[ 10 ] +
      tex2D( TexMap11, IN.TexCoord0 + PS_HDR_BlurOffset[ 11 ] ) * PS_HDR_BlurKernel[ 11 ] +
      tex2D( TexMap12, IN.TexCoord0 + PS_HDR_BlurOffset[ 12 ] ) * PS_HDR_BlurKernel[ 12 ] +
      tex2D( TexMap13, IN.TexCoord0 + PS_HDR_BlurOffset[ 13 ] ) * PS_HDR_BlurKernel[ 13 ] +
      tex2D( TexMap14, IN.TexCoord0 + PS_HDR_BlurOffset[ 14 ] ) * PS_HDR_BlurKernel[ 14 ];
      
   return float4( blurredColor, 1 );
}

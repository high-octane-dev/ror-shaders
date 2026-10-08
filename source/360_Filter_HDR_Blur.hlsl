
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
   float3 blurredColor =
      tex2D( TexMap1, IN.TexCoord1.xy ) * PS_HDR_BlurKernel.x +
      tex2D( TexMap3, IN.TexCoord1.zw ) * PS_HDR_BlurKernel.y +
      tex2D( TexMap1, IN.TexCoord2.xy ) * PS_HDR_BlurKernel.z +
      tex2D( TexMap3, IN.TexCoord2.zw ) * PS_HDR_BlurKernel.w +
      tex2D( TexMap2, IN.TexCoord3.xy ) * PS_HDR_BlurKernel.x +
      tex2D( TexMap4, IN.TexCoord3.zw ) * PS_HDR_BlurKernel.y +
      tex2D( TexMap2, IN.TexCoord4.xy ) * PS_HDR_BlurKernel.z +
      tex2D( TexMap4, IN.TexCoord4.zw ) * PS_HDR_BlurKernel.w +
      tex2D( TexMap0, IN.TexCoord0 ) * PS_HDR_BlurCenter.x;

   return float4( blurredColor, 1 );
}


#define POSITION_ALREADY_IN_WORLD_SPACE

#define USES_PARTICLE
#define USES_TEXCOORD0
#define USES_FOG

#include "360_Globals.h"

static const float2 ParticleCorners[ 4 ] = { { -1, -1 }, { 1, -1 }, { 1, 1 }, { -1, 1 } };

VS_OUTPUT vs_main( VS_INPUT IN )
{
   VS_OUTPUT OUT;
   
   FOG_OUTPUT fog = CalculateFog( IN.Position );
   
   float maxScale = fog.Distance * 0.20;

   float2 corner = ParticleCorners[ IN.Data.x ];

   float s, c;
   sincos( IN.Data.w, s, c );

   float3 right   = VS_WorldViewMatrix[ 0 ].xyz;
   float3 up      = VS_WorldViewMatrix[ 1 ].xyz;
   float3 forward = VS_WorldViewMatrix[ 2 ].xyz;

   float3 axisX = s * up + c * right;
   float3 axisY = -c * up + s * right;

   float3 offset = mul( corner, float2x3( axisX, axisY ) );

   float4 worldPosition = IN.Position;
   worldPosition.xyz += offset * min( IN.Data.y, maxScale );

   // normalize( float3( 1, 1, 0.25 ) ) == ( 0.69631058, 0.69631058, 0.17407765 )
   float3 normal = mul( float3( corner.yx * 0.69631058, 0.17407765 ), float3x3( axisY, axisX, forward ) );
   
   OUT.Position      = mul( worldPosition, VS_WorldViewProjMatrix );
   OUT.Color         = float4( normalize( normal ), saturate( IN.Data.z ) );
   OUT.TexCoord0     = IN.TexCoord0;
   OUT.Fog           = fog.Fog;
   
   return OUT;
}

float4 ps_main( VS_OUTPUT IN ) : COLOR
{
   float4 texDiffuse0 = tex2D( TexMap0, IN.TexCoord0 );
   
   LIGHT_OUTPUT L;

   L.NonAmbientColor = texDiffuse0.rgb * 1.25;
   L.AmbientColor    = texDiffuse0.rgb * 0.75;

   return CalculateFinalColor( IN, L, texDiffuse0.a * IN.Color.a );
}

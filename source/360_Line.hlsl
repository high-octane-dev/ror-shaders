
#define USES_COLOR

#include "360_Globals.h"

VS_OUTPUT vs_main( VS_INPUT IN )
{
   VS_OUTPUT OUT;

   OUT.Position = float4( mul( VS_WorldViewProjMatrix, float4( IN.Position.xy, 0, 1 ) ).xy, 0, 1 );
   OUT.Color    = IN.Color;

   return OUT;
}

float4 ps_main( VS_OUTPUT IN ) : COLOR
{
   return IN.Color;
}

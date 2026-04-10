
struct VS_INPUT
{
   float4 Pos : POSITION;
   float4 T0  : TEXCOORD0;
};

struct VS_OUTPUT
{
   float2 T0  : TEXCOORD0;
   float4 Pos : POSITION;
};

sampler tex0   : register( s0 );
sampler tex1   : register( s1 );
sampler tex2   : register( s2 );
float4 consta : register( c0 );

VS_OUTPUT vs_main( VS_INPUT IN )
{
   VS_OUTPUT output;
   output.T0 = IN.T0.xy;
   output.Pos = IN.Pos;
   return output;
}

float4 ps_main( VS_OUTPUT IN ) : COLOR {
   float4 c254 = float4(1.16412354, -0.813476563, 1.59579468, -0.87065506);
   float4 c255 = float4(-0.391448975, 2.01782227, 0.529705048, -1.08166885);
   float r1_w = tex2D(tex2, IN.T0).w;
   float r0_w0 = tex2D(tex0, IN.T0).w;
   float r0_w1 = tex2D(tex1, IN.T0).w;

   float r0_x = dot(float2(r0_w1, r0_w0), c254.xz) + c254.w;
   float2 r0_zw = float2(r0_w1, r0_w1) * c254.xx + float2(r0_w1, r0_w1) * c254.y;
   float r0_y = r0_zw.x + r0_zw.y;
   float2 r0_yz = r1_w * c255.xz + float2(r0_y, r0_y);
   r0_yz += c255.zw;

   float3 color = float3(r0_x, r0_yz);

   return float4(color, consta.w);
   /*
   float4 c;

   c.x = tex2D( tex0, IN.T0 ).w;
   c.y = tex2D( tex1, IN.T0 ).w;
   c.z = tex2D( tex2, IN.T0 ).w;
   c.w = consta.x;

   float4 p;

   float4 tor = (1.16412354, 1.59579468, 0, -0.87065506);
   float4 tog = (1.16412354, -0.813476563, -0.391448975, 0.529705048);
   float4 tob = (1.16412354, 0, 2.01782227, -1.08166885);

   p.x = dot( tor, c );
   p.y = dot( tog, c );
   p.z = dot( tob, c );
   p.w = consta.x;
   
   return p;
   */
}

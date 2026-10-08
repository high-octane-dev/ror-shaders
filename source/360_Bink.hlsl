
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

float4 ps_main( VS_OUTPUT IN ) : COLOR
{
   const float4 crc = { 1.595794678, -0.813476563, 0, 0 };
   const float4 crb = { 0, -0.391448975, 2.017822266, 0 };
   const float4 adj = { -0.87065506, 0.529705048, -1.081668854, 0 };

   float4 p;

   float y  = tex2D( tex0, IN.T0 ).w;
   float cr = tex2D( tex1, IN.T0 ).w;
   float cb = tex2D( tex2, IN.T0 ).w;

   p = y * 1.164123535;
   p += crc * cr;
   p += crb * cb;
   p += adj;
   p.w = 1.0;
   p *= consta;

   return p;
}

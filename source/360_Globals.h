
#if defined( USES_SKIN ) || defined( USES_PUPPET )

   #define POSITION_ALREADY_IN_WORLD_SPACE

#endif

#ifndef REFLECTION_TEXTURE

   #define REFLECTION_TEXTURE TexMap0

#endif

#ifdef USES_LIGHTMAP

   #define USES_DYNAMICSHADOWMAP
   #define USES_WORLDSHADOWMAP

#endif

float4x4 VS_WorldMatrix                : register( c0 );
float4x4 VS_WorldViewMatrix            : register( c4 );
float4x4 VS_ViewProjMatrix             : register( c8 );
float4x4 VS_WorldViewProjMatrix        : register( c12 );
float4x4 VS_ShadowWorldViewProjMatrix0  : register( c16 );
float4x4 VS_ShadowWorldViewProjMatrix1  : register( c216 );
float4x4 VS_ShadowWorldViewProjMatrix2  : register( c220 );
float4x2 VS_TexGenMatrix               : register( c20 );

float3   VS_WorldCameraPosition        : register( c24 );
float3   VS_LocalCameraPosition        : register( c25 );

float4   VS_FogParameters              : register( c26 );

float4x2 VS_IconMatrix                 : register( c27 );
float4   VS_IconDepth                  : register( c31 );

float4   VS_ViewportScale              : register( c34 );
float4   VS_ViewportOffset             : register( c35 );

float3   VS_VegetationColors[ 7 ]      : register( c36 );
float4   VS_VegetationVector           : register( c43 );

float4   VS_ShrubberyScale             : register( c44 );
float4   VS_ShrubberyOffset            : register( c45 );
float2   VS_ShrubberyRange             : register( c46 );

float4   VS_ClampFarZ                  : register( c47 );
float4   VS_ParticleDeltaVectors[ 4 ]  : register( c47 );
float3   VS_ParticleColor[ 4 ]         : register( c51 );

float4   VS_WorldShadowMapRegion       : register( c55 );

float4x3 VS_BoneMatrixStart[ 63 ]      : register( c63 );

float4   PS_ShaderColorScale           : register( c0 );
float4   PS_ObjectColorScale           : register( c1 );
float4   PS_FogColor                   : register( c2 );

#ifndef USES_ECOLIGHTS

   float3   PS_AmbientColor            : register( c3 );
   float3   PS_SunlightColor           : register( c4 );
   float3   PS_SunlightDirection       : register( c5 );

#else

   float3   PS_AmbientColor            : register( c6 );
   float3   PS_SunlightColor           : register( c7 );
   float3   PS_SunlightDirection       : register( c8 );

#endif

float3   PS_WorldCameraPosition        : register( c9 );
float3x2 PS_ViewMatrix                 : register( c10 );
float2   PS_EnvMapScale                : register( c12 );
float2   PS_EnvMapOffset               : register( c13 );
float4   PS_InverseDepthProjection     : register( c14 );
float2   PS_DistanceFadeMinMax         : register( c15 );
float4   PS_WorldShadowMapUVOffset     : register( c15 );
float    PS_GlossPower                 : register( c98 );
float3   PS_ShadowColor                : register( c99 );
float    PS_MudLevel                   : register( c100 );

sampler  TexMap[ 16 ]                  : register( s0 );

sampler  TexMap0                       : register( s0 );
sampler  TexMap1                       : register( s1 );
sampler  TexMap2                       : register( s2 );
sampler  TexMap3                       : register( s3 );
sampler  TexMap4                       : register( s4 );
sampler  TexMap5                       : register( s5 );
sampler  TexMap6                       : register( s6 );
sampler  TexMap7                       : register( s7 );
sampler  TexMap8                       : register( s8 );
sampler  TexMap9                       : register( s9 );
sampler  TexMap10                      : register( s10 );
sampler  TexMap11                      : register( s11 );
sampler  TexMap12                      : register( s12 );
sampler  TexMap13                      : register( s13 );
sampler  TexMap14                      : register( s14 );
sampler  TexMap15                      : register( s15 );

struct VS_INPUT
{
   float4 Position         : POSITION;

   #ifdef USES_ECOSYSTEM

      float4 Delta         : NORMAL;

   #else

      float3 Normal        : NORMAL;

   #endif

   #ifdef USES_COLOR

      float4 Color         : COLOR;

   #endif

   #if defined( USES_TEXCOORD0 ) || defined( USES_TEXGEN0 )

      #ifdef TEXCOORD0_IS_FULL_VECTOR

         float4 TexCoord0  : TEXCOORD0;

      #else

         float2 TexCoord0  : TEXCOORD0;

      #endif

   #endif

   #if defined( USES_TEXCOORD1 ) || defined( USES_TEXGEN1 )

      float2 TexCoord1     : TEXCOORD1;

   #endif

   #if defined( USES_TEXCOORD2 ) || defined( USES_TEXGEN2 ) || defined( USES_LIGHTMAP )

      float2 TexCoord2     : TEXCOORD2;

   #endif

   #if defined( USES_TEXCOORD3 )

      float2 TexCoord3     : TEXCOORD3;

   #endif

   #if defined( USES_TEXCOORD4 )

      float2 TexCoord4     : TEXCOORD4;

   #endif

   #if defined( USES_TEXCOORD5 )

      float2 TexCoord5     : TEXCOORD5;

   #endif

   #if defined( USES_TEXCOORD6 )

      float2 TexCoord6     : TEXCOORD6;

   #endif

   #if defined( USES_TEXCOORD7 )

      float2 TexCoord7     : TEXCOORD7;

   #endif

   #ifdef USES_ECOSYSTEM

      int4   Data          : TEXCOORD1;

   #endif

   #ifdef USES_PARTICLE

      float4 Data          : TEXCOORD1;

   #endif

   #ifdef USES_SKIN

      float4 BlendIndices  : BLENDINDICES;
      float4 BlendWeight   : BLENDWEIGHT;

   #endif

   #ifdef USES_PUPPET

      float  BoneIndex     : TEXCOORD4;

   #endif

   #ifdef USES_BUMP

      float3 Tangent       : TANGENT;

   #endif
};

struct VS_OUTPUT
{
   float4 Position         : POSITION;

   #if defined( USES_COLOR ) || defined( USES_ECOSYSTEM ) || defined( USES_PARTICLE )

      float4 Color         : COLOR;

   #endif

   #ifdef USES_TEXCOORD0

      float2 TexCoord0     : TEXCOORD0;

   #endif

   #ifdef USES_TEXCOORD1

      float2 TexCoord1     : TEXCOORD1;

   #endif

   #if defined( USES_TEXCOORD2 ) || defined( USES_LIGHTMAP ) || defined( USES_WORLDSHADOWMAP )

      float2 TexCoord2     : TEXCOORD2;

   #endif

   #ifdef USES_TEXCOORD3

      float2 TexCoord3     : TEXCOORD3;

   #endif

   #ifdef USES_TEXCOORD4

      float2 TexCoord4     : TEXCOORD4;

   #endif

   #ifdef USES_TEXCOORD5

      float2 TexCoord5     : TEXCOORD5;

   #endif

   #ifdef USES_TEXCOORD6

      float2 TexCoord6     : TEXCOORD6;

   #endif

   #ifdef USES_TEXCOORD7

      float2 TexCoord7     : TEXCOORD7;

   #endif

   #ifdef USES_TEXGEN0

      float2 TexGen0       : TEXCOORD3;

   #endif

   #ifdef USES_TEXGEN1

      float2 TexGen1       : TEXCOORD4;

   #endif

   #ifdef USES_TEXGEN2
   
      float2 TexGen2       : TEXCOORD5;

   #endif

   #if defined( USES_DYNAMICSHADOWMAP )

      float4 TexShadow0     : TEXCOORD6;

   #endif

   #ifdef USES_WORLDPOSITION

      float3 WorldPosition : TEXCOORD7;

   #endif

   #if defined( USES_DYNAMICSHADOWMAP )

      float4 TexShadow1     : TEXCOORD11;
      float4 TexShadow2     : TEXCOORD12;

   #endif

   #ifdef USES_WORLDNORMAL

      float3 WorldNormal   : TEXCOORD8;

   #endif

   #ifdef USES_BUMP

      float3 WorldTangent  : TEXCOORD9;
      float3 WorldBinormal : TEXCOORD10;

   #endif

   #ifdef USES_FOG

      float  Fog           : FOG;

   #endif
};

#ifdef USES_SKIN

   float4x3 CalculateSkinnedWorldMatrix( VS_INPUT IN )
   {
      return VS_BoneMatrixStart[ IN.BlendIndices.x ] * IN.BlendWeight.x + VS_BoneMatrixStart[ IN.BlendIndices.y ] * IN.BlendWeight.y + VS_BoneMatrixStart[ IN.BlendIndices.z ] * IN.BlendWeight.z + VS_BoneMatrixStart[ IN.BlendIndices.w ] * IN.BlendWeight.w;
   }

#endif

#ifdef USES_PUPPET

   float4x3 CalculateSkinnedWorldMatrix( VS_INPUT IN )
   {
      return VS_BoneMatrixStart[ IN.BoneIndex ];
   }

#endif

#ifdef USES_BUMP

   float3 CalculateBumpedNormal( VS_OUTPUT IN, float3 texBump )
   {
      float3 unitWorldNormal   = normalize( IN.WorldNormal   );
      float3 unitWorldTangent  = normalize( IN.WorldTangent  );
      float3 unitWorldBinormal = normalize( IN.WorldBinormal );
      
      return texBump.r * unitWorldTangent + texBump.g * unitWorldBinormal + texBump.b * unitWorldNormal;
   }

#endif

#ifdef USES_FOG

   struct FOG_OUTPUT
   {
      float3 EyeVector;
      float  Distance;
      float  Fog;
   };

   FOG_OUTPUT CalculateFog( float3 position )
   {
      FOG_OUTPUT FOG;

      #ifdef POSITION_ALREADY_IN_WORLD_SPACE

         FOG.EyeVector = position - VS_WorldCameraPosition;

      #else

         FOG.EyeVector = position - VS_LocalCameraPosition;

      #endif

      FOG.Distance = length( FOG.EyeVector );
      
      FOG.Fog = max( saturate( FOG.Distance * VS_FogParameters.x + VS_FogParameters.y ), VS_FogParameters.z );
      
      return FOG;
   }

#endif

VS_OUTPUT GenerateVertexShaderOutput( VS_INPUT IN )
{
   VS_OUTPUT OUT;

   #if defined( USES_SKIN ) || defined( USES_PUPPET )

      #define WORLD_MATRIX worldMatrix

      float4x3 worldMatrix = CalculateSkinnedWorldMatrix( IN );
      
      float4 worldPosition = float4( mul( IN.Position, worldMatrix ), 1 );

      OUT.Position = mul( worldPosition, VS_ViewProjMatrix );

   #else

      #define WORLD_MATRIX VS_WorldMatrix

      OUT.Position = mul( IN.Position, VS_WorldViewProjMatrix );
      OUT.Position.z = max( OUT.Position.z, VS_ClampFarZ.x );

      #if defined( USES_WORLDPOSITION ) || defined( USES_WORLDSHADOWMAP )

         #ifdef POSITION_ALREADY_IN_WORLD_SPACE

            float3 worldPosition = IN.Position;

         #else

            float3 worldPosition = mul( IN.Position, WORLD_MATRIX );

         #endif

      #else

         float3 worldPosition = 0;

      #endif

   #endif

   #ifdef USES_DYNAMICSHADOWMAP

      OUT.TexShadow0 = mul( IN.Position, VS_ShadowWorldViewProjMatrix0 );
      OUT.TexShadow1 = mul( IN.Position, VS_ShadowWorldViewProjMatrix1 );
      OUT.TexShadow2 = mul( IN.Position, VS_ShadowWorldViewProjMatrix2 );

   #endif

   #ifdef USES_COLOR

      OUT.Color = IN.Color;

   #endif

   #ifdef USES_TEXCOORD0
   
      OUT.TexCoord0 = IN.TexCoord0;

   #endif

   #ifdef USES_TEXCOORD1
   
      OUT.TexCoord1 = IN.TexCoord1;

   #endif

   #ifdef USES_LIGHTMAP
   
      OUT.TexCoord2 = IN.TexCoord2;

   #endif

   #ifdef USES_TEXGEN0
   
      OUT.TexGen0 = mul( float3( IN.TexCoord0.xy, 1 ), VS_TexGenMatrix );

   #endif

   #ifdef USES_TEXGEN1
   
      OUT.TexGen1 = mul( float3( IN.TexCoord1.xy, 1 ), VS_TexGenMatrix );

   #endif

   #ifdef USES_TEXGEN2
   
      OUT.TexGen2 = mul( float3( IN.TexCoord2.xy, 1 ), VS_TexGenMatrix );

   #endif

   #ifdef USES_WORLDPOSITION
   
      OUT.WorldPosition = worldPosition;

   #endif

   #ifdef USES_WORLDSHADOWMAP
   
      OUT.TexCoord2 = ( worldPosition.xz - VS_WorldShadowMapRegion.xy ) * VS_WorldShadowMapRegion.zw;

   #endif

   #ifdef USES_WORLDNORMAL
   
      OUT.WorldNormal = mul( IN.Normal, WORLD_MATRIX );

   #endif

   #ifdef USES_BUMP
   
      OUT.WorldTangent  = mul( IN.Tangent, WORLD_MATRIX );
      OUT.WorldBinormal = cross( OUT.WorldNormal, OUT.WorldTangent );

   #endif

   #ifdef USES_FOG

      #ifdef POSITION_ALREADY_IN_WORLD_SPACE

         OUT.Fog = CalculateFog( worldPosition ).Fog;

      #else

         OUT.Fog = CalculateFog( IN.Position ).Fog;

      #endif

   #endif

   return OUT;
}

struct LIGHT_INPUT
{
   float3   WorldPosition;
   float3   WorldNormal;
   float4   VertexColor;
   float3   TexDiffuse0;
   float3   TexDiffuse1;
   float    GlossPower;
   float    GlossLevel;
   float    ReflectionLevel;

   #ifdef USES_MUD

   float    MudLevel;

   #endif

   bool     WantAmbient;
   bool     WantDiffuse;
   bool     WantSpecular;
   bool     WantReflection;
   bool     WantFresnel;
};

struct LIGHT_OUTPUT
{
   float3 NonAmbientColor;
   float3 AmbientColor;
   float  Alpha;
};

LIGHT_OUTPUT CalculateLighting( LIGHT_INPUT IN )
{
   LIGHT_OUTPUT OUT;

   OUT.Alpha = 0;

   IN.WorldNormal = normalize( IN.WorldNormal );

   float3 eyeVector = normalize( PS_WorldCameraPosition - IN.WorldPosition );

   float viewAngle;

   if ( IN.WantFresnel )
   {
      viewAngle = saturate( 1 - dot( eyeVector, IN.WorldNormal ) );
   }

   float diffuseContribution = saturate( dot( IN.WorldNormal, PS_SunlightDirection ) );

   #ifdef USES_TWOTONE

   float3 texDiffuse = lerp( IN.TexDiffuse0, IN.TexDiffuse1, saturate( 1 - dot( eyeVector, IN.WorldNormal ) ) * 0.50 );

   #else

   float3 texDiffuse = IN.TexDiffuse0;

   #endif

   #ifdef USES_MUD

   texDiffuse = lerp( float3( 0.88f, 0.74f, 0.56f ), texDiffuse, IN.MudLevel );

   IN.MudLevel = IN.MudLevel * IN.MudLevel;

   #endif

   if ( IN.WantDiffuse )
   {
      float3 hemisphericAmbient = lerp( PS_ShadowColor, PS_AmbientColor, IN.WorldNormal.y * 0.5 + 0.5 );
      
      float negDot = saturate( -dot( IN.WorldNormal, PS_SunlightDirection ) );
      float ambientShadow = 1.0 - 0.5 * (negDot * negDot);

      OUT.NonAmbientColor  = texDiffuse * PS_SunlightColor * diffuseContribution;
      OUT.AmbientColor     = texDiffuse * hemisphericAmbient * ambientShadow;
   }
   else
   {
      OUT.NonAmbientColor  = 0;
      OUT.AmbientColor     = texDiffuse * IN.VertexColor;
   }

   if ( IN.WantSpecular )
   {
      float3 refVector = normalize( 2 * diffuseContribution * IN.WorldNormal - PS_SunlightDirection );

      float3 specularContribution = pow( max( dot( refVector, eyeVector ), 0 ), max( IN.GlossPower, 0.01 ) * PS_GlossPower + 1.0 ) * IN.GlossLevel * ( PS_SunlightColor + PS_AmbientColor );

      OUT.Alpha = saturate( dot( specularContribution, 0.35 ) );

      #ifdef USES_MUD

      specularContribution *= max( IN.MudLevel, 0.4 );

      #endif

      OUT.NonAmbientColor += specularContribution;
   }

   if ( IN.WantReflection )
   {
      #ifdef USES_ENVMAP

         float2 reflectionCoordinates = mul( normalize( eyeVector - 4.0 * dot( eyeVector, IN.WorldNormal ) * IN.WorldNormal ), PS_ViewMatrix ) * PS_EnvMapScale + PS_EnvMapOffset;

         float3 reflectionContribution = tex2D( REFLECTION_TEXTURE, reflectionCoordinates ) * 4;

      #else

         float3 reflectionCoordinates = reflect( -eyeVector, IN.WorldNormal );

         float3 reflectionContribution = texCUBE( REFLECTION_TEXTURE, reflectionCoordinates );

      #endif

      if ( IN.WantFresnel )
      {
         float fresnel = saturate( pow( saturate( 1.0 - dot( eyeVector, IN.WorldNormal ) ), 4 ) + 1.0 - 0.55 );

         float reflectionLevel = IN.ReflectionLevel * fresnel;

         #ifdef USES_MUD

         reflectionLevel *= IN.MudLevel;

         #endif

         OUT.Alpha = max( OUT.Alpha, IN.ReflectionLevel * 0.55 + reflectionLevel );

         IN.ReflectionLevel = reflectionLevel;
      }

      OUT.AmbientColor += reflectionContribution * IN.ReflectionLevel;
   }

   return OUT;
}

float3 CalculateDetailColor( float4 texDiffuse, float3 texDetail )
{
   return lerp( texDiffuse, texDiffuse * texDetail, texDiffuse.a );
}

LIGHT_OUTPUT CalculateBlendColor( LIGHT_OUTPUT from, float3 to, float4 vertexColor )
{
   LIGHT_OUTPUT L;

   L.NonAmbientColor = lerp( from.NonAmbientColor, 0,                 vertexColor.a ) * vertexColor;
   L.AmbientColor    = lerp( from.AmbientColor,    to * vertexColor, vertexColor.a );
   L.Alpha           = 0;

   return L;
}

LIGHT_OUTPUT CalculateBlendColor( float3 from, LIGHT_OUTPUT to, float4 vertexColor )
{
   LIGHT_OUTPUT L;

   L.NonAmbientColor = lerp( 0,                   to.NonAmbientColor, vertexColor.a ) * vertexColor;
   L.AmbientColor    = lerp( from * vertexColor, to.AmbientColor,    vertexColor.a );
   L.Alpha           = 0;

   return L;
}

LIGHT_OUTPUT CalculateBlendColor( LIGHT_OUTPUT from, LIGHT_OUTPUT to, float4 vertexColor )
{
   LIGHT_OUTPUT L;

   L.NonAmbientColor = lerp( from.NonAmbientColor, to.NonAmbientColor,  vertexColor.a ) * vertexColor;
   L.AmbientColor    = lerp( from.AmbientColor,    to.AmbientColor,     vertexColor.a );
   L.Alpha           = 0;

   return L;
}

#ifdef USES_WORLDSHADOWMAP

float3 CalculateWorldShadowColor( float2 texCoord )
{
   float2 gridCoord = texCoord * 3;
   float2 cell      = trunc( gridCoord );
   float2 cellCoord = gridCoord - cell;

   float2 quadrant  = step( 0.5, cellCoord );

   cellCoord = cellCoord - quadrant * 0.5;

   float  edgeFade = saturate( ( length( texCoord * 2 - 1 ) - 0.99 ) * 100 );
   float2 cellMask = 1 - saturate( abs( floor( PS_WorldShadowMapUVOffset.z - float2( cell.x, cell.y + 3 ) ) ) );

   float2 shadowCoord = ( cell + ( cellCoord * 2 + 1.0 / 512.0 ) * ( 256.0 / 257.0 ) ) / 3 + PS_WorldShadowMapUVOffset.xy;

   shadowCoord.y = 1 - shadowCoord.y;

   float4 texShadow = tex2D( TexMap7, shadowCoord );

   float shadow = dot( texShadow * float4( 1 - quadrant.x, quadrant.x, 1 - quadrant.x, quadrant.x ), float4( quadrant.y, quadrant.y, 1 - quadrant.y, 1 - quadrant.y ) );

   shadow = smoothstep( 0.2, 3.0 - dot( PS_ShadowColor, 0.66 ), shadow );

   float2 shadows = cellMask * PS_WorldShadowMapUVOffset.w + edgeFade + shadow;

   return saturate( max( shadows.x, shadows.y ) + PS_ShadowColor );
}

#endif

#ifdef USES_DYNAMICSHADOWMAP

float IsInsideShadowMap( float4 texShadow )
{
   float2 minimum = step( 0, texShadow.xy );
   float2 maximum = step( texShadow.xy, texShadow.w );

   return minimum.x * maximum.x * maximum.y * minimum.y;
}

float3 CalculateShadowColor( VS_OUTPUT IN, float3 surfaceColor )
{
   float inside0 = IsInsideShadowMap( IN.TexShadow0 );
   float inside1 = IsInsideShadowMap( IN.TexShadow1 );
   float inside2 = IsInsideShadowMap( IN.TexShadow2 );

   float cascade0 = inside0;
   float cascade1 = saturate( inside1 - inside0 );
   float cascade2 = saturate( saturate( inside2 - inside1 ) - inside0 );

   float3 texShadow = IN.TexShadow0.xyz * cascade0 + IN.TexShadow1.xyz * cascade1 + IN.TexShadow2.xyz * cascade2;

   float4 depths;
   float  depth;

   if ( cascade0 )
   {
      asm
      {
         tfetch2D depths.x___, texShadow.xy, TexMap8, OffsetX =  1, OffsetY =  1
         tfetch2D depths._x__, texShadow.xy, TexMap8, OffsetX = -1, OffsetY =  1
         tfetch2D depths.__x_, texShadow.xy, TexMap8, OffsetX =  1, OffsetY = -1
         tfetch2D depths.___x, texShadow.xy, TexMap8, OffsetX = -1, OffsetY = -1
      };

      depth = tex2D( TexMap8, texShadow.xy ).r;
   }
   else if ( cascade1 )
   {
      asm
      {
         tfetch2D depths.x___, texShadow.xy, TexMap9, OffsetX =  0.5, OffsetY =  0.5
         tfetch2D depths._x__, texShadow.xy, TexMap9, OffsetX = -0.5, OffsetY =  0.5
         tfetch2D depths.__x_, texShadow.xy, TexMap9, OffsetX =  0.5, OffsetY = -0.5
         tfetch2D depths.___x, texShadow.xy, TexMap9, OffsetX = -0.5, OffsetY = -0.5
      };

      depth = tex2D( TexMap9, texShadow.xy ).r;
   }
   else
   {
      asm
      {
         tfetch2D depths.x___, texShadow.xy, TexMap10, OffsetX =  0.5, OffsetY =  0.5
         tfetch2D depths._x__, texShadow.xy, TexMap10, OffsetX = -0.5, OffsetY =  0.5
         tfetch2D depths.__x_, texShadow.xy, TexMap10, OffsetX =  0.5, OffsetY = -0.5
         tfetch2D depths.___x, texShadow.xy, TexMap10, OffsetX = -0.5, OffsetY = -0.5
      };

      depth = tex2D( TexMap10, texShadow.xy ).r;
   }

   float shadowAmount = dot( step( texShadow.z, depths ), 0.20 ) + step( texShadow.z, depth ) * 0.20;

   return lerp( surfaceColor, PS_ShadowColor, shadowAmount * ( cascade0 + cascade1 + cascade2 ) );
}

#endif

float4 ComposeFinalColor( VS_OUTPUT IN, LIGHT_OUTPUT L, float alpha )
{
   #ifdef USES_WORLDSHADOWMAP

      float3 texShadowmap = CalculateWorldShadowColor( IN.TexCoord2 );

      #ifdef USES_DYNAMICSHADOWMAP

      texShadowmap = CalculateShadowColor( IN, texShadowmap );

      #endif

      #ifdef USES_ECOSYSTEM

      L.AmbientColor    = lerp( L.AmbientColor, L.NonAmbientColor, texShadowmap );
      L.NonAmbientColor = 0;

      #else

      L.NonAmbientColor *= texShadowmap;
      L.AmbientColor    *= texShadowmap;

      #endif

   #endif

   #ifdef USES_HDR

      float colorMultiplier = 1.00;

   #else

      float colorMultiplier = 0.25;

   #endif

   float4 color = float4( ( L.NonAmbientColor + L.AmbientColor ) * colorMultiplier, alpha );

   #ifdef USES_SHADERCOLORSCALE

      color = color * PS_ShaderColorScale;

   #endif

   #ifdef USES_OBJECTCOLORSCALE

      color = color * PS_ObjectColorScale;

   #endif

   #ifdef USES_FOG

      color = float4( lerp( PS_FogColor, color, IN.Fog ).xyz, color.a );

   #endif

   return color;
}

float4 CalculateFinalColor( VS_OUTPUT IN, LIGHT_OUTPUT L, float alpha )
{
   return ComposeFinalColor( IN, L, (1.0f - step(alpha, 0.0f)) * max( alpha, L.Alpha ) );
}

float4 CalculateFinalColor( VS_OUTPUT IN, float4 color )
{
   LIGHT_OUTPUT L;

   L.NonAmbientColor = 0;
   L.AmbientColor    = color.rgb;

   return ComposeFinalColor( IN, L, max(color.a, 0) * (1.0f - step(color.a, 0.0f)) );
}

float4 CalculateFinalColor( VS_OUTPUT IN, float3 color, float alpha )
{
   LIGHT_OUTPUT L;

   L.NonAmbientColor = 0;
   L.AmbientColor    = color;

   return ComposeFinalColor( IN, L, max(alpha, 0) * (1.0f - step(alpha, 0.0f)) );
}

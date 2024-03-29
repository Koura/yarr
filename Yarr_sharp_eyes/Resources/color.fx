matrix worldMatrix;
matrix viewMatrix;
matrix projectionMatrix;

struct VertexInputType
{
	float4 position : POSITION;
	float4 color : COLOR;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

PixelInputType ColorVertexShader(VertexInputType input)
{
	PixelInputType output;

	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);
	output.color = (input.color*output.position*0.04+.5)/(input.position.z+2)/max(1,output.position.z*0.2-2)+float4(0.1,0.1,0.1,0);
	return output;
}

float4 ColorPixelShader(PixelInputType input) : SV_TARGET
{
	return input.color;
}

technique10 ColorTechnique
{
	pass pass0
	{
		SetVertexShader(CompileShader(vs_4_0, ColorVertexShader()));
		SetPixelShader(CompileShader(ps_4_0, ColorPixelShader()));
		SetGeometryShader(NULL);
	}
}


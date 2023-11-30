//───────────────────────────────────────
// テクスチャ＆サンプラーデータのグローバル変数定義
//───────────────────────────────────────
Texture2D	g_texture : register(t0);	//テクスチャー
SamplerState	g_sampler : register(s0);	//サンプラー

//───────────────────────────────────────
 // コンスタントバッファ
// DirectX 側から送信されてくる、ポリゴン頂点以外の諸情報の定義
//───────────────────────────────────────
cbuffer global
{
	float4x4	matWVP;			// ワールド・ビュー・プロジェクションの合成行列
	float4x4	matW;			//ワールド行列
	float4		diffuseColor;	// ディフューズカラー（マテリアルの色）
	//float4		g_vecAmbient;		// アンビエントカラー（影の色）
	//float4		g_vecSpeculer;		// スペキュラーカラー（ハイライトの色）
	//float4		g_vecCameraPosition;// 視点（カメラの位置）
	//float		g_shuniness;		// ハイライトの強さ（テカリ具合）
	bool		isTexture;		// テクスチャ貼ってあるかどうか
};

//───────────────────────────────────────
// 頂点シェーダー出力＆ピクセルシェーダー入力データ構造体
//───────────────────────────────────────
struct VS_OUT
{
	float4 pos    : SV_POSITION;	//位置
	float4 normal : TEXCOORD2;		//法線
	float2 uv     : TEXCOORD;		//UV座標
	float4 color	: COLOR;	//色（明るさ）
	float4 eye	  : TEXCOORD1;		//視線
};

//───────────────────────────────────────
// 頂点シェーダ
//───────────────────────────────────────
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL)
{
	//ピクセルシェーダーへ渡す情報
	VS_OUT outData;

	//ローカル座標に、ワールド・ビュー・プロジェクション行列をかけて
	//スクリーン座標に変換し、ピクセルシェーダーへ
	outData.pos = mul(pos, matWVP);
	outData.uv = uv;

	//法線を回転
	normal = mul(normal, matW);
	//outData.normal = normal;		//これをピクセルシェーダーへ

	////視線ベクトル（ハイライトの計算に必要
	//float4 worldPos = mul(pos, matW);					//ローカル座標にワールド行列をかけてワールド座標へ
	//outData.eye = normalize(g_vecCameraPosition - worldPos);	//視点から頂点位置を引き算し視線を求めてピクセルシェーダーへ

	float4 light = float4(-1, 0.5, -0.7, 0);
	light = normalize(light);
	outData.color = clamp(dot(normal, light), 0, 1);


	//まとめて出力
	return outData;
}

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(VS_OUT inData) : SV_Target
{
	float4 lightSource = float4(1.0, 1.0, 1.0, 0.0); //RGB
	float4 ambientSource = float4(0.2, 0.2, 0.2, 1.0);
	float4 diffuse;
	float4 ambient;

	if (isTexture == false)
	{
		diffuse = lightSource * diffuseColor * inData.color;
		ambient = lightSource * diffuseColor * ambientSource;
	}
	else
	{
		diffuse = lightSource * g_texture.Sample(g_sampler, inData.uv) * inData.color;
		ambient = lightSource * g_texture.Sample(g_sampler, inData.uv) * ambientSource;
	}

	//float4 speculer = float4(0, 0, 0, 0);
	//if (g_vecSpeculer.a != 0)
	//{
	//	//float4 R = reflect(lightDir, inData.normal);    //正反射ベクトル
	//	//speculer = pow(saturate(dot(R, inData.eye)), g_shunienss) * g_vecSpeculer;    //ハイライトを求める
	//}

	//float4 output = (diffuse + ambient) * inData.uv.x;
	return (diffuse + ambient);
	//float4 output = g_texture.Sample(g_sampler, inData.uv);
	//return output;

}
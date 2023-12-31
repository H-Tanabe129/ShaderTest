﻿#pragma once

#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include <vector>
#include "Transform.h"


#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")

using std::vector;

enum RENDER_STATE
{
	RENDER_DIRLIGHT,
	RENDER_PNTLIGHT,
};
class Texture;  //前方宣言

class Fbx
{
	//マテリアル
	struct MATERIAL
	{
		Texture*    pTexture_; //これがポインタだからincludeじゃなくて前方宣言でいい
		XMFLOAT4	diffuse;
		XMFLOAT4	ambient;
		XMFLOAT4	specular;
		float 		shininess;
	};

	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;				// ワールドビュープロジェクション
		XMMATRIX	matW;				// ワールド変換のみ
		XMMATRIX	matNormal;			// スケール×平行移動の逆行列
		XMFLOAT4	diffuseColor;		// FBXからとってきた面の色（マテリアルの色）
		XMFLOAT4	ambientColor;		// 
		XMFLOAT4	specularColor;		// 
		FLOAT		shiness;
		BOOL		isTextured;		// テクスチャ貼ってあるかどうか

		XMFLOAT4	lightPosition;
		XMFLOAT4	eyePos;
	};

	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
		XMVECTOR normal;
	};


	int vertexCount_;	//頂点数
	int polygonCount_;	//ポリゴン数
	int materialCount_;	//マテリアルの個数

	ID3D11Buffer* pVertexBuffer_;      //頂点バッファ
	ID3D11Buffer** pIndexBuffer_;       //インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;    //コンスタントバッファ
	MATERIAL* pMaterialList_;
	std::vector <int> indexCount_;
	XMFLOAT4  lightSourcePosition_;
	XMFLOAT4 dColor_;
	XMVECTOR position_;

	void InitVertex(fbxsdk::FbxMesh* mesh);
	void InitIndex(fbxsdk::FbxMesh* mesh);
	void IntConstantBuffer();
	void InitMaterial(fbxsdk::FbxNode* pNode);
	RENDER_STATE state_;

public:

	Fbx();
	HRESULT Load(std::string fileName);
	void Draw(Transform& transform);
	void	SetRenderingShader(RENDER_STATE _state) { state_ = _state; }
	void Release();

	//void SetLightPos(XMFLOAT4& cos);
	//XMFLOAT4 GetLightPos() { return (lightSourcePosition_); }
};
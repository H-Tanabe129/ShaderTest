#pragma once
#include <string>
#include <vector>
#include "Fbx.h"

//-----------------------------------------------------------
//3D���f���iFBX�t�@�C���j���Ǘ�����
//-----------------------------------------------------------
namespace Model
{
	//struct ModelData
	//{
	//	Fbx* pfbx_;
	//	Transform transform_;//�g�����X�t�H�[��
	//	std::string filename_;
	//};
	int Load(std::string fileName);
	void SetTransform(int hModel, Transform transform);
	Fbx* GetModel(int _hModel);
	void Draw(int hModel);
	void Release();
	void ToggleRenderState();

};

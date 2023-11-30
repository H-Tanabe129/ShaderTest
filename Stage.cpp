#include "Stage.h"
#include "Engine/Model.h"

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage")/*, hModel_(-1)*/, hSphere_(-1), hGround_(-1), hArrow_(-1)
{
}

//デストラクタ
Stage::~Stage()
{
}

//初期化
void Stage::Initialize()
{
    //モデルデータのロード
    //hModel_ = Model::Load("Assets/BoxDefault.fbx");
    //assert(hModel_ >= 0);

    hSphere_ = Model::Load("Assets/Ball/ball.fbx");
    assert(hSphere_ >= 0);
    ball.position_ = XMFLOAT3(0, 1.5f, 0);
    ball.scale_ = XMFLOAT3(3.0f, 3.0f, 3.0f);

    hGround_ = Model::Load("Assets/ground.fbx");
    assert(hGround_ >= 0);
    grou.scale_ = XMFLOAT3(8.0f, 1.0f, 8.0f);

    hArrow_ = Model::Load("Assets/arrow.fbx");
    assert(hArrow_ >= 0);
    arrX.position_ = XMFLOAT3(0, 1, -1.5f);
    arrX.scale_ = XMFLOAT3(0.5f, 0.5f, 0.5f);

    hArrow_ = Model::Load("Assets/arrow.fbx");
    assert(hArrow_ >= 0);
    arrY.position_ = XMFLOAT3(0, 1, -1.5f);
    arrY.scale_ = XMFLOAT3(0.5f, 0.5f, 0.5f);
    arrY.rotate_.z = 90;

    hArrow_ = Model::Load("Assets/arrow.fbx");
    assert(hArrow_ >= 0);
    arrZ.position_ = XMFLOAT3(0, 1, -1.5f);
    arrZ.scale_ = XMFLOAT3(0.5f, 0.5f, 0.5f);
    arrZ.rotate_.y = 90;
}

//更新
void Stage::Update()
{
}

//描画
void Stage::Draw()
{
    //Model::SetTransform(hModel_, transform_);
    //Model::Draw(hModel_);
    Model::SetTransform(hSphere_, ball);
    Model::Draw(hSphere_);
    Model::SetTransform(hGround_, grou);
    Model::Draw(hGround_);
    Model::SetTransform(hArrow_, arrX);
    Model::Draw(hArrow_);
    Model::SetTransform(hArrow_, arrY);
    Model::Draw(hArrow_);
    Model::SetTransform(hArrow_, arrZ);
    Model::Draw(hArrow_);
}

//開放
void Stage::Release()
{
}
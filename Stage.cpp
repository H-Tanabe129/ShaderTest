#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"

namespace {
    const XMFLOAT4 DEF_LIGHT_POSITION{ 1, 2, 1, 0 };
}

void Stage::IntConstantBuffer()
{
    D3D11_BUFFER_DESC cb;
    cb.ByteWidth = sizeof(CBUFF_STAGESCENE);
    cb.Usage = D3D11_USAGE_DEFAULT;
    cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cb.CPUAccessFlags = 0;
    cb.MiscFlags = 0;
    cb.StructureByteStride = 0;

    // コンスタントバッファの作成
    HRESULT hr;
    hr = Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pCBStageScene_);
    if (FAILED(hr))
    {
        MessageBox(NULL, "コンスタントバッファの作成に失敗しました", "エラー", MB_OK);
    }

}

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), hModel_(-1), hSphere_(-1), hGround_(-1), hArrow_(-1),lightSourcePosition_(DEF_LIGHT_POSITION)
{
}

//デストラクタ
Stage::~Stage()
{
}

//初期化
void Stage::Initialize()
{
    Camera::SetPosition(XMVECTOR{ 0, 10, -20, 0 });
    Camera::SetTarget(XMVECTOR{ 0, 2, 0, 0 });

    //モデルデータのロード
    hModel_ = Model::Load("Assets/Donuts.fbx");
    assert(hModel_ >= 0);

    hSphere_ = Model::Load("Assets/Ball/ball.fbx");
    assert(hSphere_ >= 0);
    //ball.position_ = XMFLOAT3(2, 1.5f, -3);
    //ball.scale_ = XMFLOAT3(2.0f, 2.0f, 2.0f);
    trLightBall.scale_ = { 0.4, 0.4, 0.4 };

    //hGround_ = Model::Load("Assets/ground.fbx");
    //assert(hGround_ >= 0);
    //grou.scale_ = XMFLOAT3(8.0f, 1.0f, 8.0f);

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

    IntConstantBuffer();

}

//更新
void Stage::Update()
{
    //ball.rotate_.y += 0.5f;

    if (Input::IsKeyUp(DIK_SPACE))
    {
        Model::ToggleRenderState();
    }
    //transform_.rotate_.y += 0.5f;
    // trDonuts.rotate_.y += 0.5f;
    if (Input::IsKey(DIK_RIGHT))
    {
        XMFLOAT4 p = GetLightPos();
        XMFLOAT4 margin{ p.x + 0.1f, p.y + 0.0f, p.z + 0.0f, p.w + 0.0f };

        //Model::GetModel(hModel_)->SetLightPos(margin);
        SetLightPos(margin);
    }
    if (Input::IsKey(DIK_LEFT))
    {
        XMFLOAT4 p = GetLightPos();
        XMFLOAT4 margin{ p.x - 0.1f, p.y - 0.0f, p.z - 0.0f, p.w - 0.0f };

        /// Model::GetModel(hModel_)->SetLightPos(margin);
        SetLightPos(margin);
    }
    if (Input::IsKey(DIK_UP))
    {
        XMFLOAT4 p = GetLightPos();
        XMFLOAT4 margin{ p.x - 0.0f, p.y + 0.1f, p.z - 0.0f, p.w - 0.0f };

        //Model::GetModel(hModel_)->SetLightPos(margin);
        SetLightPos(margin);
    }
    if (Input::IsKey(DIK_DOWN))
    {
        XMFLOAT4 p = GetLightPos();
        XMFLOAT4 margin{ p.x - 0.0f, p.y - 0.1f, p.z - 0.0f, p.w - 0.0f };

        //Model::GetModel(hModel_)->SetLightPos(margin);
        SetLightPos(margin);
    }
    if (Input::IsKey(DIK_W))
    {
        XMFLOAT4 p = GetLightPos();
        XMFLOAT4 margin{ p.x - 0.0f, p.y - 0.0f, p.z + 0.1f, p.w + 0.0f };

        //Model::GetModel(hModel_)->SetLightPos(margin);
        SetLightPos(margin);
    }
    if (Input::IsKey(DIK_S))
    {
        XMFLOAT4 p = GetLightPos();
        XMFLOAT4 margin{ p.x - 0.0f, p.y - 0.0f, p.z - 0.1f, p.w - 0.0f };

        //Model::GetModel(hModel_)->SetLightPos(margin);
        SetLightPos(margin);
    }
    XMFLOAT4 tmp{ GetLightPos() };
    ball.position_ = { tmp.x, tmp.y,tmp.z };

    CBUFF_STAGESCENE cb;
    cb.lightPosition = lightSourcePosition_;
    XMStoreFloat4(&cb.eyePos, Camera::GetEyePosition());

    Direct3D::pContext_->UpdateSubresource(pCBStageScene_,
        0, NULL, &cb, 0, 0);
    
    Direct3D::pContext_->VSSetConstantBuffers(1, 1, &pCBStageScene_);	//頂点シェーダー用	
    Direct3D::pContext_->PSSetConstantBuffers(1, 1, &pCBStageScene_);	//ピクセルシェーダー用

}

//描画
void Stage::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
    Model::SetTransform(hSphere_, trLightBall);
    Model::Draw(hSphere_);
    //Model::SetTransform(hSphere_, ball);
    //Model::Draw(hSphere_);
    //Model::SetTransform(hGround_, grou);
    //Model::Draw(hGround_);
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
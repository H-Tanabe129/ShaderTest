#pragma once
#include "Engine/GameObject.h"
#include "Engine/Quad.h"


struct CBUFF_STAGESCENE
{
    XMFLOAT4	lightPosition;
    XMFLOAT4	eyePos;
};

//◆◆◆を管理するクラス
class Stage : public GameObject
{
    int hModel_;    //モデル番号
    //int hSphere_;    //モデル番号
    //int hGround_;    //モデル番号
    //int hArrow_;    //モデル番号
    int hLightBall_;    //モデル番号
    int hDice_;
    int hWater_;

    Transform ball;
    Transform grou;
    Transform arrX;
    Transform arrY;
    Transform arrZ;
    Transform trLightBall;

    ID3D11Buffer* pCBStageScene_;
    void IntConstantBuffer();
    XMFLOAT4 lightSourcePosition_;

public:
    //コンストラクタ
    Stage(GameObject* parent);

    //デストラクタ
    ~Stage();

    void Initialize() override;    //初期化
    void Update() override;    //更新
    void Draw() override;    //描画
    void Release() override;    //開放

    void SetLightPos(XMFLOAT4& _pos){ lightSourcePosition_ = _pos; }
    XMFLOAT4 GetLightPos() { return(lightSourcePosition_); }

};
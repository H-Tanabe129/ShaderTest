#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class Stage : public GameObject
{
    //int hModel_;    //モデル番号
    int hSphere_;    //モデル番号
    int hGround_;    //モデル番号
    int hArrow_;    //モデル番号

    Transform ball;
    Transform grou;
    Transform arrX;
    Transform arrY;
    Transform arrZ;

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

};
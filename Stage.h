#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class Stage : public GameObject
{
    int hModel_;    //モデル番号
    int hSphere_;    //モデル番号
    int hGround_;    //モデル番号
    int hArrow_;    //モデル番号

    Transform ball;
    Transform grou;
    Transform arrX;
    Transform arrY;
    Transform arrZ;

public:
    //コンストラクタ
    Stage(GameObject* parent);

    //デストラクタ
    ~Stage();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};
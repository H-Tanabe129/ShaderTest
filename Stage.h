#pragma once
#include "Engine/GameObject.h"
#include "Engine/Quad.h"


struct CBUFF_STAGESCENE
{
    XMFLOAT4	lightPosition;
    XMFLOAT4	eyePos;
};

//���������Ǘ�����N���X
class Stage : public GameObject
{
    int hModel_;    //���f���ԍ�
    //int hSphere_;    //���f���ԍ�
    //int hGround_;    //���f���ԍ�
    //int hArrow_;    //���f���ԍ�
    int hLightBall_;    //���f���ԍ�
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
    //�R���X�g���N�^
    Stage(GameObject* parent);

    //�f�X�g���N�^
    ~Stage();

    void Initialize() override;    //������
    void Update() override;    //�X�V
    void Draw() override;    //�`��
    void Release() override;    //�J��

    void SetLightPos(XMFLOAT4& _pos){ lightSourcePosition_ = _pos; }
    XMFLOAT4 GetLightPos() { return(lightSourcePosition_); }

};
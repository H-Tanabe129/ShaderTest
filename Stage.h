#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class Stage : public GameObject
{
    int hModel_;    //���f���ԍ�
    int hSphere_;    //���f���ԍ�
    int hGround_;    //���f���ԍ�
    int hArrow_;    //���f���ԍ�

    Transform ball;
    Transform grou;
    Transform arrX;
    Transform arrY;
    Transform arrZ;

public:
    //�R���X�g���N�^
    Stage(GameObject* parent);

    //�f�X�g���N�^
    ~Stage();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};
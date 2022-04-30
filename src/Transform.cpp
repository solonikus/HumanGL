//
// Created by Alteracia on 08.01.2021.
// For educational purpose. Use carefully.
//

#include "Transform.h"

Transform::Transform(Transform *parentTransform, Matrix<float> localRotation, Vector3<float> localScale)
: IComponent(), parent(parentTransform), localRotation(localRotation), localScale(localScale)
{
	if (parent != nullptr) parent->AddChild(this);
	pivotPosition = Matrix<float>(1,1).Translate(0.0f, localScale.y * 0.5f, 0.0f);
	ResetStack();
}

Transform::~Transform()
{
	for (auto c : children)
	{
		delete c;
	}
	for (auto b : behaviours)
	{
		delete b;
	}
}

int Transform::Start()
{
	for (auto b: behaviours) b->Start();
	for (auto c: children) c->Start();
	return 0;
}

void Transform::Update()
{
	//std::cout << "Transform\n";
// 1. Update Behaviors
	for (auto b: behaviours) b->Update();
	UpdateEndPosition();
// 2. Update Children
	for (auto c: children) c->Update();
	ResetStack();
}

void Transform::Finish()
{

}

void Transform::AddChild(Transform *child)
{
	children.push_back(child);
}

void Transform::AddBehaviour(IMonoBehavior *behavior)
{
	behaviours.push_back(behavior);
}

Matrix<float> Transform::TransformMatrix(bool applyScale)
{
	Matrix<float> result = Matrix<float>(1,1);
	if (applyScale)
		result = result.ToScale(localScale);
	result = result * pivotPosition;
	for (int i = rotationStack.size() - 1; i >= 0; --i) result = result * rotationStack[i];
	for (auto m : positionStack) result = result * m;

	return result;
}

void Transform::Move(Vector3<float> newPosition)
{
	Matrix<float> translate(1,1);
	positionStack.push_back(translate.Translate(newPosition));
}

void Transform::Rotate(Vector3<float> newRotation)
{
	Matrix<float> rotate(1,1);// TODO Fix this
	rotationStack.push_back(rotate.Rotate(newRotation.z, Vector3<float>(0,0,1)));
}

void Transform::ResetStack()
{
	positionStack.clear();
	if (parent != nullptr) 
		positionStack.push_back(parent->EndPosition);
	rotationStack.clear();
	rotationStack.push_back(localRotation);
}

void Transform::UpdateEndPosition()
{
	Matrix<float> transform = TransformMatrix(false);
	Matrix<float> transl = Matrix<float>(1,1).Translate(0.0f, localScale.y * 0.5f, 0.0f);

	EndPosition = transl * transform;
}

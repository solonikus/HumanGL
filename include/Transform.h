//
// Created by Alteracia on 08.01.2021.
// For educational purpose. Use carefully.
//

#ifndef HUMAN_GL_TRANSFORM_H
#define HUMAN_GL_TRANSFORM_H

# include <vector>

#include <iostream>

# include "IComponent.h"
# include "IMonoBehavior.h"
# include "matrix.hpp"

class Transform : public IComponent
{
public:
	Transform(Transform *parentTransform, Matrix<float> localRotation, Vector3<float> localScale);
	~Transform() override;

	int Start() override;
	void Update() override;
	void Finish() override;

	/// Build hierarchy
	/// \param child dependent transform
	void AddChild(Transform *child);
	/// Behavior connected to transform
	/// \param behavior
	void AddBehaviour(IMonoBehavior *behavior);

	// For Render
	Matrix<float> TransformMatrix(bool applyScale);
	// For animations
	/// Add new Translate matrix to stack, use for root bone
	/// \param newPosition translate matrix
	void Move(Vector3<float> newPosition);
	/// Add new Quaternion matrix to stack
	/// \param newRotation quaternion
	void Rotate(Vector3<float> newRotation);
	// For children
	Matrix<float> EndPosition;

private:
	void	ResetStack();
	void	UpdateEndPosition();

	// local matrix
	Matrix<float> pivotPosition;
	Matrix<float> localRotation;
	Vector3<float> localScale;
	// matrixStack
	std::vector<Matrix<float>> positionStack;
	std::vector<Matrix<float>> rotationStack;

	Transform *parent;
	std::vector<Transform*> children;
	std::vector<IMonoBehavior*> behaviours;
};

Transform *createJumpingHuman();
Transform *createWalkingHuman();
Transform *createStandingHuman();


#endif //HUMAN_GL_TRANSFORM_H

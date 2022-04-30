//
// Created by Alteracia on 11/5/21.
// For educational purpose. Use carefully.
//

#ifndef HUMAN_GL_ANIMATOR_H
# define HUMAN_GL_ANIMATOR_H

# include "IMonoBehavior.h"
# include "Transform.h"
# include <chrono>
//# include <ctime>

#include <map>

enum AnimationTarget
{
	Position, Rotation, Scale
};

struct AnimationSequence
{
	AnimationTarget target; // Move or rotate or scale
	int duration; // in frames
	int frameRate; // frame per second
	std::map<int, Vector3<float>> keys; // Frame, Vector3
};

// Keep animation sequence
// Apply transformations to Transform
class Animator : public IMonoBehavior
{
public:
	Animator(Transform *component, std::vector<AnimationSequence> sequence) : transform(component), animation(sequence) {
		transform->AddBehaviour(this);
	}
	~Animator() override;

	void Start() override;
	void Update() override;
	std::vector<AnimationSequence> animation;
private:
	Transform *transform;
#if defined __linux__ || defined _WIN32
	std::chrono::_V2::system_clock::time_point startTime;
#else
	std::chrono::steady_clock::time_point startTime;
#endif
	Vector3<float> Interpolate(const AnimationSequence& sequence);
};


#endif //HUMAN_GL_ANIMATOR_H

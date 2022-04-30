//
// Created by Alteracia on 11/5/21.
// For educational purpose. Use carefully.
//

#include "Animator.h"

void Animator::Start()
{
	startTime = std::chrono::high_resolution_clock::now();
}

void Animator::Update()
{

	// Called each frame

	for (const auto& s : animation) {
		// 1. get 2 key for current frame
		// 2. interpolate matrix
		Vector3<float> result = Interpolate(s);
		// 3. add matrix to transforms stack
		switch (s.target) {
			case Position:
				transform->Move(result);
				break;
			case Rotation:
				transform->Rotate(result);
				break;
			case Scale:
				// TODO Scale?
				break;
		}
	}
}


Vector3<float> Animator::Interpolate(const AnimationSequence& sequence)
{
 	// Get current frame of animation
	auto now = std::chrono::high_resolution_clock::now();
	float deltaTime = (float)std::chrono::duration<double, std::milli>(now - startTime).count() / 1000;
	//std::cout <<"seconds "<< deltaTime << "\n";
	int currentFrame = (int)(deltaTime * (float)sequence.frameRate) % sequence.duration;
	//std::cout <<"frame "<< currentFrame << "\n";
	// Get keys
	std::pair<int, Vector3<float>> from = *(sequence.keys.begin());
	std::pair<int, Vector3<float>> to =  *(sequence.keys.begin());
	for (auto key: sequence.keys) {
		if (key.first <= currentFrame)
			from = key;
		if (key.first >= currentFrame)
		{
			to = key;
			break;
		}
	}
	// Get alpha
	float alpha = (to.first - from.first) <= 0 ? 0.0f : (float)(currentFrame - from.first) / (float)(to.first - from.first);
	// Sin InOut easing
	alpha = -(float)(cos(M_PI * alpha) - 1.0f) / 2.0f; //alpha < 0.5 ? 4.0f * alpha * alpha * alpha : 1.0f - (float)pow(-2.0f * alpha + 2.0f, 3) / 2; //
	// Interpolate
	return (from.second * (1 -  alpha)) + (to.second * alpha); //Vector3<float>();
}


Animator::~Animator() = default;


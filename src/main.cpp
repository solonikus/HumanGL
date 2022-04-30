//
// Created by Alteracia on 05.01.2021.
// For educational purpose. Use carefully.
//

#include "GLFWEngine.h"
#include "GLRender.h"
#include "Transform.h"
#include "Animator.h"
#include "Renderer.h"


Transform *createJumpingHuman()
{
	// 0. Create root
	Transform *root = new Transform(nullptr, Matrix<float>(1,1),
									Vector3<float> {0.0f, 0.0f, 0.0f});
	new Animator(root, std::vector<AnimationSequence>{
			{Position, 60, 30, std::map<int, Vector3<float>>{
					{0,Vector3<float>(0,0,0)},
					{15,Vector3<float>(0.3,-0.5f,0)},
					{20,Vector3<float>(0,0,0)},
					{30,Vector3<float>(0,1,0)},
					{40,Vector3<float>(0,0,0)},
					{45,Vector3<float>(0.3,-0.5f,0)},
					{60,Vector3<float>(0,0,0)}
			}}});
	// 2. Spine
	Transform *spine = new Transform(root, Matrix<float>(1,1),
									 Vector3<float> {0.2f, 1.0f, 0.4f});
	new Animator(spine, std::vector<AnimationSequence>{
			{Rotation, 60, 30, std::map<int, Vector3<float>>{
					{0,Vector3<float>(0,0,0)},
					{15,Vector3<float>(0,0,10)},
					{20,Vector3<float>(0,0,0)},
					{40,Vector3<float>(0,0,0)},
					{45,Vector3<float>(0,0,10)},
					{60,Vector3<float>(0,0,0)}
			}}});
	new Renderer(spine, Vector4<float> {0.2, 0.5, 0.3, 1.0});
	// 3. Head
	Transform *head = new Transform(spine, Matrix<float>(1,1),
									Vector3<float> {0.2f, 0.4f, 0.2f});
	new Renderer(head, Vector4<float> {0.2, 1.0, 0.3, 1.0});
	// 4. Left hand
	Transform *l_shoulder = new Transform(spine,
										  Matrix<float>(1,1).Rotate(90,Vector3<float>(1.0f, 0.0f, 0.0f)),
										  Vector3<float> {0.0f, 0.25f, 0.0f});
	Transform *l_upperarm = new Transform(l_shoulder, Matrix<float>(1, 1)
												  .Rotate(90, Vector3<float>(1.0f, 0.0f, 0.0f)),
										  Vector3<float> {0.15f, 0.6f, 0.15f});
	new Animator(l_upperarm, std::vector<AnimationSequence>{
			{Rotation, 60, 30, std::map<int, Vector3<float>>{
					{0,Vector3<float>(0,0,0)},
					{25,Vector3<float>(0,0,0)},
					{30,Vector3<float>(0,0,-30)},
					{35,Vector3<float>(0,0,0)},
					{60,Vector3<float>(0,0,0)}
			}}});
	new Renderer(l_upperarm, Vector4<float> {0.1, 0.1, 0.5, 1.0});

	Transform *l_forearm = new Transform(l_upperarm, Matrix<float>(1, 1),
										 Vector3<float> {0.1f, 0.6f, 0.1f});
	new Animator(l_forearm, std::vector<AnimationSequence>{
			{Rotation, 60, 30, std::map<int, Vector3<float>>{
					{0,Vector3<float>(0,0,0)},
					{25,Vector3<float>(0,0,0)},
					{30,Vector3<float>(0,0,90)},
					{35,Vector3<float>(0,0,0)},
					{60,Vector3<float>(0,0,0)}
			}}});
	new Renderer(l_forearm, Vector4<float> {0.1, 0.1, 0.5, 1.0});
	// 4. Left leg
	Transform *l_hip = new Transform(root,
									 Matrix<float>(1,1).Rotate(90, Vector3<float>(1.0f, 0.0f, 0.0f)),
									 Vector3<float> {0.0f, 0.2f, 0.0f});
	Transform *l_thigh = new Transform(l_hip,
									   Matrix<float>(1,1).Rotate(90, Vector3<float>(1.0f, 0.0f, 0.0f)),
									   Vector3<float> {0.2f, 0.6f, 0.2f});
	new Animator(l_thigh, std::vector<AnimationSequence>{
			{Rotation, 60, 30, std::map<int, Vector3<float>>{
					{0,Vector3<float>(0,0,0)},
					{15,Vector3<float>(0,0,90)},
					{20,Vector3<float>(0,0,0)},
					{40,Vector3<float>(0,0,0)},
					{45,Vector3<float>(0,0,90)},
					{60,Vector3<float>(0,0,0)}
			}}});

	new Renderer(l_thigh, Vector4<float> {0.5, 0.1, 0.5, 1.0});
	Transform *l_feet = new Transform(l_thigh,
									  Matrix<float>(1,1),
									  Vector3<float> {0.15f, 0.6f, 0.15f});
	new Animator(l_feet, std::vector<AnimationSequence>{
			{Rotation, 60, 30, std::map<int, Vector3<float>>{
					{0,Vector3<float>(0,0,0)},
					{15,Vector3<float>(0,0,-120)},
					{20,Vector3<float>(0,0,0)},
					{40,Vector3<float>(0,0,0)},
					{45,Vector3<float>(0,0,-120)},
					{60,Vector3<float>(0,0,0)}
			}}});

	new Renderer(l_feet, Vector4<float> {0.5, 0.1, 0.5, 1.0});
	// 4. Right hand
	Transform *r_shoulder = new Transform(spine,
										  Matrix<float>(1,1).Rotate(-90,Vector3<float>(1.0f, 0.0f, 0.0f)),
										  Vector3<float> {0.0f, 0.25f, 0.0f});
	Transform *r_upperarm = new Transform(r_shoulder, Matrix<float>(1, 1).Rotate(-90, Vector3<float>(1.0f, 0.0f, 0.0f)),
										  Vector3<float> {0.15f, 0.6f, 0.15f});
	new Animator(r_upperarm, std::vector<AnimationSequence>{
			{Rotation, 60, 30, std::map<int, Vector3<float>>{
					{0,Vector3<float>(0,0,0)},
					{25,Vector3<float>(0,0,0)},
					{30,Vector3<float>(0,0,-30)},
					{35,Vector3<float>(0,0,0)},
					{60,Vector3<float>(0,0,0)}
			}}});
	new Renderer(r_upperarm, Vector4<float> {0.1, 0.1, 0.5, 1.0});

	Transform *r_forearm = new Transform(r_upperarm, Matrix<float>(1, 1),
										 Vector3<float> {0.1f, 0.6f, 0.1f});
	new Animator(r_forearm, std::vector<AnimationSequence>{
			{Rotation, 60, 30, std::map<int, Vector3<float>>{
					{0,Vector3<float>(0,0,0)},
					{25,Vector3<float>(0,0,0)},
					{30,Vector3<float>(0,0,90)},
					{35,Vector3<float>(0,0,0)},
					{60,Vector3<float>(0,0,0)}
			}}});
	new Renderer(r_forearm, Vector4<float> {0.1, 0.1, 0.5, 1.0});
	// 4. Right leg
	Transform *r_hip = new Transform(root,
									 Matrix<float>(1,1).Rotate(-90, Vector3<float>(1.0f, 0.0f, 0.0f)),
									 Vector3<float> {0.0f, 0.2f, 0.0f});
	Transform *r_thigh = new Transform(r_hip,
									   Matrix<float>(1,1).Rotate(-90, Vector3<float>(1.0f, 0.0f, 0.0f)),
									   Vector3<float> {0.2f, 0.6f, 0.2f});
	new Animator(r_thigh, std::vector<AnimationSequence>{
			{Rotation, 60, 30, std::map<int, Vector3<float>>{
					{0,Vector3<float>(0,0,0)},
					{15,Vector3<float>(0,0,90)},
					{20,Vector3<float>(0,0,0)},
					{40,Vector3<float>(0,0,0)},
					{45,Vector3<float>(0,0,90)},
					{60,Vector3<float>(0,0,0)}
			}}});

	new Renderer(r_thigh, Vector4<float> {0.5, 0.1, 0.5, 1.0});
	Transform *r_feet = new Transform(r_thigh, Matrix<float>(1,1), Vector3<float> {0.15f, 0.6f, 0.15f});
	new Animator(r_feet, std::vector<AnimationSequence>{
			{Rotation, 60, 30, std::map<int, Vector3<float>>{
					{0,Vector3<float>(0,0,0)},
					{15,Vector3<float>(0,0,-120)},
					{20,Vector3<float>(0,0,0)},
					{40,Vector3<float>(0,0,0)},
					{45,Vector3<float>(0,0,-120)},
					{60,Vector3<float>(0,0,0)}
			}}});

	new Renderer(r_feet, Vector4<float> {0.5, 0.1, 0.5, 1.0});

	return root;
}

Transform *createWalkingHuman()
{
	// 0. Create root
	Transform *root = new Transform(nullptr, Matrix<float>(1,1),
			Vector3<float> {0.0f, 0.0f, 0.0f});
	new Animator(root, std::vector<AnimationSequence>{
		{Position, 60, 30, std::map<int, Vector3<float>>{
				{0,Vector3<float>(2,0,0)},
				{60,Vector3<float>(-2,0,0)}
		}}});
	// 2. Spine
	Transform *spine = new Transform(root, Matrix<float>(1,1),
	        Vector3<float> {0.2f, 1.0f, 0.4f});
	new Renderer(spine, Vector4<float> {0.2, 0.5, 0.3, 1.0});
	// 3. Head
	Transform *head = new Transform(spine, Matrix<float>(1,1),
	        Vector3<float> {0.2f, 0.4f, 0.2f});
	new Renderer(head, Vector4<float> {0.2, 1.0, 0.3, 1.0});
	// 4. Left hand
	Transform *l_shoulder = new Transform(spine,
										  Matrix<float>(1,1).Rotate(90,Vector3<float>(1.0f, 0.0f, 0.0f)),
										  Vector3<float> {0.0f, 0.25f, 0.0f});
	Transform *l_upperarm = new Transform(l_shoulder, Matrix<float>(1, 1)
	        								.Rotate(90, Vector3<float>(1.0f, 0.0f, 0.0f)),
										  Vector3<float> {0.15f, 0.6f, 0.15f});
	new Animator(l_upperarm, std::vector<AnimationSequence>{
		   {Rotation, 60, 30, std::map<int, Vector3<float>>{
				   {0,Vector3<float>(0,0,-30)},
				   {15,Vector3<float>(0,0,0)},
				   {30,Vector3<float>(0,0,-30)},
				   {45,Vector3<float>(0,0,0)},
				   {60,Vector3<float>(0,0,-30)}
		   }}});
	new Renderer(l_upperarm, Vector4<float> {0.1, 0.1, 0.5, 1.0});

	Transform *l_forearm = new Transform(l_upperarm, Matrix<float>(1, 1),
										  Vector3<float> {0.1f, 0.6f, 0.1f});
	new Animator(l_forearm, std::vector<AnimationSequence>{
			{Rotation, 60, 30, std::map<int, Vector3<float>>{
					{0,Vector3<float>(0,0,0)},
					{15,Vector3<float>(0,0,15)},
					{30,Vector3<float>(0,0,0)},
					{45,Vector3<float>(0,0,15)},
					{60,Vector3<float>(0,0,0)}
			}}});
	new Renderer(l_forearm, Vector4<float> {0.1, 0.1, 0.5, 1.0});
	// 4. Left leg
	Transform *l_hip = new Transform(root,
									 Matrix<float>(1,1).Rotate(90, Vector3<float>(1.0f, 0.0f, 0.0f)),
									 Vector3<float> {0.0f, 0.1f, 0.0f});
	Transform *l_thigh = new Transform(l_hip,
									   Matrix<float>(1,1).Rotate(90, Vector3<float>(1.0f, 0.0f, 0.0f)),
									   Vector3<float> {0.2f, 0.6f, 0.2f});
	new Animator(l_thigh, std::vector<AnimationSequence>{
			{Rotation, 60, 30, std::map<int, Vector3<float>>{
					{0,Vector3<float>(0,0,30)},
					{15,Vector3<float>(0,0,-30)},
					{30,Vector3<float>(0,0,30)},
					{45,Vector3<float>(0,0,-30)},
					{60,Vector3<float>(0,0,30)}
			}}});

	new Renderer(l_thigh, Vector4<float> {0.5, 0.1, 0.5, 1.0});
	Transform *l_feet = new Transform(l_thigh,
									  Matrix<float>(1,1),
									  Vector3<float> {0.15f, 0.6f, 0.15f});
	new Animator(l_feet, std::vector<AnimationSequence>{
			{Rotation, 60, 30, std::map<int, Vector3<float>>{
					{0,Vector3<float>(0,0,0)},
					{15,Vector3<float>(0,0,-30)},
					{30,Vector3<float>(0,0,0)},
					{45,Vector3<float>(0,0,-30)},
					{60,Vector3<float>(0,0,0)}
			}}});

	new Renderer(l_feet, Vector4<float> {0.5, 0.1, 0.5, 1.0});
	// 4. Right hand
	Transform *r_shoulder = new Transform(spine,
										  Matrix<float>(1,1).Rotate(-90,Vector3<float>(1.0f, 0.0f, 0.0f)),
										  Vector3<float> {0.0f, 0.25f, 0.0f});
	Transform *r_upperarm = new Transform(r_shoulder, Matrix<float>(1, 1).Rotate(-90, Vector3<float>(1.0f, 0.0f, 0.0f)),
										  Vector3<float> {0.15f, 0.6f, 0.15f});
	new Animator(r_upperarm, std::vector<AnimationSequence>{
			{Rotation, 60, 30, std::map<int, Vector3<float>>{
					{0,Vector3<float>(0,0,0)},
					{15,Vector3<float>(0,0,-30)},
					{30,Vector3<float>(0,0,0)},
					{45,Vector3<float>(0,0,-30)},
					{60,Vector3<float>(0,0,0)}
			}}});
	new Renderer(r_upperarm, Vector4<float> {0.1, 0.1, 0.5, 1.0});

	Transform *r_forearm = new Transform(r_upperarm, Matrix<float>(1, 1),
										 Vector3<float> {0.1f, 0.6f, 0.1f});
	new Animator(r_forearm, std::vector<AnimationSequence>{
			{Rotation, 60, 30, std::map<int, Vector3<float>>{
					{0,Vector3<float>(0,0,15)},
					{15,Vector3<float>(0,0,0)},
					{30,Vector3<float>(0,0,15)},
					{45,Vector3<float>(0,0,0)},
					{60,Vector3<float>(0,0,15)}
			}}});
	new Renderer(r_forearm, Vector4<float> {0.1, 0.1, 0.5, 1.0});
	// 4. Right leg
	Transform *r_hip = new Transform(root,
									 Matrix<float>(1,1).Rotate(-90, Vector3<float>(1.0f, 0.0f, 0.0f)),
									 Vector3<float> {0.0f, 0.1f, 0.0f});
	Transform *r_thigh = new Transform(r_hip,
									   Matrix<float>(1,1).Rotate(-90, Vector3<float>(1.0f, 0.0f, 0.0f)),
									   Vector3<float> {0.2f, 0.6f, 0.2f});
	new Animator(r_thigh, std::vector<AnimationSequence>{
			{Rotation, 60, 30, std::map<int, Vector3<float>>{
					{0,Vector3<float>(0,0,-30)},
					{15,Vector3<float>(0,0,30)},
					{30,Vector3<float>(0,0,-30)},
					{45,Vector3<float>(0,0,30)},
					{60,Vector3<float>(0,0,-30)}
			}}});

	new Renderer(r_thigh, Vector4<float> {0.5, 0.1, 0.5, 1.0});
	Transform *r_feet = new Transform(r_thigh, Matrix<float>(1,1), Vector3<float> {0.15f, 0.6f, 0.15f});
	new Animator(r_feet, std::vector<AnimationSequence>{
			{Rotation, 60, 30, std::map<int, Vector3<float>>{
					{0,Vector3<float>(0,0,-30)},
					{15,Vector3<float>(0,0,0)},
					{30,Vector3<float>(0,0,-30)},
					{45,Vector3<float>(0,0,0)},
					{60,Vector3<float>(0,0,-30)}
			}}});

	new Renderer(r_feet, Vector4<float> {0.5, 0.1, 0.5, 1.0});

	return root;
}

Transform *createStandingHuman()
{
	// Platform
	Transform *platform = new Transform(nullptr, Matrix<float>(1,1).Rotate(90, Vector3<float>{1,0,0}),
									Vector3<float> {0.0f, 0.0f, 0.0f});
	new Animator(platform, std::vector<AnimationSequence>{
			{Rotation, 60, 30, std::map<int, Vector3<float>>{
					{0,Vector3<float>(0,0,0)},
					{60,Vector3<float>(0,0,360)}
			}}});

	// 0. Create root
	Transform *root = new Transform(platform, Matrix<float>(1,1).Rotate(-90, Vector3<float>{1,0,0}),
									Vector3<float> {2.0f, 0.2f, 2.0f});
	// 2. Spine
	Transform *spine = new Transform(root, Matrix<float>(1,1),
									 Vector3<float> {0.2f, 1.0f, 0.4f});
	new Renderer(spine, Vector4<float> {0.2, 0.5, 0.3, 1.0});
	// 3. Head
	Transform *head = new Transform(spine, Matrix<float>(1,1),
									Vector3<float> {0.2f, 0.4f, 0.2f});
	new Renderer(head, Vector4<float> {0.2, 1.0, 0.3, 1.0});
	// 4. Left hand
	Transform *l_shoulder = new Transform(spine,
										  Matrix<float>(1,1).Rotate(90,Vector3<float>(1.0f, 0.0f, 0.0f)),
										  Vector3<float> {0.0f, 0.25f, 0.0f});
	Transform *l_upperarm = new Transform(l_shoulder, Matrix<float>(1, 1)
												  .Rotate(90, Vector3<float>(1.0f, 0.0f, 0.0f)),
										  Vector3<float> {0.15f, 0.6f, 0.15f});
	new Renderer(l_upperarm, Vector4<float> {0.1, 0.1, 0.5, 1.0});

	Transform *l_forearm = new Transform(l_upperarm, Matrix<float>(1, 1),
										 Vector3<float> {0.1f, 0.6f, 0.1f});
	new Renderer(l_forearm, Vector4<float> {0.1, 0.1, 0.5, 1.0});
	// 4. Left leg
	Transform *l_hip = new Transform(root,
									 Matrix<float>(1,1).Rotate(90, Vector3<float>(1.0f, 0.0f, 0.0f)),
									 Vector3<float> {0.0f, 0.1f, 0.0f});
	Transform *l_thigh = new Transform(l_hip,
									   Matrix<float>(1,1).Rotate(90, Vector3<float>(1.0f, 0.0f, 0.0f)),
									   Vector3<float> {0.2f, 0.6f, 0.2f});
	new Renderer(l_thigh, Vector4<float> {0.5, 0.1, 0.5, 1.0});
	Transform *l_feet = new Transform(l_thigh,
									  Matrix<float>(1,1),
									  Vector3<float> {0.15f, 0.6f, 0.15f});
	new Renderer(l_feet, Vector4<float> {0.5, 0.1, 0.5, 1.0});
	// 4. Right hand
	Transform *r_shoulder = new Transform(spine,
										  Matrix<float>(1,1).Rotate(-90,Vector3<float>(1.0f, 0.0f, 0.0f)),
										  Vector3<float> {0.0f, 0.25f, 0.0f});
	Transform *r_upperarm = new Transform(r_shoulder, Matrix<float>(1, 1).Rotate(-90, Vector3<float>(1.0f, 0.0f, 0.0f)),
										  Vector3<float> {0.15f, 0.6f, 0.15f});
	new Renderer(r_upperarm, Vector4<float> {0.1, 0.1, 0.5, 1.0});

	Transform *r_forearm = new Transform(r_upperarm, Matrix<float>(1, 1),
										 Vector3<float> {0.1f, 0.6f, 0.1f});
	new Renderer(r_forearm, Vector4<float> {0.1, 0.1, 0.5, 1.0});
	// 4. Right leg
	Transform *r_hip = new Transform(root,
									 Matrix<float>(1,1).Rotate(-90, Vector3<float>(1.0f, 0.0f, 0.0f)),
									 Vector3<float> {0.0f, 0.1f, 0.0f});
	Transform *r_thigh = new Transform(r_hip,
									   Matrix<float>(1,1).Rotate(-90, Vector3<float>(1.0f, 0.0f, 0.0f)),
									   Vector3<float> {0.2f, 0.6f, 0.2f});
	new Renderer(r_thigh, Vector4<float> {0.5, 0.1, 0.5, 1.0});
	Transform *r_feet = new Transform(r_thigh, Matrix<float>(1,1), Vector3<float> {0.15f, 0.6f, 0.15f});
	new Renderer(r_feet, Vector4<float> {0.5, 0.1, 0.5, 1.0});

	return platform;
}

int main()
{
	GLRender	glRenderer;
	Transform	*human = createStandingHuman();
	// Collect all components
	auto *components = new std::vector<IComponent*>;
	components->push_back(&glRenderer);
	components->push_back(human);
	// Setup glfw
	GLFWEngine glfwEngine(components);
	if (glfwEngine.init() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	glfwEngine.setInputCallbacks(nullptr, nullptr, nullptr, nullptr);
	// Load glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("GLAD ERROR: Can't load glad");
		return (EXIT_FAILURE);
	}
	// Run loop
	glfwEngine.loop();
	return 0;
}

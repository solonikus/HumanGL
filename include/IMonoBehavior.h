//
// Created by Alteracia on 11/6/21.
// For educational purpose. Use carefully.
//

#ifndef HUMAN_GL_IMONOBEHAVIOR_H
#define HUMAN_GL_IMONOBEHAVIOR_H

class IMonoBehavior
{
public:
	IMonoBehavior() = default;
	virtual ~IMonoBehavior() = default;

	virtual void Start() = 0;
	virtual void Update() = 0;
};

#endif //HUMAN_GL_IMONOBEHAVIOR_H

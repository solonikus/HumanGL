//
// Created by acalandr on 11/5/21.
//

#ifndef HUMAN_GL_ICOMPONENT_H
#define HUMAN_GL_ICOMPONENT_H

# include "IMonoBehavior.h"

class IComponent
{
public:
	IComponent() = default;
	virtual ~IComponent() = default;

	virtual int Start() = 0;
	virtual void Update() = 0;
	virtual void Finish() = 0;
};

#endif //HUMAN_GL_ICOMPONENT_H

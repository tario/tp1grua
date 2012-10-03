#ifndef _DIBUJABLE_H
#define _DIBUJABLE_H

class Dibujable {
public:
	virtual void dibujar(const glm::mat4& m)=0;
	virtual ~Dibujable(){};
};

#endif

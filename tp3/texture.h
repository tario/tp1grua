#ifndef __TEXTURE_H
#define __TEXTURE_H 

class Texture {
	public:
		virtual void load(int slot)=0;
		virtual ~Texture() {
		};
};

#endif

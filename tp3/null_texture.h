#ifndef __NULL_TEXTURE_H
#define __NULL_TEXTURE_H

#include "texture.h"

class NullTexture : public Texture {
	public:
		void load(int slot) {
		}

		static Texture* instance() {
			static NullTexture texture;
			return &texture;
		}
};

#endif

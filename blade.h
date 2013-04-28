#ifndef BLADE_H
#define BLADE_H

#include "thug.h"
#include "knife.h"

class Blade : public Thug {
	private:
		QPixmap *altPic;
		
	public:
		Blade(int pos);
		~Blade();
		void move();
		Knife* throwKnife();
};
		
#endif

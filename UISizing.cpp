#include "MediaQuery.h"

class UISizing
{
public:
	static float playerLocalBoundsCenter() {
		return MediaQuery::screenWidth() * 0.25;
	}
};
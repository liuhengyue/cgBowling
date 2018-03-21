#ifndef BOWL_HPP_
#define BOWL_HPP_

#include "../utils/common.hpp"
#include "../utils/movingObject.hpp"
#include "../utils/texturizableObject.hpp"

class Bowl: public MovingObject, public TexturizableObject
{
	private:
		float radius;

	public:
		Point3df center;//center of mass
		float mass;
		Bowl();
		Bowl(std::vector<std::string> filenames);
		void reset();
		void setRadius(float radius);
		float getRadius() const;
};

#endif /* BOWL_HPP_ */

/*
 * GglEvent.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLEVENT_HPP
#define GGLEVENT_HPP


enum GglEventType {
	DESTROY,
	RESHAPE,
	KEY,
	MOUSE,
	OTHER
};


class GglEvent {
public:
	GglEvent(GglEventType type);
	virtual ~GglEvent();
	virtual GglEventType getType();
private:
	GglEventType type;
};

#endif

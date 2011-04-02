/*
 * GglListener.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLLISTENER_HPP
#define GGLLISTENER_HPP

/**
 * @brief Object that listens to GGL events.
 */
class GglListener {
public:
	GglListener();
	virtual ~GglListener();
	virtual void init() = 0;
	virtual void display() = 0;
	virtual void destroy() = 0;
};

#endif

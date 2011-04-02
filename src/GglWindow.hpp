/*
 * GglWindow.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLWINDOW_HPP
#define GGLWINDOW_HPP
#include "common.h"
#include "GglConfig.hpp"
#include "GglEvent.hpp"
#include "GglListener.hpp"


/** @brief OpenGL window that can be shown. */
class GglWindow {
public:
	GglWindow();
	virtual ~GglWindow();
	virtual void addListener(GglListener *listener);
	virtual void open();
	virtual void close();
	static void run(GglWindow *window);
protected:
	virtual void doOpen() = 0;
	virtual void doClose() = 0;
	virtual GglEvent doGetEvent() = 0;
private:
	bool opened;
	bool closed;
	list<GglListener*> listeners;
};

#endif

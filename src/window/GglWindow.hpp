/*
 * GglWindow.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLWINDOW_HPP
#define GGLWINDOW_HPP
#include "ggl_common.h"
#include "ggl_keys.h"
#include "GglException.hpp"
#include "GglConfig.hpp"
#include "GglEvent.hpp"
#include "GglListener.hpp"


/**
 * @brief Abstract base class for an OpenGL window.
 * 
 * Because GGL is meant to keep things as simple as possible, currently
 * <i>%GglWindow</i> encompasses both the OpenGL drawing area and the native
 * operating system window itself.  Future releases may benefit from a cleaner
 * separation, but right now it seems wise to not over-complicate things.
 * 
 * <i>%GglWindow</i> relies heavily on the <i>Template</i> design pattern.  It
 * describes the base functionality for displaying an OpenGL window, and
 * derived classes provide the concrete functionality for implementing that
 * behavior by overriding <i>hooks</i>.  To make it easy to identify a hook, we
 * follow the convention of naming the method with the prefix <i>do</i>.  For
 * example, the hook for creating a native window is named
 * <i>doCreateWindow</i>.
 * 
 * The process outlined by <i>%GglWindow</i> has four major steps, and there is
 * a hook for each one.  Two of the steps deal with creating objects, and the
 * other two handle cleaning them up.  The objects themselves are the native
 * operating system window and the OpenGL context.  Therefore a derived class
 * needs to implement creating and destroying the native window, as well as
 * creating and destroying an OpenGL context with the native OpenGL
 * interface.
 * 
 * In addition, a derived class should fill in a few more details.  First it
 * needs to implement <i>doGetEvent()</i>, which allows the window to process
 * input from the user.  At the very least, a derived class should accept the
 * event generated when the user closes the window.  Second, it should
 * implement <i>doFlush()</i>, which typically swaps the buffers.
 */
class GglWindow {
public:
    GglWindow();
    virtual ~GglWindow();
    void addListener(GglListener *listener);
    void close();
    static void open(GglWindow *window);
// Getters and setters
    int getWidth() const;
    int getHeight() const;
    void setSize(int width, int height);
    int getX() const;
    int getY() const;
    void setLocation(int x, int y);
    bool isClosed() const;
protected:
    virtual void doActivateContext() = 0;
    virtual void doActivateWindow() = 0;
    virtual void doCreateConnection() throw(GglException) = 0;
    virtual void doCreateWindow() throw(GglException) = 0;
    virtual void doCreateContext() throw(GglException) = 0;
    virtual void doDestroyConnection() = 0;
    virtual void doDestroyWindow() = 0;
    virtual void doDestroyContext() = 0;
    virtual void doFlush() = 0;
    virtual GglEvent doGetEvent() = 0;
private:
    bool created;
    bool destroyed;
    int width;
    int height;
    int x;
    int y;
    bool closed;
    list<GglListener*> listeners;
// Helpers
    void create();
    void createConnection() throw(GglException);
    void createWindow() throw(GglException);
    void createContext() throw(GglException);
    void destroy();
    void fireKeyEvent(GglEvent &event);
    void fireDestroyEvent();
    void fireDisplayEvent();
    void fireInitEvent();
// Constants
    static const int DEFAULT_WIDTH = 512;
    static const int DEFAULT_HEIGHT = 512;
    static const int DEFAULT_X = 25;
    static const int DEFAULT_Y = 25;
};

#endif
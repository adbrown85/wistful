# Start
AC_PREREQ([2.67])
define([MY_NAME], [ggl])
define([MY_MAJOR_VERSION], [0])
define([MY_MINOR_VERSION], [1])
define([MY_VERSION], MY_MAJOR_VERSION.MY_MINOR_VERSION)
define([MY_EMAIL], [adb1413@rit.edu])
AC_INIT(MY_NAME, MY_VERSION, MY_EMAIL)
AC_CONFIG_SRCDIR([src/ggl_common.h])
AC_CONFIG_HEADERS([config.h])

# Checks for programs
AC_PROG_CXX
AC_LANG([C++])
AC_PROG_INSTALL

# Check for OpenGL
error_no_gl() {
    echo "no"
    echo "--------------------"
    echo " No OpenGL!"
    echo "--------------------"
    (exit 1); exit 1;
}
AC_SEARCH_LIBS([glGetString], [GL], , [error_no_gl])
AC_CHECK_HEADER([GL/gl.h], , [error_no_gl])

# Check for GLX
define_have_glx() {
    AC_DEFINE([HAVE_GLX], [1], [Define to 1 if GLX is available.])
}
AC_CHECK_HEADER([GL/glx.h], [define_have_glx])

# Finish
AC_CONFIG_FILES([Makefile])
AC_OUTPUT

# Report
echo \
"--------------------------------------------------------------
 ${PACKAGE_NAME} ${PACKAGE_VERSION}

 prefix      ${prefix}
 CXX         ${CXX}
 CXXFLAGS    ${CXXFLAGS}
 LDFLAGS     ${LDFLAGS}
 LIBS        ${LIBS}
 DEFS        ${DEFS}
 
 Now type 'make' then 'sudo make install'
--------------------------------------------------------------"

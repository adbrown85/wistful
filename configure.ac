# Check for Autoconf
AC_PREREQ([2.67])

# Initialize package information
define([MY_NAME], [ggl])
define([MY_MAJOR_VERSION], [0])
define([MY_MINOR_VERSION], [1])
define([MY_VERSION], MY_MAJOR_VERSION.MY_MINOR_VERSION)
define([MY_EMAIL], [adb1413@rit.edu])
AC_INIT(MY_NAME, MY_VERSION, MY_EMAIL)
AC_SUBST([PACKAGE_MAJOR_VERSION], MY_MAJOR_VERSION)
AC_SUBST([PACKAGE_MINOR_VERSION], MY_MINOR_VERSION)
AC_CONFIG_SRCDIR([src/ggl/ggl_common.h])
AC_CONFIG_HEADERS([config.h])

# Check for system
AC_CANONICAL_HOST

# Check for compilers and languages
AC_PROG_CC
AC_PROG_CXX
AC_LANG([C++])
if test "$host_vendor" = 'apple'; then
    AC_PROG_OBJCXX
fi

# Check for common headers
AC_HEADER_STDBOOL

# Check for tools
AC_PROG_INSTALL
AC_PROG_SED

# Check for OpenGL
error_no_gl() {
    echo "no"
    echo "--------------------"
    echo " No OpenGL!"
    echo "--------------------"
    (exit 1); exit 1;
}
if test "$host_vendor" != 'apple'; then
    AC_SEARCH_LIBS([glGetString], [GL], , [error_no_gl])
    AC_CHECK_HEADER([GL/gl.h], , [error_no_gl])
fi

# Check for backend
if test "$host_vendor" = 'apple'; then
    AC_LANG_PUSH([Objective C++])
    AC_CHECK_HEADER(
        [Cocoa/Cocoa.h],
        [AC_DEFINE([HAVE_COCOA], [1], [Define to 1 if have Cocoa.])])
    LDFLAGS="-framework Cocoa -framework OpenGL"
    CPPFLAGS='-ObjC++'
    AC_LANG_POP()
else
    AC_CHECK_HEADER(
        [GL/glx.h],
        [AC_DEFINE([HAVE_GLX], [1], [Define to 1 if have GLX.])])
fi

# Set up exclusions
if test "$host_vendor" = 'apple'; then
    AC_SUBST([EXCLUSIONS], [ggl/window/glx])
else
    AC_SUBST([EXCLUSIONS], [ggl/window/cocoa])
fi

# Finish
AC_CONFIG_FILES([Makefile])
AC_OUTPUT

# Report
echo \
"--------------------------------------------------------------
 ${PACKAGE_NAME} ${PACKAGE_VERSION}

 prefix      ${prefix}
 CXX         ${CXX}
 CPPFLAGS    ${CPPFLAGS}
 CXXFLAGS    ${CXXFLAGS}
 LDFLAGS     ${LDFLAGS}
 LIBS        ${LIBS}
 DEFS        ${DEFS}
 EXCLUSIONS  ${EXCLUSIONS}
 
 Now type 'make' then 'sudo make install'
--------------------------------------------------------------"

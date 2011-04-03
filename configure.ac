# Start
AC_PREREQ([2.67])
AC_INIT([GGL], [0.1], [adb1413@rit.edu])
AC_CONFIG_SRCDIR([src/common.h])
AC_CONFIG_HEADERS([config.h])

# Checks for programs
AC_PROG_CXX
AC_LANG([C++])
AC_PROG_INSTALL

# Checks for types
AC_HEADER_STDBOOL

# Finish
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
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

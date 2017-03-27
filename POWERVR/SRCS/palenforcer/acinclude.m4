dnl define macro to check valid arguments to compiler
AC_DEFUN(AC_CHECK_COMPILER_ARG,
[AC_CACHE_CHECK(whether $1 accepts $2, $3,
[echo 'void f(){}' > conftest.c
if test -z "`$1 $2 -c conftest.c 2>&1`"; then
  $3=yes
else
  $3=no
fi
rm -f conftest.c conftest.o
])])

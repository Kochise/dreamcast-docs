@echo off

echo *********************************************
echo *  Building Inside OLE 2nd Edition Samples  *
echo *********************************************

cd build
echo Error Log > err
echo ****************************************** >> err
echo. >> err
cd..

cd inole
call makeall
cd..

cd classlib
call makeall
cd..

cd chap01
call makeall
cd..

cd chap02
call makeall
cd..

cd chap03
call makeall
cd..

cd chap04
call makeall
cd..

cd chap05
call makeall
cd..

cd chap06
call makeall
cd..

cd chap07
call makeall
cd..

cd chap08
call makeall
cd..

cd chap09
call makeall
cd..

cd chap10
call makeall
cd..

cd chap11
call makeall
cd..

cd chap12
call makeall
cd..

cd chap13
call makeall
cd..

cd chap14
call makeall
cd..

cd chap15
call makeall
cd..

cd chap16
call makeall
cd..

cd chap17
call makeall
cd..

cd chap18
call makeall
cd..

cd chap19
call makeall
cd..

cd chap20
call makeall
cd..

cd chap21
call makeall
cd..

cd chap22
call makeall
cd..

cd chap23
call makeall
cd..

cd chap24
call makeall
cd..

cd chap25
call makeall
cd..


:Done

echo *************************
echo *    BUILD COMPLETE     *
echo *-----------------------*
echo *   See BUILD\ERR for   *
echo *  complete error log.  *
echo *************************

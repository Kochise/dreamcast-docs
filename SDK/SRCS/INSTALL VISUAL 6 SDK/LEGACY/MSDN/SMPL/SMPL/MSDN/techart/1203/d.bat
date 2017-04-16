copy *.sym c:\win
cd \win
wdeb386 -c:1 -b -s:krnl386.sym -s:sprites.sym win.com

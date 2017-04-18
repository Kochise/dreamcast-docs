*--------------------------------------------------*
PROCEDURE setup
*--------------------------------------------------*
* Sets up a database and two tables for use in transaction examples
*--------------------------------------------------*
CREATE DATABASE mydatabase
SET DATABASE TO mydatabase
CREATE TABLE mytable (myfield I)
CREATE TABLE yourtable (yourfield I)

CLOSE DATABASES ALL
ENDPROC


*--------------------------------------------------*
PROCEDURE firstexample
*--------------------------------------------------*
* Demonstrates committing and rolling back transactions.
*--------------------------------------------------*
USE mytable
?"Record count = " + STR(RECCOUNT("mytable"))

*-- First transaction
BEGIN TRANSACTION
  INSERT INTO mytable (myfield) VALUES (1)
END TRANSACTION
?"Record count = " + STR(RECCOUNT("mytable"))

*-- Second transaction
BEGIN TRANSACTION
  INSERT INTO mytable (myfield) VALUES (2)
ROLLBACK
?"Record count = " + STR(RECCOUNT("mytable"))

CLOSE DATABASES ALL
ENDPROC


*--------------------------------------------------*
PROCEDURE secondexample
*--------------------------------------------------*
* Demonstrates wrapping two updates in a transaction.
*--------------------------------------------------*
USE mytable
CURSORSETPROP("Buffering", 3)
INSERT INTO mytable (myfield) VALUES (3)
INSERT INTO mytable (myfield) VALUES (4)
BEGIN TRANSACTION
IF TABLEUPDATE(1, .F.)
  END TRANSACTION
ELSE
  ROLLBACK
ENDIF

CLOSE DATABASES ALL
ENDPROC


*--------------------------------------------------*
PROCEDURE thirdexample
*--------------------------------------------------*
* Demonstrates updating multiple tables in a transaction.
*--------------------------------------------------*
USE mytable IN 0
USE yourtable IN 0
CURSORSETPROP("Buffering", 3, "mytable")
CURSORSETPROP("Buffering", 3, "yourtable")
INSERT INTO mytable (myfield) VALUES (5)
INSERT INTO yourtable (yourfield) VALUES (6)
BEGIN TRANSACTION
IF TABLEUPDATE(1, .F., "mytable")
  IF TABLEUPDATE(1, .F., "yourtable")
    END TRANSACTION
  ELSE
    ROLLBACK
  ENDIF
ELSE
  ROLLBACK
ENDIF

CLOSE DATABASES ALL
ENDPROC


*--------------------------------------------------*
PROCEDURE fourthexample
*--------------------------------------------------*
* Demonstrates transactions nesting.
*--------------------------------------------------*
USE mytable
?"Transaction level = " + STR(TXNLEVEL()) + 
  "  Record count = " + STR(RECCOUNT("mytable"))

*-- Outer transaction
BEGIN TRANSACTION
?"Transaction level = " + STR(TXNLEVEL()) + 
  "  Record count = " + STR(RECCOUNT("mytable"))

*-- Inner transaction
BEGIN TRANSACTION
INSERT INTO mytable (myfield) VALUES (6)
?"Transaction level = " + STR(TXNLEVEL()) + 
  "  Record count = " + STR(RECCOUNT("mytable"))

*-- Commit inner transaction
END TRANSACTION
?"Transaction level = " + STR(TXNLEVEL()) + 
  "  Record count = " + STR(RECCOUNT("mytable"))

*-- Roll back outer transaction
ROLLBACK
?"Transaction level = " + STR(TXNLEVEL()) + 
  "  Record count = " + STR(RECCOUNT("mytable"))

CLOSE DATABASES ALL
ENDPROC



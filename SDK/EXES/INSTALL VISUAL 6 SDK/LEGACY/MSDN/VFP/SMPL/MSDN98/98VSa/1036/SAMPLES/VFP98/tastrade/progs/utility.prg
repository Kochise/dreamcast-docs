*-- (c) Microsoft Corporation 1995

*-- Fonctions d'utilité générale indépendantes de toutes les classes
*-- pour de meilleures performances et accessibilités

#INCLUDE "INCLUDE\TASTRADE.H"

************************************
FUNCTION IsTag (tcTagName, tcAlias)
  *-- Reçoit un nom d'indicateur et un alias (optionnel) comme
  *-- paramètres et retourne .T. (Vrai) si le nom de l'indicateur existe dans
  *-- l'alias. Si aucun alias est passé, l'alias courant est considéré.
  LOCAL llIsTag, ;
        lcTagFound

  IF PARAMETERS() < 2
    tcAlias = ALIAS()
  ENDIF
  
  IF EMPTY(tcAlias)
    RETURN .F.
  ENDIF

  llIsTag = .F.
  tcTagName = UPPER(ALLTRIM(tcTagName))

  lnTagNum = 1
  lcTagFound = TAG(lnTagNum, tcAlias)
  DO WHILE !EMPTY(lcTagFound)
    IF UPPER(ALLTRIM(lcTagFound)) == tcTagName
      llIsTag = .T.
      EXIT
    ENDIF
    lnTagNum = lnTagNum + 1
    lcTagFound = TAG(lnTagNum, tcAlias)
  ENDDO

  RETURN llIsTag
ENDFUNC

FUNCTION NotYet()
  *-- Utilisé durant la construction des Négociants Tasmaniens pour indiquer
  *-- les parties de l'application pas encore terminées.
  =MESSAGEBOX(NOTYET_LOC, MB_ICONINFORMATION)
  RETURN
ENDFUNC

FUNCTION FileSize(tcFileName)
  *-- Retourne la taille d'un fichier. SET COMPATIBLE doit être définie à ON
  *-- pour que FSIZE() retourne la taille d'un fichier. Sinon,
  *-- la taille d'un champ est retournée.
  LOCAL lcSetCompatible, lnFileSize

  lcSetCompatible = SET('COMPATIBLE')
  SET COMPATIBLE ON
  lnFileSize = FSIZE(tcFileName)
  SET COMPATIBLE &lcSetCompatible
  RETURN lnFileSize
ENDFUNC

FUNCTION FormIsObject()
  *-- Retourne .T. (Vrai) si le formulaire actif est de type "O" et
  *-- sa classe de base est "Form".
  RETURN (TYPE("_screen.activeform") == "O" AND ;
          UPPER(_screen.ActiveForm.BaseClass) = "FORM")
ENDFUNC

FUNCTION ToolBarEnabled
  *- renvoyer la valeur d'un objet de barre d'outils
  PARAMETER oObject
  LOCAL oToolObj
  oToolObj = "oApp.oToolBar." + oobject + ".enabled"
  IF TYPE(oToolObj) # "L"
    RETURN .F. 
  ELSE
    RETURN EVAL(oToolObj)
  ENDIF
ENDFUNC

FUNCTION OnShutdown()
  *-- Message personnalisé appelé par la commande ON SHUTDOWN pour indiquer
  *-- que l'utilisateur doit quitter les Négociants Tasmaniens avant de quitter FoxPro.
  =MESSAGEBOX(CANNOTQUIT_LOC, ;
              MB_ICONEXCLAMATION, ;
              TASTRADE_LOC)
ENDFUNC
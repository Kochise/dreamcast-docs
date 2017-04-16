*--------------------------------------------------------------------------
* File name: Granted.prg
* Purpose  : Checks if user has specified rights for a certain item
* Parm     : <expC> - item Id, <expC> - name of the right (ACCESS,READ etc.)
* Returns  : .t. or .f. 
* Called by: Various
*--------------------------------------------------------------------------
PARAMETER inItem,inRight
* Since one way to use this function is to call it in the evaluation of
* the "visible" property in a form, we MUST guarantee that the variable
* "pSupervisor" exists even if we're only going to edit the form.
IF TYPE ( "pSupervisor" ) = "U"
   pSupervisor = .F.
ENDIF
IF pSupervisor
	RETURN .T.
ENDIF	
IF NOT USED("UserRght")		&& Testing
	RETURN .T.
ENDIF	
inItem  = padr(upper(inItem),20," ")
inRight = upper(inRight)
RETURN SEEK(inItem+inRight,'UserRght')
*--------------------------------------------------------------------------

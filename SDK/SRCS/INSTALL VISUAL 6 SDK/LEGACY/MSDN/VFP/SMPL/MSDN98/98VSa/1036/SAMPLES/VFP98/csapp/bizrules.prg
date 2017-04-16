
#DEFINE ERR_BADCOUNTRY_LOC		"La valeur de 'Country' est incorrecte."
#DEFINE ERR_BADHIREDATE_LOC		"La valeur de 'Hire_date' doit être supérieure à  "
#DEFINE ERR_BADBIRTHDATE_LOC	"La valeur de 'Birth_date' doit être supérieure à "
#DEFINE ERR_BADTITLE_LOC		"La valeur de 'Title' est incorrecte."
#DEFINE ERR_BADSALARY1_LOC		"La valeur de 'Salary' pour le titre de l'emploi '"
#DEFINE ERR_BADSALARY2_LOC		"' doit être comprise entre  "
#DEFINE ERR_BADSALARY3_LOC		"$"
#DEFINE ERR_BADSALARY4_LOC		" et $"

DEFINE CLASS salaryrule AS Custom OLEPUBLIC

	nSaveArea = 1
	
	PROCEDURE Init
		* BUGBUG needs error checking
		IF !USED('bizrules')
			USE bizrules IN 0 AGAIN
		ENDIF
	ENDPROC
	
	PROCEDURE Destroy
		USE IN bizrules
	ENDPROC

	PROCEDURE validate
		PARAMETERS lcTitle, lnSalary, ldBirth, ldHire, lcCountry
		LOCAL lcError, lcStr
		
		THIS.nSaveArea = SELECT()	
		SELECT bizrules

		lcError = ""

		* enforces a common set of bussiness rules
		* returns a list of error messages, one for every rule that failed

		* bussiness rule for title and for salary range per title
		LOCATE FOR lcTitle = ALLTRIM(title)
		IF EOF()
			THIS.ErrorMessage(ERR_BADTITLE_LOC, @lcError)
		ELSE
			IF !BETWEEN(lnSalary, min_salary, max_salary)
				lcStr = ERR_BADSALARY1_LOC + ALLTRIM(title) + ERR_BADSALARY2_LOC + ;
						ERR_BADSALARY3_LOC + ALLTRIM(STR(min_salary)) + ERR_BADSALARY4_LOC + ALLTRIM(STR(max_salary))
				THIS.ErrorMessage(lcStr, @lcError)
			ENDIF
		ENDIF

		* bussiness rule for dates
		GO TOP
		IF ldBirth < birth_date
			lcStr = ERR_BADBIRTHDATE_LOC + ALLTRIM(DTOC(birth_date))
			THIS.ErrorMessage(lcStr, @lcError)
		ENDIF

		GO TOP		&& just for consistence
		IF ldHire < hire_date
			lcStr = ERR_BADHIREDATE_LOC + ALLTRIM(DTOC(hire_date))
			THIS.ErrorMessage(lcStr, @lcError)
		ENDIF

		* business rule for country
		LOCATE FOR lcCountry = ALLTRIM(country)
		IF EOF()
			THIS.ErrorMessage(ERR_BADCOUNTRY_LOC, @lcError)
		ENDIF

		SELECT (THIS.nSaveArea)
	
		* wait window lcError
		RETURN lcError
	ENDPROC


	PROCEDURE ErrorMessage
		PARAMETERS lcMessage, lcError
		* add message to error list
		lcError = lcError + IIF(EMPTY(lcError), lcMessage, chr(13) + lcMessage)
		SELECT (THIS.nSaveArea)
	ENDPROC

ENDDEFINE

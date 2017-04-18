Attribute VB_Name = "modDHTML"
'PutProperty: Stocke des informations dans un cookie en appelant cette
'             fonction.
'             Entrées: Propriété nommée
'             et valeur de la propriété à stocker.
'
'             Entrées facultatives:
'             expires : date qui définit la durée de vie valide
'                       de la propriété. Une fois la date d'expiration
'                       atteinte, n'est plus stockée ni restituée.

Public Sub PutProperty(objDocument As HTMLDocument, strName As String, vntValue As Variant, Optional Expires As Date)

     objDocument.cookie = strName & "=" & CStr(vntValue) & _
        IIf(CLng(Expires) = 0, "", "; expires=" & Format(CStr(Expires), "ddd, dd-mmm-yy hh:mm:ss") & " GMT") ' & _

End Sub

'GetProperty: Extrait la valeur d'une propriété en appelant cette
'             fonction. L'entrée est la propriété nommée
'             et la valeur de retour de la fonction est la valeur actuelle
'             de la propriété. Si la propriété est absente ou périmée,
'             la valeur de retour est une chaîne vide.
'
Public Function GetProperty(objDocument As HTMLDocument, strName As String) As Variant
    Dim aryCookies() As String
    Dim strCookie As Variant
    On Local Error GoTo NextCookie

    ' Fractionne l'objet cookie du document en tableau de cookies.
    aryCookies = Split(objDocument.cookie, ";")
    For Each strCookie In aryCookies
        If Trim(VBA.Left(strCookie, InStr(strCookie, "=") - 1)) = Trim(strName) Then
            GetProperty = Trim(Mid(strCookie, InStr(strCookie, "=") + 1))
            Exit Function
        End If
NextCookie:
        Err = 0
    Next strCookie
End Function



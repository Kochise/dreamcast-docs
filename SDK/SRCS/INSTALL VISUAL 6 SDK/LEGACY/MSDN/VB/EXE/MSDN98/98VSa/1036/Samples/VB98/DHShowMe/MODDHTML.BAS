Attribute VB_Name = "modDHTML"
' Le code suivant vous permet d'utiliser le jeu de propriétés
' du navigateur Web pour conserver des informations entre
' différentes pages HTML.
Public objWebBrowser As WebBrowser

' PutProperty: Stocke des informations dans le jeu de propriétés en appelant cette
'              fonction.  Les paramètres d'entrée sont la propriété nommée
'              et la valeur qu'elle doit stocker.
'
Public Sub PutProperty(strName As String, vntValue As Variant)
    
    ' Vérifier s'il existe une instance du navigateur.
    If objWebBrowser Is Nothing Then Set objWebBrowser = New WebBrowser
    
    ' Appeler la méthode PutProperty du navigateur pour stocker la valeur.
    objWebBrowser.PutProperty strName, vntValue

End Sub

' GetProperty: Extraire des informations du jeu de propriétés en appelant cette
'              fonction.  Le paramètre d'entrée est la propriété nommée
'              et la valeur de retour de la fonction est la valeur actuelle
'              de la propriété.
'
Public Function GetProperty(strName As String) As Variant
    
    ' Vérifier s'il existe une instance du navigateur.
    If objWebBrowser Is Nothing Then Set objWebBrowser = New WebBrowser
    
    ' Appeler la méthode GetProperty du navigateur pour lire la valeur.
    GetProperty = objWebBrowser.GetProperty(strName)

End Function

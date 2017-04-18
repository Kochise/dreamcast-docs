Attribute VB_Name = "modChart"
' ------------------------------------------------------------------------
'      Copyright © 1997 Microsoft Corporation.  Tous droits réservés.
'
' Vous disposez d'un droit accordé à titre gratuit d'utiliser, modifier, reproduire et distribuer,
' de quelque manière que ce soit, des extraits de Fichiers d'Applications Exemples. Vous reconnaissez être informé et vous  acceptez que Microsoft exclut toute garantie, obligation ou responsabilité relatives à
' l'exercice du droit gratuit qui vous est accordé ci-dessus.

' ------------------------------------------------------------------------

Option Explicit
' REMARQUE IMPORTANTE: Si vous utilisez Windows NT 4.0, vous devez installer
' Service Pack 3.

' Public shtGas As WorkSheet
Public appGas As Excel.Application
Public shtGas As Workbook
Public rngGas As Range

Public ExcelWasNotRunning As Boolean
Public intRows              ' Nombre de lignes. Utilisez cette variable pour définir le nombre de lignes dans un tableau.
Public arrMPG()             ' Kilomètres par litre
Public arrGall()            ' Litres par réservoir
Public arrMiles()           ' Kilomètres par réservoir
Public arrPrices()          ' Prix des réservoirs
Public arrPerTank()         ' Prix par réservoir
Public arrMPGandTank()      ' Km/L et litres par réservoir
Public arrMPGandMiles()     ' Km/L et Km par réservoir

Public Sub SetupChart()
Attribute SetupChart.VB_Description = "Begins to configure chart by first invoking the GetObject method on an Excel worksheet. "
    ' IMPORTANT : Si Excel 97 n'est pas installé sur votre ordinateur,
    ' vous devez modifier la référence de la bibliothèque d'objet Excel 95.
    ' Puis, dans la section de Déclarations ci-dessus, remplacez la
    ' déclaration de la variable "shtGas as Workbook" par "shtGas As Worksheet"
    
    On Error Resume Next 'Ignore les erreurs
    
    Set appGas = GetObject(, "Excel.Application") 'recherche une instance d'Excel
    If Err.Number <> 0 Then 'Si Excel n'est pas chargé
        Set appGas = CreateObject("Excel.Application") 'exécutez-le
        ExcelWasNotRunning = True
    End If
    Err.Clear   ' Efface l'objet Err en cas d'erreur.
    
    On Error GoTo 0 'Poursuit le traitement normal des erreurs
    
    Set shtGas = appGas.Workbooks.Open(App.Path & "\gas.xls")

    ' Définit la variable de type range avec la propriété CurrentRegion de la colonne A.
    Set rngGas = shtGas.Worksheets(1).Range("A1").CurrentRegion
    
    ' À l'aide de l'objet range, vous pouvez à présent obtenir le nombre de lignes dans la
    ' feuille de calcul. Soustrayez 1 car la première ligne est un en-tête, et non
    ' une donnée valide.
    intRows = rngGas.Rows.Count - 1
        
    ' Configure le graphique.
    With frmChart.chtSample
        .Title = shtGas.Name
        .RowCount = intRows ' Définit le nombre de lignes. Cette opération doit être effectuée avant
                            '   de définir les données du graphique.
        .ColumnCount = 2    ' Deux colonnes. La première affiche les kilomètres par
                            '   litre, la deuxième les litres consommés.
        .ColumnLabelCount = 2
        .AllowDynamicRotation = True
        .AllowDithering = True  ' Définit cette propriété sur False si votre moniteur couleur
                                '   utilise seulement 8 bits.
                                
        ' Définit la légende de la carte dans le coin supérieur droit, puis
        '    les coordonnées de la légende.
        .Legend.Location.LocationType = VtChLocationTypeTop
        '.Legend.Location.LocationType = VtChLocationTypeTopRight
        .Legend.VtFont.Style = VtFontStyleBold
        .Legend.Location.Rect.Max.Set 7560, 5132
        .Legend.Location.Rect.Min.Set 3004, 4864
    End With
End Sub

Public Sub PopOneArray(thisarray As Variant, col As String)
    ' Cette procédure permet simplement de remplir les tableaux.
    Dim i As Integer
    ReDim thisarray(1 To intRows, 1 To 2)
    For i = 1 To intRows
        ' Récupère les valeurs Date.
        thisarray(i, 1) = CStr(rngGas.Range("A" & i + 1).Value)
        ' Récupère les valeurs.
        thisarray(i, 2) = Format(rngGas.Range(col & i + 1).Value, "##.##")
        frmChart.prgArrays.Value = i
    Next i

End Sub

Public Sub PopTwoArray(ByRef thisarray, col1 As String, col2 As String)
    ' Remplit les tableaux avec deux séries. Le troisième élément est utilisé pour récupérer
    '   les valeurs date.
    Dim i As Integer
    ReDim thisarray(1 To intRows, 1 To 3)
    For i = 1 To intRows
        ' Récupère les valeurs Date.
        thisarray(i, 1) = CStr(rngGas.Range("A" & i + 1).Value)
        ' Récupère les valeurs.
        thisarray(i, 2) = Format(rngGas.Range(col1 & i + 1).Value, "##.##")
        thisarray(i, 3) = Format(rngGas.Range(col2 & i + 1).Value, "##.##")
        frmChart.prgArrays.Value = i
    Next i
End Sub

Public Sub PopThreeArray(ByRef thisarray, col1 As String, col2 As String, col3 As String)
    Dim i As Integer
    ReDim thisarray(1 To intRows, 1 To 4)
    For i = 1 To intRows
        ' Récupère les valeurs Date.
        thisarray(i, 1) = CStr(rngGas.Range("A" & i + 1).Value)
        ' Récupère les valeurs.
        thisarray(i, 2) = Format(rngGas.Range(col1 & i + 1).Value, "##.##")
        thisarray(i, 3) = Format(rngGas.Range(col2 & i + 1).Value, "##.##")
        thisarray(i, 4) = Format(rngGas.Range(col3 & i + 1).Value, "##.##")
        frmChart.prgArrays.Value = i
    Next i
End Sub

Public Sub Chart(ByRef arrayName(), chtTitle As String, colLabel As String)
Attribute Chart.VB_Description = "This procedure takes an array as an argument, and sets the ChartData property to the array, which creates a chart."
    ' Cette procédure prend chaque tableau comme argument, et définit la
    '   propriété ChartData pour le tableau courant, afin de créer un graphique.
    With frmChart.chtSample
        .ChartData = arrayName()
        .Title = chtTitle
        .ColumnCount = 1
        .ColumnLabelCount = 1
        .Column = 1
        .ColumnLabel = colLabel
        .Refresh
    End With
End Sub

Public Sub twoColChart()

    ' Utilise le tableau arrMPGandTank pour créer un graphique à deux colonnes
    With frmChart.chtSample
        .ChartData = arrMPGandTank
        .Title = "Kilomètres par litre"
        .ColumnLabelCount = 2
        .ColumnCount = 2
        .Column = 1
        .ColumnLabel = "Litres"
        .Column = 2
        .ColumnLabel = "Km/L"
        .Refresh
    End With
End Sub

Public Sub threeColChart()
    ' Utilise le tableau MPGandMiles pour créer un graphique à trois colonnes. Définit la
    '   propriété ChartData pour le tableau, puis définit le titre et les étiquettes
    '    de la colonne.
    
    With frmChart.chtSample
        .ChartData = arrMPGandMiles
        .Title = "Coûts"
        .ColumnCount = 3
        .ColumnLabelCount = 3
        .Column = 1
        .ColumnLabel = "Prix par litre"
        .Column = 2
        .ColumnLabel = "Litres"
        .Column = 3
        .ColumnLabel = "Prix * Litres"
        .Refresh
    End With
End Sub

Public Sub Cleanup()
    ' Invoque cette fonction avant la fermeture de l'app.
    ' Définit toutes les variables globales sur nothing.

    
    shtGas.Close 'Ferme la feuille de travail
    
    Set shtGas = Nothing
    Set rngGas = Nothing
    
    ' Si cette instance de Microsoft Excel n'était pas en cours d'exécution quand vous
    ' avez démarré, fermez-la à l'aide de la méthode Quitter de l'application.
    ' Veuillez noter que lorsque vous essayez de quitter Microsoft Excel, la
    ' barre de titre clignote et un message s'affiche vous demandant si vous
    ' souhaitez sauvegarder les fichiers ouverts.
    If ExcelWasNotRunning = True Then
        appGas.Quit
    End If
    Set appGas = Nothing
End Sub


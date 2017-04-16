Attribute VB_Name = "modGeofacts"
Option Explicit
Public appWorld As Excel.Application
Public wbWorld As Excel.Workbook
'
' Public shtWorld As Excel.Worksheet

Sub Setup()
    ' IMPORTANT: Si Excel 97 n'est pas installé sur votre machine,
    ' vous devez changer la référence vers la bibliothèque d'objet Excel 95.
    ' Ensuite, dans la section Declarations ci-dessus, changez la 
    ' déclaration de variable de "wbWorld as Workbook" en "shtWorld As Worksheet".
    ' Ensuite, changez toutes les références de "wbWorld" en "shtWorld".

    On Error Resume Next 'ignore errors
    Set appWorld = GetObject(, "Excel.Application") 'rechercher une copie d'Excel en cours 
    If Err.Number <> 0 Then 'Si Excel n'est pas en cours
        Set appWorld = CreateObject("Excel.Application") 'le lancer
    End If
    Err.Clear   ' Effacer l'objet Err en cas d'erreur.
    
    On Error GoTo 0 'Reprendre le traitement d'erreur normal

    Set wbWorld = appWorld.Workbooks.Open(App.Path & "\world.xls")

End Sub

' Définit les objets à Nothing.
Sub CleanUp()
    ' Ceci doit forcer un déchargement de Microsoft Excel,
    ' à conditon qu'aucune autre application ou aucun autre utilisateur ne l'aient chargé.
    Set appWorld = Nothing
    Set wbWorld = Nothing
End Sub

' Remplit la liste déroulante des continents avec les noms
' des feuilles du classeur.
Sub FillContinentsList()
    Dim shtContinent As Excel.Worksheet
    
    ' Parcourt la collection de feuilles et ajoute
    ' le nom de chaque feuille dans la liste déroulante.
    For Each shtContinent In wbWorld.Sheets
        frmGeoFacts.cmbContinents.AddItem shtContinent.Name
    Next
    ' Sélectionne le premier élément et l'affiche dans la liste déroulante.
    frmGeoFacts.cmbContinents.Text = frmGeoFacts.cmbContinents.List(0)

    Set shtContinent = Nothing
End Sub

' Remplit la liste déroulante des continents avec les noms
' des caractéristiques correspondant à un continent donné.
Sub FillFeaturesList()
    Dim shtContinent As Excel.Worksheet
    Dim rngFeatureList As Excel.Range
    Dim intFirstBlankCell As Integer
    Dim loop1 As Integer

    ' Masque la liste de l'ancien classement.
    frmGeoFacts.lstTopRanking.Visible = False
    
    ' Obtient la feuille avec le nom du continent sélectionné dans la liste déroulante des continents.
    Set shtContinent = wbWorld.Sheets(frmGeoFacts.cmbContinents.Text)
    ' Affecte la première ligne de cette feuille à un objet.
    Set rngFeatureList = shtContinent.Rows(1)
    
    ' Vérifie si ce n'est pas une liste vide.
    If (rngFeatureList.Cells(1, 1) = "") Then
        intFirstBlankCell = 0
    Else
        ' Recherche la première cellule vierge de la ligne.
        intFirstBlankCell = rngFeatureList.Find("").Column
    End If
    
    ' Vide le contenu précédent de la liste déroulante des caractéristiques.
    frmGeoFacts.cmbFeatures.Clear
            
    ' Ajoute les éléments à la liste déroulante des caractéristiques.
    For loop1 = 1 To intFirstBlankCell
        frmGeoFacts.cmbFeatures.AddItem rngFeatureList.Cells(1, loop1)
    Next
    
    ' Sélectionne le premier élément et l'affiche dans la liste déroulante.
    frmGeoFacts.cmbFeatures.Text = frmGeoFacts.cmbFeatures.List(0)

    ' Nettoie.
    Set shtContinent = Nothing
    Set rngFeatureList = Nothing
End Sub

' Remplit la liste des éléments de la caractéristique spécifiée.
Sub FillTopRankingList()
    Dim shtContinent As Excel.Worksheet
    Dim intColumOfFeature As Integer
    Dim rngRankedList As Excel.Range
    Dim intFirstBlankCell As Integer
    Dim loop1 As Integer
    
    ' Obtient la feuille avec le nom du continent sélectionné dans la liste déroulante des continents.
    Set shtContinent = wbWorld.Sheets(frmGeoFacts.cmbContinents.Text)
    
    ' Vide le contenu précédent de la liste de classement.
    frmGeoFacts.lstTopRanking.Clear
    
    ' S'il n'y a aucune sélection de caractéristique, ne rien faire.
    If (frmGeoFacts.cmbFeatures <> "") Then
        
        ' Recherche la colonne de la caractéristique sélectionnée dans la première
        ' ligne de la feuille de calcul.
        intColumOfFeature = shtContinent.Rows(1).Find(frmGeoFacts.cmbFeatures.Text).Column
        
        ' Affecte la colonne à un objet.
         Set rngRankedList = shtContinent.Columns(intColumOfFeature)
        
        ' Vérifie si la liste est vide
        If (rngRankedList.Cells(1, 1) = "") Then
            intFirstBlankCell = 0
        Else
            ' Recherche la première cellule vide de la ligne.
            intFirstBlankCell = rngRankedList.Find("").Row
        End If
                
        ' Ajoute dans la liste déroulante les éléments de la caractéristique.
        For loop1 = 2 To intFirstBlankCell
            frmGeoFacts.lstTopRanking.AddItem rngRankedList.Cells(loop1, 1)
        Next
    
        ' Affiche la liste du nouveau classement.
        frmGeoFacts.lstTopRanking.Visible = True
    
    End If
    
    ' Nettoie.
    Set shtContinent = Nothing
    Set rngRankedList = Nothing
End Sub

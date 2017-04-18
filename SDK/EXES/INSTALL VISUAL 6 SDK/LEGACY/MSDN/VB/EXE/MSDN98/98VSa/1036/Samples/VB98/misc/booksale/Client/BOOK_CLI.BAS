Attribute VB_Name = "ClientMain"
Option Explicit

Public gobjServer As Object    ' Référence d'objet à l'objet d'entreprise du serveur Vente de livres.
Public goStatusPanel As Panel  ' Référence d'objet au Panel1 du contrôle StatusBar.

Public gstrPubRevenue As String
Public gstrAuthorRoyalty As String
Public gDBName As String           ' Maintient une chaîne se référant à la base de données globale.

Public gSn As ADODB.Recordset         ' Objet ADO Recordset
Public gCN As ADODB.Connection        ' Objet Connection ADO global

Public rsTitles As ADODB.Recordset
Public rsAuthors As ADODB.Recordset

Sub GetAuthors()
   On Error GoTo GetAuthorsError
   Set rsAuthors = gobjServer.GetAuthors
   Do While Not rsAuthors.EOF
      frmRevenue.cboAuthors.AddItem rsAuthors.Fields(0).Value
      rsAuthors.MoveNext
   Loop
   frmRevenue.cboAuthors.ListIndex = 0
  Exit Sub
GetAuthorsError:
   If IsObject(rsAuthors) Then
      rsAuthors.Close
    Else
      ' gérer les autres erreurs ici
   End If
   Exit Sub
End Sub

Sub GetTitles(strAuthor As String)
   Dim strSQL As String
   Dim rsTitles As ADODB.Recordset
   On Error GoTo GetTitlesError
   
   strSQL = "SELECT Titles.Title " & _
         "FROM Titles INNER JOIN (Authors INNER JOIN [Title Author] ON Authors.Au_ID = [Title Author].Au_ID) ON Titles.ISBN = [Title Author].ISBN " & _
         "WHERE ((Authors.Author=" & Chr$(34) & strAuthor & Chr$(34) & "));"

   Set rsTitles = gobjServer.GetTitles(strSQL)
   frmRevenue.cboBooks.Clear

   Do While Not rsTitles.EOF
      frmRevenue.cboBooks.AddItem rsTitles!Title
      rsTitles.MoveNext
   Loop

   rsTitles.Close
   frmRevenue.cboBooks.ListIndex = 0
Exit Sub
GetTitlesError:
  If Not rsTitles Is Nothing Then rsTitles.Close
  Exit Sub
End Sub


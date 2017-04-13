Attribute VB_Name = "basNEWCONTA"
'Global variables (For NewConta.FRM use ONLY!)
Global NewContaUserCanceled%
Global hNewContaConnection&
Global NewContaName$
Global NewContaTag&

Function NewContainer%(hConnect&, NewName$, NewTag&)
    hNewContaConnection& = hConnect&
    
    frmNewContainer.Show MODAL
    
    If Not NewContaUserCanceled% Then
        NewName$ = NewContaName$
        NewTag& = NewContaTag&
    End If

    NewContainer% = Not NewContaUserCanceled%
End Function


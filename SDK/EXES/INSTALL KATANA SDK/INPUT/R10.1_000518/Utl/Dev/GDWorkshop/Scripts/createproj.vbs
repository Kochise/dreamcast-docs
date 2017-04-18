
Public st,  MyDir, Quote, Input
Public FileSystemObj, ScriptFile
Public MyFileList()
Public MyTrackList()

OpenDoor
CreateScript
LoadScript ("D:\example.scr")
EmulationWarnings (0)
CloseDoor

Sub CreateScript
	Dim     v, DrvLetter, fso, f, Myfiles, Path
	Dim	TrackFolder, NoOfFiles
	Dim	BadFolder

	DrvLetter = ShowDriveList

	Quote = String (1 , 34)

	v = MsgBox (DrvLetter , 65, "Removable Drive Letter Is :-")
	Path = DrvLetter & ":\YourTest"
	Input = InputBox("Enter Project Directory","",Path)

	BadFolder = ReportFolderStatus(Cstr(Input))
	if BadFolder = 0 Then
		v = MsgBox (Cstr(Input) , 65, "Can't find you folder")
	Else
		TrackCount = ShowFolderList(Cstr(Input))

		Set FileSystemObj = CreateObject("Scripting.FileSystemObject")
		Set ScriptFile = FileSystemObj.CreateTextFile ("D:\example.scr", True)

		CreateFiles
		WriteHeader
		for Track = 0 to TrackCount - 1
			if Track = 0 or Track = 2 Then
				if Track = 0 Then
					ScriptFile.WriteLine ("    RecordArea SINGLE")
					ScriptFile.WriteLine ("    FileNameType ISO9660L2")
					ScriptFile.WriteLine ("    SystemArea " & Quote & "\IP0000.BIN" & Quote)
				Else
					ScriptFile.WriteLine ("    EndRecordArea")
					ScriptFile.WriteLine ("    RecordArea HIGH")
					ScriptFile.WriteLine ("    FileNameType ISO9660L2")
					ScriptFile.WriteLine ("    SystemArea " & Quote & "\IP.BIN" & Quote)
				End If
			End If
			if Track = 0 or Track = 2 or Track = 4 Then
				ScriptFile.WriteLine ("        Track MODE1")
			Else
				ScriptFile.WriteLine ("        Track CDDA")
			End If
			if Track = 0 or Track = 2 Then
				if Track = 0 Then
					WritePVD1
				Else
					WritePVD2
				End If
			End If
			TrackFolder = Cstr(Input) & "\" & MyTrackList(Track)
			NoOfFiles = ShowFileList(TrackFolder)

			for i = 0 to NoOfFiles - 1
				if Track = 0 or Track = 2 or Track = 4 Then
					ScriptFile.WriteLine ("            File " & Ucase (MyFileList (i)))
					ScriptFile.WriteLine ("                FileSource "  & Quote & Cstr(Input) & "\" & MyTrackList(Track) & "\" & MyFileList (i) & Quote)
					ScriptFile.WriteLine ("                EndFileSource")
					ScriptFile.WriteLine ("            EndFile")

				Else
					ScriptFile.WriteLine ("            FileSource " & Quote & Cstr(Input) & "\" & MyTrackList(Track) & "\" & MyFileList (i) & Quote)
					ScriptFile.WriteLine ("            EndFileSource")
				End If
			next
			ScriptFile.WriteLine ("        EndTrack")
		next
		ScriptFile.WriteLine ("    EndRecordArea")
		CloseScript
	End If
	ScriptFile.Close
End Sub

Function ShowDriveList
  Const Unknown = 0 , Removable = 1, Fixed = 2, Remote = 3, CDROM = 4, RAMDisk = 5
  Dim   fso, d, dc
  Set   fso = CreateObject("Scripting.FileSystemObject")
  Set   dc = fso.Drives

  For Each d in dc
    If d.DriveLetter > "B" Then
    	If d.DriveType = Removable Then
      	  ShowDriveList = d.DriveLetter
    	End If
    End If
  Next
End Function

Function ShowFolderList(fldr)
  Dim fso, f, f1, sf
  Set fso = CreateObject("Scripting.FileSystemObject")
  Set f = fso.GetFolder(fldr)
  Set sf = f.SubFolders

  ReDim Preserve MyTrackList(sf.Count)
  Dim   filecount

  trackcount = 0
  For Each f1 in sf
    MyTrackList(trackcount) = f1.Name
    trackcount = trackcount + 1
  Next

  ShowFolderList = trackcount
End Function

Function ReportFolderStatus(fldr)
  Dim fso
  Set fso = CreateObject("Scripting.FileSystemObject")

  If (fso.FolderExists(fldr)) Then
    ReportFolderStatus = 1
  Else
    ReportFolderStatus = 0
  End If
End Function

Function ShowFileList(folderspec)
  Dim fso, f, f1, fc, filecount
  Set fso = CreateObject("Scripting.FileSystemObject")
  Set f = fso.GetFolder(folderspec)
  Set fc = f.Files

  filecount = 0
  ReDim Preserve MyFilelist(fc.Count)
  For Each f1 in fc
    MyFileList (filecount) = f1.name
    filecount = filecount + 1
  Next
  ShowFileList = filecount
End Function

Sub WriteHeader
	ScriptFile.WriteLine ("Gd "  & Quote & "SCR1" & Quote)
End Sub

Sub WritePVD1
	ScriptFile.WriteLine ("            PrimaryVolume")
	ScriptFile.WriteLine ("                VolumeIdentifier                " & Quote & "EXAMPLE" & Quote)
	ScriptFile.WriteLine ("                    CopyrightFileIdentifier     " & Quote & "COPYRIGH.TXT" & Quote)
        ScriptFile.WriteLine ("                    AbstractFileIdentifier      " & Quote & "ABSTRACT.TXT" & Quote)
        ScriptFile.WriteLine ("                    BibliographicFileIdentifier " & Quote & "BIBLIOGR.TXT" & Quote)
        ScriptFile.WriteLine ("                EndPrimaryVolume")
      	ScriptFile.WriteLine ("            EndVolume")
End Sub

Sub WritePVD2
	ScriptFile.WriteLine ("            PrimaryVolume")
	ScriptFile.WriteLine ("                VolumeIdentifier                " & Quote & "EXAMPLE" & Quote)
        ScriptFile.WriteLine ("                EndPrimaryVolume")
      	ScriptFile.WriteLine ("            EndVolume")
End Sub


Sub CloseScript
	ScriptFile.WriteLine ("EndGd " & Quote & "EXAMPLE" & Quote)
End Sub

Sub CreateFiles
	Dim	Filesys , TextFile
	Set 	Filesys = CreateObject("Scripting.FileSystemObject")
	Set 	TextFile = FileSystemObj.CreateTextFile (Input & "\Track1\COPYRIGH.TXT" , True)

	TextFile.WriteLine ("EXAMPLE FILE COPYRIGHT FILE")
	TextFile.Close

	Set TextFile = FileSystemObj.CreateTextFile (Input & "\Track1\ABSTRACT.TXT" , True)
	TextFile.WriteLine ("EXAMPLE FILE ABSTRACT FILE")
	TextFile.Close

	Set TextFile = FileSystemObj.CreateTextFile (Input & "\Track1\BIBLIOGR.TXT" , True)
	TextFile.WriteLine ("EXAMPLE FILE BIBLIOGR FILE")
	TextFile.Close
End Sub

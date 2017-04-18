			Exemple VBMAIL

L'exemple VBMail utilise les contrôles MAPISessions et MAPIMessages en conjonction avec une application de messagerie sous-jacente, comme Microsoft Exchange ou Microsoft Outlook, pour afficher et composer les messages. L'exemple utilise également la bibliothèque ActiveX Data Objects Recordset 2.0 pour créer un jeu d'enregistrements autonome. Ce jeu d'enregistrements est rempli avec les messages non lus fournis par le contrôle MAPIMessages. 

Fichiers		Description

frmLogOn.frm		Connexion et lecture des messages non lus.
frmRead.frm		Feuille utilisée pour lire un message.
prjMapi.vbp		Fichier de projet.

Exécution
Le contrôle DataGrid est utilisé pour afficher les messages non lus. Un clic sur un message en permet la lecture. Les autres fonctions sont l'affichage du carnet d'adresses du système de messagerie sous-jacent et la composition d'un nouveau message.

À partir de la lecture d'un message, vous pouvez répondre, répondre à tous ou transférer le message.



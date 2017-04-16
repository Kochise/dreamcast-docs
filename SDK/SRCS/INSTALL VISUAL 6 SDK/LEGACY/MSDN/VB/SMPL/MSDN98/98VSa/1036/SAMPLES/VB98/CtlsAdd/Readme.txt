                  CtlCfg.vbp et CtlView.vbp

Les deux projets de ce dossier illustrent l'ajout de contrôle dynamique (Form1.Controls.Add), ou la possibilité d'ajouter des contrôles non référencés au moment de l'exécution à une feuille, un document ActiveX ou un contrôle utilisateur.

L'exemple CtlCfg (configuration du contrôle) vous permet d'ajouter des informations au sujet de tout contrôle (contrôle intrinsèque ou utilisateur) à la base de données Controls.mdb. La base de données stocke la clé de licence du contrôle si une clé est requise pour charger et ajouter le contrôle. La base de données peut aussi stocker diverses propriétés pouvant être définies à mesure que le contrôle est ajoutée de manière dynamique. 

Une fois les informations sur le contrôle ajoutées à la base de données, vous pouvez ouvrir l'exemple ctlView (affichage des contrôles). Cet exemple lit simplement la base de données et affiche une liste des contrôles que vous pouvez ajouter de manière dynamique. Cliquez sur un contrôle pour l'ajouter à l'application. 

	NOTE : Assurez-vous que vous pouvez écrire dans le fichier Controls.mdb.

Pour plus d'informations sur l'ajout de contrôle dynamique, reportez-vous aux rubriques d'aide suivantes :

Add, méthode (collection Controls)
Add, méthode (collection Licenses)
EventInfo, objet
Licenses, collection
ObjectEvent, événement
Parameter, objet (Visual Basic)

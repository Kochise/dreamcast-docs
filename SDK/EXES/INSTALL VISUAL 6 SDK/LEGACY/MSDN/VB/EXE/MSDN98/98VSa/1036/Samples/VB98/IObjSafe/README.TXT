                  Exemple d'interface IObjectSafety Visual Basic 6
                                Document Lisezmoi
                                19 mars 1998

Résumé
-------
   IObjSafe.OCX implémente l'interface IObjectSafety, qui expose les fonctionnalités 
   aux fonctions de Internet Explorer 4.x Sécurisé pour le script et Sécurisé pour 
   l'initialisation.

Définition IObjectSafety
------------------------
   IObjectSafety doit être implémenté par des objets dont les interfaces prennent
   en charge les clients non fiables (par exemple, les scripts). Il permet au détenteur
   de l'objet de spécifier quelles interfaces doivent être protégées d'une
   utilisation non fiable. Voici des exemples d'interfaces pouvant être protégées
   de cette manière :

   IID_IDispatch         - "Sécurisé pour l'automation avec client d'automation non fiable
			    ou script"
   IID_IPersist*         - "Sécurisé pour l'initialisation avec des données non fiables"
   IID_IActiveScript     - "Sécurisé pour l'exécution des scripts non fiables"

Problèmes de sécurité
--------------------
   Il existe trois scénarios de script de sécurité éventuels à prendre en considération.

   i.   L'objet est toujours sécurisé pour le script.
        Si vous êtes sûr que toutes les méthodes et propriétés de votre objet sont
        sécurisées pour le script, vous devez notifier l'application client hôte en 
        ne renvoyant pas d'erreur dans la méthode de l'interface
        IObjectSafety_SetInterfaceSafetyOptions. Cela permet la création et 
        l'exécution correctes de l'objet.

   ii.  L'objet n'est jamais sécurisé pour le script.
        Si vous êtes sûr qu'aucune méthode et propriété de votre objet n'est
        sécurisée pour le script, vous devez notifier l'application client hôte en 
        renvoyant une erreur, E_Fail, dans la méthode de l'interface
        IObjectSafety_SetInterfaceSafetyOptions. Cela permet de refuser l'accès 
        à toutes les méthodes et propriétés.
        
   iii. L'objet est partiellement sécurisé pour le script.
        Au moins une méthode ou une propriété est sécurisée pour le script. 
        Dans ce cas, vous avez deux options à prendre en considération.  
        1.  Notifiez l'application client que l'objet n'est pas sécurisé pour le script.
            Cela permet de refuser l'accès à toutes les méthodes et propriétés.
        2.  Notifiez l'application client que l'objet est sécurisé pour le script,
            mais désactivez les méthodes et propriétés qui ne sont pas sécurisées 
            pour le script. Cela permet la création correcte de l'objet et refuse 
            l'accès aux méthodes et propriétés qui ne sont pas sécurisées pour 
            le script.

Test et exécution des exemples
---------------------------
   Il est recommandé d'utiliser Internet Explorer version 4.0 ou ultérieure pour tester
   cet exemple. Un exemple HTML est inclus pour illustrer l'utilisation et le test
   du projet Visual Basic de l'exemple IObjSafe.OCX.

Description du projet
-------------------
   IObjSafe.vbp est un exemple ActiveX OCX qui implémente l'interface IObjectSafety
   définie dans la bibliothèque de types IObjectSafety.TLB. Le fichier HTML 
   IObjSafe.HTM teste l'interface IObjectSafety implémentée dans 
   IObjSafe.OCX en créant et recevant le contrôle UCObjectSafety, puis référence 
   les propriétés Safe et UnSafe à l'aide de VBScript dans le document HTML.

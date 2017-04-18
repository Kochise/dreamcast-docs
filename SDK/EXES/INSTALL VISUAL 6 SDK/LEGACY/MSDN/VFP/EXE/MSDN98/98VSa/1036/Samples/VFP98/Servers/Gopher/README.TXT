Ce serveur personnalisé vise à fournir un objet de recherche rapide capable d'explorer un réseau d'entreprise à la recherche d'un client, sans indication sur la manière de procéder ni l'endroit de la recherche; ce client peut se trouver dans une base de données parmi cinquante bases de données différentes (p. ex. un gopher).

Le scénario utilisé par ce serveur simule une stratégie de recherche simple, les chemins de recherche concernant une base de données locale (Testdata) par opposition à une base de données distante (Tastrade).

En réalité, nous changeons l'environnement de données courant d'un formulaire et remplaçons les propriétés de la source de données liée par les nouvelles propriétés du serveur. Cette stratégie permet d'utiliser Visual FoxPro dans un modèle à trois niveaux, pour lequel les services utilisateur ne sont pas aussi étroitement liés aux services données que dans la plupart des systèmes client/serveur actuels.

Examinons l'événement BeforeOpenTables de l'environnement de données du formulaire.

Procédure à suivre:

1. Veillez à modifier le chemin de base de données dans le programme SearchData afin d'y placer votre répertoire de travail VFP5.

2. Vous devrez régénérer le projet Foxsrch.pjx et créer un serveur local (EXE) pour permettre son enregistrement. Le code qui appelle le serveur se trouve dans l'événement BeforeOpenTables de l'environnement de données WING1.SCX.

3. Exécutez le formulaire.


IMPORTANT!!! Cet exemple très simple a été conçu pour illustrer le concept de gopher et fonctionne uniquement avec un serveur local. N'essayez pas de l'utiliser pour un serveur d'automation distante; sinon, un blocage survient lorsque le client attend la réalisation d'un appel alors que le serveur tente d'y répondre. L'exemple de Gestionnaire de groupe constitue un meilleur exemple de réponse OLE par automation distante.
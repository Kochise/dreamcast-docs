Attribute VB_Name = "modMT"
Option Explicit

' Ce module montre la création par Visual Basic
'   d'une instance séparée de données globales
'   pour chaque thread. Ainsi, la variable
'   glngGlobalData aura une valeur séparée pour
'   chaque thread que Visual Basic démarre.
'
' Cet aspect est utilisé pour comptabiliser les
'   objets Coffee de chaque thread: il en ajoute
'   un à la variable glngGlobalData dans
'   l'événement Initialize de l'objet Coffee; il
'   en retire un dans l'événement Terminate.
'
' N'importe quel objet Coffee peut donc savoir
'   combien d'objets Coffee se trouvent sur sa
'   thread en testant la variable glngGlobalData.
'   Les clients peuvent également obtenir ce
'   résultat en appelant la propriété NumberOnThread
'   qui renvoie la variable glngGlobalData.
'
' Lorsque l'objet MTCoffee est exécuté dans
'   l'environnement de développement, qui contient
'   une seule thread, la propriété NumberOnThread
'   représente le nombre total d'objets Coffee.
'   Lorsque MTCoffee est compilé avec l'option
'   Thread par objet, le nombre sera un (1) pour
'   chaque objet Coffee, à moins que la méthode
'   GetCoffeeOnSameThread ne soit appelé pour
'   créer un deuxième objet Coffee sur la thread.
'
' Lorsque le projet MTCoffee est compilé avec
'   l'option Nb max de threads, la propriété
'   NumberOnThread sera supérieure à 1 sur
'   certaines threads dès lors que le nombre
'   des objets Coffee actifs est supérieur
'   au nombre de threads du regroupement.
'
' Cet aspect est traité à la rubrique
'   "Évolutivité et traitement multithread"
'   des Manuels en ligne.

Public glngGlobalData As Long


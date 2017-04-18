Attribute VB_Name = "InsuraceModule"
Option Explicit
Global Const KEY_NAME = "Nom"
Global Const KEY_STREET = "Rue"
Global Const KEY_CITY = "Ville"
Global Const KEY_STATE = "État"
Global Const KEY_CLAIM = "Réclamation"
Global Const CLAIM_AUTO = "VÉHICULE"
Global Const CLAIM_HOME = "MAISON"
Global Const CLAIM_BOAT = "BATEAU"
Global Const KEY_AMOUNT = "MontantRéclamation"

' ---------------------------------------------------
' Ceci pourrait être généré automatiquement par un Assistant
' ---------------------------------------------------
Global Const INSURANCE_CLAIMS_QUEUE_NAME = "sampleInsuranceClaimsQueue3"
Global Const INSURANCE_CLAIMS_QUEUE_LOCATION = ".\sampleInsuranceClaimsQueue3"

Global Const INSURANCE_ACCOUNTING_QUEUE_NAME = "sampleInsuranceAccountingQueue3"
Global Const INSURANCE_ACCOUNTING_QUEUE_LOCATION = ".\sampleInsuranceAccountingQueue3"

' ---------------------------------------------------
' Message d'erreur
' ---------------------------------------------------
Global Const ERROR_TEXT_RUNADMINTOOL = "La file de messages est inaccessible.  Vérifiez que vous avez bien créé les files nécessaires en utilisant le projet 'Administer_Step0'."

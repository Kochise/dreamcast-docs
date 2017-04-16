/*****************************************************************************/
/*                                                                           */
/* SYNCDTCT.H - External include file for SYNCDTCT.DLL which is used by      */
/*              setup to detect sync. comms. cards.                          */
/*                                                                           */
/*  SEE SYNCDTCT.C FOR DETAILED SYNTAX OF THE CALLS                          */
/*                                                                           */
/*****************************************************************************/

/*****************************************************************************/
/* Returned structure containing config data on the card                     */
/*                                                                           */
/* NEVER CHANGE THESE STRUCTURES WITHOUT ALSO CHANGING IBMSYNC.SYS           */
/*                                                                           */
/* The individual SYNC_CFG structures are stored as raw data in a single     */
/* registry value under \SERVICES\IBMSYNC\PARAMETERS\CardCfg.                */
/*                                                                           */
/* When IBMSYNC starts, it reads the raw data into memory and then uses the  */
/* result as it's config array. This means the data must be in the form the  */
/* driver expects.                                                           */
/*                                                                           */
/* Note: For MCA buses, the DMA & port info is read in a new every time the  */
/*       driver runs. It is the McaSlot & McaId field which define the cards.*/
/*                                                                           */
/*       For ISA/EISA buses, the base port addresses define the cards, and   */
/*       this infois only updated when setup is run.                         */
/*                                                                           */
/*****************************************************************************/
typedef struct _SYNC_CARD
{
  ULONG        IdandUseCount;        /* LOWORD is the adapter ID             */
                                     /* HIWORD is the use count              */
                                     /* Done this way to preserve back       */
                                     /* compatibility.                       */
  UCHAR        DisplayName[50];
} SYNC_CARD,* PSYNC_CARD;

typedef struct _PORT_DEF
{
  ULONG Addr;
  ULONG Len;
} PORT_DEF;

typedef struct _SYNC_CFG
{
  SYNC_CARD    Card;
  UCHAR        DeviceName[25];
  PORT_DEF     AdapterBase;          /* Zero for MPA/A card if sync disabled */
  UCHAR        Irq;
#define NO_IRQ_GENERATED 0xFF        /* Adapter failed to generate interrupt */
  UCHAR        DmaChannel;
#define DMA_CANT_BE_DETECTED 0xFF    /* Need to get user to select 0, 1 or 3 */
#define NO_DMA               0x10    /* IBMSYNC checks for this define       */
  USHORT       McaId;
  UCHAR        McaSlot;
  PORT_DEF     MpcaModePort;
  UCHAR        MpcaModeValue;
} SYNC_CFG,* PSYNC_CFG;

/*****************************************************************************/
/*                                                                           */
/* Calls to query sync cards                                                 */
/* -------------------------                                                 */
/*                                                                           */
/* DetectPresentCards() is used during an initial install of sync devices to */
/*                      get a list of present cards.This corresponds to      */
/*                      primary netcard detection.                           */
/*                                                                           */
/* QueryPossibleCards() are used when a users wants to add a new card. The   */
/* & QueryCardConfig()  fisrt call is made to get a list of all sync cards   */
/*                      and then once one has been selected, the second call */
/*                      checks for the cards existence and returns the config*/
/*                      to be written to the registry. These calls correspond*/
/*                      to secondary net card detection.                     */
/*                                                                           */
/* Both sets of cards can return NO_IRQ_GENERATED in the Irq field to        */
/* indicate a possible interrupt clash and DMA_CANT_BE_DETECTED in the case  */
/* of MicroGate cards when the DMA channel can't be selected.  In the second */
/* case setup has to prompt the user for either 0,1 or 3 before putting info */
/* in the registry.                                                          */
/*****************************************************************************/
DWORD DetectPresentCards(SYNC_CFG  CfgArray[], int MaxNum, int * pAvailNum);

DWORD QueryPossibleCards(SYNC_CARD CardArray[], int MaxNum, int * pAvailNum);
DWORD QueryCardConfig(ULONG CardId, PSYNC_CFG pCfg);

/*****************************************************************************/
/*                                                                           */
/* Calls used to store cfg                                                   */
/* -----------------------                                                   */
/*                                                                           */
/* These calls store the card configuration information under the IBMSYNC    */
/* key in a format which the device driver can understand.                   */
/*                                                                           */
/* WriteSyncCfg()  Saves an array of card config entries where they can be   */
/*                 accessed by the card.                                     */
/*                                                                           */
/* ReadSyncCfg()   Returns an array containing config on all the cards       */
/*                 currently configured.                                     */
/*                                                                           */
/*****************************************************************************/
DWORD WriteSyncCfg(SYNC_CFG  CfgArray[], int NumEntries);
DWORD ReadSyncCfg  (SYNC_CFG  CfgArray[], int MaxNum, int * pAvailNum);



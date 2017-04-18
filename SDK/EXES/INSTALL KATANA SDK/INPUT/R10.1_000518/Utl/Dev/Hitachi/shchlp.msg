
             -------------------------------------------------------
                      HELP INFORMATION  of SH C/C++ Compiler        
             -------------------------------------------------------
  1. Compiler specification:
     shc|shcpp [-option [...]]  operand [,[...]] 
     operand:==filename [-option [...]]
  2. Compiler options:
   (1) OPtimize=[0|1]                   Selects optimization level
   (2) SHow=<sub-option> [,[...]]       Specifies listing file contents
       <sub-option>:==[NO]SOurce|[NO]Object|[NO]STatistics|[NO]Include|
                      [NO]Expansion|Width=<width>|Length=<length>
   (3) Listfile[=<list-file-name>]      Generates listing file
       NOListfile                       Doesn't generate listing file
   (4) OBjectfile=<object-file-name>    Specifies object file name
   (5) Code=[Machinecode|Asmcode]       Selects target language
   (6) DEBug|NODEBug                    Generates debug information
   (7) DEFine=<sub-option> [,[...]]     Defines macro
       <sub-option>:==<macro>|<macro>=<id>|<macro>=<constant>
   (8) Include=<include-path> [,[...]]  Specifies include file directory
   (9) SEction=<sub-option> [,[...]]    Specifies section name
       <sub-option>:==Program=<id>|Const=<id>|Data=<id>|Bss=<id>
  (10) CPu=[sh1|sh2|sh2e|sh3|sh3e|sh4]  Specifies target CPU
  (11) Pic=[0|1]                        Generates position independent code
  (12) STring=[Const|Data]              Selects section for strings
  (13) COMment=[Nest|NONest]            Allows nested comment
  (14) SPeed|NOSPeed|SIze               Selects speed/size optimization
  (15) Help                             Shows help information
  (16) Euc|SJis                         Specifies Japanese code(EUC|Shift-JIS)
  (17) SUbcommand=<sub-file-name>       Specifies subcommand file name
  (18) ENdian=[Big|Little]              Selects object endian
  (19) DIvision=[Cpu|Peripheral|Nomask] Selects division code expansion
  (20) Macsave=[0|1]                    Selects MACL/MACH register save rules
  (21) PREInclude=<preinclude-file-name> [,[...]]
                                        Specifies preinclude file name
  (22) INLine[=<node-count>]            Executes automatic inline expansion
       NOINLine                         Doesn't execute automatic inline
                                                                      expansion
  (23) MEssage|NOMEssage                Outputs information message
  (24) ALign16|NOALign16                Generates 16 byte aligned code
  (25) NEstinline=<number>              Specifies nesting level of the inlining
  (26) DOuble=Float                     Treates "double" as single precision
  (27) OUtcode=[EUc|SJis]               Selects Japanese outcode(EUC|Shift-JIS)
  (28) ABs16=[RUn|ALl]                  Generates 2 byte address code
  (29) LOop|NOLOop                      Selects loop unrolling optimization
  (30) RTnext|NORTnext                  Extends return value
  (31) PREProcessor[=<expanded-file-name>] 
                                        Specifies preprocessor output source
  (32) Browser                          Specifies C++ browser/debugger data
                                                                   (only shcpp)
  (33) FPu=[Single|Double]              Treates floating type as single/double
  (34) DENormalize=[ON|OFF]             Treates denormalized number
  (35) Round=[Nearest|Zero]             Selects round to nearest even/zero
  (36) LAng=[C|CPp]                     Selects compiler C/C++ (only shc)
  (37) CAse=[Ifthen|Table]              Selects switch statement's code
                                                                [if-then|table]
  (38) Goptimize                        Generates global optimizing data

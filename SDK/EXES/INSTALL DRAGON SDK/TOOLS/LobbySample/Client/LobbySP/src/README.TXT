************************************************************
*      Lobby Service Porvider API ReadMe 
*					99.10.25
************************************************************
ロビーサービスプロバイダを使用して、アプリケーションを作成・実行する場合には、以下のリソースが必要となります。

1.DLL
  実行環境のフォルダに以下のDLLをあらかじめ格納して置かなければなりません。
　-LobbySP.dll
　-LSPdebug.dll
　-LSPmanage.dll
　-LSPreceive.exe
　-LSPregistry.dll
　-LSPsend.dll

２.INCLUDE
  アプリケーションをBUILDするINCLUDEとして、以下のものが必要となります。
　-LSPlobby.h
　-SRScom.h

3.レジストリ
　アプリケーションを実行する際に、使用するLobby Service　ProviderのGUIDとして、以下の情報をレジストリにあらかじめ書き込んでおかなければなりません。
[HKEY_LOCAL_MACHINE\Software\Microsoft\DirectPlay\Lobby Providers]
[HKEY_LOCAL_MACHINE\Software\Microsoft\DirectPlay\Lobby Providers\Lobby Connection For DirectPlay]
	"Guid"="{17AF6382-87AF-11D3-ADF6-0020AF6849EF}"
	"Path"="LobbySP.dll"
	"dwReserved1"=dword:0
	"dwReserved2"=dword:0




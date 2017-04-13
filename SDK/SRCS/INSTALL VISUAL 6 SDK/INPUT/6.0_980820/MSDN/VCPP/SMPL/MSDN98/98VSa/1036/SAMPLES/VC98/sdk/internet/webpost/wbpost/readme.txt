This is sample application showing the usage of WebPost APIs.

You should run the webpost.exe to install the webpost components before 
using this sample code. If you have the INetSDK, the webpost.exe can be 
found in the bin directory under the directory of INetSDK.

Usage:
	wbpost	-?		: usage
	wbpost -l		: list sites
	wbpost -e		: enumerates all available providers
	wbpost 			: call the wizard
	wbpost filename		: call the wizard, with filename chosen
	wbpost -s site filename	: post filename to site

This example demonstrates calling WpPost() for the simple usage
as well as calling WpBindToSite() to get a pointer to the provider
interface and calling the functions in the web post provider.


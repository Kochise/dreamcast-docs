document.write('<style type="text/css">');
document.write('A.e64nbar:link 		{color : #FFFFFF; text-decoration: none; FONT: 11px Tahoma, Verdana, sans-serif;}');
document.write('A.e64nbar:visited		{color : #FFFFFF; text-decoration: none; FONT: 11px Tahoma, Verdana, sans-serif;}');
document.write('A.e64nbar:active		{color : #DFDFDF; text-decoration: none; FONT: 11px Tahoma, Verdana, sans-serif;}');
document.write('A.e64nbar:hover		{color : #DFDFDF; text-decoration: none; FONT: 11px Tahoma, Verdana, sans-serif;}');
document.write('.e64nbar			{color: #FFFFFF; text-decoration: none; FONT: 11px Tahoma, Verdana, sans-serif;}');
document.write('.e64nbarform  { font-size: 10px; font-family: Tahoma, Verdana, sans-serif; vertical-align: middle }');
document.write('</style>');
function redirect(e64n){
	var name = e64n.selectedIndex;
	var url = e64n.options[name].value;
	if(url != "") {
		window.open(url,'_top');
	}
	return true;
}
document.write('<table bgcolor="#000000" border="0" cellpadding="0" cellspacing="0" width="100%">');
document.write('<tbody><tr><td><img src="/e64nbar.gif" alt="Emulation64 Network"></td><td style="text-align:left;width: 100%;"><span class="e64nbar">: ');

document.write('<a class="e64nbar" href="http://www.nathell.com/" target="_blank">Buy Crap in Swedish!</a> - <a class="e64nbar" href="http://www.emulation64.com" target="_blank">Emulation64</a> - <a class="e64nbar" href="http://www.emuhelp.com" target="_blank">EmuHelp</a> - <a class="e64nbar" href="http://www.emufanatics.com" target="_blank">EmuFanatics</a>');

document.write('</span></td><td align="right" nowrap="nowrap"><span class="e64nbar">Network Sites:&nbsp;</span></td><td><select name="site" class="e64nbarform" onChange="return redirect(this);">');

document.write('<option value="">News Sites:</option>');
document.write('<option value="http://www.emulation64.com"> - Emulation64</option>');
document.write('<option value="http://www.emuhelp.com"> - EmuHelp</option>');
document.write('<option value="http://www.emufanatics.com"> - Emufanatics</option>');
document.write('<option value="http://www.dcemu.co.uk"> - DCEmu</option>');
document.write('<option value="http://www.vg-network.com"> - VGN</option>');
document.write('<option value="http://emutastic.emulation64.com/"> - Emutastic</option>');
document.write('<option value="http://saturn.emulation64.com/"> - The Saturn Shack</option>');
document.write('<option value="http://cps2emu.emuhelp.com/"> - CPS2Emu</option>');
document.write('<option value="">Message Boards:</option>');
document.write('<option value="http://www.emutalk.net"> - EmuTalk</option>');
document.write('<option value="http://www.emuhelp.com/forums/"> - EmuHelp Forums</option>');
document.write('<option value="http://www.emufanatics.com/forums/"> - EmuFanatics Forums</option>');
document.write('<option value="">Emulators:</option>');
document.write('<option value="http://www.dolphin-emu.com/"> - GC - Dolphin</option>');
document.write('<option value="http://dolwin.emulation64.com/"> - GC - Dolwin</option>');
document.write('<option value="http://whinecube.emulation64.com/"> - GC - WhineCube</option>');
document.write('<option value="http://ninphin.emulation64.com/"> - GC - Ninphin</option>');
document.write('<option value="http://ps2emu.efx2.com/"> - PS2 - PS2Emu</option>');
document.write('<option value="http://nsx2.emulation64.com/"> - PS2 - NSX2</option>');
document.write('<option value="http://www.dreamemu.net/"> - DC - Dreamemu</option>');
document.write('<option value="http://1964emu.emulation64.com/"> - N64 - 1964</option>');
document.write('<option value="http://www.apollo64.com/"> - N64 - Apollo64</option>');
document.write('<option value="http://mupen64.emulation64.com/"> - N64 - Mupen64</option>');
document.write('<option value="http://pj64.emulation64.com/"> - N64 - PJ64</option>');
document.write('<option value="http://pj64k.emulation64.com/"> - N64 - PJ64K</option>');
document.write('<option value="http://tr64.emulation64.com/"> - N64 - TR64</option>');
document.write('<option value="http://alpha.emulation64.com/"> - N64 - UHLE Alpha</option>');
document.write('<option value="http://batard.psxfanatics.com/"> - PSX - PSXeven</option>');
document.write('<option value="http://fpsearm.psxfanatics.com/"> - PSX - FPSEce</option>');
document.write('<option value="http://nesterdc.emulation64.com/"> - NES - NesterDC</option>');
document.write('<option value="">Glide Wrappers:</option>');
document.write('<option value="http://evoodoo.emulation64.com/"> - eVoodoo</option>');
document.write('<option value="">Emulator Plugins:</option>');
document.write('<option value="http://gsmax.emufanatics.com/"> - PS2 - GSMax</option>');
document.write('<option value="http://mooby.psxfanatics.com/"> - PSX - CDR Mooby</option>');
document.write('<option value="http://gln64.emulation64.com/"> - N64 - glnintendo64()</option>');
document.write('<option value="">Front Ends:</option>');
document.write('<option value="http://ggloader.emulation64.com/"> - Giri Giri Loader</option>');
document.write('<option value="">Support:</option>');
document.write('<option value="http://olax.emulation64.com/"> - Olax\'s Emulation Centre</option>');
document.write('<option value="http://cheats.emulation64.com/1964/"> - 1964 Cheats</option>');
document.write('<option value="http://www.pj64cheats.net/"> - PJ64 Cheats</option>');
document.write('<option value="http://dreamcomp.emulation64.com/"> - DreamComp</option>');
document.write('<option value="http://cheats.emulation64.com/"> - Emu64 Cheats</option>');
document.write('<option value="">Humour:</option>');
document.write('<option value="http://doejo.emuhelp.com/"> - JCD\'s The Doejo</option>');
document.write('<option value="">Other:</option>');
document.write('<option value="http://www.efx2.com"> - EFX2 Blogs</option>');
document.write('<option value="http://darkwatcher.psxfanatics.com/console/"> - DW\'s Console History</option>');
document.write('<option value="http://wiki.emulation64.com/"> - Wiki Emulation</option>');
document.write('<option value="http://www.darkengine.net/"> - DarkEngine</option>');
document.write('<option value="http://ssb.emulation64.com/"> - SSB Emulation</option>');
document.write('<option value="http://www.jabosoft.com/"> - JaboSoft</option>');
document.write('<option value="http://www.emulnation.info/"> - EmulNation</option>');
document.write('<option value="http://www.ckemu.com/"> - CKEmu</option>');
document.write('<option value="http://www.bab3s.com/"> - Bab3s</option>');
document.write('<option value="http://thecpy.emulation64.com/Gateway/iedefault.htm"> - The Company 2064</option>');
document.write('<option value="http://ej.psxfanatics.com/"> - E}I{\'s Software</option>');

document.write('</select></td><td nowrap><span class="e64nbar">&nbsp;&nbsp;');
document.write('<a class="e64nbar" href="http://network.emulation64.com/about.php" target="_blank">About</a> - <a class="e64nbar" href="http://network.emulation64.com/hosting.php" target="_blank">Hosting</a> - <a class="e64nbar" href="http://network.emulation64.com/donate.php" target="_blank">Donate</a>');
document.write('&nbsp;</span></td></tr>');
document.write('</tbody></table>');
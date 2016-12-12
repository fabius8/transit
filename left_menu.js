/*
**	定义左边功能选择框的函数
**  id表:
**	1. system info: sys_info_id
**  2. general setup: gen_setup_id
**  3. network setup: net_setup_id
**  4. wifi setup: wifi_setup_id
**  5. ssid: ssid_id
**  6. vlan: vlan_id
**  7. snmp: snmp_id
**  8. netsniff: netsniff_id
**  9. system: sys_id
**  10. dynamic info: dny_info_id
**  11. logout: logout_id
**  12. advertisement: advertisement_id
**/

/* 一级菜单定义 */
function sys_info_id1()
{
	document.getElementById("sys_info_id1").style.display="none";
	document.getElementById("sys_info_id2").style.display="block";
}
function sys_info_id2()
{
	document.getElementById("sys_info_id2").style.display="none";
	document.getElementById("sys_info_id1").style.display="block";
}

function quick_id1()
{
	document.getElementById("quick_id1").style.display="none";
	document.getElementById("quick_id2").style.display="block";
}

function quick_id2()
{
	document.getElementById("quick_id2").style.display="none";
	document.getElementById("quick_id1").style.display="block";
}

function gen_setup_id1()
{
	document.getElementById("gen_setup_id1").style.display="none";
	document.getElementById("gen_setup_id2").style.display="block";
}
function gen_setup_id2()
{
	document.getElementById("gen_setup_id2").style.display="none";
	document.getElementById("gen_setup_id1").style.display="block";
}

function net_setup_id1()
{
	document.getElementById("net_setup_id1").style.display="none";
	document.getElementById("net_setup_id2").style.display="block";
}
function net_setup_id2()
{
	document.getElementById("net_setup_id2").style.display="none";
	document.getElementById("net_setup_id1").style.display="block";
}

/* BEGIN: Added by wanggang, 2014/10/16   PN:gwifi */
/* LTE配置 */
function lte_setup_id1()
{
	document.getElementById("lte_setup_id1").style.display="none";
	document.getElementById("lte_setup_id2").style.display="block";
}

function lte_setup_id2()
{
	document.getElementById("lte_setup_id1").style.display="block";
	document.getElementById("lte_setup_id2").style.display="none";
}
/* END:   Added by wanggang, 2014/10/16   PN:gwifi */


function wifi_setup_id1()
{
	document.getElementById("wifi_setup_id1").style.display="none";
	document.getElementById("wifi_setup_id2").style.display="block";
}
function wifi_setup_id2()
{
	document.getElementById("wifi_setup_id2").style.display="none";
	document.getElementById("wifi_setup_id1").style.display="block";
}

function ssid_id1()
{
	document.getElementById("ssid_id1").style.display="none";
	document.getElementById("ssid_id2").style.display="block";
}
function ssid_id2()
{
	document.getElementById("ssid_id2").style.display="none";
	document.getElementById("ssid_id1").style.display="block";
}

function vlan_id1()
{
	document.getElementById("vlan_id1").style.display="none";
	document.getElementById("vlan_id2").style.display="block";
}

function vlan_id2()
{
	document.getElementById("vlan_id2").style.display="none";
	document.getElementById("vlan_id1").style.display="block";
}

function snmp_id1()
{
	document.getElementById("snmp_id1").style.display="none";
	document.getElementById("snmp_id2").style.display="block";
}
function snmp_id2()
{
	document.getElementById("snmp_id2").style.display="none";
	document.getElementById("snmp_id1").style.display="block";
}

function network_security_id1()
{
	document.getElementById("network_security_id1").style.display="none";
	document.getElementById("network_security_id2").style.display="block";
}
function network_security_id2()
{
	document.getElementById("network_security_id2").style.display="none";
	document.getElementById("network_security_id1").style.display="block";
}

function access_control_id1()
{
	document.getElementById("access_control_id1").style.display="none";
	document.getElementById("access_control_id2").style.display="block";
}
function access_control_id2()
{
	document.getElementById("access_control_id2").style.display="none";
	document.getElementById("access_control_id1").style.display="block";
}

function advertisement_id1()
{
	document.getElementById("advertisement_id1").style.display="none";
	document.getElementById("advertisement_id2").style.display="block";
}
function advertisement_id2()
{
	document.getElementById("advertisement_id2").style.display="none";
	document.getElementById("advertisement_id1").style.display="block";
}


function attack_defense_id1()
{
	document.getElementById("attack_defense_id1").style.display="none";
	document.getElementById("attack_defense_id2").style.display="block";
}
function attack_defense_id2()
{
	document.getElementById("attack_defense_id2").style.display="none";
	document.getElementById("attack_defense_id1").style.display="block";
}

function info_collect_id1()
{
	document.getElementById("info_collect_id1").style.display="none";
	document.getElementById("info_collect_id2").style.display="block";
}
function info_collect_id2()
{
	document.getElementById("info_collect_id2").style.display="none";
	document.getElementById("info_collect_id1").style.display="block";
}

function sys_id1()
{
	document.getElementById("sys_id1").style.display="none";
	document.getElementById("sys_id2").style.display="block";
}
function sys_id2()
{
	document.getElementById("sys_id2").style.display="none";
	document.getElementById("sys_id1").style.display="block";
}

function function_debug_id1()
{
	sys_id1();
	document.getElementById("function_debug_id1").style.display="none";
	document.getElementById("function_debug_id2").style.display="block";
}
function function_debug_id2()
{
	sys_id1();
	document.getElementById("function_debug_id2").style.display="none";
	document.getElementById("function_debug_id1").style.display="block";
}



function dny_info_id1()
{
	document.getElementById("dny_info_id1").style.display="none";
	document.getElementById("dny_info_id2").style.display="block";
}
function dny_info_id2()
{
	document.getElementById("dny_info_id2").style.display="none";
	document.getElementById("dny_info_id1").style.display="block";
}

/* 二级菜单定义 */
function select_id(id)
{
	document.getElementById(id).style.color="#ff0000";
}

function dev_basic_id()
{
	gen_setup_id1();
	document.getElementById("dev_basic_id").style.color="#ff0000";
}

function legap_id()
{
	gen_setup_id1();
	document.getElementById("legap_id").style.color="#ff0000";
}

function ap_flow_id()
{
	gen_setup_id1();
	document.getElementById("ap_flow_id").style.color="#ff0000";
}

function wifidog_id()
{
	gen_setup_id1();
	document.getElementById("wifidog_id").style.color="#ff0000";
}

function tr69c_id()
{
	gen_setup_id1();
	document.getElementById("tr69c_id").style.color="#ff0000";
}

function cdn_id()
{
	gen_setup_id1();
	document.getElementById("cdn_id").style.color="#ff0000";
}
/*
function home_other_id()
{
	gen_setup_id1();
	document.getElementById("home_other_id").style.color="#ff0000";
}
*/
function dev_advanced_id()
{
	gen_setup_id1();
	document.getElementById("dev_advanced_id").style.color="#ff0000";
}

function ipv4_id()
{
	net_setup_id1();
	document.getElementById("ipv4_id").style.color="#ff0000";
}

function wan_id()
{
	net_setup_id1();
	document.getElementById("wan_id").style.color="#ff0000";
}

function dns_conf_id()
{
	net_setup_id1();
	document.getElementById("dns_conf_id").style.color="#ff0000";
}

function wan2_id()
{
	net_setup_id1();
	document.getElementById("wan2_id").style.color="#ff0000";
} 

function wan3_id()
{
	net_setup_id1();
	document.getElementById("wan3_id").style.color="#ff0000";
}

function wan_vitual_id()
{
	net_setup_id1();
	document.getElementById("wan_vitual_id").style.color="#ff0000";
}

function wan_strategy_id()
{
	net_setup_id1();
	document.getElementById("wan_strategy_id").style.color="#ff0000";
}

function lan_id()
{
	net_setup_id1();
	document.getElementById("lan_id").style.color="#ff0000";
}
function dns_mapping_id()
{
        net_setup_id1();
        document.getElementById("dns_mapping_id").style.color="#ff0000";
}


function ethernet_id()
{
	net_setup_id1();
	document.getElementById("ethernet_id").style.color="#ff0000";
}

function forward_mode_id()
{
	net_setup_id1();
	document.getElementById("forward_mode_id").style.color="#ff0000";
}

function wx_follow_id()
{
	net_setup_id1();
	document.getElementById("wx_follow_id").style.color="#ff0000";
}

/* begin: add@2014.9.11*/
function network_route_config_id()
{
	net_setup_id1();
	document.getElementById("network_route_config_id").style.color="#ff0000";
}
/* end: add@2014.9.11*/

function network_portmap_config_id()
{
	net_setup_id1();
	document.getElementById("network_portmap_config_id").style.color="#ff0000";
}

function portconf_id()
{
	net_setup_id1();
	document.getElementById("portconf_id").style.color="#ff0000";
}


function vpn_pass_id()
{
	net_setup_id1();
	document.getElementById("vpn_pass_id").style.color="#ff0000";
}

function dhcp_server_id()
{
	net_setup_id1();
	document.getElementById("dhcp_server_id").style.color="#ff0000";
}

function pppoe_client_id()
{
	net_setup_id1();
	document.getElementById("pppoe_client_id").style.color="#ff0000";
}

function net_advanced_id()
{
	net_setup_id1();
	document.getElementById("net_advanced_id").style.color="#ff0000";
}

/* BEGIN: Added by wanggang, 2014/10/16   PN:gwifi */
/* lte releated */
function lte_basic_config_id()
{
	lte_setup_id1();
	document.getElementById("lte_basic_config_id").style.color="#ff0000";
}

function lte_advanced_config_id()
{
	lte_setup_id1();
	document.getElementById("lte_access_config_id").style.color="#ff0000";
}

function lte_keepalive_config_id()
{
	lte_setup_id1();
	document.getElementById("lte_keepalive_config_id").style.color="#ff0000";
}

function lte_pin_config_id()
{
	lte_setup_id1();
	document.getElementById("lte_pin_config_id").style.color="#ff0000";
}
/* END:   Added by wanggang, 2014/10/16   PN:gwifi */


function wifi1_id()
{
	wifi_setup_id1();
	document.getElementById("wifi1_id").style.color="#ff0000";
}

function wifi2_id()
{
	wifi_setup_id1();
	document.getElementById("wifi2_id").style.color="#ff0000";
}

function ssid_id()
{
	ssid_id1();
	document.getElementById("ssid_id").style.color="#ff0000";
}

function ssid_x86_id()
{
	ssid_id1();
	document.getElementById("ssid_x86_id").style.color="#ff0000";
}

function vlan_add_id()
{
	vlan_id1();
	document.getElementById("vlan_add_id").style.color="#ff0000";
}

function vlan_mapping_id()
{
	vlan_id1();
	document.getElementById("vlan_mapping_id").style.color="#ff0000";
}

function vlan_fc_id()
{
	vlan_id1();
	document.getElementById("vlan_fc_id").style.color="#ff0000";
}

function vlan_port_id()
{
	vlan_id1();
	document.getElementById("vlan_port_id").style.color="#ff0000";
}

function snmp_id()
{
	gen_setup_id1();
	document.getElementById("snmp_id").style.color="#ff0000";
}

function netsniff_id()
{
	network_security_id1();
	document.getElementById("netsniff_id").style.color="#ff0000";
} 

function audit_server_id()
{
	network_security_id1();
	document.getElementById("audit_server_id").style.color="#ff0000";
}

function transit_id()
{
    network_security_id1();
    document.getElementById("transit_id").style.color="#ff0000";
}

function attack_defense_id()
{
	network_security_id1();
	document.getElementById("attack_defense_id").style.color="#ff0000";
}

function freeauth_mac_config_id()
{
	access_control_id1();
	document.getElementById("freeauth_mac_config_id").style.color="#ff0000";
}

function flowctrl_sta_config_id()
{
	access_control_id1();
	document.getElementById("flowctrl_sta_config_id").style.color="#ff0000";
}

function qos_id()
{
	access_control_id1();
	document.getElementById("qos_id").style.color="#ff0000";	
}

function fraud_site_config_id()
{
	access_control_id1();
	document.getElementById("fraud_site_config_id").style.color="#ff0000";
}

function other_access_control_id()
{
	access_control_id1();
	document.getElementById("other_access_control_id").style.color="#ff0000";
}


function span_ssid_auth_id()
{
	access_control_id1();
	document.getElementById("span_ssid_auth_id").style.color="#ff0000";
}



function advertisement_id()
{
	advertisement_id1();
	document.getElementById("advertisement_id").style.color="#ff0000";
}

function info_collect_id()
{
	info_collect_id1();
	document.getElementById("info_collect_id").style.color="#ff0000";
}

function info_audit_id()
{
	info_collect_id1();
	document.getElementById("info_audit_id").style.color="#ff0000";
}

function info_advanced_id()
{
	info_collect_id1();
	document.getElementById("info_advanced_id").style.color="#ff0000";
}

function info_decrypt_id()
{
	info_collect_id1();
	document.getElementById("info_advanced_id").style.color="#ff0000";
}

function locator_status_id()
{
	info_collect_id1();
	document.getElementById("locator_status_id").style.color="#ff0000";
}
function gps_id()
{
	info_collect_id1();
	document.getElementById("gps_id").style.color="#ff0000";
}


function stadct_id()
{
	info_collect_id1();
	document.getElementById("stadct_id").style.color="#ff0000";
}

function storage_id()
{
	info_collect_id1();
	document.getElementById("storage_id").style.color="#ff0000";
}


function trap_id()
{
	snmp_id1();
	document.getElementById("trap_id").style.color="#ff0000";
}

function time_id()
{
	sys_id1();
	document.getElementById("time_id").style.color="#ff0000";
}
function http_port_id()
{
	sys_id1();
	document.getElementById("http_port_id").style.color="#ff0000";
}

function restore_id()
{
	sys_id1();
	document.getElementById("restore_id").style.color="#ff0000";
}

function software_update_id()
{
	sys_id1();
	document.getElementById("software_update_id").style.color="#ff0000";
}

function users_id()
{
	sys_id1();
	document.getElementById("users_id").style.color="#ff0000";
}
function dev_reboot_id()
{
	sys_id1();
	document.getElementById("dev_reboot_id").style.color="#ff0000";
}

function timed_task_id()
{
	sys_id1();
	document.getElementById("timed_task_id").style.color="#ff0000";
}

function vpn_l2tp_id()
{
	sys_id1();
	document.getElementById("vpn_l2tp_id").style.color="#ff0000";
}

function local_cmd_id()
{
	sys_id1();
	document.getElementById("local_cmd_id").style.color="#ff0000";
}
/* begin: add@2014.9.1 */





/*
function sys_id1()
{
	document.getElementById("sys_id1").style.display="none";
	document.getElementById("sys_id2").style.display="block";
}
function sys_id2()
{
	document.getElementById("sys_id2").style.display="none";
	document.getElementById("sys_id1").style.display="block";
}
*/



/* end: add@2014.9.1 */

function mast_backup_id()
{
	sys_id1();
	document.getElementById("mast_backup_id").style.color="#ff0000";
}


function log_upload_id()
{
	function_debug_id1();
	document.getElementById("log_upload_id").style.color="#ff0000";
}

function client_info_id()
{
	dny_info_id1();
	document.getElementById("client_info_id").style.color="#ff0000";
}
function sta_info1_id()
{
	dny_info_id1();
	document.getElementById("sta_info1_id").style.color="#ff0000";
}
function sta_info2_id()
{
	dny_info_id1();
	document.getElementById("sta_info2_id").style.color="#ff0000";
}

function sta_info3_id()
{
	dny_info_id1();
	document.getElementById("sta_info3_id").style.color="#ff0000";
}
function flow_statistics_id()
{
	dny_info_id1();
	document.getElementById("flow_statistics_id").style.color="#ff0000";
}

function sysinfo_lte_show_id()
{
	sys_info_show_id1();
	document.getElementById("sysinfo_lte_show_id").style.color="#ff0000";
}


function ssid_scan_id()
{
	dny_info_id1();
	document.getElementById("ssid_scan_id").style.color="#ff0000";
}
function rogue_ap_id()
{
	dny_info_id1();
	document.getElementById("rogue_ap_id").style.color="#ff0000";
}


/*third */
/*一键收集*/
function debug_collect_id()
{
	function_debug_id1();
	document.getElementById("debug_collect_id").style.color="#ff0000";
}
/*认证控制*/
function authorize_control_id()
{
	function_debug_id1();
	document.getElementById("authorize_control_id").style.color="#ff0000";
}
/*网络诊断*/
function net_diagnose_id()
{
	function_debug_id1();
	document.getElementById("net_diagnose_id").style.color="#ff0000";
}
function log_id()
{
	function_debug_id1();
	document.getElementById("log_id").style.color="#ff0000";
}

/* 主函数入口 */
function write_to_stari_br(id, href, func, info)
{
	document.write('<div id="'+id+'"><img src="/minus.png"><a href="'+href+'" onclick="'+ func +'();">'+ info +'</a></br></br>');
	return;
}

function write_to_stari_div(id, href, func, info)
{
	document.write('<div id="'+id+'"><img src="/plus.png"><a href="'+href+'" onclick="'+ func +'();">'+ info +'</a></div>');
	return;
}

function write_to_second_br(href, id, info)
{
	document.write('<a href="/cgi-bin/snmpManager.cgi?cgimodule='+href+'" id="'+id+'">&nbsp;&nbsp;&nbsp;&nbsp;'+info+'</a></br></br>');
	return;
}

function write_to_second_br_pl(href, id, info, language)
{
    document.write('<a href="/transit.pl?i18nLanguage='+language+'&cgimodule='+href+'" id="'+id+'">&nbsp;&nbsp;&nbsp;&nbsp;'+info+'</a></br></br>');
    return;
}

function write_to_second_div(href, id, info)
{
	document.write('<a href="/cgi-bin/snmpManager.cgi?cgimodule='+href+'" id="'+id+'">&nbsp;&nbsp;&nbsp;&nbsp;'+info+'</a></div>');
	return;
}


function write_second_satri_br(id, href, func, info)
{
	document.write('<div id="'+id+'">&nbsp;&nbsp;&nbsp;<img src="/minus.png"><a href="'+href+'" onclick="'+ func +'();">'+ info +'</a></br></br>');
	return;
}

function write_second_satri_div(id, href, func, info)
{
	document.write('<div id="'+id+'">&nbsp;&nbsp;&nbsp;<img src="/plus.png"><a href="'+href+'" onclick="'+ func +'();">'+ info +'</a></div>');
	return;
}

function write_to_third_br(href, id, info)
{
	document.write('<a href="/cgi-bin/snmpManager.cgi?cgimodule='+href+'" id="'+id+'">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;'+info+'</a></br></br>');
	return;
}

function write_to_third_div(href, id, info)
{
	document.write('<a href="/cgi-bin/snmpManager.cgi?cgimodule='+href+'" id="'+id+'">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;'+info+'</a></div>');
	return;
}
function insert_one_line()
{
		document.write('</br>');
		return;
}

function insert_one_line_div()
{
	document.write('</div>');
	return;
}

function left_menu(language)
{
	/* 定义设备类型:0表示单频, 1表示双频 (3表示X86网关  add by zhz 2014-1-16) */
	var dev_type="1";
	/* 0表示 不带有有线LAN口，1表示带有有线LAN口*/
	var have_lan_port="0";
	/* 0表示 不带有netsniff功能，1表示带有netsniff功能*/
	var have_netsniff="1";
	/* 0表示不支持LTE，1表示支持LTE*/
	var lte_support="0";
	//var oem_company = "other"
	/* 0表示 不带有SNMP功能，1表示带有SNMP功能*/
	var have_minisnmp="1"; 
	/* 0表示 不带有L2TP功能，1表示带有L2TP功能*/
	var have_l2tp="1";
	/* 0表示 不带有CDN功能，1表示带有CDN功能*/
	var have_cdn="0";
	/* 0表示 不带有微信扫码功能，1表示带有微信扫码功能*/
	var have_wxflow="0";
	/* 0表示 不带有端口映射功能，1表示带有端口映射功能*/
	var have_portmap="0";
	/* 0表示 不带有端口模式配置功能，1表示带有端口模式配置功能*/
	var have_portconf="0";
	/* 0表示 不支持多WAN口配置功能，1表示支持多WAN口配置功能*/
	var have_multiwan="0";
	/* 0表示 不支持防攻击功能，1表示支持防攻击功能*/
	var have_attack_defense="0"
	/* 0表示 不支持访问控制功能，1表示支持访问控制功能*/
	var have_access_control="1"
	/* 0表示 不支持审计对接功能，1表示支持审计对接功能*/
	var have_audit="1"
    var have_transit="1"
	/* 0表示 不支持静态DNS解析功能，1表示支持静态DNS解析功能*/
        var have_dns_mapping="1"
	/* 0表示 不支持广告推送，1表示支持广告推送*/
	var have_advertisement="0";
	
	var have_locator="1";
	/* 0表示 不支持访问控制功能，1表示支持访问控制功能*/
	var have_access_control="1"
	
	/* 0表示 不带有GPS功能，1表示带有GPS功能*/
	var have_gps="1";
	/* 0表示 不支持报文截取，1表示支持报文截取*/
	var have_pcap="0";
	
	/* 0表示 wifidog没有启用 1表示wifidog启用*/
	var have_wifidog_open="0";
	
	/* 0: 简体, 1: 繁体, 2: 英文 */
	switch(parseInt(language))
	{
		case 0:
			document.write('<div id="sys_info_id1"><img src="/plus.png"><a href="/cgi-bin/snmpManager.cgi?cgimodule=home_page" id="homepage_id">系统信息</a></div>');
      document.write('<div id="quick_id1"><img src="/plus.png"><a href="/cgi-bin/snmpManager.cgi?cgimodule=quick_set" id="quick_set_id">配置向导</a></div>');
			
			/* 基本信息 */
			write_to_stari_div("gen_setup_id1", "javascript:void(0)", "gen_setup_id1", "基本信息");
			write_to_stari_br("gen_setup_id2", "javascript:void(0)", "gen_setup_id2", "基本信息");
			write_to_second_br("dev_basic", "dev_basic_id","设备信息");	
			if ("1" == have_cdn)  
			{
				write_to_second_br("cdn", "cdn_id", "资源同步");
			}
			if ("1" == have_minisnmp) 
			{
				write_to_second_br("tr69c", "tr69c_id", "远程管理");
				//if("dianwifi" != oem_company)/*2015-3-3 wangang(dianwifi) 去掉snmp页面显示*/
				//{
					write_to_second_br("snmp", "snmp_id", "SNMP配置");
				//}
			}
			else
			{ 
				write_to_second_br("tr69c", "tr69c_id", "远程管理");		
			}
			write_to_second_div("wifidog", "wifidog_id", "热点配置");
			
			//write_to_second_br("legap", "legap_id", "合法AP配置");
			//write_to_second_br("ap_flow", "ap_flow_id", "AP流控配置");
			//write_to_second_div("dev_advanced", "dev_advanced_id","高级配置");

			/* 网络配置 */
			write_to_stari_div("net_setup_id1", "javascript:void(0)", "net_setup_id1", "网络配置");
			write_to_stari_br("net_setup_id2", "javascript:void(0)", "net_setup_id2", "网络配置");
			if ("1" == have_multiwan){
				write_to_second_br("wan1", "wan_id", "WAN");
			}
			else{
				write_to_second_br("ipv4", "ipv4_id", "WAN");
			}
			write_to_second_br("lan", "lan_id", "LAN");
			if("1" == have_dns_mapping)
			{
				write_to_second_br("dns_mapping", "dns_mapping_id", "域名映射");
			}
			//write_to_second_br("ethernet", "ethernet_id", "WAN");
			write_to_second_br("forward_mode", "forward_mode_id", "转发模式");
			if ("1" == have_wxflow){
				write_to_second_br("wx_follow", "wx_follow_id", "微信扫码");
			}
			write_to_second_br("network_route_show", "network_route_config_id","路由配置");
			if ("1" == have_portmap){
				write_to_second_br("network_portmap_show", "network_portmap_config_id","端口映射");
			}
			if ("1" == have_portconf){
				write_to_second_br("portconf", "portconf_id","端口配置");
			}
			write_to_second_br("vpn_pass", "vpn_pass_id","VPN透传");
			write_to_second_div("dhcp_server", "dhcp_server_id", "DHCP 服务器");
			//write_to_second_br("pppoe_client", "pppoe_client_id", "PPPoE");
			//write_to_second_div("net_advanced", "net_advanced_id", "高级配置");
			
			/* LTE配置 */
			if ("1" == lte_support){
					write_to_stari_div("lte_setup_id1", "javascript:void(0)", "lte_setup_id1", "LTE配置");
					write_to_stari_br("lte_setup_id2", "javascript:void(0)", "lte_setup_id2", "LTE配置");
					write_to_second_br("lte_basic_page", "lte_basic_config_id", "基本配置");
					write_to_second_div("lte_access_page", "lte_access_config_id", "高级配置");
			}
			
			
			/* 无线配置 */
      if ("3" != dev_type){
    			write_to_stari_div("wifi_setup_id1", "javascript:void(0)", "wifi_setup_id1", "Wi-Fi");
    			write_to_stari_br("wifi_setup_id2", "javascript:void(0)", "wifi_setup_id2", "Wi-Fi");
    			if("0" == dev_type)
    			{
    				write_to_second_div("wifi_mode&wifi_id=0", "wifi1_id", "Wi-Fi 2.4GHz(1)");
    			}
    			else
    			{
    				write_to_second_br("wifi_mode&wifi_id=0", "wifi1_id", "Wi-Fi 2.4GHz(1)");
    				write_to_second_div("wifi_mode&wifi_id=1", "wifi2_id", "Wi-Fi 5GHz(2)");
    			}
    			
					write_to_stari_div("ssid_id1", "javascript:void(0)", "ssid_id1", "SSID");
					write_to_stari_br("ssid_id2", "javascript:void(0)", "ssid_id2", "SSID");
					write_to_second_div("vap", "ssid_id", "SSID");
    	}
    	else
    	{ 
					write_to_stari_div("ssid_id1", "javascript:void(0)", "ssid_id1", "SSID");
					write_to_stari_br("ssid_id2", "javascript:void(0)", "ssid_id2", "SSID");
					write_to_second_div("ssid_x86", "ssid_x86_id", "SSID");    			
    	}
             
      /* VLAN 配置*/
      write_to_stari_div("vlan_id1", "javascript:void(0)", "vlan_id1", "VLAN");
			write_to_stari_br("vlan_id2", "javascript:void(0)", "vlan_id2", "VLAN");
			if ("1" == have_lan_port)
			{
				write_to_second_br("vlan_mapping", "vlan_mapping_id", "端口VLAN配置");
				write_to_second_div("vlan_fc", "vlan_fc_id", "VLAN流控配置");
			}
			else
			{ 
				write_to_second_div("vlan_mapping", "vlan_mapping_id", "端口VLAN配置");
		
			}

			/* snmp 配置 
			write_to_stari_div("snmp_id1", "javascript:void(0)", "snmp_id1", "SNMP");
			write_to_stari_br("snmp_id2", "javascript:void(0)", "snmp_id2", "SNMP");
			write_to_second_div("snmp", "snmp_id", "SNMP V2");
			*/
			
			/* 广告配置 */
			if ("1" == have_advertisement)
			{
				write_to_stari_div("advertisement_id1", "javascript:void(0)", "advertisement_id1", "广告推送");
				write_to_stari_br("advertisement_id2", "javascript:void(0)", "advertisement_id2", "广告推送");
				write_to_second_div("advertisement", "advertisement_id", "基本配置");
			}

			
			/* 网络监控配置 */

			write_to_stari_div("network_security_id1", "javascript:void(0)", "network_security_id1", "网络安全");
			write_to_stari_br("network_security_id2", "javascript:void(0)", "network_security_id2", "网络安全");

			if ("1" == have_attack_defense)
			{
				write_to_second_br("attack_defense", "attack_defense_id", "攻击防御");
			}
			if ("1" == have_netsniff)  
			{
				write_to_second_br("netsniff", "netsniff_id", "网络监控");
			} 
        if ("1" == have_transit) {
            write_to_second_br_pl("transit", "transit_id", "无线汇聚", parseInt(language));
        }


			if ("1" == have_audit)
			{
				write_to_second_div("audit_server", "audit_server_id", "审计服务");
			}
			else
			{
				insert_one_line_div();
			}

			
        
			/* 访问控制配置 */
			if("vtache" != oem_company)
			{ 
				if ("1" == have_access_control)
				{
					write_to_stari_div("access_control_id1", "javascript:void(0)", "access_control_id1", "访问控制");
					write_to_stari_br("access_control_id2", "javascript:void(0)", "access_control_id2", "访问控制");
					if("0" == have_wifidog_open)
					{
						write_to_second_br("freeauth_mac_show", "freeauth_mac_config_id","终端免认证");
						write_to_second_br("flowctrl_sta_show", "flowctrl_sta_config_id","终端流控");
					}
					//write_to_second_br("span_ssid_auth", "span_ssid_auth_id", "跨ssid认证");
					write_to_second_br("qos","qos_id","QOS");
					write_to_second_br("fraud_site_show","fraud_site_config_id","诈骗过滤");					
					write_to_second_div("other_access_control", "other_access_control_id", "其它控制");
				}
			}
 
 			if("dianwifi" != oem_company)/*2015 dianwifi(wang gang) 不要信息采集*/
			{
				/* 信息采集 add by zhz 2014-4-15 */
				if ("3" != dev_type)
				{
				write_to_stari_div("info_collect_id1", "javascript:void(0)", "info_collect_id1", "信息采集");
				write_to_stari_br("info_collect_id2", "javascript:void(0)", "info_collect_id2", "信息采集");

				write_to_second_br("info_collect", "info_collect_id", "基本配置");
				write_to_second_br("info_audit", "info_audit_id", "场所信息");
				write_to_second_br("info_advanced", "info_advanced_id", "高级配置");
				write_to_second_div("locator_status", "locator_status_id", "状态显示");			
				}
			}
            /* system   */
			write_to_stari_div("sys_id1", "javascript:void(0)", "sys_id1", "系统操作");
			write_to_stari_br("sys_id2", "javascript:void(0)", "sys_id2", "系统操作");
			write_to_second_br("time", "time_id", "时间配置");
			write_to_second_br("restore", "restore_id", "恢复出厂配置");
			write_to_second_br("software_update", "software_update_id", "软件升级");
			write_to_second_br("dev_reboot", "dev_reboot_id", "设备重启");
            write_to_second_br("timed_task", "timed_task_id", "定时任务");
			if ("1" == have_l2tp)
			{
				//write_to_second_br("vpn_l2tp", "vpn_l2tp_id", "VPN 配置");
			}
			
			write_to_second_br("local_cmd","local_cmd_id","本地命令配置");	
			write_to_second_br("http_port", "http_port_id", "登录端口配置");
			write_to_second_br("users", "users_id", "登录帐号配置");
            if ("3" == dev_type){
				write_to_second_br("mast_backup", "mast_backup_id", "主备配置");
            }
			
			write_second_satri_div("function_debug_id1", "javascript:void(0)", "function_debug_id1", "功能调试");
			write_second_satri_br("function_debug_id2", "javascript:void(0)", "function_debug_id2", "功能调试");
			write_to_third_br("debug_collect", "debug_collect_id", "一键收集");
			write_to_third_br("net_diagnose", "net_diagnose_id", "网络诊断");
			write_to_third_br("log", "log_id", "日志输出");
			write_to_third_br("log_upload", "log_upload_id", "日志上传");
			write_to_third_div("authorize_control", "authorize_control_id", "认证控制");
			insert_one_line_div();

			/* dny info */            
			write_to_stari_div("dny_info_id1", "javascript:void(0)", "dny_info_id1", "查询信息");
			write_to_stari_br("dny_info_id2", "javascript:void(0)", "dny_info_id2", "查询信息");
			write_to_second_br("flow_statistics", "flow_statistics_id", "流量统计");
			if ("1" == lte_support){
					write_to_second_br("sta_info&wifi_id=0", "client_info_id", "客户端信息");
					write_to_second_div("sysinfo_lte_page", "sysinfo_lte_show_id", "LTE状态");
    		}else{
				write_to_second_div("sta_info&wifi_id=0", "client_info_id", "客户端信息");	
			}
          
			//write_to_second_br("ssid_scan&wifi_id=0", "ssid_scan_id", "干扰设备查询");
			//write_to_second_div("rogue_ap&wifi_id=0", "rogue_ap_id", "非法AP查询");
			//write_to_second_div("dhcp_client_info", "dhcp_client_info_id", "DHCP 分配记录");
			

			/* help */
			//document.write('<div id="help_id"><img src="/plus.png"><a href="/help.html">在线帮助</a></div>');

      /* logout */
			document.write('<div id="logout_id"><img src="/plus.png"><a href="/cgi-bin/snmpManager.cgi?cgimodule=logout">退出登录</a></div>');
			break;
		case 1:
			document.write('<div id="sys_info_id1"><a href="/cgi-bin/snmpManager.cgi?cgimodule=home_page">&nbsp;&nbsp;&nbsp;&nbsp;系統信息</a></div>');
      document.write('<div id="quick_id1"><a href="/cgi-bin/snmpManager.cgi?cgimodule=quick_set">&nbsp;&nbsp;&nbsp;&nbsp;配置向导</a></div>');
			break;
		case 2:
			document.write('<div id="sys_info_id1"><img src="/plus.png"><a href="/cgi-bin/snmpManager.cgi?cgimodule=home_page" id="homepage_id">System Info</a></div>');
      document.write('<div id="quick_id1"><img src="/plus.png"><a href="/cgi-bin/snmpManager.cgi?cgimodule=quick_set" id="quick_set_id">Quick Setup</a></div>');
			//document.write('<div id="quick_id1"><a href="/cgi-bin/snmpManager.cgi?cgimodule=multiple_ssid" id="quick_id">&nbsp;&nbsp;&nbsp;Quick Setup</a></div>');
			/* 基本信息 */
			write_to_stari_div("gen_setup_id1", "javascript:void(0)", "gen_setup_id1", "Basic Info");
			write_to_stari_br("gen_setup_id2", "javascript:void(0)", "gen_setup_id2", "Basic Info");
			write_to_second_br("dev_basic", "dev_basic_id","Device Info"); 
			if ("1" == have_cdn) 
			{
				write_to_second_br("cdn", "cdn_id","CDN"); 
			}
			if ("1" == have_minisnmp)
			{
				write_to_second_br("tr69c", "tr69c_id", "Remote Management");
				if("dianwifi" != oem_company)/*2015-3-3 wangang(dianwifi)去掉snmp配置页面*/
				{
					write_to_second_br("snmp", "snmp_id","SNMP Config");
				}
			}
			else
			{ 
				write_to_second_br("tr69c", "tr69c_id", "Remote Management");		
			}
			write_to_second_div("wifidog", "wifidog_id", "Hotspot Config");
			/* 网络配置 */
			write_to_stari_div("net_setup_id1", "javascript:void(0)", "net_setup_id1", "Network Setup");
			write_to_stari_br("net_setup_id2", "javascript:void(0)", "net_setup_id2", "Network Setup");
			if ("1" == have_multiwan){
				write_to_second_br("wan1", "wan_id", "WAN");
			}
			else{
 				write_to_second_br("ipv4", "ipv4_id", "WAN");
 			}
      write_to_second_br("lan", "lan_id", "LAN");  
			if("1" == have_dns_mapping)
                        {
                                write_to_second_br("dns_mapping", "dns_mapping_id", "DNS Mapping");
                        }  
			//write_to_second_br("ethernet", "ethernet_id", "WAN");
			write_to_second_br("forward_mode", "forward_mode_id", "Forward Mode");
			if ("1" == have_wxflow){
				write_to_second_br("wx_follow", "wx_follow_id", "Weixin Scan");
			}
			write_to_second_br("network_route_show", "network_route_config_id","Route Config");
			if ("1" == have_portmap){
				write_to_second_br("network_portmap_show", "network_portmap_config_id","PortMap Config");
			}
			if ("1" == have_portconf){
				write_to_second_br("portconf", "portconf_id","PortConf Config");
			}
			write_to_second_br("vpn_pass", "vpn_pass_id","VPN  Pass Through");
			write_to_second_div("dhcp_server", "dhcp_server_id", "DHCP Server");
			//write_to_second_br("pppoe_client", "pppoe_client_id", "PPPoE");
			//write_to_second_div("net_advanced", "net_advanced_id", "Network Advanced");

			/*LTE配置*/
			if ("1" == lte_support)
			{
					write_to_stari_div("lte_setup_id1", "javascript:void(0)", "lte_setup_id1", "LTE Setup");
					write_to_stari_br("lte_setup_id2", "javascript:void(0)", "lte_setup_id2", "LTE Setup");
					write_to_second_br("lte_basic_page", "lte_basic_config_id", "Basic Settinh");
					write_to_second_div("lte_access_page", "lte_access_config_id", "Advanced Setting");
			}
			/* 无线配置 */
      if ("3" != dev_type)
      { 
    			write_to_stari_div("wifi_setup_id1", "javascript:void(0)", "wifi_setup_id1", "Wi-Fi");
    			write_to_stari_br("wifi_setup_id2", "javascript:void(0)", "wifi_setup_id2", "Wi-Fi");
    			if("0" == dev_type)
    			{
    				write_to_second_div("wifi_mode&wifi_id=0", "wifi1_id", "Wi-Fi 2.4GHz(1)");
    			}
    			else
    			{
    				write_to_second_br("wifi_mode&wifi_id=0", "wifi1_id", "Wi-Fi 2.4GHz(1)");
    				write_to_second_div("wifi_mode&wifi_id=1", "wifi2_id", "Wi-Fi 5GHz(2)");
    			}
    			write_to_stari_div("ssid_id1", "javascript:void(0)", "ssid_id1", "SSID");
    			write_to_stari_br("ssid_id2", "javascript:void(0)", "ssid_id2", "SSID");
    			write_to_second_div("vap", "ssid_id", "SSID");
      }
      else
      {
 					write_to_stari_div("ssid_id1", "javascript:void(0)", "ssid_id1", "SSID");
    			write_to_stari_br("ssid_id2", "javascript:void(0)", "ssid_id2", "SSID");
    			write_to_second_div("ssid_x86", "ssid_x86_id", "SSID");
 	    }

			/* vlan */
			write_to_stari_div("vlan_id1", "javascript:void(0)", "vlan_id1", "VLAN");
			write_to_stari_br("vlan_id2", "javascript:void(0)", "vlan_id2", "VLAN");
			if ("1" == have_lan_port)
      {
				write_to_second_br("vlan_mapping", "vlan_mapping_id", "VLAN Mapping");
				write_to_second_div("vlan_fc", "vlan_fc_id", "VLAN Flow Control");
			}
			else
			{ 
				write_to_second_div("vlan_mapping", "vlan_mapping_id", "VLAN Mapping");
			}

			/* snmp 配置 
			write_to_stari_div("snmp_id1", "javascript:void(0)", "snmp_id1", "SNMP");
			write_to_stari_br("snmp_id2", "javascript:void(0)", "snmp_id2", "SNMP");
			write_to_second_div("snmp", "snmp_id", "SNMP V2");
			*/
			/* 广告配置 */
			if ("1" == have_advertisement){
				write_to_stari_div("advertisement_id1", "javascript:void(0)", "advertisement_id1", "Advertisement");
				write_to_stari_br("advertisement_id2", "javascript:void(0)", "advertisement_id2", "Advertisement");
				write_to_second_div("advertisement", "advertisement_id", "Basic Config");
			}
			
			/* 网络安全配置 */
			write_to_stari_div("network_security_id1", "javascript:void(0)", "network_security_id1", "Network Security");
			write_to_stari_br("network_security_id2", "javascript:void(0)", "network_security_id2", "Network Security");
			if ("1" == have_attack_defense)
			{
				write_to_second_br("attack_defense", "attack_defense_id", "Attack Defense");
			} 
			if ("1" == have_netsniff) 
			{
				write_to_second_br("netsniff", "netsniff_id", "Net Monitor"); 
			}
        if ("1" == have_transit) {
            write_to_second_br_pl("transit", "transit_id", "Transit", parseInt(language));
        }


			if ("1" == have_audit)
			{
				write_to_second_div("audit_server", "audit_server_id", "Audit");
			}
            else
            {
				insert_one_line_div();
			}
			
			/* 访问控制配置 */
			if("vtache" != oem_company)  
			{
				if ("1" == have_access_control)
				{
					write_to_stari_div("access_control_id1", "javascript:void(0)", "access_control_id1", "Access Control");
					write_to_stari_br("access_control_id2", "javascript:void(0)", "access_control_id2", "Access Control");
					if("0" == have_wifidog_open)
					{
						write_to_second_br("freeauth_mac_show", "freeauth_mac_config_id","STA Free Auth");
						write_to_second_br("flowctrl_sta_show", "flowctrl_sta_config_id","STA Flow Control");
					}
					write_to_second_br("qos","qos_id","QOS");
					write_to_second_br("fraud_site_show","fraud_site_config_id","fraud filter");
					write_to_second_div("other_access_control", "other_access_control_id", "Other Control");
				} 
			}
			
			/*信息采集*/
			if("dianwifi" != oem_company)/*2015-3-3 dianwifi(wangang)不要显示信息采集*/
			{
				if ("3" != dev_type)
				{
					write_to_stari_div("info_collect_id1", "javascript:void(0)", "info_collect_id1", "Info Collect");
					write_to_stari_br("info_collect_id2", "javascript:void(0)", "info_collect_id2", "Info Collect");
			
					write_to_second_br("info_collect", "info_collect_id", "Basic config");
					write_to_second_br("info_audit", "info_audit_id", "Place information");
					write_to_second_br("info_advanced", "info_advanced_id", "Advanced config");
					write_to_second_div("locator_status", "locator_status_id", "Status display");		
				}
			}

			/* system */
			write_to_stari_div("sys_id1", "javascript:void(0)", "sys_id1", "System Setup");
			write_to_stari_br("sys_id2", "javascript:void(0)", "sys_id2", "System Setup");
			write_to_second_br("time", "time_id", "Time Setting");
			write_to_second_br("restore", "restore_id", "Restore Default");
			write_to_second_br("software_update", "software_update_id", "Software Update");
			write_to_second_br("dev_reboot", "dev_reboot_id", "Reboot");
			write_to_second_br("timed_task", "timed_task_id", "Regular tasks");
			if ("1" == have_l2tp) 
			{
				//write_to_second_br("vpn_l2tp", "vpn_l2tp_id", "VPN");
			}
			write_to_second_br("local_cmd","local_cmd_id","Local Cmd");
			write_to_second_br("http_port", "http_port_id", "Http Port");
			write_to_second_br("users", "users_id", "Account");

			if("3" == dev_type)
			{
				write_to_second_br("mast_backup","mast_back_id","Master Backup");
			}
			
		  write_second_satri_div("function_debug_id1", "javascript:void(0)", "function_debug_id1", "Debug");
			write_second_satri_br("function_debug_id2", "javascript:void(0)", "function_debug_id2", "Debug");
			write_to_third_br("debug_collect", "debug_collect_id", "Debug Collect");
			write_to_third_br("net_diagnose", "net_diagnose_id", "Net Diagnose");
			write_to_third_br("log", "log_id", "LOG Output");
			write_to_third_br("log_upload", "log_upload_id", "LOG Upload");
			write_to_third_div("authorize_control", "authorize_control_id", "Authorize Control");
			
			insert_one_line_div();
			
			/* dny info */
			write_to_stari_div("dny_info_id1", "javascript:void(0)", "dny_info_id1", "Dynamic Info");
			write_to_stari_br("dny_info_id2", "javascript:void(0)", "dny_info_id2", "Dynamic Info");
			write_to_second_br("flow_statistics", "flow_statistics_id", "Flow statistics");
			if("1" == lte_support)
			{
				write_to_second_br("sta_info&wifi_id=0", "client_info_id", "Client Info");
				write_to_second_div("sysinfo_lte_page", "sysinfo_lte_show_id", "LTE Stat");
			}
			else
			{
				write_to_second_div("sta_info&wifi_id=0", "client_info_id", "Client Info");
			}
			
			//write_to_second_br("ssid_scan&wifi_id=0", "ssid_scan_id", "Interference Info");
			//write_to_second_div("rogue_ap&wifi_id=0", "rogue_ap_id", "Rogue AP");

            /* help */
			//document.write('<div id="help_id"><img src="/plus.png"><a href="/help.html">online help</a></div>');
            
			/* logout */
			document.write('<div id="logout_id"><img src="/plus.png"><a href="/cgi-bin/snmpManager.cgi?cgimodule=logout">Logout</a></div>');
			break;
		default:
			//document.write('亲, @@ 设备出故障啦....');
			break;
	}
}

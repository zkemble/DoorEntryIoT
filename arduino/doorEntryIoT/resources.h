/*
 * Project: Door Entry IoT
 * Author: Zak Kemble, contact@zakkemble.net
 * Copyright: (C) 2022 by Zak Kemble
 * License: 
 * Web: https://blog.zakkemble.net/iot-and-a-door-entry-system/
 */

const char html_home[] PROGMEM = "\
<!DOCTYPE html>\
<html lang=\"en\">\
<head>\
<title>Door Entry</title>\
<link rel=\"shortcut icon\" href=\"/favicon.ico\" type=\"image/x-icon\" />\
<meta http-equiv=\"Content-type\" content=\"text/html; charset=UTF-8\" />\
<style>\
body { text-align: center; background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
button { width: 200px; height: 50px; cursor: pointer; }\
table { margin-left: auto; margin-right: auto; text-align: left; width:300px; background-color: #e0e0f0; }\
tr:nth-child(odd) { background-color: #f2f2f2; }\
</style>\
</head>\
<body>\
<script type=\"text/javascript\">\
function unlock(btn)\
{\
	btn.innerText = \"...\";\
	var ajaxReq = window.XMLHttpRequest ? new XMLHttpRequest() : new ActiveXObject(\"Microsoft.XMLHTTP\");\
	ajaxReq.onreadystatechange = function(){\
		if(this.readyState == 4)\
			btn.innerText = \"Unlock\";\
	};\
	ajaxReq.open(\"GET\",\"/unlock?duration=\" + document.getElementById(\"duration\").value + \"&\" + new Date().getTime(),true);\
	/*if(type == \"POST\")\
		ajaxReq.setRequestHeader(\"Content-Type\",\"application/x-www-form-urlencoded\");*/\
	ajaxReq.send();\
}\
</script>\
<h1>Door Entry</h1>\
<p>\
<input type=\"number\" id=\"duration\" name=\"quantity\" min=\"1\" max=\"15000\" value=\"500\">\
<br /><br />\
<button onclick=\"unlock(this)\" type=\"button\">Unlock</button>\
</p>\
<p>\
<table style=\"white-space:nowrap\">\
<tr><td>Uptime</td><td>%u days, %u hours, %u mins (%llu ms)</td></tr>\
<tr><td>Session ID</td><td>%s</td></tr>\
<tr><td>WiFi conns</td><td>%u (Reason: %u)</td></tr>\
<tr><td>WebSocket conns</td><td>%u</td></tr>\
<tr><td>Rings</td><td>%u</td></tr>\
<tr><td>Unlocks</td><td>%u</td></tr>\
<tr><td>Neighbour</td><td>%u</td></tr>\
<tr><td>Stuck</td><td>%u</td></tr>\
<tr><td>IP</td><td>%s</td></tr>\
<tr><td>Subnet</td><td>%s</td></tr>\
<tr><td>Gateway</td><td>%s</td></tr>\
<tr><td>DNS1</td><td>%s</td></tr>\
<tr><td>DNS2</td><td>%s</td></tr>\
<tr><td>Hostname</td><td>%s</td></tr>\
<tr><td>MAC</td><td>%s</td></tr>\
<tr><td>SSID</td><td>%s</td></tr>\
<tr><td>BSSID</td><td>%s</td></tr>\
<tr><td>Channel</td><td>%d</td></tr>\
<tr><td>RSSI</td><td>%ddBi</td></tr>\
<tr><td>Temperature</td><td>%.2f&deg;C</td></tr>\
<tr><td>Humidity</td><td>%.2f%%</td></tr>\
</table>\
</p>\
<p>\
<a href=\"/update\">Update firmware</a>\
</p>\
<p>\
%s, %s\
</p>\
</body>\
</html>\
";

const uint8_t favicon[] PROGMEM = {
	0x00,0x00,0x01,0x00,0x01,0x00,0x10,0x10,0x00,0x00,0x01,0x00,0x20,0x00,0x68,0x04,0x00,0x00,0x16,0x00,
	0x00,0x00,0x28,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x01,0x00,0x20,0x00,0x00,0x00,
	0x00,0x00,0x40,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,
	0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,
	0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,
	0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,
	0xff,0x00,0xff,0xff,0xff,0x00,0xe6,0xe6,0xe6,0x13,0x94,0x94,0x94,0x75,0x73,0x73,0x73,0x9b,0x7b,0x7b,
	0x7b,0x91,0x73,0x73,0x73,0x9b,0x7b,0x7b,0x7b,0x91,0xde,0xde,0xde,0x1d,0xff,0xff,0xff,0x00,0xff,0xff,
	0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,
	0xff,0x00,0xff,0xff,0xff,0x00,0xb5,0xb5,0xb5,0x4c,0x4a,0x4a,0x4a,0xcb,0x3a,0x3a,0x3a,0xff,0x52,0x52,
	0x52,0xff,0x52,0x52,0x52,0xff,0x52,0x52,0x52,0xff,0x42,0x42,0x42,0xff,0x4a,0x4a,0x4a,0xcb,0xe6,0xe6,
	0xe6,0x13,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,
	0xff,0x00,0xef,0xef,0xef,0x07,0x8c,0x8c,0x8c,0x7e,0x29,0x29,0x29,0xf3,0x7b,0x7b,0x7b,0xff,0xe6,0xe6,
	0xe6,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7b,0x7b,
	0x7b,0xff,0x73,0x73,0x73,0x9b,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,
	0xff,0x00,0xff,0xff,0xff,0x00,0x5a,0x5a,0x5a,0xb8,0x3a,0x3a,0x3a,0xff,0xce,0xce,0xce,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xef,0xef,0xef,0xff,0x9c,0x9c,0x9c,0xff,0x8c,0x8c,0x8c,0xff,0xef,0xef,
	0xef,0xff,0xef,0xef,0xef,0xff,0x42,0x42,0x42,0xd4,0xd6,0xd6,0xd6,0x26,0xff,0xff,0xff,0x00,0xff,0xff,
	0xff,0x00,0xff,0xff,0xff,0x00,0xa5,0xa5,0xa5,0x5f,0x52,0x52,0x52,0xc1,0xde,0xde,0xde,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xce,0xce,0xce,0xff,0x3a,0x3a,0x3a,0xff,0x19,0x19,0x19,0xff,0x21,0x21,
	0x21,0xff,0x84,0x84,0x84,0xff,0xff,0xff,0xff,0xff,0x9c,0x9c,0x9c,0xff,0x73,0x6b,0x6b,0xa4,0xff,0xff,
	0xff,0x00,0xff,0xff,0xff,0x00,0xe6,0xe6,0xe6,0x13,0x52,0x52,0x52,0xc1,0xde,0xde,0xde,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xd6,0xd6,0xd6,0xff,0x3a,0x3a,0x3a,0xff,0x6b,0x6b,0x6b,0xff,0xbd,0xbd,
	0xbd,0xff,0x31,0x31,0x31,0xff,0x31,0x31,0x31,0xff,0xef,0xef,0xef,0xff,0xbd,0xbd,0xbd,0xff,0x6b,0x6b,
	0x6b,0xa4,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xc5,0xc5,0xc5,0xff,0x63,0x63,0x63,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xf7,0xf7,0xf7,0xff,0x52,0x52,0x52,0xff,0x08,0x08,0x00,0xff,0xa5,0xa5,
	0xa5,0xff,0x63,0x63,0x63,0xff,0x42,0x42,0x3a,0xff,0x9c,0x9c,0x94,0xff,0xf7,0xf7,0xf7,0xff,0xa5,0xa5,
	0xa5,0xff,0x7b,0x7b,0x7b,0x91,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xef,0xef,0xef,0x07,0x5a,0x5a,
	0x5a,0xb8,0xc5,0xc5,0xc5,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf7,0xff,0x9c,0x9c,0x94,0xff,0x4a,0x4a,
	0x4a,0xff,0x29,0x29,0x29,0xff,0x42,0x42,0x42,0xff,0xc5,0xc5,0xd6,0xff,0xde,0xde,0xff,0xff,0xef,0xef,
	0xf7,0xff,0x63,0x63,0x5a,0xff,0xce,0xce,0xce,0x30,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,
	0xff,0x00,0xbd,0xbd,0xbd,0x43,0x4a,0x4a,0x4a,0xcb,0xf7,0xf7,0xef,0xff,0xde,0xde,0xf7,0xff,0x5a,0x63,
	0xde,0xff,0x9c,0x9c,0xde,0xff,0xde,0xde,0xde,0xff,0xe6,0xe6,0xef,0xff,0x5a,0x5a,0xe6,0xff,0x21,0x21,
	0xd6,0xff,0x94,0x94,0xbd,0xff,0x63,0x63,0x5a,0xb8,0xf7,0xef,0xef,0x07,0xff,0xff,0xff,0x00,0xff,0xff,
	0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0x6b,0x6b,0x6b,0xa4,0x8c,0x8c,0x84,0xff,0xd6,0xd6,
	0xff,0xff,0x29,0x29,0xd6,0xff,0x42,0x42,0xd6,0xff,0xf7,0xf7,0xff,0xff,0xff,0xff,0xff,0xff,0xad,0xa5,
	0xf7,0xff,0x84,0x84,0xde,0xff,0x4a,0x52,0x5a,0xcb,0xa5,0xa5,0x9c,0x6b,0xff,0xff,0xff,0x00,0xff,0xff,
	0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xe6,0xe6,0xe6,0x13,0x3a,0x3a,
	0x3a,0xde,0xad,0xad,0xad,0xff,0xef,0xef,0xff,0xff,0xde,0xe6,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xce,0xce,0xc5,0xff,0x52,0x52,0x42,0xff,0x5a,0x5a,0x52,0xc1,0xff,0xff,0xff,0x00,0xff,0xff,
	0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,
	0xff,0x00,0xde,0xde,0xd6,0x26,0x4a,0x4a,0x4a,0xcb,0xa5,0xa5,0x9c,0xff,0xce,0xce,0xc5,0xff,0x94,0x94,
	0x94,0xff,0x63,0x63,0x63,0xff,0x21,0x21,0x21,0xfd,0x73,0x73,0x73,0x9b,0xe6,0xe6,0xe6,0x13,0xff,0xff,
	0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,
	0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0x7b,0x7b,0x7b,0x91,0x00,0x00,0x00,0xff,0x19,0x19,
	0x19,0xff,0x29,0x29,0x29,0xf3,0x6b,0x6b,0x6b,0xa4,0xce,0xce,0xce,0x30,0xff,0xff,0xff,0x00,0xff,0xff,
	0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,
	0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xc5,0xc5,0xc5,0x39,0x7b,0x7b,
	0x7b,0x91,0x94,0x94,0x8c,0x7e,0xef,0xef,0xef,0x07,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,
	0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,
	0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,
	0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,
	0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,
	0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xff,0x00,0x00,0xf8,0x0f,0x00,0x00,0xf0,0x07,0x00,0x00,0xc0,0x07,
	0x00,0x00,0xc0,0x03,0x00,0x00,0x80,0x03,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x03,
	0x00,0x00,0x80,0x03,0x00,0x00,0xc0,0x07,0x00,0x00,0xc0,0x0f,0x00,0x00,0xe0,0x0f,0x00,0x00,0xf0,0x3f,
	0x00,0x00,0xf0,0xff,0x00,0x00,0xff,0xff,0x00,0x00
 };
 
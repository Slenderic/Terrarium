"use strict";

var websocket;
var ipEsp = "ws://192.168.4.1";
var debug = true;
var command = 1;
var scedual = [6, 16];

// other commands
var COMMAND_SET_INITIAL_VALUES = 20;
var COMMAND_SET_TIME = 30;
var COMMAND_SET_LDR = 91;
var COMMAND_SET_HOSTNAMW = 92;
var COMMAND_SET_TIMESERVER = 93;
var COMMAND_SET_WIFI_AND_RESTART = 94;

var COMMAND_RESET = 100;
var COMMAND_REQUEST_CONFIG_VALUES = 300;
var COMMAND_REQUEST_WIFI_LIST = 301;

// data that gets sent back to the esp
var DATA_SSID_TEXT_LENGTH = 25;
var DATA_PASSWORT_TEXT_LENGTH = 25;
var DATA_TIMESERVER_TEXT_LENGTH = 16;
var DATA_HOST_TEXT_LENGTH = 16;

function initConfigValues(){
    var locationHost = location.host;
    if(locationHost !== ""){
        ipESP =  "ws://" + locationHost;
    } else {
        ipEsp = "ws://192.168.4.1";
    }
    debug = true;
    var scedual = [6, 16];
}

/**
 * Displays a debug message, if the global debug flag is set to true. Optionally
 * an object can be provided that will be printed on the console (when a console
 * is available).
 */
/* eslint-disable no-console */
function debugMessage(debugMessage, someObject) {
	if (debug === true) {

		if (console !== undefined) {
			console.log(debugMessage);

			if (someObject) {
				console.log(someObject);
			}
		}

		$("#output").fill(debugMessage);
	}
}

function initWebsocket(){
    websocket = new WebSocket(ipEsp);
    websocket.onopen = function(event) {
        $("#status").set("+online");
        $("#status").set("+offline");
		$("#status").set("@value", "Online");
		$(".status-button").fill("Cut connection");
		$(".status-button").set("@value", "1");
		$("#section-connection-lost").set({
			$display: "none"
		});

		debugMessage("Connection with the websocket achieved.", event);

		sendData(301, 0, 0);
	};
    websocket.onclose = function(event) {

		$("#status").set("-online");
		$("#status").set("+offline");
		$("#status").set("@value", "Offline");
		$(".status-button").fill("Verbinden");
		$(".status-button").set("@value", "0");
		$("#section-connection-lost").set({
			$display: "block"
		});

		debugMessage("Die Verbindung mit dem Websocket wurde geschlossen (Code " + event.code + ").", event);
	};

	websocket.onmessage = function(event) {

		var data = JSON.parse(event.data);

		debugMessage("Webservice response arrived (Command " + data.command + ").", data);

		if (data.command === "config") {

			$("#ssid").set("value", data.ssid);

			$("#timeserver").set("value", data.zeitserver);
			$("#hostname").set("value", data.hostname);
			$("#marquee").set("value", data.ltext);
            
			$("#showSeconds").set("value", data.zeige_sek);
			$("#showMinutes").set("value", data.zeige_min);

			$("#owm-api-key").set("value", data.apiKey);
			$("#owm-city-id").set("value", data.cityid);
		}
		if (data.command === "set") {
            scedual = data.scedual;
		}
	};
	websocket.onerror = function(event) {
		debugMessage("Bei der Verbindung mit dem Websocket ist ein Fehler aufgetreten.", event);
	};
}

/**
 * Add '0' as a padding in front of the number to make it 
 * a 3 character string.
 * 
 * @param  {int} number - The number to be padded.
 * @return {string} The padded number.
 */
function nstr(number) {
	if (number < 10) {
		number = "00" + number;
	} else {
		if (number < 100) {
			number = "0" + number;
		}
	}
	return number;
}

/**
 * Sends data to the esp via a websocket connection.
 * 
 * @param  {int} The command that specifies what to do on the esp.
 * @param  {int} An unknown parameter.
 * @param  {int} An unknown parameter.
 */
function sendData(command, unknown2, unknown3) {
	var data = nstr(command) +
		nstr(unknown2) +
		nstr(unknown3) +
		nstr(scedual) + + "999";

	websocket.send(data);
	debugMessage("Send data: ", data);
}

$.ready(function(){
    initConfigValues();
    $(".status-button").on("click", function() {
		var value = $(this).get("value");
		if (value === "1") {
			value = 0;
			$("#status").fill("Verbinden ...");
			$(".status-button").set("value", value);
			websocket.close();
		} else {
			value = 1;
			$("#status").fill("Verbinden ...");
			$(".status-button").set("value", value);
			initWebsocket();
		}
		return false;
	});

	/**
	 * A menu item has been clicked.
	 */
    $("a[class~='pure-menu-link']").on("click", function() {
		var navigation = $(this)[0].dataset.navigation;

		// add/remove active class
		$(".pure-menu-link").set("-active");
		$(this).set("+active");

		if (navigation === "settings") {
			sendData(COMMAND_REQUEST_CONFIG_VALUES, 0, 0);
		}

		// show/hide sections
		$(".section").set({
			$display: "none"
		});
		$(".section-" + navigation).set({
			$display: "block"
		});
	});
});
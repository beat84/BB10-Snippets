import bb 1.0
import bb.cascades 1.0
import bb.system 1.0
import bb.display 1.0

Page{
    property string account: "UA-XXXXXX-XX" //your Google Analytics account
    property string trackerUUID: _app.trackerUUID()

    function trackNow(trackval, category, action) { //category and action are for event only
        if(trackerUUID==""){
            console.log("!!! Tracker not initialized");
            return false;
        }
        var data = "v=1"; //for more information about data start from here: https://developers.google.com/analytics/devguides/collection/protocol/v1/devguide
        data = data + "&tid=" + account;
        data = data + "&cid=" + trackerUUID;
        data = data + "&an=" + appInfo.title;
        data = data + "&sr=" + dispInfo.pixelSize.width + "x"+ dispInfo.pixelSize.height;
        data = data + "&cd=" + trackval;
        if(typeof(category)!="undefined" && typeof (action) != "undefined"){
            data = data + "&t=event";
            data = data + "&ec=" + category;
            data = data + "&ea=" + action;

        }else{
            data = data + "&av=" + appInfo.version;
            data = data + "&t=appview";

        }
        data = encodeURIComponent(data);
        var request = new XMLHttpRequest()
	    request.onreadystatechange = function() {
	        if (request.readyState == 4) {
	            var response = request.responseText
                console.log("!!! Tracking "+data+": " + response); //usually is a GIF
	        }
	    }
	
	    request.open("POST", "http://www.google-analytics.com/collect", true);
	    request.send(data);
	    return true;
	}
    onCreationCompleted:{
        console.log("!!! Tracker initialized!");
        trackNow("Start"); //first tracking
    }
    attachedObjects: [
        ApplicationInfo {
            id: appInfo
        },
        DisplayInfo{
            id: dispInfo
        }
    ]
}
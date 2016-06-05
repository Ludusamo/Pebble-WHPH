var WORK = 0, PLAY = 1;

function createSession(start, end, tag) {
	var session = new Object();
	session.start = start;
	session.end = end;
	session.tag = tag;
	return session;
}

function calcTotalTime(timeArr) {
	var totalTime = 0;
	if (timeArr) {
		for (var i = 0; i < timeArr.length; i++) {
			totalTime += timeArr[i].end - timeArr[i].start;
		}
	}
	return totalTime;
}

Pebble.addEventListener('ready', function() {
	console.log('PebbleKit JS Ready!');
});

Pebble.addEventListener('appmessage', function(e) {

});

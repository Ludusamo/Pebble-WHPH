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
	var dict = e.payload;
	console.log('Got message: ' + JSON.stringify(dict));
	var mode = dict['TYPE'];
	switch (mode) {
	case WORK:
		var work = JSON.parse(localStorage.getItem('work'));
		if (!work) work = [];
		var session = createSession(dict['TIME_START'], dict['TIME_STOP'], dict['TAG']);
		work.push(session);
		localStorage.setItem('work', JSON.stringify(work));
		break;
	case PLAY:
		var play = JSON.parse(localStorage.getItem('play'));
		if (!play) play = [];
		var session = createSession(dict['TIME_START'], dict['TIME_STOP'], dict['TAG']);
		play.push(session);
		localStorage.setItem('play', JSON.stringify(play));
		break;
	case 2:
		var work = JSON.parse(localStorage.getItem('work'));
		var play = JSON.parse(localStorage.getItem('play'));
		var dict = {
			'TIME_START': calcTotalTime(work),
			'TIME_STOP': calcTotalTime(play)
		};
		Pebble.sendAppMessage(dict, function() {
			console.log('Message sent successfully: ' + JSON.stringify(dict));
		}, function(e) {
			console.log('Message failed: ' + JSON.stringify(e));
		});
		break;
	case 3:
		localStorage.removeItem('work');
		localStorage.removeItem('play');
		break;
	}
});

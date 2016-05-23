var WORK = 0, PLAY = 1;

function createSession(start, end, tag) {
	var session = new Object();
	session.start = start;
	session.end = end;
	session.tag = tag;
	return session;
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
		var play = localStorage.getItem('play');
		if (!play) play = [];
		var session = createSession(dict['TIME_START'], dict['TIME_STOP'], dict['TAG']);
		play.push(session);
		localStorage.setItem('play', JSON.stringify(play));
		break;
	}
});

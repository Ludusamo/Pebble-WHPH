all:
	pebble build
	pebble install --emulator aplite 
	pebble install --emulator basalt 
	pebble install --emulator chalk 

clean:
	rm -rf build

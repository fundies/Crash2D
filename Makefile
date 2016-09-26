.PHONY: all lib tests demo coverage clean

all: lib
	make -j3 -C tests
	make -j3 -C demo
	./Collision_Test &
	sleep 1
	lcov --directory . --capture --output-file app.info --no-external
	genhtml --output-directory cov_html app.info
	
lib:
	make -j 3 -C library

tests: lib
	make -j3 -C tests
	
demo: lib
	make -j3 -C demo
	
coverage: lib tests
	./Collision_Test &
	sleep 1
	lcov --directory . --capture --output-file app.info --no-external
	genhtml --output-directory cov_html app.info
	
clean:
	find . -name "app.info" -exec rm {} \;
	rm -rf cov_html
	make -C library clean
	make -C tests clean
	make -C demo clean
	



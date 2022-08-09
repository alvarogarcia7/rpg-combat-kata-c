install: install-githooks install-dependencies
.PHONY: install

install-githooks:
	cp githooks/* .git/hooks
.PHONY: install-githooks

.PHONY: test
test: build
	@echo "Make test"
	$(MAKE) -Ccmake-build-debug unit_tests
	@echo "Execute tests (with more debug information)"
	./cmake-build-debug/tests/unit_tests

build:
	cmake -Bcmake-build-debug .
	$(MAKE) -Ccmake-build-debug all

install-dependencies:
	mkdir cmake-build-debug || true
	cmake -Bcmake-build-debug .
	cmake -B cmake-build-debug -DCMAKE_BUILD_TYPE=Debug cmake-build-debug
	$(MAKE) -Ccmake-build-debug all
.PHONY: install-dependencies

prepare-mark-start:
	@echo "This is a manual goal. Paste what's on the copy-paste buffer"
	@echo 'f cc "Time-Marker: start" --allow-empty' | pbcopy

prepare-mark-end:
	@echo "This is a manual goal. Paste what's on the copy-paste buffer"
	@echo 'f cc "Time-Marker: end" --allow-empty' | pbcopy

pre-commit: build test

pre-push:
	echo "pre-push: No Op"
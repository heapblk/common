RELEASE_DIR := cmake-build-release
DEBUG_DIR := cmake-build-debug

.PHONY: build

build: 
	mkdir -p $(RELEASE_DIR) && cd $(RELEASE_DIR) && cmake -G Ninja .. -DCMAKE_BUILD_TYPE=Release && ninja
	mkdir -p $(DEBUG_DIR) && cd $(DEBUG_DIR) && cmake -G Ninja .. -DCMAKE_BUILD_TYPE=Debug && ninja

clean:
	rm -rf $(RELEASE_DIR) $(DEBUG_DIR)

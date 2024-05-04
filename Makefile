# Author: Samuel Hejnicek
# Used to build the project using CMake make doxygen doc and clean the project

BUILD_DIR := build
PROJ_NAME := EpicRobotSurvival

all: $(BUILD_DIR) $(PROJ_NAME)

# Create the build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $@

# Build the project using CMake
$(PROJ_NAME): $(BUILD_DIR) 
	cd $(BUILD_DIR) && cmake ..
	cd $(BUILD_DIR) && make 
	cp $(BUILD_DIR)/$(PROJ_NAME) . 

run: all
	./$(PROJ_NAME)
	
pack:
	zip xeffenn00_xhejni00.zip -r src/ examples/ images/ Orbitron/ CMakeLists.txt Makefile

clean:
	rm -rf $(BUILD_DIR) && rm $(PROJ_NAME)
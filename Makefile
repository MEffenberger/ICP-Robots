# Author: Samuel Hejnicek
# Used to build the project using CMake make doxygen doc and clean the project

BUILD_DIR := build
PROJ_NAME := EpicRobotSurvival

all: $(PROJ_NAME)

# Create build folder if not present
$(BUILD_DIR):
	mkdir -p $@

# Run CMake and make to build the project
$(PROJ_NAME): $(BUILD_DIR) 
	cd $(BUILD_DIR) && cmake ..
	cd $(BUILD_DIR) && make 
	cp $(BUILD_DIR)/$(PROJ_NAME) . 

run: all
	./$(PROJ_NAME)
	
pack:
	zip xeffenn00_xhejni00.zip -r src/ examples/ images/ Orbitron/ CMakeLists.txt Makefile

doxygen:
	cd src && doxygen Doxyfile

clean:
	rm -rf $(BUILD_DIR) && rm $(PROJ_NAME)
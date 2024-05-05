# Author: Samuel Hejnicek
# Used to build the project using CMake make doxygen doc and clean the project

SRC_DIR := src
DOC_DIR := doc
BUILD_DIR := build
PROJ_NAME := EpicRobotSurvival

all: $(PROJ_NAME)

# Create build folder if not present
$(BUILD_DIR):
	mkdir -p $@

# Run CMake and make to build the project
$(PROJ_NAME): $(BUILD_DIR) 
	cd $(BUILD_DIR) && cmake .. && make
	cp $(BUILD_DIR)/$(PROJ_NAME) . 

run: all
	./$(PROJ_NAME)
	
pack:
	zip xeffen00_xhejni00.zip -r src/ examples/ images/ Orbitron/ readme_images/ README.txt CMakeLists.txt Makefile technickeinfo.pdf

doxygen: $(DOC_DIR)
	cd $(SRC_DIR) && doxygen Doxyfile

# Create doc folder if not present
$(DOC_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR) && rm -f $(PROJ_NAME) && rm -rf $(DOC_DIR)
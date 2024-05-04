BUILD_DIR := build
BIN_NAME := ICP  # Adjust the name of your binary

all: $(BUILD_DIR) $(BIN_NAME)

# Create the build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $@

# Build the project using CMake
$(BIN_NAME): $(BUILD_DIR) 
	cd $(BUILD_DIR) && cmake ..
	cd $(BUILD_DIR) && make 
	cp $(BUILD_DIR)/$(BIN_NAME) . 
	

# Move the binary to the root folder
.PHONY: clean install

clean:
	rm -rf $(BUILD_DIR) && rm ICP

install: 
	cp $(BUILD_DIR)/$(BIN_NAME) . 

BUILD_DIR := build
INC_FLAGS += -I=/usr/include/opencv4
CPP_SRCS := $(shell find . -name "*.cpp")
OBJS = $(patsubst ./src/%.cpp,$(BUILD_DIR)/%.cpp.o,$(CPP_SRCS))
CPP_BIN := image_grabber
LDLIBS += -lopencv_videoio -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lopencv_core -lpthread -lzbar -lz -ldl
CPPFLAGS += -g

all: folder $(CPP_BIN) 

$(BUILD_DIR)/%.cpp.o: src/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(INC_FLAGS) $(CPPDEFS) -c $< -o $@


$(CPP_BIN): $(OBJS) 
	$(CXX) -o $(BUILD_DIR)/$@ $(CPPFLAGS) $(CXXFLAGS) $(INC_FLAGS) $(CPPDEFS) $(LDFLAGS) $^  $(LDLIBS) 

folder:
	mkdir -p $(BUILD_DIR)


.PHONY:clean 

clean:
	-rm $(BUILD_DIR)/*.o
	-rm $(BUILD_DIR)/$(CPP_BIN)

GENERATED_CODE_DIR        := SingleColumn_CODE
CXXFLAGS                  += -std=c++11 -Wall -Wpedantic -Wextra

.PHONY: all clean generated_code

OBJS                      := SingleColumnSim.o RecordFunc.o

all: SingleColumn

SingleColumn: $(OBJS) generated_code
	$(CXX) $(CXXFLAGS) $(OBJS) -o SingleColumn -L$(GENERATED_CODE_DIR) -lrunner -Wl,-rpath $(GENERATED_CODE_DIR)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

generated_code:
	$(MAKE) -C $(GENERATED_CODE_DIR)

clean:
	$(MAKE) -C $(GENERATED_CODE_DIR) clean
	rm -f $(OBJS) SingleColumn

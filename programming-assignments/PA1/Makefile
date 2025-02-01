# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -Wall -Wextra -std=c++17

# Source files
SRC := main.cpp \
       wrapper/application_wrapper.cpp \
       file_readers/gene_sequence_reader.cpp \
       file_readers/alignment_parameters_reader.cpp \
       pairwise_sequence_alignment/pairwise_sequence_alignment.cpp

# Output executable
OUTPUT := exe

# Default rule
all: $(OUTPUT)

# Compile the executable
$(OUTPUT): $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Clean rule
clean:
	rm -f $(OUTPUT)

run: $(OUTPUT)
	if [ -f $(OUTPUT) ]; then ./$(OUTPUT) sample_inputs/Human-Mouse-BRCA2-cds.fasta 0 parameters.config; fi
# Compiler
CXX := g++

CXXFLAGS := -Wall -Wextra -std=c++17

SRC := main.cpp

# Output executable name
OUTPUT := exe

# Default rule
all: $(OUTPUT)

# Compile the executable
$(OUTPUT): $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Remove executable
clean:
	rm -f $(OUTPUT)

# Global test cases
run-human-mouse-global: $(OUTPUT)
	if [ -f $(OUTPUT) ]; then ./$(OUTPUT) sample_inputs/Human-Mouse-BRCA2-cds.fasta 0 parameters.config; fi

run-color-blindness-global: $(OUTPUT)
	if [ -f $(OUTPUT) ]; then ./$(OUTPUT) sample_inputs/Opsin1_colorblindness_gene.fasta 0 parameters.config; fi

run-known-sample-global: $(OUTPUT)
	if [ -f $(OUTPUT) ]; then ./$(OUTPUT) sample_inputs/known_sample.fasta 0 parameters.config; fi

# Local test cases
run-human-mouse-local: $(OUTPUT)
	if [ -f $(OUTPUT) ]; then ./$(OUTPUT) sample_inputs/Human-Mouse-BRCA2-cds.fasta 1 parameters.config; fi

run-color-blindness-local: $(OUTPUT)
	if [ -f $(OUTPUT) ]; then ./$(OUTPUT) sample_inputs/Opsin1_colorblindness_gene.fasta 1 parameters.config; fi

run-known-sample-local: $(OUTPUT)
	if [ -f $(OUTPUT) ]; then ./$(OUTPUT) sample_inputs/known_sample.fasta 1 parameters.config; fi
#!/usr/bin/env bash

g++ main.cpp wrapper/application_wrapper.cpp file_readers/gene_sequence_reader.cpp file_readers/alignment_parameters_reader.cpp -o exe
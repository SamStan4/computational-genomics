#pragma once

#include "./../globals-imports/globals_includes.hpp"
#include "./../sequence-alignment/sequence_alignment.hpp"

class application_wrapper
{
    public:

        static void run(int argc, char** argv)
        {
            string sequence_file_path, parameter_config_file_path;
            int alignment_flag = 0;

            if (!application_wrapper::parse_command_line_args(argc, argv, sequence_file_path, parameter_config_file_path, alignment_flag))
            {
                cerr << RED << "Error parsing command line arguments, aborting" << RESET << endl;

                return;
            }

            #if MULTI_THREAD

                cout << MAGENTA << "Executing program using multiple threads" << RESET << endl;

            #else

                cout << MAGENTA << "Executing program using single thread" << RESET << endl;

            #endif

            sequence_alignment alignment(sequence_file_path, parameter_config_file_path);

            alignment.print_parameters_cout();
        }

    private:

        static bool parse_command_line_args(int argc, char** argv, string& sequence_file_path, string& parameter_config_file_path, int& alignment_flag)
        {
            try
            {
                if (argc != 4)
                {
                    return false;
                }

                sequence_file_path = argv[1];
                alignment_flag = stoi(argv[2]);
                parameter_config_file_path = argv[3];

                return true;
            }
            catch(const std::exception& e)
            {
                return false;
            }
        }
};
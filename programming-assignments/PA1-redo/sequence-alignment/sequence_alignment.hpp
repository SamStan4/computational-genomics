#pragma once

#include "./../globals-imports/globals_includes.hpp"

class sequence_alignment
{
    public:

        sequence_alignment(const string& sequence_file_path, const string& parameter_config_file_path)
        {
            if (!filesystem::exists(sequence_file_path))
            {
                throw runtime_error("unable to locate genetic sequence file path");
            }

            if (!filesystem::exists(parameter_config_file_path))
            {
                throw runtime_error("unable to locate parameter config file path");
            }

            this->load_genetic_sequences(sequence_file_path);

            this->load_alignment_parameters(parameter_config_file_path);
        }

        void global_alignment_affine_gap_penalty(const string& output_file_path)
        {

        }

        void local_alignment_affine_gap_penalty(const string& output_file_path)
        {

        }

        void print_sequences_cout(void)
        {
            cout
                << "s1 name: " << this->s1_name << endl << endl
                << this->s1 << endl << endl
                << "s2 name: " << this->s2_name << endl << endl
                << this->s2 << endl << endl;
        }

        void print_parameters_cout(void)
        {
            cout
                << "match =         " << this->match << endl
                << "mismatch =      " << this->mismatch << endl
                << "opening gap =   " << this->opening_gap << endl
                << "gap extension = " << this->extension_gap << endl;
        }

    private:

        int match,
            mismatch,
            opening_gap,
            extension_gap;

        string s1_name, s2_name, s1, s2;

        void load_genetic_sequences(const string& sequence_file_path)
        {
            cout << MAGENTA << "Loading sequence alignment parameters" << RESET << endl;

            ifstream file(sequence_file_path);

            if (!file.is_open())
            {
                throw runtime_error("unable to open genetic sequence file path");
            }

            string read_buffer, * cur_sequence = nullptr;

            while (getline(file, read_buffer))
            {
                if (read_buffer.empty())
                {
                    continue;
                }

                if (read_buffer[0] == '>')
                {
                    if (cur_sequence == nullptr)
                    {
                        this->s1_name = read_buffer.substr(1);
                        cur_sequence = &(this->s1);
                    }
                    else
                    {
                        this->s2_name = read_buffer.substr(1);
                        cur_sequence = &(this->s2);
                    }

                    continue;
                }

                if (cur_sequence)
                {
                    *cur_sequence += read_buffer;
                }
            }
        }

        void load_alignment_parameters(const string& parameter_config_file_path)
        {
            static unordered_map<string, double> key_value =
            {
                {"match", 0},
                {"mismatch", 0},
                {"g", 0},
                {"h", 0}
            };

            cout << MAGENTA << "Loading sequence alignment parameters" << RESET << endl;

            // set to default
            key_value["match"] = 0;
            key_value["mismatch"] = 0;
            key_value["g"] = 0;
            key_value["h"] = 0;

            ifstream file(parameter_config_file_path);

            if (!file.is_open())
            {
                throw runtime_error("unable to open parameter config file path");
            }

            string read_buffer;

            while (getline(file, read_buffer))
            {
                if (read_buffer.empty())
                {
                    continue;
                }

                stringstream read_stream(read_buffer);

                string key, value;

                read_stream >> key >> value;

                if (key_value.find(key) != key_value.end())
                {
                    try
                    {
                        key_value[key] = stoi(value);
                    }
                    catch(...)
                    {
                        throw runtime_error("Error while parsing parameter config file");
                    }
                }
            }

            this->match = key_value["match"];
            this->mismatch = key_value["mismatch"];
            this->opening_gap = key_value["h"];
            this->extension_gap = key_value["g"];
        }
};
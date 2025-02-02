#pragma once

#include "./../globals-imports/globals_includes.hpp"
#include "./dp_cell.hpp"
#include "./global_alignment_statistics.hpp"

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
            global_alignment_statistics stats;

            this->run_global_alignment(stats);

            ofstream file(output_file_path);

            stats.dump_stats_to_file(file, this->s1_name, this->s2_name, this->s1, this->s2);
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

        void run_global_alignment(global_alignment_statistics& stats) const
        {
            static const int negative_infinity_int = numeric_limits<int>::min();
            static const signed long long negative_infinity_sll = (signed long long)numeric_limits<int>::min();

            if (this->s1.empty() || this->s2.empty())
            {
                return;
            }

            vector<vector<dp_cell>> dp_table(this->s1.size() + 1, vector<dp_cell>(this->s2.size() + 1));

            const int n = (int)dp_table.size(), m = (int)dp_table[0].size();

            dp_table[0][0].d_score = 0;
            dp_table[0][0].i_score = 0;
            dp_table[0][0].s_score = 0;

            for (int i = 1; i < n; ++i) {
                dp_table[i][0].s_score = negative_infinity_int;
                dp_table[i][0].d_score = this->opening_gap + (i * this->extension_gap);
                dp_table[i][0].i_score = negative_infinity_int;
            }
            for (int j = 1; j < m; ++j) {
                dp_table[0][j].s_score = negative_infinity_int;
                dp_table[0][j].d_score = negative_infinity_int;
                dp_table[0][j].i_score = this->opening_gap + (j * this->extension_gap);
            }

            const signed long long
                m_a_sll = (signed long long)this->match,
                m_i_sll = (signed long long)this->mismatch,
                h_sll = (signed long long)this->opening_gap,
                g_sll = (signed long long)this->extension_gap;

            for (int i = 1; i < n; ++i) {
                for (int j = 1; j < m; ++j) {
                    // Handle s_score
                    dp_table[i][j].s_score = (int)max(negative_infinity_sll, max((signed long long)max(dp_table[i-1][j-1].s_score, dp_table[i-1][j-1].d_score), (signed long long)dp_table[i-1][j-1].i_score) + (this->s1[i-1] == this->s2[j-1] ? m_a_sll : m_i_sll));
                    // Handle d_score
                    dp_table[i][j].d_score = (int)max(negative_infinity_sll, max((signed long long)max(dp_table[i-1][j].i_score, dp_table[i-1][j].s_score) + h_sll + g_sll, (signed long long)dp_table[i-1][j].d_score + g_sll));
                    // Handle i_score
                    dp_table[i][j].i_score = (int)max(negative_infinity_sll, max((signed long long)max(dp_table[i][j-1].s_score, dp_table[i][j-1].d_score) + h_sll + g_sll, (signed long long)dp_table[i][j-1].i_score + g_sll));
                }
            }

            string path_retrace;

            int i = n - 1, j = m - 1;

            while (i > 0 && j > 0)
            {
                switch (dp_table[i][j].get_max_score())
                {
                    case S_VALUE_KEY:
                        if (this->s1[i-1] == this->s2[j-1])
                        {
                            path_retrace.push_back(MATCH_SYMBOL);
                        }
                        else
                        {
                            path_retrace.push_back(MISMATCH_SYMBOL);
                        }
                        --i;
                        --j;
                    break;
                    case D_VALUE_KEY:
                        path_retrace.push_back(DELETION_SYMBOL);
                        --i;
                    break;
                    case I_VALUE_KEY:
                        path_retrace.push_back(INSERTION_SYMBOL);
                        --j;
                    break;
                }
            }

            while (i > 0)
            {
                path_retrace.push_back(DELETION_SYMBOL);
                --i;
            }

            while (j > 0)
            {
                path_retrace.push_back(INSERTION_SYMBOL);
                --j;
            }

            reverse(path_retrace.begin(), path_retrace.end());

            stats.set_optimal_path(path_retrace);
        }
};
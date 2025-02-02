#pragma once

#include "./../globals-imports/globals_includes.hpp"

class global_alignment_statistics
{
    public:

        global_alignment_statistics()
        {
            this->alignment_score = 0;
            this->number_matches = 0;
            this->number_mismatches = 0;
            this->number_opening_gaps = 0;
            this->number_gap_extensions = 0;
        }

        void set_optimal_path(const string& new_path)
        {
            this->optimal_path = new_path;

            this->set_all();
        }

        int get_alignment_score(void) const
        {
            return this->alignment_score;
        }

        int get_number_matches(void) const
        {
            return this->number_matches;
        }

        int get_number_mismatches(void) const
        {
            return this->number_mismatches;
        }

        int get_number_number_opening_gaps(void) const
        {
            return this->number_opening_gaps;
        }

        int get_number_gap_extensions(void) const
        {
            return this->number_gap_extensions;
        }

        const string& get_optimal_path(void) const
        {
            return this->optimal_path;
        }

        double get_identity_percentage(void) const
        {
            if (this->optimal_path.empty())
            {
                return numeric_limits<double>::min();
            }

            return (double)this->number_matches / (double)this->optimal_path.size();
        }

        double get_gap_percentage(void) const
        {
            if (this->optimal_path.empty())
            {
                return numeric_limits<double>::min();
            }

            return (double)this->number_gap_extensions / (double)this->optimal_path.size();
        }

        void dump_stats_to_file(ofstream& file, const string& s1_name, const string& s2_name, const string& s1, const string& s2)
        {
            if (!file.is_open())
            {
                throw runtime_error("file not opened");
            }

            this->dump_input_header_to_file(file, s1_name, s2_name, s1, s2);
        }

    private:

        int
            alignment_score,
            number_matches,
            number_mismatches,
            number_opening_gaps,
            number_gap_extensions;

        string optimal_path;

        void dump_input_header_to_file(ofstream& file, const string& s1_name, const string& s2_name, const string& s1, const string& s2, const int gene_print_width = 60)
        {
            file
                << "INPUT:" << endl << "******" << endl << endl
                << ">" << s1_name << endl;

            for (int i = 0; i < (int)s1.size();)
            {
                for (int j = 0, k = i; k < (int)s1.size() && j < gene_print_width; ++j, ++k)
                {
                    file << s1[k];
                }

                i += gene_print_width;

                file << endl;
            }

            file << endl << ">" << s2_name << endl;

            for (int i = 0; i < (int)s2.size();)
            {
                for (int j = 0, k = i; k < (int)s2.size() && j < gene_print_width; ++j, ++k)
                {
                    file << s2[k];
                }

                i += gene_print_width;

                file << endl;
            }

            file << endl;
        }

        void set_all(void)
        {
            for (int i = 0; i < (int)this->optimal_path.size(); ++i)
            {
                switch (this->optimal_path[i])
                {
                    case MATCH_SYMBOL:
                        ++this->number_matches;
                    break;
                    case MISMATCH_SYMBOL:
                        ++this->number_mismatches;
                    break;
                    case INSERTION_SYMBOL:
                    case DELETION_SYMBOL:
                        ++this->number_gap_extensions;
                    break;
                }
            }

            if (this->optimal_path.empty())
            {
                this->number_opening_gaps = 0;

                return;
            }

            if (this->optimal_path[0] == DELETION_SYMBOL || this->optimal_path[0] == INSERTION_SYMBOL)
            {
                ++this->number_opening_gaps;
            }

            for (int i = 0; i < (int)this->optimal_path.size(); ++i)
            {
                if ((this->optimal_path[i] == DELETION_SYMBOL && this->optimal_path[i-1] != DELETION_SYMBOL) || (this->optimal_path[i] == INSERTION_SYMBOL && this->optimal_path[i-1] != INSERTION_SYMBOL))
                {
                    ++this->number_opening_gaps;
                }
            }
        }
};
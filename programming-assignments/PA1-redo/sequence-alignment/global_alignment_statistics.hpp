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

        void set_alignment_score(const int new_score)
        {
            this->alignment_score = new_score;
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

        void dump_stats_to_file(ofstream& file, const string& s1_name, const string& s2_name, const string& s1, const string& s2, const int match, const int mismatch, const int opening_gap, const int extension_gap)
        {
            if (!file.is_open())
            {
                throw runtime_error("file not opened");
            }

            this->dump_input_header_to_file(file, s1_name, s2_name, s1, s2);

            this->dump_results_to_file(file, s1_name, s2_name, s1, s2, match, mismatch, opening_gap, extension_gap);
        }

    private:

        int
            alignment_score,
            number_matches,
            number_mismatches,
            number_opening_gaps,
            number_gap_extensions;

        string optimal_path;

        void dump_alignment_visual_to_file(ofstream& file, const string& s1, const string& s2, const int gene_print_width = OUTPUT_WIDTH_FORMAT) const
        {
            const int n = this->optimal_path.size();

            for (int i = 0, j = 0, k = 0; i < n; i += gene_print_width)
            {
                int m = 0, l = 0;

                file << left << setw(5) << "s1" << setw(10) << j + 1;

                for (l = 0, m = i; m < n && l < gene_print_width; ++l, ++m)
                {
                    switch (this->optimal_path[m])
                    {
                        case MISMATCH_SYMBOL:
                        case MATCH_SYMBOL:
                        case DELETION_SYMBOL:
                            file << s1[j++];
                        break;
                        case INSERTION_SYMBOL:
                            file << "-";
                        break;
                    }
                }

                file << left << setw(3) << "" << j << endl << setw(15) << "";

                for (l = 0, m = i; m < n && l < gene_print_width; ++l, ++m)
                {
                    switch (this->optimal_path[m])
                    {
                        case MATCH_SYMBOL:
                            file << "|";
                        break;
                        case MISMATCH_SYMBOL:
                        case DELETION_SYMBOL:
                        case INSERTION_SYMBOL:
                            file << " ";
                        break;
                    }
                }

                file << endl << left << setw(5) << "s2" << setw(10) << k + 1;

                for (l = 0, m = i; m < n && l < gene_print_width; ++l, ++m)
                {
                    switch (this->optimal_path[m])
                    {
                        case MISMATCH_SYMBOL:
                        case MATCH_SYMBOL:
                        case INSERTION_SYMBOL:
                            file << s2[k++];
                        break;
                        case DELETION_SYMBOL:
                            file << "-";
                        break;
                    }
                }

                file << left << setw(3) << "" << k << endl << endl;
            }
        }

        void dump_input_header_to_file(ofstream& file, const string& s1_name, const string& s2_name, const string& s1, const string& s2, const int gene_print_width = OUTPUT_WIDTH_FORMAT) const
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

        void dump_report_to_file(ofstream& file) const
        {
            file
                << "Report:" << endl << endl
                << "Global optimal score = " << this->alignment_score << endl << endl
                << "Number of: matches = " << this->number_matches << ", mismatches = " << this->number_mismatches << ", opening gaps = " << this->number_opening_gaps << ", gap extensions = " << this->number_gap_extensions << endl << endl
                << " Identites = " << this->number_matches << "/" << this->optimal_path.size() << " (" << this->get_identity_percentage() << "%), Gaps = " << this->number_gap_extensions << "/" << this->optimal_path.size() << " (" << this->get_gap_percentage() << "%)";
        }

        void dump_results_to_file(ofstream& file, const string& s1_name, const string& s2_name, const string& s1, const string& s2, const int match, const int mismatch, const int opening_gap, const int extension_gap, const int gene_print_width = OUTPUT_WIDTH_FORMAT) const
        {
            file 
                << "OUTPUT:" << endl << "******" << endl << endl
                << "Scores:    match = " << match << ", mismatch = " << mismatch << ", h = " << opening_gap << ", g = " << extension_gap << endl << endl
                << "Sequence 1 = " << s1_name << ", length = " << s1.size() << " characters" << endl
                << "Sequence 2 = " << s2_name << ", length = " << s2.size() << " characters" << endl << endl;

            this->dump_alignment_visual_to_file(file, s1, s2);

            this->dump_report_to_file(file);
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
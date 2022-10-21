#include <iostream>
#include <string>
#include <fstream>
#include <vector>

// Namespace
using std::string;
using std::fstream;
using std::cout;
using std::endl;
using std::vector;
using std::fixed;
using std::setprecision;

// Declaration
bool in(string, vector<string>);
vector<string> get_unique(vector<string>, vector<string>);
vector<string> get_common(vector<string>, vector<string>);
bool generate_file(char*, char*, vector<string>&, vector<string>&, vector<string>&, vector<string>&, vector<string>&);


int main(int argc, char** argv)
{
    fstream first_file(argv[1]);
    fstream second_file(argv[2]);

    std::istream_iterator<string> first_start(first_file), first_end;
    std::istream_iterator<string> second_start(second_file), second_end;

    vector<string> first_imgs(first_start, first_end);
    vector<string> second_imgs(second_start, second_end);

    cout << "read " << first_imgs.size() << " entries from " << argv[1] << endl;
    cout << "read " << second_imgs.size() << " entries from " << argv[2] << endl;

    vector<string> first_uniques = get_unique(first_imgs, second_imgs);
    vector<string> second_uniques = get_unique(second_imgs, first_imgs);
    vector<string> common = get_common(first_imgs, second_imgs);

    cout << "First uniques " << first_uniques.size() << endl;
    cout << "Second uniques " << second_uniques.size() << endl;

    generate_file(argv[1], argv[2], first_imgs, second_imgs, first_uniques, second_uniques, common);
}


/**
 * @brief checks if a string is in a string vector
 * 
 * @param string_to_search_for 
 * @param vector_to_search 
 * @return true 
 * @return false 
 */
bool in(string string_to_search_for, vector<string> vector_to_search)
{
    for (string s: vector_to_search)
    {
        if (s == string_to_search_for)
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief Get the unique values from the first vector that aren't
 *        in the second
 * 
 * @param first 
 * @param second 
 * @return vector<string> 
 */
vector<string> get_unique(vector<string> first, vector<string> second)
{
    vector<string> uniques;
    for (string i: first)
    {
        if(!in(i, second)) // if the string is NOT in the vector
        {
            uniques.push_back(i);
        }
    }
    return uniques;
}

/**
 * @brief Get the common entries between two vector<string>
 * 
 * @param first 
 * @param second 
 * @return vector<string> 
 */
vector<string> get_common(vector<string> first, vector<string> second)
{
    vector<string> common;
    for (string i: first)
    {
        if(in(i, second)) // if the string IS in the vector
        {
            common.push_back(i);
        }
    }
    return common;
}


/**
 * @brief 
 * 
 * @param first_name 
 * @param second_name 
 * @param first 
 * @param second 
 * @param first_unique 
 * @param second_unique 
 * @return true 
 * @return false 
 */
bool generate_file(char* first_name, char* second_name, vector<string>& first, vector<string>& second, 
                   vector<string>& first_unique, vector<string>& second_unique, vector<string>& commons)
{
    char outfile_name[100];
    snprintf(outfile_name, 100, "%s_V_%s.txt", first_name, second_name);

    fstream outfile;
    outfile.open(string(outfile_name), fstream::out);

    if (outfile.is_open())
    {
        outfile << "Comparing " << first_name << " and " << second_name << endl;
        outfile << first_name << " has " << first.size() << " entries" << endl;
        outfile << second_name << " has " << second.size() << " entries" << endl;
        outfile << setprecision(3) << ((float)first_unique.size() / (float)first.size() * 100)
            << "\% of " << first_name << " is unique" << endl;
        outfile << setprecision(3) << ((float)second_unique.size() / (float)second.size() * 100) 
            << "\% of " << second_name << " is unique" << endl;
        outfile << commons.size() << " entries in common" << endl;
        outfile << "Unique to " << first_name << endl;
        for (string s: first_unique)
        {
            outfile << s << "\n";
        }
        outfile << endl;
        outfile << "Unique to " << second_name << endl;
        for (string s: first_unique)
        {
            outfile << s << "\n";
        }
        outfile << endl;

        outfile << "entries in common" << endl;
        for (string s: commons)
        {
            outfile << s << "\n";
        }
        outfile << endl;

        outfile.close();
        return true;
    }
    cout << outfile_name << " was not opened" << endl;
    exit(1);
    return false;
}
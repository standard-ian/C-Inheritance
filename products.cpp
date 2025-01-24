/*
 * Ian Leuty
 * ileuty@pdx.edu
 * 1/7/2025
 * CS302 Winter 2025
 * Program 1
 *
 *********************************************************************
 *
 * implementation for "Product" and its derivations
 *
 ********************************************************************
 */

#include "products.h"

/*
 ********************************************************************
 *
 * Product (base)
 * data members:
 *  char *name
 *
 ********************************************************************
 */

bool Product::read_string_from_file(std::ifstream &filein, std::string &dest, char delim)
{
    using namespace std;
    filein.peek();
    if (filein.eof()) return false;
    getline(filein, dest, delim);
    return true;
}

//reads a string in and returns it
const std::string Product::read_string()
{
    using namespace std;
    string the_string;
    cout << "\033[38;5;32m" << ">>" << "\033[0m";;
    getline(cin, the_string);
    return the_string;
}

//reads an int in and return it
const int Product::read_int()
{
    using namespace std;
    int the_int{};
    cout << "\033[38;5;32m" << ">>" << "\033[0m";;
    cin >> the_int;
    while (cin.fail()){
        cin.clear();
        cin.ignore(100, '\n');
        cout << "\nYou must enter a number." << endl;
        cout << "\033[38;5;32m" << ">>" << "\033[0m";;
        cin >> the_int;
    }
    cin.ignore(100, '\n');
    return the_int;
}

//default constructor
Product::Product() : name(nullptr), type(nullptr) {}

//default read in constructor
Product::Product(int i) : name(nullptr), type(nullptr)
{
    using namespace std;
    string name_in{};
    string type_in{};

    cout << "\nEnter the Product name." << endl;
    name_in = read_string();

    cout << "Enter the Product type." << endl;
    type_in = read_string();

    name = new char[strlen(name_in.c_str()) + 1];
    strcpy(name, name_in.c_str());
    type = new char[strlen(type_in.c_str()) + 1];
    strcpy(type, type_in.c_str());
}

Product::Product(std::ifstream &filein) : name(nullptr), type(nullptr)
{
    using namespace std;
    if (!filein) return;

    filein.peek();                  //check the file

    if (filein.eof()) return;
    string name_in{};
    string type_in{};

    if (!read_string_from_file(filein, name_in, ',')) return;
    if (!read_string_from_file(filein, type_in, ',')) return;

    name = new char[strlen(name_in.c_str()) + 1];
    strcpy(name, name_in.c_str());
    type = new char[strlen(type_in.c_str()) + 1];
    strcpy(type, type_in.c_str());
}

//destructor
Product::~Product()
{
    delete [] name;
    delete [] type;
    name = nullptr;
    type = nullptr;
}

//constructor with name char* arg
Product::Product(const char *name_in, const char *type_in) : name(nullptr), type(nullptr)
{
    name = new char[strlen(name_in) + 1];
    strcpy(name, name_in);
    type = new char[strlen(type_in) + 1];
    strcpy(type, type_in);
}

//copy constructor
Product::Product(const Product &source) : name(nullptr), type(nullptr)
{
    if (!source.name || !source.type)
        return;

    name = new char[strlen(source.name) + 1]; //allocate new memory
    strcpy(name, source.name); //copy
    type = new char[strlen(source.type) + 1];
    strcpy(type, source.type);
}

/*
 * overloaded assignment operator
 *  arguments(s):
 *      const product object refrence
 *
 *  return type:
 *      Product reference
 *********************************************************************
 */
Product &Product::operator=(const Product &source)
{   //check for self assignment
    if (this == &source) return *this;

    char *new_name = nullptr;
    char *new_type = nullptr;

    //if there is no source name allocated, return the nullptr
    if (source.name && source.type){
        new_name = new char[strlen(source.name) + 1];
        strcpy(new_name, source.name);
        new_type = new char[strlen(source.type) + 1];
        strcpy(new_type, source.type);
    }

    if (name)
        delete [] name;

    if (type)
        delete [] type;

    type = new_type;
    name = new_name;

    return *this; //"this" is always a pointer to the current object. we dereference it and return that
}

//compare this name
bool Product::compare_names(const char *to_compare) const
{
    if (strcmp(to_compare, name) == 0) return true;
    return false;
}

//compare this type
bool Product::compare_types(const char *to_compare) const
{
    if (strcmp(to_compare, type) == 0) return true;
    return false;
}

//copy this name out
int Product::copy_name(char *&copy) const
{
    if (copy) return -1;
    if (!name) return 0;
    copy = new char[strlen(name) + 1];
    strcpy(copy, name);
    return 1;
}

//copy this type out
int Product::copy_type(char *&copy) const
{
    if (copy) return -1;
    if (!type) return 0;
    copy = new char[strlen(type) + 1];
    strcpy(copy, type);
    return 1;
}

//display the name and type
bool Product::display() const
{
    if (!name) return false;
    std::cout << std::left << std::setw(30) << name << " | " << std::setw(15) << type << " | ";
    //printf("%-30s| %-15s|", name, type);
    return true;
}

/**********************************************************************
 *
 * Motherboard
 *
 * Data Members:
 *  char *details;
 *  int usb_ports;
 *  processor the_processor;
 *
 **********************************************************************
 */

//default  constructor
Motherboard::Motherboard()
    : Product(), details(nullptr), usb_ports(0), the_processor(processor::none) {}

//read in constructor
Motherboard::Motherboard(int i)
    : Product(i), details(nullptr), usb_ports(0), the_processor(processor::none)
{
    using namespace std;
    int processor_selection{};
    string details_in{};

    cout << "Enter the details or product specifications." << endl;
    details_in = read_string();
    details = new char[strlen(details_in.c_str())];
    strcpy(details, details_in.c_str());

    cout << "Enter the number of USB ports." << endl;
    usb_ports = read_int();
    cout << "Select which processor the board accepts." << endl
       << '\t' <<  "1. Intel" << endl
       << '\t' << "2. AMD" << endl
       << '\t' << "3. ARM" << endl;
    processor_selection = read_int();

    switch (processor_selection){
       case 1:
               the_processor = processor::intel;
               break;
       case 2:
               the_processor = processor::amd;
               break;
       case 3:
               the_processor = processor::arm;
               break;
       default:
               //throw exception
               break;
    }
}

//destructor
Motherboard::~Motherboard()
{
    delete [] details;
    details = nullptr;
}

Motherboard::Motherboard(std::ifstream &filein) : Product(filein)
{
    using namespace std;

    if (!filein) return;

    filein.peek();

    if (filein.eof()) return;

    int processor_selection{};
    string details_in{};

    if (!read_string_from_file(filein, details_in, ',')) return;
    filein >> usb_ports; filein.ignore(100, ',');
    filein >> processor_selection; filein.ignore(100, '\n');

    switch (processor_selection){
        case 1:
                the_processor = processor::intel;
                break;
        case 2:
                the_processor = processor::amd;
                break;
        case 3:
                the_processor = processor::arm;
                break;
        default:
                break;
    }
    details = new char[strlen(details_in.c_str())];
    strcpy(details, details_in.c_str());
}


//copy constructor
Motherboard::Motherboard(const Motherboard &source) : Product(source)/*Product(source.name, source.type)*/, details(nullptr), usb_ports(source.usb_ports), the_processor(source.the_processor)
{
    if(!source.details) return;
    details = new char[strlen(source.details) + 1]; //allocate new memory
    strcpy(details, source.details); //copy
}

/*
//this is no longer needed. all reading in happens in the constructor

//constructor w/ args
Motherboard::Motherboard(const int usb_ports_in, const char *details_in, processor processor_in, const char *name_in, const char *type_in)
    : Product(name_in, type_in), details(nullptr), usb_ports(usb_ports_in), the_processor(processor_in)
{
    if (!details_in) return;
    details = new char[strlen(details_in) + 1];
    strcpy(details, details_in);
}
*/

//overload assignment operator
Motherboard &Motherboard::operator=(const Motherboard &source)
{   //check for self assignment
    if (this == &source) return *this;

    //base class
    Product::operator=(source);

    usb_ports = source.usb_ports;
    the_processor = source.the_processor;

    char *new_details = nullptr;

    if (source.details){
        new_details = new char[strlen(source.details) + 1];
        strcpy(new_details, source.details);
    }

    if (details)
        delete [] details;

    details = new_details;

    return *this;
}

//display
bool Motherboard::display() const
{
    if (!name || !details || usb_ports == 0)
        return false;
    Product::display();
    std::cout << std::left << std::setw(40) << details << " | "
                           << std::setw(3) << usb_ports << " | ";
    //printf(" %-40s| %-3i|", details, usb_ports);
    switch (the_processor){
        case processor::none:
            return false;
        case processor::intel:
            std::cout << "Intel |" << std::endl;
            break;
        case processor::amd:
            std::cout << "AMD   |" << std::endl;
            break;
        case processor::arm:
            std::cout << "ARM   |" << std::endl;
            break;
        default:
            break;
    }
    return true;
}

bool Motherboard::is_processor(const processor &processor_in) const
{
    if (the_processor == processor_in) return true;
    return false;
}

bool Motherboard::is_more_than_ports(int ports) const
{
    if (usb_ports >= ports) return true;
    return false;
}

bool Motherboard::is_details_contain(const std::string &new_details) const
{
    std::string temp_details = details;
    long unsigned int result = temp_details.find(new_details);
    if (result != std::string::npos)
        return true;
    return false;
}


/*
 ********************************************************************
 *
 * Graphics
 *
 * Data Members:
 *  int vram;
 *  int fans;
 *  std::string review;
 *
 ********************************************************************
 */

//default constructor
Graphics::Graphics() : Product(), vram(0), fans(0), review("") {}

//read in constructor
Graphics::Graphics(int i) : Product(i), vram(0), fans(0), review("")
{
    using namespace std;
    cout << "Enter the number of fans." << endl;
    fans = read_int();
    cout << "Enter the amount of VRAM." << endl;
    vram = read_int();
    cout << "Enter a review for the card." << endl;
    review = read_string();
}

//destructor
Graphics::~Graphics()
{
    vram = 0; fans = 0; review = "";
}

Graphics::Graphics(std::ifstream &filein) : Product(filein)
{
    if (!read_string_from_file(filein, review, ',')) return;
    filein >> vram; filein.ignore(100, ',');
    filein >> fans; filein.ignore(100, '\n');
}

/*
//copy constructor, probably not needed, no dynamic memory in this class
Graphics::Graphics(const Graphics &source)
    : Product(source.name, source.type), vram(source.vram), fans(source.fans), review(source.review) {}
*/

/*
//constructor with arguments, no longer needed
Graphics::Graphics(const int vram_in, const int fans_in, const std::string &review_in, const char *name_in, const char *type_in)
    : Product(name_in, type_in), vram(vram_in), fans(fans_in), review(review_in) {}
*/

//display
bool Graphics::display() const
{
    if (!name || fans == 0 || vram == 0)
        return false;

    Product::display();
    std::cout << std::left << std::setw(40) << review  << " | "
                           << std::setw(3) << fans << " | "
                           << std::setw(4) << vram << "GB | " << std::endl;
    //printf(" %-40s| %-3i| %-3iGB |\n", review.c_str(), fans, vram);

    return true;
}

//return true if vram is > vram in
bool Graphics::is_vram_over(const int vram_in) const
{
    if (vram >= vram_in) return true;
    return false;
}

//return true if fans is equivalent to fans_in
bool Graphics::is_fans_count(const int fans_in) const
{
    if (fans == fans_in) return true;
    return false;
}

//return true if to_find is a substring of review
bool Graphics::is_review_contain(const std::string& to_find) const
{
    std::string temp_review = review;
    long unsigned int result = temp_review.find(to_find);
    if (result != std::string::npos)
        return true;
    return false;
}

/**********************************************************************
 *
 * Screen
 *
 * Data Members:
 *  int resolution_height;
 *  int resolution_width;
 *  std::string manufacturer;
 *
 **********************************************************************
 */

//default constructor
Screen::Screen() : Product(), resolution_height(0), resolution_width(0), manufacturer("") {}

//read in constructor
Screen::Screen(int i) : Product(i), resolution_height(0), resolution_width(0), manufacturer("")
{
    using namespace std;
    cout << "Enter the width." << endl;
    resolution_width = read_int();
    cout << "Enter the height." << endl;
    resolution_height = read_int();
    cout << "Enter the manufacturer." << endl;
    manufacturer = read_string();
}

//destructor
Screen::~Screen()
{
    resolution_height = 0; resolution_width = 0; manufacturer = "";
}

Screen::Screen(std::ifstream &filein) : Product(filein)
{

    filein >> resolution_width; filein.ignore(100, ',');
    filein >> resolution_height; filein.ignore(100, ',');
    if (!read_string_from_file(filein, manufacturer, '\n')) return;
}
/*
//copy constructor - probably not explicitly needed. no dynamic memory in this class
Screen::Screen(const Screen &source)
    : Product(source.name, source.type), resolution_height(source.resolution_height),
      resolution_width(source.resolution_width), manufacturer(source.manufacturer) {}
*/

/*
//constructor w/ arguments, no longer needed
Screen::Screen(const int width_in, const int height_in, const std::string &manufacturer_in, const char *name_in, const char *type_in)
    : Product(name_in, type_in), resolution_height(height_in), resolution_width(width_in), manufacturer(manufacturer_in) {}
*/

//display a Screen
bool Screen::display() const
{
    if (!name || manufacturer == "" || resolution_width == 0 || resolution_height == 0) return 0;

    Product::display();
    std::cout << std::left << std::setw(20) << manufacturer << " | "
              << std::setw(7) << resolution_width << "X "
              << std::setw(7) << resolution_height << " | ";
    //printf(" %-20s| %-6iX %-6i|", manufacturer.c_str(), resolution_width, resolution_height);
    return true;
}

//return true if screen width is > 3840
bool Screen::is_4k() const
{
    if (resolution_width >= 3840) return true;
    return false;
}

//return true if string matches manufacturer
bool Screen::is_manufacturer(std::string to_find) const
{
    std::transform(to_find.begin(), to_find.end(), to_find.begin(), ::toupper);
    std::string temp_man = manufacturer;
    std::transform(temp_man.begin(), temp_man.end(), temp_man.begin(), ::toupper);

    if (temp_man == to_find) return true;
    return false;
}

//return the aspect ratio
std::string Screen::aspect_ratio() const
{
    std::ostringstream ratio_out{};
    int ratio{std::__gcd(resolution_width, resolution_height)};
    int num{resolution_width / ratio};
    int dem{resolution_height / ratio};
    ratio_out << num << ':' << dem;
    return ratio_out.str();
}

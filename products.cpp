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

//default constructor
Product::Product() : name(nullptr), type(nullptr) {}

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
    //std::cout << name << " | " << type;
    printf("%-30s| %-15s|", name, type);
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

//destructor
Motherboard::~Motherboard()
{
    delete [] details;
    details = nullptr;
}

//copy constructor
Motherboard::Motherboard(const Motherboard &source) : Product(source.name, source.type), details(nullptr), usb_ports(source.usb_ports), the_processor(source.the_processor)
{
    if(!source.details) return;
    details = new char[strlen(source.details) + 1]; //allocate new memory
    strcpy(details, source.details); //copy
}

//constructor w/ args
Motherboard::Motherboard(const int usb_ports_in, const char *details_in, processor processor_in, const char *name_in, const char *type_in)
    : Product(name_in, type_in), details(nullptr), usb_ports(usb_ports_in), the_processor(processor_in)
{
    if (!details_in) return;
    details = new char[strlen(details_in) + 1];
    strcpy(details, details_in);
}

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
    /*
    std::cout << " | " << details
              << " | " << usb_ports
              << " | ";
    */
    printf(" %-40s| %-3i|", details, usb_ports);
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

bool Motherboard::is_processor(processor &processor_in) const
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

//destructor
Graphics::~Graphics()
{
    vram = 0; fans = 0; review = "";
}

//copy constructor, probably not needed, no dynamic memory in this class
Graphics::Graphics(const Graphics &source)
    : Product(source.name, source.type), vram(source.vram), fans(source.fans), review(source.review) {}

//constructor with arguments
Graphics::Graphics(const int vram_in, const int fans_in, const std::string &review_in, const char *name_in, const char *type_in)
    : Product(name_in, type_in), vram(vram_in), fans(fans_in), review(review_in) {}

//display
bool Graphics::display() const
{
    if (!name || fans == 0 || vram == 0)
        return false;

    Product::display();
    /*
    std::cout << " | " << review
              << " | " << fans
              << " | " << vram << "GB" << std::endl;
    */
    printf(" %-40s| %-3i| %-3iGB |\n", review.c_str(), fans, vram);

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

//destructor
Screen::~Screen()
{
    resolution_height = 0; resolution_width = 0; manufacturer = "";
}

//copy constructor - probably not explicitly needed. no dynamic memory in this class
Screen::Screen(const Screen &source)
    : Product(source.name, source.type), resolution_height(source.resolution_height),
      resolution_width(source.resolution_width), manufacturer(source.manufacturer) {}

//constructor w/ arguments
Screen::Screen(const int width_in, const int height_in, const std::string &manufacturer_in, const char *name_in, const char *type_in)
    : Product(name_in, type_in), resolution_height(height_in), resolution_width(width_in), manufacturer(manufacturer_in) {}

//display a Screen
bool Screen::display() const
{
    if (!name || manufacturer == "" || resolution_width == 0 || resolution_height == 0) return 0;

    Product::display();
    /*
    std::cout << " | " << manufacturer
              << " | " << resolution_width << 'x' << resolution_height
              << std::endl;
    */
    printf(" %-20s| %-6iX %-6i|", manufacturer.c_str(), resolution_width, resolution_height);
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

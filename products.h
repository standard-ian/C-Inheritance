/*
 * Ian Leuty
 * ileuty@pdx.edu
 * 1/7/2025 * CS302 Winter 2025
 * Program 1
 *
 ******************************************************************************
 *
 * base class and derived classes interfaces
 *
 *******************************************************************************
 *
 * Shopping optimiation application.
 *
 * First Progress Submission:
 *
 * Base class: Purchasable item
 *      >supports dynamic character arrays
 *      >must have common property of all 3 derived
 *
 * Derived classes x3: purchasable items + more unique things each
 *      >one must support dynamic character arrays
 *      >3x max. data members for each
 *      >3x functions for each that support purchasing decisions (i.e. speed, ROI, durability, etc.)
 *      >push any comonalities up to the base class
 *
 *
 * Second Progress Submission:
 *
 * Node class for CLL & Node class for ARR - Could we just have one general node class for both?
 *
 * 3 data structures: support insert, removal, display, retreive, remove all, find
 *      >Vector/Array from STL
 *      >Circular linked list - Node class derived from items.
 *      >Array of linked lists - Will also require nodes, right? How to traverse recursively?
 *
 *******************************************************************************
 *
 * Final Deliverables:
 *      Complete the implementation of the three different types of products
 *      Complete the implementation of the Array of LLL
 *      CLL Node derived from another of your data classes
 *      Complete the implementation of a CLL using recursion
 *      Code needs to compile and run
 *      All warnings should be resolved
 *
 */

#include <cstring>
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <bits/stdc++.h>
#include <sstream>

//enum class for processor socket on MB
enum class processor{none=0, intel=1, amd=2, arm=3};

/*
 * base class, properties shared among derived classes
 * contains dynamically assigned data, copy constructor & overloaded assignemnt
 */
class Product
{
    public:
        Product();
        ~Product();
        Product(const char *name_in, const char *type_in);
        Product(const Product &source);

        Product& operator=(const Product &source);
        bool compare_names(const char *to_compare) const;
        bool compare_types(const char *to_compare) const;
        int copy_name(char *&copy) const;
        int copy_type(char *&copy) const;
        bool display() const;

    protected:
        char *name;
        char *type;
};

//derived class 1, "is-a" product plus properties unique to GPUs
class Graphics : public Product
{
    public:
        Graphics();
        ~Graphics();
        Graphics(const Graphics &source);
        Graphics(const int vram_in, const int fans_in, const std::string &review_in, const char *name_in, const char *type_in);

        bool display() const;

        bool is_vram_over(const int vram) const;
        bool is_fans_count(const int fans) const;
        bool is_review_contain(const std::string& to_find) const;

    protected:
        int vram;
        int fans;
        std::string review;
};


/*
 * derived class 2, "is-a" product plus properties unique to MBs
 * contains dynamically assigned data member, copy constructor and overloaded asignemnt
 */
class Motherboard : public Product
{
    public:
        Motherboard();
        ~Motherboard();
        Motherboard(const int usb_ports, const char *details, processor the_processor, const char *name, const char *type_in);
        Motherboard(const Motherboard &source);

        Motherboard& operator=(const Motherboard &source);
        bool display() const;

        bool is_processor(processor &processor_in) const;
        bool is_more_than_ports(int ports) const;
        bool is_details_contain(const std::string &new_details) const;

    protected:
        char *details;
        int usb_ports;
        processor the_processor;

};

//derived class 3, "is-a" product plus properties unique to Displays.
class Screen : public Product
{
    public:
        Screen();
        ~Screen();
        Screen(const Screen &source);
        Screen(const int height_in, const int width_in, const std::string &manufacturer_in, const char *name_in, const char *type_in);

        bool display() const;

        bool is_4k() const;
        bool is_manufacturer(std::string to_find) const;
        std::string aspect_ratio() const;

    protected:
        int resolution_height;
        int resolution_width;
        std::string manufacturer;
};

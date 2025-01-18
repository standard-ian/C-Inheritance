/*
 * Ian Leuty
 * ileuty@pdx.edu
 * 1/7/2025
 * CS302 Winter 2025
 * Program 1
 *
 ********************************************************************
 *
 * application interface
 *
 *********************************************************************
 */

#include "structures.h"


class Menu
{
    public:
        Menu();
        void prompt();
        void motherboard_options();
        void screen_options();
        void graphics_options();

        bool load_motherboards();
        bool load_graphics();
        bool load_screens();

        bool load_cart();
        bool save_cart();
        void display_cart();

        bool read_string_from_file(std::string &dest, char delim);


        bool again();
        const std::string read_string();
        const int read_int();

    protected:
        std::ifstream filein;
        std::ofstream fileout;

        std::vector<Motherboard> Motherboards;
        ARRScreen Screens;
        CLLGraphics GPUs;

        std::vector<Product> cart;
};


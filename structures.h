/*
 * Ian Leuty
 * ileuty@pdx.edu
 * 1/7/2025
 * CS302 Winter 2025
 * Program 1
 *
 ********************************************************************
 *
 * data structure interfaces
 *
 *********************************************************************
 */

#include "products.h"

/*
 * "node" objects for the ciruclar linked list
 */
class Graphics_Node : public Graphics
{
    public:
        Graphics_Node();
        Graphics_Node(const Graphics_Node &source);
        Graphics_Node(const Graphics &source);
        //Graphics_Node(const int vram_in, const int fans_in, const std::string &review_in, const std::string &name_in, const std::string &type_in);

        void set_next(Graphics_Node *new_next);
        Graphics_Node*& get_next();
        bool has_next() const;

    protected:
        Graphics_Node *next;
};

/*
 * circular linked list of GPUs
 *
 */
class CLLGraphics
{
    public:
        CLLGraphics();
        ~CLLGraphics();
        CLLGraphics(const CLLGraphics &source);

        CLLGraphics& operator=(const CLLGraphics &source);
        int display(const int display_opt, const std::string &review_keyword, const int vram_in, const int fans_in) const;
        bool empty();
        bool append(const Graphics &source);
        bool remove(const std::string &to_remove);
        int remove_all();
        bool find(const std::string &to_find);
        int retreive(const std::string &to_retreive, Graphics *retreived) const;
        int deep_copy(const CLLGraphics &source);
        bool load_graphics();

    protected:
        std::ifstream filein;
        Graphics_Node *rear;
        mutable int nums;

        void put_nums() const;
        void reset_nums() const;

        int display(Graphics_Node *current, const int display_opt, const std::string &review_keyword, const int vram_in, const int fans_in) const;
        bool remove(const std::string &to_remove, Graphics_Node *&current);
        int remove_all(Graphics_Node *&current);
        bool find(const std::string &to_find, Graphics_Node *current);
        void retreive(Graphics_Node *current, const std::string &to_retreive, Graphics *retreived, int &number_retreived) const;
        int deep_copy(Graphics_Node *source_current, const Graphics_Node *source_rear, Graphics_Node *&dest_current);

};

/*
 * "node" objects for the linked lists in the ARR
 */
class Screen_Node : public Screen
{
    public:
        Screen_Node();
        Screen_Node(const Screen &source);
        Screen_Node(const Screen_Node &source);
        //Screen_Node(const int height_in, const int width_in, const std::string &manufacturer, const std::string &name_in, const std::string &type_in);

        void set_next(Screen_Node *new_next);
        Screen_Node*& get_next();
        bool has_next() const;

    protected:
        Screen_Node *next;
};

/*
 * array of linked lists of Screens (Displays)
 *
 */
class ARRScreen
{
    public:
        ARRScreen(const int size, const int max_per_chain);
        ~ARRScreen();
        ARRScreen(const ARRScreen &source);

        ARRScreen& operator=(const ARRScreen &source);
        bool empty();
        int display(const int display_opt, const std::string &the_manufacturer) const;
        bool append(const Screen &source);
        bool remove(const std::string &to_remove);
        int remove_all();
        bool find(const std::string &to_find) const;
        int retreive(const std::string &to_retreive, Screen *retreived) const;
        int deep_copy(const ARRScreen &source);
        bool load_screens();

    protected:
        std::ifstream filein;
        Screen_Node **ARR;
        int size, max_per_chain;
        mutable int nums;

        void init(Screen_Node **ptr);
        void put_nums() const;
        void reset_nums() const;

        int display(Screen_Node **ptr, const int display_opt, const std::string &the_manufacturer) const;
        int display(Screen_Node *current, const int display_opt, const std::string &the_manufacturer) const;

        bool append(const Screen &source, Screen_Node **ptr);
        bool append_chain(const Screen &source, Screen_Node *&current, int &nodes);

        bool remove(const std::string &to_remove, Screen_Node **ptr);
        bool remove(const std::string &to_remove, Screen_Node *&current);

        int remove_all(Screen_Node **ARR);
        int remove_all_chain(Screen_Node *&current);

        bool find(const std::string &to_find, Screen_Node **ptr) const;
        bool find(const std::string &to_find, Screen_Node *current) const;

        void retreive(const std::string &to_retreive, Screen_Node **ptr, Screen *retreived, int &num_retreived) const;
        void retreive(const std::string &to_retreive, Screen_Node *current, Screen *retreived, int &num_retreived) const;

        int deep_copy(Screen_Node **&source_ptr, Screen_Node **&dest_ptr);
        int deep_copy(Screen_Node *source, Screen_Node *&dest);
};

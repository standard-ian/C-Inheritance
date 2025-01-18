/*
 * Ian Leuty
 * ileuty@pdx.edu
 * 1/7/2025
 * CS302 Winter 2025
 * Program 1
 *
 *************************************************************************
 *
 * data structures implementation
 *
 ************************************************************************
 *
 */

#include "structures.h"

/*
 * Graphics "node" implementation
 *
 **************************************************************************
 *
 */

//default constructor
Graphics_Node::Graphics_Node() : Graphics(), next(nullptr) {}

//copy constructor
Graphics_Node::Graphics_Node(const Graphics_Node &source) : Graphics(source), next(nullptr) {}

//constructor w/ arguments - Graphics object
Graphics_Node::Graphics_Node(const Graphics &source) : Graphics(source), next(nullptr) {}

//constructor w/ individual arguments
Graphics_Node::Graphics_Node(const int vram_in, const int fans_in, const std::string &review_in, const std::string &name_in, const std:: string &type_in)
    : Graphics(vram_in, fans_in, review_in, name_in.c_str(), type_in.c_str()), next(nullptr) {}

//sets next pointer, usually private to the structure using this node
void Graphics_Node::set_next(Graphics_Node *new_next)
{
    next = new_next;
}

//retreive next pointer, usually private to the structure using this node
Graphics_Node*& Graphics_Node::get_next()
{
    return next;
}

//check if there is a next pointer
bool Graphics_Node::has_next() const
{
    if (next) return true;
    return false;
}


/*
 * CLLGraphics implementation
 *
 **************************************************************************
 *
 */

//default constructor
CLLGraphics::CLLGraphics() : rear(nullptr), nums(1) {}

//destructor
CLLGraphics::~CLLGraphics()
{
    if (!rear) return;
    remove_all();
}

//copy constructor
CLLGraphics::CLLGraphics(const CLLGraphics &source) : rear(nullptr)
{
    deep_copy(source);
}

//overloaded assigment between CLLGraphics
CLLGraphics& CLLGraphics::operator=(const CLLGraphics &source)
{
    if (this == &source)
        return *this;
    remove_all();
    deep_copy(source);
    return *this;
}

//display all the GPUs in the CLLGraphics, return nodes displayed. this is the wrapper
int CLLGraphics::display(const int display_opt, const std::string &review_keyword, const int vram_in, const int fans_in) const
{
    if (!rear) return 0;
    if (display_opt == 4 && review_keyword == "") return 0;
    int displayed =  display(rear -> get_next(), display_opt, review_keyword, vram_in, fans_in);
    reset_nums();
    return displayed;
}

//display all the GPUs in the CLLGraphics, return nodes displayed. this is the recursive function
int CLLGraphics::display(Graphics_Node *current, const int display_opt, const std::string &review_keyword, const int vram_in, const int fans_in) const
{
    switch (display_opt){
        case 1: {
                    put_nums();
                    rear -> display();
                }
                break;

        case 2:
                if (rear -> is_vram_over(vram_in)){
                    put_nums();
                    rear -> display();
                }
                break;

        case 3:
                if (rear -> is_fans_count(fans_in)){
                    put_nums();
                    rear -> display();
                }
                break;

        case 4:
                if (rear -> is_review_contain(review_keyword)){
                    put_nums();
                    rear -> display();
                }
                break;

    }
    if (current == this -> rear)
        return 0;
    return display(current -> get_next(), display_opt, review_keyword, vram_in, fans_in) + 1;
}

//add a new Graphics to the CLLGraphics. return success or faliure.
bool CLLGraphics::append(const Graphics &source)
{
    if (!rear){
        rear = new Graphics_Node(source);
        rear -> set_next(rear);
        return true;
    }
    Graphics_Node *add = new Graphics_Node(source);
    Graphics_Node *hold = rear -> get_next();
    rear -> set_next(add);
    rear = add;
    rear -> set_next(hold);
    return true;
}

//search for a name (string) and remove it. return success or faliure - wrapper
bool CLLGraphics::remove(const std::string &to_remove)
{
    if (!rear) return false;                       //no list, return
    if (rear -> compare_names(to_remove.c_str()) //match found
    && (rear -> get_next() == this -> rear)){    //and rear is the only item
        delete rear;
        rear = nullptr;
        return true;
    }
    bool is_removed{remove(to_remove, rear -> get_next())};
    if (rear -> compare_names(to_remove.c_str()) and !is_removed){ //if rear is the match and we haven't already removed
        Graphics_Node *hold{rear -> get_next()};    //hold next
        delete rear;                                //delete current
        rear = hold;                                //update current
        return true;
    }
    return is_removed;
}

//search for a name (string) and remove it. return success or faliure - recursive function
bool CLLGraphics::remove(const std::string &to_remove, Graphics_Node *&current)
{
    if (current == (this -> rear)) return false; //we're back at the start

    if (current -> compare_names(to_remove.c_str())){   //match found
        Graphics_Node *hold{current -> get_next()};    //hold next
        delete current;                                //delete current
        current = hold;                                //update current
        return true;
    }
    return remove(to_remove, current -> get_next());  //keep looking until we find or come full circle
}

//remove all wrapper
int CLLGraphics::remove_all()
{
    if (!rear) return 0;
    int count = remove_all(rear -> get_next());
    delete rear;
    rear = nullptr;
    return count + 1;
}

//remove all recursion
int CLLGraphics::remove_all(Graphics_Node *&current)
{
    if (current == this -> rear)
        return 0;
    int count = remove_all(current ->get_next());
    delete current;
    current = nullptr;
    return count + 1;
}

//search for a name (string) and return true if in the CLLGraphics, wrapper
bool CLLGraphics::find(const std::string &to_find)
{
    if (!rear) return false;
    if (rear -> compare_names(to_find.c_str())){ //match found
        rear -> display();
        return true;
    }
    return find(to_find, rear -> get_next());
}

//search for a name (string) and return true if in the CLLGraphics, reursive function
bool CLLGraphics::find(const std::string &to_find, Graphics_Node *current)
{
    if (current == this -> rear) return false;
    if (current -> compare_names(to_find.c_str())){ //match found
        current -> display();
        return true;
    }
    return find(to_find, current -> get_next());
}

//retrive and return (via a Graphics array reference argument) matching Graphics from a CLLGraphics. This is the wrapper
int CLLGraphics::retreive(const std::string &to_retreive, Graphics *retreived) const
{
    if (!rear) return 0;
    int number_retreived{};
    retreive(rear -> get_next(), to_retreive, retreived, number_retreived);
    if (rear -> compare_names(to_retreive.c_str())){
        retreived[number_retreived] = *rear;
        ++number_retreived;
    }
    return number_retreived;
}

//retrive and return (via a Graphics array reference argument) matching Graphics from a CLLGraphics. This is the recursive function
void CLLGraphics::retreive(Graphics_Node *current, const std::string &to_retreive, Graphics *retreived, int &number_retreived) const
{
    if (current == this -> rear) return;
    if (current -> compare_names(to_retreive.c_str())){
        retreived[number_retreived] = *current;
        ++number_retreived;
    }
    return retreive(current -> get_next(), to_retreive, retreived, number_retreived);
}

//make a deep copy of a CLLGraphics, return nodes copied - wrapper
int CLLGraphics::deep_copy(const CLLGraphics &source)
{
    if (!source.rear){
        rear = nullptr;
        return 0;
    }

    this -> rear = new Graphics_Node(*source.rear);
    return deep_copy(source.rear -> get_next(), source.rear, rear) + 1;
}

//make a deep copy of a CLLGraphics, return nodes copied - recursive
int CLLGraphics::deep_copy(Graphics_Node *source_current, const Graphics_Node *source_rear, Graphics_Node *&dest_current)
{
    if (source_current == source_rear){
        dest_current -> set_next(this -> rear);
        return 0;
    }

    dest_current -> set_next(new Graphics_Node(*source_current));
    return deep_copy(source_current -> get_next(), source_rear, dest_current -> get_next()) + 1;
}

void CLLGraphics::put_nums() const
{
    printf("|\033[3;38;91m%4i. \033[0;0m", nums++);
}

void CLLGraphics::reset_nums() const
{
    nums = 1;
}

/*
 *
 * Screen "node" implementation
 *
 ***********************************************************************
 */

//default constructor
Screen_Node::Screen_Node() : next(nullptr) {}

//copy constructor
Screen_Node::Screen_Node(const Screen_Node &source) : Screen(source), next(nullptr) {}

//constructor w/ arguments - Screen object
Screen_Node::Screen_Node(const Screen &source) : Screen(source), next(nullptr) {}

//constructor w/ individual arguments
Screen_Node::Screen_Node(const int height_in, const int width_in, const std::string &manufacturer, const std::string &name_in, const std::string &type_in)
    : Screen(height_in, width_in, manufacturer, name_in.c_str(), type_in.c_str()), next(nullptr) {}

//sets next pointer, usually private to the structure using this node
void Screen_Node::set_next(Screen_Node *new_next)
{
    next = new_next;
}

//retreive next pointer, usually private to the structure using this node
Screen_Node*& Screen_Node::get_next()
{
    return next;
}

//determine if there is a next pointer
bool Screen_Node::has_next() const
{
    if (next) return true;
    return false;
}



/*
 * ScreenARR implementation
 *
 ************************************************************
 *
 */

//constructor sets size, calls init to set all "heads" to nullptr;
ARRScreen::ARRScreen(const int size_in, const int max_per_chain_in)
    : size(size_in), max_per_chain(max_per_chain_in), nums(1)
{
    ARR = new Screen_Node* [size];
    Screen_Node **ptr{ARR};
    init(ptr);
}

//traverse array of Screen_Node pointers and set all to nullptr;
void ARRScreen::init(Screen_Node **ptr)
{
    if (ptr >= (ARR +  size)) return;
    *ptr = nullptr;
    init(++ptr);
}


//destructor
ARRScreen::~ARRScreen()
{
    if (!ARR) return;
    remove_all();
}

//copy constructor
ARRScreen::ARRScreen(const ARRScreen &source)
{
    deep_copy(source);
}

//overloaded assigment
ARRScreen& ARRScreen::operator=(const ARRScreen &source)
{
    if (this == &source)
        return *this;
    remove_all();
    deep_copy(source);
    return *this;
}

//display all, wrapper
int ARRScreen::display(const int display_opt, const std::string &the_manufacturer) const
{
    if (!ARR) return 0;
    if (the_manufacturer == "" && display_opt == 3) return 0;
    Screen_Node **ptr{ARR};
    int displayed = display(ptr, display_opt, the_manufacturer);
    reset_nums();
    return displayed;
}

//display all, recursive function - array traversal
int ARRScreen::display(Screen_Node **ptr, const int display_opt, const std::string &the_manufacturer) const
{
    if (ptr >= ARR + size) return 0;
    int displayed = display(*ptr, display_opt, the_manufacturer);
    return display(++ptr, display_opt, the_manufacturer) + displayed;
}

//display all, recursive function - LLL traversal
int ARRScreen::display(Screen_Node *current, const int display_opt, const std::string &the_manufacturer) const
{
    if (!current) return 0;
    switch (display_opt){
        case 1: {
                    put_nums();
                    current -> display();
                    std::cout << std::endl;
                }
                break;

        case 2:
                if (current -> is_4k()){
                    put_nums();
                    current -> display();
                    std::cout << std::endl;
                }
                break;

        case 3:
                if (current -> is_manufacturer(the_manufacturer)){
                    put_nums();
                    current -> display();
                    std::cout << std::endl;
                }
                break;

        case 4: {
                    put_nums();
                    current -> display();
                    printf(" %-5s|\n", current -> aspect_ratio().c_str());
                }
                break;
    }
    return display(current -> get_next(), display_opt, the_manufacturer) + 1;
}

//add a new Screen to the ARR, wrapper
bool ARRScreen::append(const Screen &source)
{
    //if this function is being called, we can assume that ARR has had dynamic memory assigned by constructor
    //perhaps we should still check?
    Screen_Node **ptr{ARR};                                 //temp pointer for traversal
    bool is_added{append(source, ptr)};                     //call array traversal
    return is_added;
}

//add a new Screen to the ARR, recursive function - array traversal
bool ARRScreen::append(const Screen &source, Screen_Node **ptr)
{
    if (ptr >= (ARR +  size)) return false;                 //ARR is "full"
    int nodes = 1;                                          //counter to increment & compare with max(nodes)_per_chain
    if (append_chain(source, *ptr, nodes)) return true;     //call LLL recursive LLL traversal
    return append(source, ++ptr);                           //if LLL is "full" go to next array
}

//add a new Screen to the ARR, recursive function - LLL traversal
bool ARRScreen::append_chain(const Screen &source, Screen_Node *&current, int &nodes)
{
    if (nodes > max_per_chain) return false;                //if LLL is "full", exit
    if (!current){                //if we reach a null node and have space,
        current = new Screen_Node(source);                  //add stuff
        current -> set_next(nullptr);
        return true;                                        //return success
    }
    return append_chain(source, current -> get_next(), ++nodes); //otherwise traverse to next node
}

//search for a Screen and remove it from the ARR, wrapper
bool ARRScreen::remove(const std::string &to_remove)
{
    if (!ARR) return false;
    Screen_Node **ptr{ARR};
    return remove(to_remove, ptr);
}

//search for a Screen by name and remove it and return true if it exists in the ARR, recursive function - array traversal
bool ARRScreen::remove(const std::string &to_remove, Screen_Node **ptr)
{
    if (ptr >= ARR + size) return false;
    if (remove(to_remove, *ptr)) return true;
    return remove(to_remove, ++ptr);
}

//search for a Screen by name, remove it and return true if it exists in the ARR, recursive function - LLL traversal
bool ARRScreen::remove(const std::string &to_remove, Screen_Node *&current)
{
    if (!current) return false;
    if (current -> compare_names(to_remove.c_str())){
        Screen_Node *hold = current -> get_next();
        delete current;
        current = hold;
        return true;
    }
    return remove(to_remove, current -> get_next());
}


//remove all Screens from the ARR wrapper
int ARRScreen::remove_all()
{
    if (!ARR) return 0;
    Screen_Node **ptr{ARR};
    int removed = remove_all(ptr);
    delete [] ARR;
    ARR = nullptr;
    return removed;
}

int ARRScreen::remove_all(Screen_Node **ptr)
{
    if (ptr >= ARR + size) return 0;
    int removed = remove_all_chain(*ptr);
    return remove_all(++ptr) + removed;
}

int ARRScreen::remove_all_chain(Screen_Node *&current)
{
    if (!current) return 0;
    Screen_Node *hold = current -> get_next();
    delete current;
    current = nullptr;
    return remove_all_chain(hold) + 1;
}

//search for a Screen by name and return true if it exists in the ARR, wrapper
bool ARRScreen::find(const std::string &to_find) const
{
    if (!ARR) return false;
    Screen_Node **ptr{ARR};
    return find(to_find, ptr);
}

//search for a Screen by name and return true if it exists in the ARR, recursive function - array traversal
bool ARRScreen::find(const std::string &to_find, Screen_Node **ptr) const
{
    if (ptr >= ARR + size) return false;
    if (find(to_find, *ptr)) return true;
    return find(to_find, ++ptr);
}

//search for a Screen by name and return true if it exists in the ARR, recursive function - LLL traversal
bool ARRScreen::find(const std::string &to_find, Screen_Node *current) const
{
    if (!current) return false;
    if (current -> compare_names(to_find.c_str())){
        std::cout << std::endl;
        current -> display();
        return true;
    }
    return find(to_find, current -> get_next());
}

//search for Screens in the ARR with names matching the argument and retreive in an array of Screens, wrapper
int ARRScreen::retreive(const std::string &to_retreive, Screen *retreived) const
{
    if (!ARR) return false;
    int num_retreived{};
    Screen_Node **ptr{ARR};
    retreive(to_retreive, ptr, retreived, num_retreived);
    return num_retreived;
}

//search for a Screen by name and return true if it exists in the ARR, recursive function - array traversal
void ARRScreen::retreive(const std::string &to_retreive, Screen_Node **ptr, Screen *retreived, int &num_retreived) const
{
    if (ptr >= ARR + size) return;
    retreive(to_retreive, *ptr, retreived, num_retreived);
    retreive(to_retreive, ++ptr, retreived, num_retreived);
}

//search for a Screen by name and return true if it exists in the ARR, recursive function - LLL traversal
void ARRScreen::retreive(const std::string &to_retreive, Screen_Node *current, Screen *retreived, int &num_retreived) const
{
    if (!current) return;
    if (current -> compare_names(to_retreive.c_str())){
        retreived[num_retreived] = *current;
        ++num_retreived;
    }
    retreive(to_retreive, current -> get_next(), retreived, num_retreived);
}

//make a deep copy of the entire ARR, return number of items copied, wrapper
int ARRScreen::deep_copy(const ARRScreen &source)
{
    if (!source.ARR){
        ARR = nullptr;
    }

    size = source.size;
    max_per_chain = source.max_per_chain;
    ARR = new Screen_Node* [size];
    Screen_Node **dest_ptr{ARR};
    Screen_Node **source_ptr{source.ARR};
    init(dest_ptr);
    return deep_copy(source_ptr, dest_ptr);
}

int ARRScreen::deep_copy(Screen_Node **&source_ptr, Screen_Node **&dest_ptr)
{
    if (dest_ptr >= (ARR + size)) return 0;
    int num_copied = deep_copy(*source_ptr, *dest_ptr);
    return deep_copy(++source_ptr, ++dest_ptr) + num_copied;
}

int ARRScreen::deep_copy(Screen_Node *source, Screen_Node *&dest)
{
    if (!source){
        dest = nullptr;
        return 0;
    }

    dest = new Screen_Node(*source);
    dest -> set_next(nullptr);
    return deep_copy(source -> get_next(), dest -> get_next()) + 1;
}

void ARRScreen::put_nums() const
{
    printf("|\033[3;38;91m%4i. \033[0;0m", nums++);
}

void ARRScreen::reset_nums() const
{
    nums = 1;
}

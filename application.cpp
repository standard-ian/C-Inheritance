/*
 * Ian Leuty
 * ileuty@pdx.edu
 * 1/7/2025
 * CS302 Winter 2025 * Program 1
 *
 ********************************************************************
 *
 *
 * application implementation
 *
 *********************************************************************
 */

/*
 * menu class implementation
 * data menmbers are:
 *      ARRScreen Screens;
 *      CLLGraphics GPUs;
 *      vector<Motherboard> Motherboards;
 ***************************************************************************
 */
#include "application.h"
using namespace std;


Menu::Menu() : Screens(5, 20) {}

//Menu::Menu(ARRScreen &Screens_in, CLLGraphics &GPUs_in, std::vector<Motherboard> Motherboards_in) {}
void Menu::prompt()
{
    //push up to top of term window and print welcome
    cout << "\033[2J\033[1;1H" << "\033[38;3;32m" << endl
        << R"(

                                  .,,uod8B8bou,,.
                  ..,uod8BBBBBBBBBBBBBBBBRPFT?l!i:.
             ,=m8BBBBBBBBBBBBBBBRPFT?!||||||||||||||
             !...:!TVBBBRPFT||||||||||!!^^""'   ||||
             !.......:!?|||||!!^^""'            ||||
             !.........||||                     ||||
             !.........||||    Welcome to the   ||||
             !.........||||                     ||||
             !.........||||   Computer Parts    ||||
             !.........||||                     ||||
             !.........||||      Database!      ||||
             `.........||||                    ,||||
              .;.......||||               _.-!!|||||
       .,uodWBBBBb.....||||       _.-!!|||||||||!:'
    !YBBBBBBBBBBBBBBb..!|||:..-!!|||||||!iof68BBBBBb....
    !..YBBBBBBBBBBBBBBb!!||||||||!iof68BBBBBBRPFT?!::   `.
    !....YBBBBBBBBBBBBBBbaaitf68BBBBBBRPFT?!:::::::::     `.
    !......YBBBBBBBBBBBBBBBBBBBRPFT?!::::::;:!^"`;:::       `.
    !........YBBBBBBBBBBRPFT?!::::::::::^''...::::::;         iBBbo.
    `..........YBRPFT?!::::::::::::::::::::::::;iof68bo.      WBBBBbo.
      `..........:::::::::::::::::::::::;iof688888888888b.     `YBBBP^'
        `........::::::::::::::::;iof688888888888888888888b.     `
          `......:::::::::;iof688888888888888888888888888888b.
            `....:::;iof688888888888888888888888888888888899fT!
              `..::!8888888888888888888888888888888899fT|!^"'
                `' !!988888888888888888888888899fT|!^"'
                    `!!8888888888888888899fT|!^"'
                      `!988888888899fT|!^"'
                        `!9899fT|!^"'
                          `!^"'

         )" << "\033[0;0m" << endl;

    if (!load_cart()) cout << "\nERROR! Failed to load shopping cart." << endl;
    int choice{};
    do{
        cout << "\n\t\t     Main Menu\n\nPlease make a selection" << endl
            << "\n\t0. Quit\n\t1. Motherboards\n\t2. GPUs\n\t3. Displays (Screens)\n\t4. View Cart" << endl;
        choice = read_int();

        switch (choice){
            case 0:
                    break;

            case 1:
                    motherboard_options();
                    break;

            case 2:
                    graphics_options();
                    break;

            case 3:
                    screen_options();
                    break;

            case 4:
                    display_cart();
                    break;

            default:
                    break;
        }
    }while (choice);

    save_cart();
}



//present options for working w/ motherboards
void Menu::motherboard_options()
{
    cout << "\nMotherboards! Please select an option." << endl;

    int choice{};
    do{
        cout << "\n\t"
             << "0. Return to main menu\n\t"
             << "1. Display All Motherboards\n\t"
             << "2. Check if a motherboard is in the list\n\t"
             << "3. Find a motherboard and retreive it to your cart\n\t"
             << "4. Delete all Motherboards from the list\n\t"
             << "5. Delete a specific Motherboard\n\t"
             << "6. Add a new Motherboard\n\t"
             << "7. Load Motherboards from file" << endl;
        choice = read_int();

        switch (choice){
            case 0: break;

            case 1: {
                        if (Motherboards.empty()){
                            cout << "\nERROR! There are no motherboards in the list." << endl;
                            break;
                        }

                        cout << "\nApply display filters?" << endl;

                        int display_opt{};
                        do{
                            processor the_processor;
                            int processor_selection{};
                            int ports_in{};
                            string details_keyword{};
                            int count{1};

                            cout << "\n\t"
                                 << "0. Return to Motherboards menu\n\t"
                                 << "1. All\n\t"
                                 << "2. Processsor \n\t"
                                 << "3. Ports\n\t"
                                 << "4. Details contain" << endl;
                            display_opt = read_int();

                            //display options for motherboards
                            switch (display_opt){
                                case 0: break;

                                case 1: {
                                            cout << endl;
                                            for (const auto& item : Motherboards){
                                                //printf("|\033[38;3;91m%4i. \033[0;0m", count);
                                                cout << "|\033[38;3;91m" << right << setw(6) << count << ". \033[0;0m";
                                                if (item.display())
                                                    ++count;
                                            }
                                        }
                                        break;

                                case 2: {
                                            cout << "\nSelect which processor type boards to display." << endl
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
                                            for (const auto& item : Motherboards){
                                                if (item.is_processor(the_processor)){
                                                    //printf("|\033[38;3;91m%4i. \033[0;0m", count);
                                                    cout << "|\033[38;3;91m" << right << setw(6) << count << ". \033[0;0m";
                                                    if (item.display())
                                                        ++count;
                                                }
                                            }
                                        }
                                        break;

                                case 3: {
                                            cout << "\nEnter the number of USB ports." << endl;
                                            ports_in = read_int();
                                            for (const auto& item : Motherboards){
                                                if (item.is_more_than_ports(ports_in)){
                                                    //printf("|\033[38;3;91m%4i. \033[0;0m", count);
                                                    cout << "|\033[38;3;91m" << right << setw(6) << count << ". \033[0;0m";
                                                    if (item.display())
                                                        ++count;
                                                }
                                            }
                                        }
                                        break;

                                case 4: {
                                            cout << "\nEnter a keyword to search for in details." << endl;
                                            details_keyword = read_string();
                                            for (const auto& item : Motherboards){
                                                if (item.is_details_contain(details_keyword)){
                                                    //printf("|\033[38;3;91m%4i. \033[0;0m", count);
                                                    cout << "|\033[38;3;91m" << right << setw(6) << count << ". \033[0;0m";
                                                    if (item.display())
                                                        ++count;
                                                }
                                            }
                                        }
                                        break;

                                default:
                                        break;
                            }

                            if (count > 1)
                                cout << "\n" << count-1 << " Motherboards displayed" << endl;
                            else
                                cout << "\nERROR! No Motherboards in list." << endl;

                        }while (display_opt && again());
                    }
                    break;

            case 2: {
                        if (Motherboards.empty()){
                            cout << "\nERROR! There are no motherboards in the list." << endl;
                            break;
                        }
                        do{
                            bool found{false};
                            cout << "\nEnter a Motherboard name to find." << endl;
                            string to_find = read_string();
                            cout << endl;
                            for (const auto& item : Motherboards){
                                if (item.compare_names(to_find.c_str())){
                                    //item.display();
                                    found = true;
                                    break;
                                }
                            }

                            if (!found)
                                cout << "\nMotherboard not found." << endl;
                            else
                                cout << "\nThat Motherboard was found." << endl;

                        }while (again());
                    }
                    break;

            case 3: {
                        if (Motherboards.empty()){
                            cout << "\nERROR! There are no motherboards in the list." << endl;
                            break;
                        }
                        do{
                            int retreived{0};
                            cout << "\nEnter a Motherboard to retreive." << endl;
                            string to_retreive = read_string();
                            for (const auto& item : Motherboards){
                                if (item.compare_names(to_retreive.c_str())){
                                    cart.push_back(item);
                                    ++retreived;
                                }
                            }

                            cout << '\n' << retreived << " Motherboards matching that name were added to the cart.\n\nCart Updated!\n" << endl;

                            display_cart();

                        }while (again());
                    }
                    break;

            case 4: {
                        if (Motherboards.empty()){
                            cout << "\nERROR! There are no motherboards in the list." << endl;
                            break;
                        }
                        int removed = Motherboards.size();
                        Motherboards.clear();
                        cout << "\n" << removed << " Motherboards have been removed. The list is now empty." << endl;
                    }
                    break;

            case 5: {
                        if (Motherboards.empty()){
                            cout << "\nERROR! There are no motherboards in the list." << endl;
                            break;
                        }
                        do{
                            cout << "\nEnter a Motherboard name to remove." << endl;
                            string to_remove = read_string();
                            for (auto it = Motherboards.begin(); it != Motherboards.end();) {
                                if (it -> compare_names(to_remove.c_str()))
                                    it = Motherboards.erase(it);  // erase returns iterator to next element
                                else
                                    ++it;
                            }
                        }while (again());
                    }
                    break;

            case 6:
                    do{
                        Motherboards.push_back(Motherboard(1));

                        /*
                        //this was all moved down to the underlying data classes.
                        //
                        string name{};
                        string type{};

                        cout << "\nEnter the Motherboard name." << endl;
                        name = read_string();

                        do{
                            for (const auto& item : Motherboards){
                                if (item.compare_names(name.c_str())){
                                    name = "";
                                    found = true;
                                    cout << "\nERROR! That item already exists. Try entering a unique name." << endl;
                                    name = read_string();
                                    break;
                                }
                                else found = false;
                            }
                        }while (found);

                        cout << "Enter the product type." << endl;
                        type = read_string();

                        do{
                            cout << "\nERROR! The type must be \"Motherboard\"." << endl;
                            type = read_string();
                            cout << endl;
                        }while (type.compare("Motherboard"));

                        cout << "Enter the details or product specifications." << endl;
                        details = read_string();
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

                        Motherboards.push_back(Motherboard(usb_ports, details.c_str(), the_processor, name.c_str(), type.c_str()));
                        */

                    }while (again());
                    break;

            case 7:
                    if (!load_motherboards())
                        cout << "\nERROR! Failed to load Motherboards." << endl;
                    break;

            default: break;
        }
    } while (choice);
}

//present options for working with GPUs
void Menu::graphics_options()
{
    cout << "\nGPUs! Please select an option." << endl;
    int choice{};
    do{
        cout << "\n\t"
             << "0. Return to main menu\n\t"
             << "1. Display All GPUs\n\t"
             << "2. Check if a GPU is in the list\n\t"
             << "3. Find a GPU by name and retreive it to your cart\n\t"
             << "4. Delete all GPUs from the list\n\t"
             << "5. Delete a specific GPU\n\t"
             << "6. Add a new GPU.\n\t"
             << "7. Load GPUs from a file\n\t"
             << "8. Test the assignemnt operator for the GPU CLL" << endl;
        choice = read_int();

        switch (choice){
            case 0:
                    break;

            case 1: {
                        if (GPUs.empty()){
                            cout << "\nERROR! There are no GPUs in the list." << endl;
                            break;
                        }
                        cout << "\nApply display filters?" << endl;
                        int display_opt{};
                        do{
                            int vram_in{};
                            int fans_in{};
                            string review_keyword{""};

                            cout << "\n\t"
                                 << "0. Return to GPUs menu\n\t"
                                 << "1. All\n\t"
                                 << "2. Vram minimum\n\t"
                                 << "3. Fans\n\t"
                                 << "4. Review contains" << endl;

                            display_opt = read_int();
                            switch (display_opt){

                                case 1:
                                        break;

                                case 2: {
                                            cout << "\nEnter a VRAM amount." << endl;
                                            vram_in = read_int();
                                        }
                                        break;

                                case 3: {
                                            cout << "\nEnter a number of fans." << endl;
                                            fans_in = read_int();
                                        }
                                        break;

                                case 4: {
                                            cout << "\nEnter a keyword to search for in reviews." << endl;
                                            review_keyword = read_string();
                                        }
                                        break;

                                default:
                                        break;

                            }
                            int displayed = GPUs.display(display_opt, review_keyword, vram_in, fans_in);

                            if (!displayed)
                                cout << "\nERROR! No GPUs in the list." << endl;
                            else
                                cout << "\n" << displayed << " GPUs displayed." << endl;

                        }while (display_opt && again());
                    }
                    break;

            case 2: {
                        if (GPUs.empty()){
                            cout << "\nERROR! There are no GPUs in the list." << endl;
                            break;
                        }
                        do{
                            cout << "\nEnter a GPU name to find." << endl;
                            if (!GPUs.find(read_string()))
                                cout << "\nThat GPU was not found." << endl;
                            else{
                                cout << "\nThat GPU was found." << endl;
                            }
                        }while (again());
                    }
                    break;

            case 3: {
                        if (GPUs.empty()){
                            cout << "\nERROR! There are no GPUs in the list." << endl;
                            break;
                        }
                        do{
                            Graphics retreived[10];
                            cout << "\nEnter a GPU name to retreive matches." << endl;
                            int num_retreived{GPUs.retreive(read_string(), retreived)};

                            cout << '\n' << num_retreived << " GPUs matching that name were added to the cart.\n\nCart Updated!\n" << endl;
                            for (int item = 0; item < num_retreived; ++item)
                                cart.push_back(retreived[item]);

                            display_cart();

                        }while(again());
                    }
                    break;

            case 4: {
                        if (GPUs.empty()){
                            cout << "\nERROR! There are no GPUs in the list." << endl;
                            break;
                        }

                        cout << '\n' << GPUs.remove_all() << " GPUs have been removed. The list is now empty." << endl;
                        break;
                    }

            case 5: {
                        if (GPUs.empty()){
                            cout << "\nERROR! There are no GPUs in the list." << endl;
                            break;
                        }
                        do{
                            string to_remove{};
                            cout << "\nEnter a GPU name to remove from the list." << endl;
                            if (GPUs.remove(read_string()))
                                cout << "\nGPU removed." << endl;
                            else
                                cout << "\nThat GPU was not found." << endl;
                        }while (again());
                    }
                    break;

            case 6:
                    do{
                        if (!GPUs.append(Graphics(1)))
                            cout << "\nERROR! GPU could not be added." << endl;
                    }while (again());
                    break;

            case 7: {
                    if (!GPUs.load_graphics())
                        cout << "\nERROR! Failed to load GPUs." << endl;
                    }
                    break;

            case 8: {
                        CLLGraphics the_copy;
                        string null_keyword{""};
                        the_copy = GPUs;
                        cout << "\nThe original list of GPUs was copied"
                             //<< " (" << the_copy.deep_copy(GPUs) << " items),"
                             << " then cleared. Here is the copy:\n" << endl;
                        GPUs.remove_all();
                        the_copy.display(1, null_keyword, 0, 0);
                        cout << "\nHere is the original:\n" << endl;
                        GPUs.display(1, null_keyword, 0, 0);
                    }
                    break;

            default:
                    break;
        }
    }while (choice);
}

//present options for working with screens (displays)
void Menu::screen_options()
{
    cout << "\nScreens! Please select an option." << endl;
    int choice{};
    do{
        cout << "\n\t"
             << "0. Return to main menu\n\t"
             << "1. Display All Screens\n\t"
             << "2. Check if a Screen is in the list\n\t"
             << "3. Find a Screen by name and retreive it to your cart\n\t"
             << "4. Delete all Screens from the list\n\t"
             << "5. Delete a specific Screen\n\t"
             << "6. Add a new Screen.\n\t"
             << "7. Load Screens from a file\n\t"
             << "8. Test the assignment operator for the ARR" << endl;
        choice = read_int();
        switch (choice){
            case 0:
                    break;
            case 1: {
                        if (Screens.empty()){
                            cout << "\nERROR! There are no Screens in the list." << endl;
                            break;
                        }
                        cout << "\nApply display filters?" << endl;
                        int display_opt{};
                        int displayed{};
                        do{
                            string the_manufacturer{""};
                            cout << "\n\t"
                                 << "0. Return to Screens menu\n\t"
                                 << "1. All\n\t"
                                 << "2. Over 4K\n\t"
                                 << "3. Manufacturer\n\t"
                                 << "4. Include aspect ratio" << endl;
                            display_opt = read_int();
                            if (display_opt == 3){
                                cout << "\nEnter a manufaturer name." << endl;
                                the_manufacturer = read_string();
                            }
                            if (display_opt){
                                cout << endl;
                                displayed = Screens.display(display_opt, the_manufacturer);
                            }
                            if (!displayed)
                                cout << "\nERROR! No Screens in the list." << endl;
                            else
                                cout << "\n" << displayed << " Screens were displayed." << endl;

                        }while (display_opt && again());
                    }
                    break;

            case 2: {
                        if (Screens.empty()){
                            cout << "\nERROR! There are no Screens in the list." << endl;
                            break;
                        }
                        do{
                            cout << "\nEnter a Screen name to find." << endl;
                            if (!Screens.find(read_string()))
                                cout << "\nThat Screen was not found." << endl;
                            else{
                                cout << "\nThat Screen was found." << endl;
                            }
                        }while (again());
                    }
                    break;

            case 3:
                    {
                        if (Screens.empty()){
                            cout << "\nERROR! There are no Screens in the list." << endl;
                            break;
                        }
                        do{
                            Screen retreived[10];
                            cout << "\nEnter a Screen name to retreive matches." << endl;
                            int num_retreived{Screens.retreive(read_string(), retreived)};

                            cout << '\n' << num_retreived << " Screens matching that name were added to the cart.\n\nCart Updated!\n" << endl;
                            for (int item = 0; item < num_retreived; ++item)
                                cart.push_back(retreived[item]);

                            display_cart();

                        }while (again());
                    }
                    break;

            case 4: {
                        if (Screens.empty()){
                            cout << "\nERROR! There are no Screens in the list." << endl;
                            break;
                        }
                        cout << '\n' << Screens.remove_all() << " Screens have been removed. The list is now empty." << endl;
                    }
                    break;

            case 5: {

                        if (Screens.empty()){
                            cout << "\nERROR! There are no Screens in the list." << endl;
                            break;
                        }

                        do{
                            cout << "\nEnter a Screen name to remove." << endl;
                            if (!Screens.remove(read_string()))
                                cout << "\nThat Screen was not found." << endl;
                            else{
                                cout << "\nScreen removed." << endl;
                            }
                        }while (again());
                    }

                    break;

            case 6:
                    do{
                        if (!Screens.append(Screen(1)))
                            cout << "\nERROR! Screen could not be added." << endl;

                    }while (again());
                    break;

            case 7: {
                    if (!Screens.load_screens())
                        cout << "\nERROR! Failed to load screens." << endl;
                    }
                    break;

            case 8: {
                        ARRScreen the_copy(0,0);
                        string null_string{};
                        the_copy = Screens;
                        cout << "\nThe original list of Motherboards was copied"
                             //<< " (" << the_copy.deep_copy(Screens) << " items)," <<
                             << " then cleared. Here is the copy:\n" << endl;
                        Screens.remove_all();
                        the_copy.display(1, null_string);
                        cout << "\nHere is the original:\n" << endl;
                        Screens.display(1, null_string);

                    }
                    break;

            default:
                     break;
        }
    }while (choice);
}

//reads a string in and returns it
const string Menu::read_string()
{
    string the_string;
    cout << "\033[38;5;32m" << ">>" << "\033[0m";;
    getline(cin, the_string);
    return the_string;
}

//reads an int in and return it
const int Menu::read_int()
{
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

//utility function to prompt repeat
bool Menu::again()
{
    char again{};
    cout << "\nAgain? (y/n)" << endl;
    cout << "\033[38;5;32m" << ">>" << "\033[0m";;
    cin >> again;
    cin.ignore(100, '\n');
    if (toupper(again) == 'Y')
        return true;
    return false;
}

//load motherboards in from file to the vector
bool Menu::load_motherboards()
{
    cout << "\nEnter the name of the file with the Motherboards inventory." << endl;
    string filename = read_string();
    filein.open(filename);

    if (!filein) return false;
    filein.peek();                  //check the file

    while (!filein.eof()){            //while !eof flag
        Motherboards.push_back(Motherboard(filein));
        filein.peek();
    }

    filein.close();
    return true;
}

//load the cart in from a file to the vector
bool Menu::load_cart()
{
    cout << "\nEnter the name of the file containing your cart." << endl;
    string filename = read_string();
    filein.open(filename);
    if (!filein) return false;
    filein.peek();

    while (!filein.eof()){
        string name{};
        string type{};

        if (!read_string_from_file(name, ',')) return false;
        if (!read_string_from_file(type, '\n')) return false;

        cart.push_back(Product(name.c_str(), type.c_str()));

        filein.peek();
    }
    filein.close();
    return true;
}

//write the cart out to a file
bool Menu::save_cart()
{
    cout << "\nEnter the name of the file to store your cart." << endl;
    string filename = read_string();
    fileout.open(filename);
    for (auto &item : cart){
        char *name = nullptr;
        char *type = nullptr;
        item.copy_name(name);
        item.copy_type(type);
        fileout << name << ',' << type << endl;
        delete [] name;
        delete [] type;
    }
    fileout.close();
    return true;
}


//display the cart
void Menu::display_cart(){
    int count{1};
    for (const auto& item : cart){
        //cout << "\033[38;3;91m" << count++ << ". " << "\033[0;0m";
        //printf("|\033[38;3;91m%4i. \033[0;0m", count++);
        cout << "|\033[38;3;91m" << right << setw(6) << count++ << ". \033[0;0m";
        item.display();
        cout << endl;
    }
}

//utility function to read in from a file
bool Menu::read_string_from_file(string &dest, char delim)
{
    filein.peek();
    if (filein.eof()) return false;
    getline(filein, dest, delim);
    return true;
}

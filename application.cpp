/*
 * Ian Leuty
 * ileuty@pdx.edu
 * 1/7/2025
 * CS302 Winter 2025
 * Program 1
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
    cout << "\033[2J\033[1;1H" << "\033[3;38;32m" << endl
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
            case 4: {
                        display_cart();
                    }
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
        cout << "\n\t0. Return to main menu\n\t1. Display All Motherboards\n\t2. Find a Motherboard by name and display it\n\t3. Find a motherboard and retreive it to your cart" << endl
            << "\t4. Delete all Motherboards from the list\n\t5. Delete a specific Motherboard\n\t6. Add a new Motherboard\n\t7.Load Motherboards from file" << endl;
        choice = read_int();

        switch (choice){
            case 0: break;

            case 1: {
                        cout << "\nApply display filters?" << endl;
                        int display_opt{};
                        do{
                            processor the_processor;
                            int processor_selection{};
                            int ports_in{};
                            string details_keyword{};
                            int count{1};
                            cout << "\n\t0. Return to Motherboards menu\n\t1. All\n\t2. Processsor \n\t3. Ports\n\t4. Details contain" << endl;
                            display_opt = read_int();
                            if (display_opt == 2){
                                cout << "\nelect which processor type boards to display." << endl
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
                            else if (display_opt == 3){
                                cout << "\nEnter the number of USB ports." << endl;
                                ports_in = read_int();
                            }
                            else if (display_opt == 4){
                                cout << "\nEnter a keyword to search for in details." << endl;
                                details_keyword = read_string();
                            }
                            cout << endl;
                            switch (display_opt){
                                case 0: break;

                                case 1:
                                        for (const auto& item : Motherboards){
                                            printf("|\033[3;38;91m%4i. \033[0;0m", count++);
                                            item.display();
                                        }
                                        break;

                                case 2:
                                        for (const auto& item : Motherboards){
                                            if (item.is_processor(the_processor)){
                                                printf("|\033[3;38;91m%4i. \033[0;0m", count++);
                                                item.display();
                                            }
                                        }
                                            break;

                                case 3:
                                        for (const auto& item : Motherboards){
                                            if (item.is_more_than_ports(ports_in)){
                                                printf("|\033[3;38;91m%4i. \033[0;0m", count++);
                                                item.display();
                                            }
                                        }
                                            break;

                                case 4:
                                        for (const auto& item : Motherboards){
                                            if (item.is_details_contain(details_keyword)){
                                                printf("|\033[3;38;91m%4i. \033[0;0m", count++);
                                                item.display();
                                            }
                                        }
                                        break;

                                default: break;
                            }
                        }while (display_opt && again());
                    }
                    break;

            case 2:
                    do{
                        bool found{false};
                        cout << "\nEnter a Motherboard name to find." << endl;
                        string to_find = read_string();
                        cout << endl;
                        for (const auto& item : Motherboards){
                            if (item.compare_names(to_find.c_str())){
                                item.display();
                                found = true;
                                break;
                            }
                        }

                        if (!found)
                            cout << "\nMotherboard not found." << endl;

                    }while (again());
                    break;

            case 3:
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
                    break;

            case 4: {
                       Motherboards.clear();
                       cout << "\nAll Motherboards removed." << endl;
                    }
                    break;

            case 5:
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
                    break;

            case 6:
                    do{
                        int usb_ports{};
                        int processor_selection{};
                        processor the_processor{processor::none};
                        string details{};
                        string name{};
                        string type{};

                        cout << "\nEnter the product type." << endl;
                        type = read_string();
                        cout << "\nEnter the Motherboard name." << endl;
                        name = read_string();
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

                    }while (again());
                    break;

            case 7:{
                    if (!load_motherboards())
                        cout << "\nERROR! Failed to load Motherboards." << endl;
                   }
                    break;

            default: break;
        }
    }while (choice);
}

//present options for working with GPUs
void Menu::graphics_options()
{
    cout << "\nGPUs! Please select an option." << endl;
    int choice{};
    do{
        cout << "\n\t0. Return to main menu\n\t1. Display All GPUs\n\t2. Find a GPU by name and display it\n\t3. Find a GPU by name and retreive it to your cart" << endl
            <<  "\t4. Delete all GPUs from the list\n\t5. Delete a specific GPU\n\t6. Add a new GPU.\n\t7. Load GPUs from a file\n\t8. Test the assignemnt operator for the GPU CLL" << endl;
        choice = read_int();

        switch (choice){
            case 0:
                    break;

            case 1: {
                        cout << "\nApply display filters?" << endl;
                        int display_opt{};
                        do{
                            int vram_in{};
                            int fans_in{};
                            string review_keyword{""};

                            cout << "\n\t0. Return to GPUs menu\n\t1. All\n\t2. Vram minimum\n\t3. Fans\n\t4. Review contains" << endl;

                            display_opt = read_int();

                            if (display_opt == 2){
                                cout << "\nEnter a VRAM amount." << endl;
                                vram_in = read_int();
                            }

                            else if (display_opt == 3){
                                cout << "\nEnter a number of fans." << endl;
                                fans_in = read_int();
                            }

                            else if (display_opt == 4){
                                cout << "\nEnter a keyword to search for in reviews." << endl;
                                review_keyword = read_string();
                            }

                            if (display_opt){
                                cout << endl;
                                GPUs.display(display_opt, review_keyword, vram_in, fans_in);
                            }

                        }while (display_opt && again());
                    }
                    break;

            case 2:
                    do{
                        cout << "\nEnter a GPU name to find." << endl;
                        if (!GPUs.find(read_string()))
                            cout << "\nThat GPU was not found." << endl;
                        else{
                            cout << "\nThat GPU was found." << endl;
                        }
                    }while (again());
                    break;

            case 3:
                    do{
                        Graphics retreived[10];
                        cout << "\nEnter a GPU name to retreive matches." << endl;
                        int num_retreived{GPUs.retreive(read_string(), retreived)};

                        cout << '\n' << num_retreived << " GPUs matching that name were added to the cart.\n\nCart Updated!\n" << endl;
                        for (int item = 0; item < num_retreived; ++item)
                            cart.push_back(retreived[item]);

                        display_cart();

                    }while(again());
                    break;

            case 4:
                    cout << '\n' << GPUs.remove_all() << " GPUs have been removed. The list is now empty." << endl;
                    break;

            case 5:
                    do{
                        string to_remove{};
                        cout << "\nEnter a GPU name to remove from the list." << endl;
                        if (GPUs.remove(read_string()))
                            cout << "\nGPU removed." << endl;
                        else
                            cout << "\nThat GPU was not found." << endl;
                    }while (again());
                    break;

            case 6:
                    do{
                        int fans{};
                        int vram{};
                        string name{};
                        string review{};
                        string type{};

                        cout << "\nEnter the product type." << endl;
                        type = read_string();
                        cout << "\nEnter the Graphics Card name." << endl;
                        name = read_string();
                        cout << "Enter the number of fans." << endl;
                        fans = read_int();
                        cout << "Enter the amount of VRAM." << endl;
                        vram = read_int();
                        cout << "Enter a review for the card." << endl;
                        review = read_string();

                        if (!GPUs.append(Graphics(vram, fans, review, name.c_str(), type.c_str())))
                            cout << "\nERROR! GPU could not be added." << endl;

                    }while (again());
                    break;

            case 7: {
                    if (!load_graphics())
                        cout << "\nERROR! Failed to load GPUs." << endl;
                    }
                    break;

            case 8: {
                        CLLGraphics the_copy;
                        string null_keyword{""};
                        the_copy = GPUs;
                        cout << "\nThe original list of GPUs was copied" /*<< " (" << the_copy.deep_copy(GPUs) << " items),"*/ << " then cleared. Here is the copy:\n" << endl;
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
        cout << "\n\t0. Return to main menu\n\t1. Display All Screens\n\t2. Find a Screen by name and display it\n\t3. Find a Screen by name and retreive it to your cart" << endl
            << "\t4. Delete all Screens from the list\n\t5. Delete a specific Screen\n\t6. Add a new Screen.\n\t7. Load Screens from a file\n\t8. Test the assignment operator for the ARR" << endl;
        choice = read_int();
        switch (choice){
            case 0:
                    break;
            case 1: {
                        cout << "\nApply display filters?" << endl;
                        int display_opt{};
                        do{
                            string the_manufacturer{""};
                            cout << "\n\t0. Return to Screens menu\n\t1. All\n\t2. Over 4K\n\t3. Manufacturer\n\t4. Include aspect astio" << endl;
                            display_opt = read_int();
                            if (display_opt == 3){
                                cout << "\nEnter a manufaturer name." << endl;
                                the_manufacturer = read_string();
                            }
                            if (display_opt){
                                cout << endl;
                                Screens.display(display_opt, the_manufacturer);
                            }

                        }while (display_opt && again());
                    }
                    break;

            case 2:
                    do{
                        cout << "\nEnter a Screen name to find." << endl;
                        if (!Screens.find(read_string()))
                            cout << "\nThat Screen was not found." << endl;
                        else{
                            cout << "\nThat Screen was found." << endl;
                        }
                    }while (again());
                    break;

            case 3:
                    do{
                        Screen retreived[10];
                        cout << "\nEnter a Screen name to retreive matches." << endl;
                        int num_retreived{Screens.retreive(read_string(), retreived)};

                        cout << '\n' << num_retreived << " Screens matching that name were added to the cart.\n\nCart Updated!\n" << endl;
                        for (int item = 0; item < num_retreived; ++item)
                            cart.push_back(retreived[item]);

                        display_cart();

                    }while (again());
                    break;

            case 4: {

                    cout << '\n' << Screens.remove_all() << " Screens have been removed. The list is now empty." << endl;
                    }
                    break;

            case 5: {
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
                        int width{};
                        int height{};
                        string name{};
                        string manufacturer{};
                        string type{};

                        cout << "\nEnter the product type." << endl;
                        type = read_string();
                        cout << "\nEnter the Display's name." << endl;
                        name = read_string();
                        cout << "Enter the width." << endl;
                        width = read_int();
                        cout << "Enter the height." << endl;
                        height = read_int();
                        cout << "Enter the manufacturer." << endl;
                        manufacturer = read_string();

                        if (!Screens.append(Screen(height, width, manufacturer, name.c_str(), type.c_str())))
                            cout << "\nERROR! Screen could not be added." << endl;

                    }while (again());
                    break;

            case 7: {
                    if (!load_screens())
                        cout << "\nERROR! Failed to load screens." << endl;
                    }
                    break;

            case 8: {
                        ARRScreen the_copy(0,0);
                        string null_string{};
                        the_copy = Screens;
                        cout << "\nThe original list of Motherboards was copied" <</* " (" << the_copy.deep_copy(Screens) << " items)," << */" then cleared. Here is the copy:\n" << endl;
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
    cout << '>';
    getline(cin, the_string);
    return the_string;
}

//reads an int in and return it
const int Menu::read_int()
{
    int the_int{};
    cout << '>';
    cin >> the_int;
    while (cin.fail()){
        cin.clear();
        cin.ignore(100, '\n');
        cout << "\nYou must enter a number.\n>";
        cin >> the_int;
    }
    cin.ignore(100, '\n');
    return the_int;
}

//utility function to prompt repeat
bool Menu::again()
{
    char again{};
    cout << "\nAgain? (y/n)\n>";
    cin >> again;
    cin.ignore(100, '\n');
    if (toupper(again) == 'Y')
        return true;
    return false;
}

bool Menu::load_motherboards()
{
    cout << "\nEnter the name of the file with the Motherboards inventory." << endl;
    string filename = read_string();
    filein.open(filename);

    if (!filein) return false;
    filein.peek();                  //check the file

    while (!filein.eof()){            //while !eof flag
        processor the_processor{processor::none};
        int usb_ports{};
        int processor_selection{};
        string details{};
        string name{};
        string type{};

        if (!read_string_from_file(name, ',')) return false;
        if (!read_string_from_file(type, ',')) return false;
        if (!read_string_from_file(details, ',')) return false;
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

        Motherboards.push_back(Motherboard(usb_ports, details.c_str(), the_processor, name.c_str(), type.c_str()));

        filein.peek();
    }
    filein.close();
    return true;
}


bool Menu::load_screens()
{
    cout << "\nEnter the name of the file with the Screens inventory." << endl;
    string filename = read_string();
    filein.open(filename);

    if (!filein) return false;
    filein.peek();                  //check the file

    while (!filein.eof()){            //while !eof flag
        int height{};
        int width{};
        string manufacturer{};
        string name{};
        string type{};

        if (!read_string_from_file(name, ',')) return false;
        if (!read_string_from_file(type, ',')) return false;
        filein >> width; filein.ignore(100, ',');
        filein >> height; filein.ignore(100, ',');
        if (!read_string_from_file(manufacturer, '\n')) return false;

        if (!Screens.append(Screen(width, height, manufacturer, name.c_str(), type.c_str()))) return false;

        filein.peek();
    }
    filein.close();
    return true;
}


bool Menu::load_graphics()
{
    cout << "\nEnter the name of the file with the GPU inventory." << endl;
    string filename = read_string();
    filein.open(filename);

    if (!filein) return false;
    filein.peek();

    while (!filein.eof()){
        int vram{};
        int fans{};
        string review{};
        string name{};
        string type{};

        if (!read_string_from_file(name, ',')) return false;
        if (!read_string_from_file(type, ',')) return false;
        if (!read_string_from_file(review, ',')) return false;
        filein >> vram; filein.ignore(100, ',');
        filein >> fans; filein.ignore(100, '\n');


        if (!GPUs.append(Graphics(vram, fans, review, name.c_str(), type.c_str()))) return false;

        filein.peek();
    }
    filein.close();
    return true;
}

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
    }
    fileout.close();
    return true;
}

bool Menu::read_string_from_file(string &dest, char delim)
{
    const int SIZE{1000};
    char temp[SIZE];
    filein.get(temp, SIZE, delim);
    if (filein.peek() != delim) return false;
    filein.ignore(100, delim);
    dest = temp;
    return true;
}

void Menu::display_cart(){
    int count{1};
    for (const auto& item : cart){
        //cout << "\033[3;38;91m" << count++ << ". " << "\033[0;0m";
        printf("|\033[3;38;91m%4i. \033[0;0m", count++);
        item.display();
        cout << endl;
    }
}

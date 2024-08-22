//
// Created by LookO on 10/19/2023.
//
#include <iostream>
#include <ostream>
#include <fstream>
#include "Image.h"
#include <cstring> // This for strcmp

using namespace std;
Image t_image;
//you may need to track image to the first input later in the project !!!!!
Image input_1;
Image input_2;
Image input_3; // put here because of combine
int no = 0;


bool tgachecker(string& tga)
{
    int index = tga.find_last_of(".");
    index++;
    string format = tga.substr(index);
    if(format == "tga")
    {
        return true;
    }
    else
        return false;

}

string conversion(char*& command)
{
    string convert = command;
    return convert;

}


int main(int argc, char** argv) {


//(1) Create a main() with arguments argc and argv
//(2) print out argc

//(3) Check if user entered "help" and only "help" using an if-statement
//

    if (argc == 1 )
    {
        cout << "Project 2: Image Processing, Fall 2023\n"
                "\n"
                "Usage:\n"
                " ./project2.out [output] [firstImage] [method] [...]   " << endl;
        return 0;

    }
    else if (strcmp(argv[1], "--help") == 0) {
        cout << "Project 2: Image Processing, Fall 2023\n"
                "\n"
                "Usage:\n"
                " ./project2.out [output] [firstImage] [method] [...]   " << endl;
        return 0;

    }
    int argIndex = 1;
    string command_input = argv[argIndex];


    //(4) Create a while-loop that runs while argIndex is less than argc
    try {

        while (argIndex < argc) {

            //output clarification
            string command = argv[argIndex];
            if (tgachecker(command)) {
                argIndex++;
            } else {
                cout << "Invalid file name.";
                no++;
                break;
            }

            //input clarification:
            //argIndex == 2 at this point
            command_input = argv[argIndex];

            if (tgachecker(command_input)) {
                ifstream inputt(command_input, ios_base::binary);

                if (!inputt.is_open()) {
                    cout << "File does not exist." << endl;
                    no++;

                    break;
                } else {

                    t_image.read(conversion(argv[argIndex]));

                    argIndex++;

                }
            } else {
                cout << "Invalid file name.";
                no++;

                break;
            }
            break;
        }

        ///method clarification
        //argIndex == 3 at this point//

            while (argIndex < argc)
            {
                if(no>0)
                {
                    break;
                }


            command_input = argv[argIndex];


           // mulitply functionality
            if (command_input == "multiply")
            {
                if(argc == 4)
                {
                    throw invalid_argument("Missing argument.");
                }
                argIndex++;
                //argIndex == 4 at this point another input
                command_input = argv[argIndex];
                cout << command_input;


                if (tgachecker(command_input)) {
                    ifstream inputt(command_input, ios_base::binary);

                    if (!inputt.is_open()) {
                        cout << "Invalid argument, file does not exist." << endl;
                        break;
                    } else {
                        input_2.read(command_input);
                        t_image = t_image.multiply(t_image, input_2);
                        t_image.write(conversion(argv[1]));
                        argIndex++;


                    }
                } else {
                    cout << "Invalid argument, invalid file name.";
                    break;
                }


                /* t_image.

                 Image layer1;
                 layer1.read("input/layer1.tga");

                 Image pattern1;
                 pattern1.read("input/pattern1.tga");

                 Image task1;
                 task1 = layer1.multiply(layer1, pattern1);
                 task1.write("output/part1.tga");
                 */


            }
            //subtract functionality
            else if (command_input == "subtract")
            {

                if(argc == 4)
                {
                    throw invalid_argument("Missing argument.");
                }


                argIndex++;
                //argIndex == 4 at this point another input
                command_input = argv[argIndex];
                cout << command_input;


                if (tgachecker(command_input)) {
                    ifstream inputt(command_input, ios_base::binary);

                    if (!inputt.is_open()) {
                        cout << "Invalid argument, file does not exist." << endl;
                        break;
                    } else {
                        input_2.read((command_input));
                        t_image = t_image.subtract(t_image, input_2);
                        t_image.write(conversion(argv[1]));
                        argIndex++;
                    }
                }
                else
                {
                    cout << "Invalid argument, invalid file name.";
                    break;
                }


            }
            else if (command_input == "flip")
            {
                t_image = t_image.upsidedown(t_image);
                t_image.write(conversion(argv[1]));
                argIndex++;
            }

            //overlay
            else if (command_input == "overlay")
            {

                if(argc == 4)
                {
                    throw invalid_argument("Missing argument.");
                }


                argIndex++;
                //argIndex == 4 at this point another input
                command_input = argv[argIndex];


                if (tgachecker(command_input)) {
                    ifstream inputt(command_input, ios_base::binary);

                    if (!inputt.is_open()) {
                        cout << "Invalid argument, file does not exist." << endl;
                        break;
                    } else {
                        input_2.read(conversion(argv[argIndex]));
                        t_image = t_image.overlay(t_image, input_2);
                        t_image.write(conversion(argv[1]));
                        argIndex++;
                    }
                }
                else
                {
                    cout << "Invalid argument, invalid file name.";
                    break;
                }



            }

            //screen function
            else if (command_input == "screen")
            {

                if(argc == 4)
                {
                    throw invalid_argument("Missing argument.");
                }


                argIndex++;
                //argIndex == 4 at this point another input
                command_input = argv[argIndex];


                if (tgachecker(command_input)) {
                    ifstream inputt(command_input, ios_base::binary);

                    if (!inputt.is_open()) {
                        cout << "Invalid argument, file does not exist." << endl;
                        break;
                    } else {
                        input_2.read(conversion(argv[argIndex]));
                        t_image = t_image.screen(t_image, input_2);
                        t_image.write(conversion(argv[1]));
                        argIndex++;
                    }
                }
                else
                {
                    cout << "Invalid argument, invalid file name.";
                    break;
                }



            }
            else if (command_input == "onlyred")
            {
                t_image = t_image.redd(t_image,t_image);
                t_image.write(conversion(argv[1]));
                argIndex++;
            }
            else if (command_input == "onlygreen")
            {
                t_image = t_image.greenn(t_image,t_image);
                t_image.write(conversion(argv[1]));
                argIndex++;
            }
            else if (command_input == "onlyblue")
            {
                t_image = t_image.bluee(t_image,t_image);
                t_image.write(conversion(argv[1]));
                argIndex++;
            }

            else if (command_input == "addgreen")
            {
                int increase;
                argIndex++;
                command_input = argv[argIndex];
                try {
                     increase = stoi(command_input);
                }
                catch(invalid_argument)
                {
                    throw invalid_argument("Invalid argument, file does not exist.");
                }



                t_image = t_image.add_green(t_image,increase);
                t_image.write(conversion(argv[1]));
                argIndex++;
            }

            else if (command_input == "addred")
            {
                int increase;
                argIndex++;
                command_input = argv[argIndex];
                try {
                    increase = stoi(command_input);
                }
                catch(invalid_argument)
                {
                    throw invalid_argument("Invalid argument, file does not exist.");
                }



                t_image = t_image.add_red(t_image,increase);
                t_image.write(conversion(argv[1]));
                argIndex++;
            }

            else if (command_input == "addblue")
            {
                int increase;
                argIndex++;
                command_input = argv[argIndex];
                try {
                    increase = stoi(command_input);
                }
                catch(invalid_argument)
                {
                    throw invalid_argument("Invalid argument, file does not exist.");
                }



                t_image = t_image.add_blue(t_image,increase);
                t_image.write(conversion(argv[1]));
                argIndex++;
            }

            else if (command_input == "combine")
            {
                argIndex++;
                command_input = argv[argIndex];
                if(argc < 6)
                {
                    throw invalid_argument("Missing argument.");
                }

            for(int i = 0; i < 2; i++)
            {
                if (tgachecker(command_input))
                {
                    ifstream inputt(command_input, ios_base::binary);

                    if (!inputt.is_open())
                    {
                        cout << "Invalid argument, file does not exist." << endl;
                        break;
                    }
                    else if(i == 0)
                    {
                        input_2.read(conversion(argv[argIndex]));
                        argIndex++;
                    }
                    else if(i == 1)
                    {
                        input_3.read(conversion(argv[argIndex]));
                        argIndex++;
                    }
                }

                else
                {
                    cout << "Invalid argument, invalid file name.";
                    break;
                }
            }
            t_image = t_image.combine(t_image,input_2,input_3);
            t_image.write(conversion(argv[1]));


        }
            else if (command_input == "scalered")
            {
                int increase;
                argIndex++;
                command_input = argv[argIndex];
                try {
                    increase = stoi(command_input);
                    if(increase < 0)
                    {
                        throw invalid_argument("Invalid argument, expected number.");

                    }
                }
                catch(invalid_argument)
                {
                    throw invalid_argument("Invalid argument, expected number.");
                }


                t_image = t_image.scale_red(t_image,increase);
                t_image.write(conversion(argv[1]));
                argIndex++;
            }
            else if (command_input == "scaleblue")
            {
                int increase;
                argIndex++;
                command_input = argv[argIndex];
                try {
                    increase = stoi(command_input);
                    if(increase < 0)
                    {
                        throw invalid_argument("Invalid argument, expected number.");

                    }
                }
                catch(invalid_argument)
                {
                    throw invalid_argument("Invalid argument, expected number.");
                }



                t_image = t_image.scale_blue(t_image,increase);
                t_image.write(conversion(argv[1]));
                argIndex++;
            }
            else if (command_input == "scalegreen")
            {
                int increase;
                argIndex++;
                command_input = argv[argIndex];
                try {
                    increase = stoi(command_input);
                    if(increase < 0)
                    {
                        throw invalid_argument("Invalid argument, expected number.");

                    }
                }
                catch(invalid_argument)
                {
                    throw invalid_argument("Invalid argument, expected number.");
                }



                t_image = t_image.scale_green(t_image,increase);
                t_image.write(conversion(argv[1]));
                argIndex++;
            }
            else
            {
                throw invalid_argument("Invalid method name.");

            }
    }
            //if its not any of function names throw an error but after you define every function


    }
    catch(invalid_argument &e)
    {
        cout<< e.what()<<endl;
    }
}














            //(16) Add a try block around steps 4 - 16

        //(17) Add a catch block "catch(invalid_argument &e)"



/* Image layer1;
    layer1.read("input/layer1.tga");

    Image pattern1;
    pattern1.read("input/pattern1.tga");

    Image task1;
    task1 = layer1.multiply(layer1, pattern1);
    task1.write("output/part1.tga");
//-------------------------------------------
    Image car;
    car.read("input/car.tga");

    Image layer2;
    layer2.read("input/layer2.tga");

    Image task2;
    task2 = car.subtract(car, layer2);
    task2.write("output/part2.tga");
//----------------------------------

    Image lay1;
    lay1.read("input/layer1.tga");

    Image pattern2;
    pattern2.read("input/pattern2.tga");



    Image text;
    text.read("input/text.tga");



    Image task3;
    task3 = pattern2.screen(lay1, pattern2, text);
    task3.write("output/part3.tga");

    //--------------------------------------

    Image circles;
    circles.read("input/circles.tga");


    Image mixed;
    mixed = circles.multiply(layer2, circles);

    Image task4;
    task4 = circles.subtract(mixed, pattern2);

    task4.write("output/part4.tga");
//---------------------------------------
    Image task5;

    Image lay1of_2;
    lay1of_2.read("input/layer1.tga");
    task5 = layer1.overlay(lay1of_2, pattern1);
    task5.write("output/part5.tga");

    //---------------------------------------

    Image task6;

    Image car_2;
    car_2.read("input/car.tga");
    task6 = car_2.add_green(car_2);
    task6.write("output/part6.tga");
//---------------------------------------------

    Image task7;

    Image car_3;
    car_3.read("input/car.tga");
    task7 = car_3.change(car_3);
    task7.write("output/part7.tga");
//---------------------------------------------
    Image task8 = car;

    Image car_4 = car;

    task8 = car_4.greenn(task8,car_4);
    task8.write("output/part8_g.tga");


    task8 = car_4.redd(task8, car_4);
    task8.write("output/part8_r.tga");

    task8 = car_4.bluee(task8, car_4);
    task8.write("output/part8_b.tga");








    //task9
    Image lR;
    lR.read("input/layer_red.tga");
    Image lG;
    lG.read("input/layer_green.tga");
    Image lB;
    lB.read("input/layer_blue.tga");


    Image task9;
    task9.header = lR.header;

    task9 = task9.color(lB, lG, lR, task9);
    task9.write("output/part9.tga");





    Image text_2;

    text_2.read("input/text2.tga");

    Image task10 = text_2.upsidedown(text_2);
    task10.write("output/part10.tga");



   */


// /b .\examples\EXAMPLE_part2.tga .\'Project 2'\task2.tga

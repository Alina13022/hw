#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include "end.h"
#include "get_rand.h"


int main() {
    system ("chcp 65001" );
    srand(time(NULL));

    string array;
    string for_record;
    string name_first, name_second;
    string mode;
    string alphabet[11] = {"Q", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
    string alphabet_r[11] = {"ы", "А", "Б", "В", "Г", "Д", "Е", "Ж", "З", "И", "К"};
    string numbers[11] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
    string field[11][11];
    string field_1[11][11];
    string coordinate_letter;
    int coordinate_index;
    int array_letters[7];
    int array_numbers[7];
    int index_letters = 0;
    int index_numbers = 0;
    bool hit;
    string field_empty_1[11][11];
    int field_in_s_empty[11][11];
    string field_empty_2[11][11];
    int left_or_down;
    bool field_in_s[11][11];
    char yes;
    string letter;
    bool miss_or_not=false;
    string language;


    choose_language:
    cout<<"Choose language. If english, enter 'e'\n Выберите язык. Если русский, введите 'r'\n Seleziona la lingua. Se italiano, digita 'i'\n";
    cin >> language;
    if (language=="e") {
//Заполнение полей
        for (int i = 0; i <= 10; i++) {
            for (int j = 0; j <= 10; j++) {
                if ((i == 0) && (j != 0)) {
                    field[i][j] = alphabet[j];
                }
                if ((j == 0) && (i != 0)) {
                    field[i][j] = numbers[i];
                }
                if (!(j == 0) && (i != 0) && (i == 0) && (j != 0)) {
                    field[i][j] = " ";
                }
                if ((i == 0) && (j != 0)) {
                    field_1[i][j] = alphabet[j];
                }
                if ((j == 0) && (i != 0)) {
                    field_1[i][j] = numbers[i];
                }
                if (!(j == 0) && (i != 0) && (i == 0) && (j != 0)) {
                    field_1[i][j] = " ";
                }
                if ((i == 0) && (j != 0)) {
                    field_empty_1[i][j] = alphabet[j];
                }
                if ((j == 0) && (i != 0)) {
                    field_empty_1[i][j] = numbers[i];
                }
                if (!(j == 0) && (i != 0) && (i == 0) && (j != 0)) {
                    field_empty_1[i][j] = " ";
                }
                if ((i == 0) && (j != 0)) {
                    field_empty_2[i][j] = alphabet[j];
                }
                if ((j == 0) && (i != 0)) {
                    field_empty_2[i][j] = numbers[i];
                }
                if (!(j == 0) && (i != 0) && (i == 0) && (j != 0)) {
                    field_empty_2[i][j] = " ";
                }
                field_in_s[i][j] = false;
                field_in_s_empty[i][j]=0;
            }
        }
//Правила

        cout << R"(***Rules***
    The goal of the game is to drown all the opponent's combat units.
    The player chooses which cell he wants to check.
    After which he first calls its letter, and then a number (for example, "E8").
    If the second player has a ship in such a cell, the person answers "hit" or "killed".
    The attacker puts a cross in the right place on the drawn empty field.
    After being hit, a person gets the right to another shot.

    When he calls the cell that the opponent has empty, he will answer "by".
    After that, the move goes to the second player.
    The winner is the one who first discovered all the opponent's vessels.

    ***the fleet consists of ***
        one four - deck
        two three - deck
        three two - deck
        four single - deck)";

        cout << "\nIf you want to continue, enter your name, else enter 'exit' and you will lost!\n";
        cin >> name_first;
        if (name_first == "exit") {
            Lost();
            return 0;
        } else {
            cout << "Now you can choose the mode. Doubles -> 'd' or singles -> 's'\t:";
            enter_the_mode:
            cin >> mode;
            if (mode == "d") {
                cout << "OK, then enter the name of the second player: ";
                cin >> name_second;
                cout << "Well, now we should arrange the ships. " << name_first << " will be first" << endl;
                cout << "This is blank field\n\n";
//Вывод незаполненного поля
                for (int i = 0; i < 11; ++i) {
                    for (int j = 0; j < 11; ++j)
                        if (i == 0 && j != 0) {
                            cout << field[i][j] << " | ";
                        } else if (i != 10) {
                            cout << field[i][j] << " |  ";
                        } else {
                            cout << field[i][j] << "|   ";
                        }
                    cout << endl;
                }
                int j = 1;
                int s = 1;
                int trust = 0;
                int domn = 0;
                int sch = 1;

//Ввод координат, раставление плюсов на месте кораблей
                do {
                    switch (j) {
                        case 1:
                            domn = 4;
                            break;
                        case 4:
                            domn = 4;
                            break;
                        case 2:
                            domn = 6;
                            break;
                        case 3:
                            domn = 6;
                            break;
                        default:
                            cerr << "ERROR IN SWITCH ";
                    }
                    do {
                        cout << "Enter the coordinates of the " << j << "-deck. Each coordinate enter with 'enter'\n";
                        cin >> coordinate_letter >> coordinate_index;
                        array_numbers[index_numbers] = coordinate_index;
                        for (int i = 1; i < 11; i++) {
                            if (coordinate_letter == alphabet[i]) {
                                array_letters[index_letters] = i;
                            }
                        }
                        index_letters++;
                        index_numbers++;
                        s++;
                    } while (s <= domn);
                    j++;
                    for (int i = 0; i <= domn - 1; i++) {
                        field[array_numbers[i]][array_letters[i]] = "+";
                    }
                    index_letters = 0;
                    index_numbers = 0;
                    sch = 1;
                    s = 1;
                } while (j <= 4);


                for (int i = 0; i < 11; ++i) {
                    for (int j = 0; j < 11; ++j) {
                        if (i == 0) {
                            cout << "|" << field[i][j];
                        } else {
                            if (j == 0) {
                                cout << field[i][j];
                            } else {
                                if (field[i][j] != "+" && j != 10) {
                                    cout << "  " << field[i][j];
                                } else {
                                    if (field[i][j] != "+" && j == 10) {
                                        cout << " " << field[i][j];
                                    } else {
                                        if (field[i][j] == "+" && j != 10) {
                                            cout << " " << field[i][j];
                                        } else {
                                            cout << " " << field[i][j];
                                        }
                                    }
                                }
                            }
                        }
                    }
                    cout << endl;
                }

//Второй игрок вводит свои координаты
                j = 1;
                s = 1;
                domn = 0;
                sch = 1;
                do {
                    cout << j;
                    switch (j) {
                        case 1:
                            domn = 4;
                            break;
                        case 4:
                            domn = 4;
                            break;
                        case 2:
                            domn = 6;
                            break;
                        case 3:
                            domn = 6;
                            break;
                        default:
                            cerr << "ERROR IN SWITCH ";
                    }
                    do {
                        cout << "Enter the coordinates of the " << j << "-deck. Each coordinate enter with 'enter'\n";
                        cin >> coordinate_letter >> coordinate_index;
                        array_numbers[index_numbers] = coordinate_index;
                        for (int i = 1; i < 11; i++) {
                            if (coordinate_letter == alphabet[i]) {
                                array_letters[index_letters] = i;
                            }
                        }
                        index_letters++;
                        index_numbers++;
                        s++;
                    } while (s <= domn);
                    j++;
                    for (int i = 0; i <= domn - 1; i++) {
                        field_1[array_numbers[i]][array_letters[i]] = "+";
                    }
                    index_letters = 0;
                    index_numbers = 0;
                    sch = 1;
                    s = 1;
                } while (j <= 4);

//Вывод массива с +
                for (int i = 0; i < 11; ++i) {
                    for (int j = 0; j < 11; ++j) {
                        if (i == 0) {
                            cout << "|" << field_1[i][j];
                        } else {
                            if (j == 0) {
                                cout << field_1[i][j];
                            } else {
                                if (field_1[i][j] != "+" && j != 10) {
                                    cout << "  " << field_1[i][j];
                                } else {
                                    if (field_1[i][j] != "+" && j == 10) {
                                        cout << " " << field_1[i][j];
                                    } else {
                                        if (field_1[i][j] == "+" && j != 10) {
                                            cout << " " << field_1[i][j];
                                        } else {
                                            cout << " " << field_1[i][j];
                                        }
                                    }
                                }
                            }
                        }
                    }
                    cout << endl;
                }

                cout << "Well, when all ships are in the field, we can start game! Good luck\n";
                cout << name_first << " will be first. Enter the coordinates\n";
                int hit_1 = 0, hit_2 = 0;

//САМА ИГРА

                while (true) {

//FIRST_PLAYER_COORDINATES

                    first_player_coordinates:
                    cin >> coordinate_letter >> coordinate_index;
//индекс по букве
                    for (int i = 1; i < 11; i++) {
                        if (coordinate_letter == alphabet[i]) {
                            index_letters = i;
                            break;
                        }
                    }
//Сначала строка потом столбец


                    if (field_1[coordinate_index][index_letters] == "+") {
                        cout << name_first << " is hit\n";
                        field_1[coordinate_index][index_letters] = "%";
                        field_empty_2[coordinate_index][index_letters] = "%";
                        hit_1 += 1;
                        hit = true;
                    } else {
                        cout << name_first << " is miss\n";
                        field_empty_2[coordinate_index][index_letters] = "¶";
                        field_1[coordinate_index][index_letters] = "¶";
                        hit = false;
                    }
//Безусловный переход на first_player_coordinates
                    if ((hit) && (hit_1 < 20)) {
                        cout << name_first << " you can enter the coordinates one more time!\n";
                        coordinate_index = 0;
                        index_letters = 0;
                        coordinate_letter = "0";
                        goto first_player_coordinates;
                    } else {
                        if (hit_1 == 20) {
                            goto label_for_exit;
                        }
                    }
//Вывод массива
                    for (int i = 0; i < 11; ++i) {
                        for (int j = 0; j < 11; ++j) {
                            if (i == 0) {
                                cout << "|" << field_empty_2[i][j];
                            } else {
                                if (j == 0) {
                                    cout << field_empty_2[i][j];
                                } else {
                                    if ((field_1[i][j] != "+") && field_1[i][j] != "%" && field_1[i][j] != "¶" &&
                                        j != 10) {
                                        cout << "  " << field_empty_2[i][j];
                                    } else {
                                        if (field_1[i][j] != "+" && field_1[i][j] != "%" && field_1[i][j] != "¶" &&
                                            j == 10) {
                                            cout << " " << field_empty_2[i][j];
                                        } else {
                                            if ((field_1[i][j] == "+" || field_1[i][j] != "%" ||
                                                 field_1[i][j] != "¶") &&
                                                j != 10) {
                                                cout << " " << field_empty_2[i][j];
                                            } else {
                                                cout << " " << field_empty_2[i][j];
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        cout << endl;
                    }


                    coordinate_index = 0;
                    index_letters = 0;
                    coordinate_letter = "0";


                    cout << name_second << ". Enter the coordinates!\n";
//SECOND_PLAYER_COORDINATES
                    second_player_coordinates:
                    cin >> coordinate_letter >> coordinate_index;
//индекс по букве
                    for (int i = 1; i < 11; i++) {
                        if (coordinate_letter == alphabet[i]) {
                            index_letters = i;
                            break;
                        }
                    }

                    if (field[coordinate_index][index_letters] == "+") {
                        cout << name_second << " is hit\n";
                        field[coordinate_index][index_letters] = "%";
                        field_empty_1[coordinate_index][index_letters] = "%";
                        hit_2 += 1;
                        hit = true;
                    } else {
                        cout << name_second << " is miss\n";
                        field_empty_1[coordinate_index][index_letters] = "¶";
                        field[coordinate_index][index_letters] = "¶";
                        hit = false;
                    }
//Безусловный переход к SECOND_PLAYER_COORDINATES
                    if ((hit) && (hit_2 < 20)) {
                        cout << name_second << " you can enter the coordinates one more time!\n";
                        coordinate_index = 0;
                        index_letters = 0;
                        coordinate_letter = "0";
                        goto second_player_coordinates;
                    } else {
                        if (hit_2 == 20) {
                            goto label_for_exit;
                        }
                    }

                    for (int i = 0; i < 11; ++i) {
                        for (int j = 0; j < 11; ++j) {
                            if (i == 0) {
                                cout << "|" << field_empty_1[i][j];
                            } else {
                                if (j == 0) {
                                    cout << field_empty_1[i][j];
                                } else {
                                    if ((field[i][j] != "+") && field[i][j] != "%" && field[i][j] != "¶" && j != 10) {
                                        cout << "  " << field_empty_1[i][j];
                                    } else {
                                        if (field[i][j] != "+" && field[i][j] != "%" && field[i][j] != "¶" && j == 10) {
                                            cout << " " << field_empty_1[i][j];
                                        } else {
                                            if ((field[i][j] == "+" || field[i][j] != "%" || field[i][j] != "¶") &&
                                                j != 10) {
                                                cout << " " << field_empty_1[i][j];
                                            } else {
                                                cout << " " << field_empty_1[i][j];
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        cout << endl;
                    }

                    label_for_exit:

                    if (hit_1 == 20 || hit_2 == 20) {
                        break;
                    } else {
                        cout << name_first << ". Enter the coordinates\n";
                    }


                    coordinate_index = 0;
                    index_letters = 0;
                    coordinate_letter = "0";
                }
                if (hit_1 == 20) {
                    Winner(name_first);
                } else {
                    Winner(name_second);
                }


            } else if (mode == "s") {

//Вывод незаполненного поля

                for (int i = 0; i < 11; ++i) {
                    for (int j = 0; j < 11; ++j)
                        if (i == 0 && j != 0) {
                            cout << field[i][j] << " | ";
                        } else if (i != 10) {
                            cout << field[i][j] << " |  ";
                        } else {
                            cout << field[i][j] << "|   ";
                        }
                    cout << endl;
                }

                int j = 1;
                int s = 1;
                int trust = 0;
                int domn = 0;

//Неудачная попытка рандомного расположения кораблей
/*Четырехпалубный{

            index_numbers = GetRandomNumber(1, 10);
            index_letters = GetRandomNumber(1, 7);
            field_in_s[index_numbers][index_letters] = 1;
            field_in_s[index_numbers][index_letters + 1] = 1;
            field_in_s[index_numbers][index_letters + 2] = 1;
            field_in_s[index_numbers][index_letters + 3] = 1;
            //up
            field_in_s[index_numbers + 1][index_letters] = 0;
            field_in_s[index_numbers + 1][index_letters + 1] = 0;
            field_in_s[index_numbers + 1][index_letters + 2] = 0;
            field_in_s[index_numbers + 1][index_letters + 3] = 0;
            //down
            field_in_s[index_numbers - 1][index_letters] = 0;
            field_in_s[index_numbers - 1][index_letters + 1] = 0;
            field_in_s[index_numbers - 1][index_letters + 2] = 0;
            field_in_s[index_numbers - 1][index_letters + 3] = 0;
            //l+r
            field_in_s[index_numbers][index_letters - 1] = 0;
            field_in_s[index_numbers][index_letters + 4] = 0;
            //corner
            field_in_s[index_numbers - 1][index_letters - 1] = 0;
            field_in_s[index_numbers - 1][index_letters + 1] = 0;
            field_in_s[index_numbers + 1][index_letters + 4] = 0;
            field_in_s[index_numbers - 1][index_letters + 4] = 0;


            while (true){
                index_numbers= GetRandomNumber(1, 8);
                index_letters= GetRandomNumber(1, 10);
                if (field_in_s[index_numbers][index_letters]!=3){
                    continue;
                }else{
                    break;
                }
            }
*/
//заполнение 1 field_in_s
                {
                    field_in_s[1][2] = true;
                    field_in_s[2][4] = true;
                    field_in_s[2][5] = true;
                    field_in_s[2][6] = true;
                    field_in_s[2][7] = true;
                    field_in_s[3][10] = true;
                    field_in_s[4][1] = true;
                    field_in_s[5][1] = true;
                    field_in_s[6][1] = true;
                    field_in_s[5][3] = true;
                    field_in_s[5][4] = true;
                    field_in_s[5][9] = true;
                    field_in_s[5][10] = true;
                    field_in_s[7][3] = true;
                    field_in_s[8][6] = true;
                    field_in_s[9][6] = true;
                    field_in_s[10][2] = true;
                    field_in_s[10][3] = true;
                    field_in_s[10][4] = true;
                    field_in_s[8][9] = true;
                }



//Ввод координат игроком и вывод заполненного поля

                do {
                    switch (j) {
                        case 1:
                            domn = 4;
                            break;
                        case 4:
                            domn = 4;
                            break;
                        case 2:
                            domn = 6;
                            break;
                        case 3:
                            domn = 6;
                            break;
                        default:
                            cerr << "ERROR IN SWITCH 2 ";
                    }
                    do {
                        cout << "Enter the coordinates of the " << j << "-deck. Each coordinate enter with 'enter'\n";
                        cin >> coordinate_letter >> coordinate_index;
                        array_numbers[index_numbers] = coordinate_index;
                        for (int i = 1; i < 11; i++) {
                            if (coordinate_letter == alphabet[i]) {
                                array_letters[index_letters] = i;
                            }
                        }
                        index_letters++;
                        index_numbers++;
                        s++;
                    } while (s <= domn);
                    j++;
                    for (int i = 0; i <= domn - 1; i++) {
                        field[array_numbers[i]][array_letters[i]] = "+";
                        field_in_s_empty[array_numbers[i]][array_letters[i]] = 1;
                    }
                    index_letters = 0;
                    index_numbers = 0;
                    s = 1;

                } while (j <= 4);
//Вывод массива
                for (int i = 0; i < 11; ++i) {
                    for (int j = 0; j < 11; ++j) {
                        if (i == 0) {
                            cout << "|" << field[i][j];
                        } else {
                            if (j == 0) {
                                cout << field[i][j];
                            } else {
                                if (field[i][j] != "+" && j != 10) {
                                    cout << "  " << field[i][j];
                                } else {
                                    if (field[i][j] != "+" && j == 10) {
                                        cout << " " << field[i][j];
                                    } else {
                                        if (field[i][j] == "+" && j != 10) {
                                            cout << " " << field[i][j];
                                        } else {
                                            cout << " " << field[i][j];
                                        }
                                    }
                                }
                            }
                        }
                    }
                    cout << endl;
                }
//САМА ИГРА

                int hit_1 = 0, hit_2 = 0;

                cout << "You should be first.\n";
                while (true) {
                    cout << name_first << ". Enter the coordinates";
//player enter coordinates
                    player_enter_coordinates:
                    cin >> coordinate_letter >> coordinate_index;
//Индкекс по букве
                    for (int i = 1; i < 11; i++) {
                        if (alphabet[i] == coordinate_letter) {
                            index_letters = i;
                        }
                    }

//Проверка, попал игрок или нет

                    if (field_in_s[coordinate_index][index_letters]) {
                        cout << "\nYou're hit!\n";
                        field_in_s[coordinate_index][index_letters] = false;
                        hit_1 += 1;
                        hit = true;
                    } else {
                        cout << "\nYou're miss(\n";
                        hit = false;
                    }
                    if (hit && hit_1 != 20) {
                        cout << name_first << ". You can enter the coordinates one more time!\n";
                        goto player_enter_coordinates;
                    } else {
                        if (hit_1 == 20) {
                            break;
                        }
                    }
//bot enter coordinates
                    bot_enter_coordinates:
                    index_letters = GetRandomNumber(1, 10);
                    letter = alphabet[index_letters];
                    coordinate_index = GetRandomNumber(1, 10);
                    for_record = letter;
                    for_record += " ";
                    auto s = to_string(coordinate_index);
                    for_record += s;
                    if (field_in_s_empty[coordinate_index][index_letters] == 3) {
                        coordinate_index = 0;
                        index_letters = 0;
                        coordinate_letter = "";
                        hit = false;
                        goto bot_enter_coordinates;
                    } else {
                        if (field_in_s_empty[coordinate_index][index_letters] == 1) {
                            cout << for_record;
                            cout << "\nHit!\n";
                            field_in_s_empty[coordinate_index][index_letters] = 3;
                            hit_2 += 1;
                            hit = true;
                            field[coordinate_index][index_letters] = "%";

                        } else {
                            cout << for_record;
                            cout << "\nMiss\n";
                            field_in_s_empty[coordinate_index][index_letters] = 3;
                            hit = false;
                            goto player_enter_coordinates;
                        }
                    }
                    if (hit && hit_2 != 20) {
                        coordinate_index = 0;
                        index_letters = 0;
                        coordinate_letter = "";
                        goto bot_enter_coordinates;
                    } else {
                        if (hit_2 == 20) {
                            goto little_win;
                        } else {
                            continue;
                        }
                    }
                    little_win:
                    if (hit_1 != 20 && hit_2 != 20) {
                        continue;
                    } else {
                        break;
                    }

                }
                if (hit_1 == 20) {
                    Win();
                } else {
                    Lost();
                }
            } else {
                cerr << "Error in choosing the mode\n";
                cout << "Do you want to enter the mode again? yes -> 'y'\n";
                cin >> yes;
                if (yes == 'y') {
                    cout << "Enter: ";
                    goto enter_the_mode;
                } else {
                    Lost();
                }
            }
        }
    }else{
        if (language == "r"){

//Заполнение полей
            for (int i = 0; i <= 10; i++) {
                for (int j = 0; j <= 10; j++) {
                    if ((i == 0) && (j != 0)) {
                        field[i][j] = alphabet_r[j];
                    }
                    if ((j == 0) && (i != 0)) {
                        field[i][j] = numbers[i];
                    }
                    if (!(j == 0) && (i != 0) && (i == 0) && (j != 0)) {
                        field[i][j] = " ";
                    }
                    if ((i == 0) && (j != 0)) {
                        field_1[i][j] = alphabet_r[j];
                    }
                    if ((j == 0) && (i != 0)) {
                        field_1[i][j] = numbers[i];
                    }
                    if (!(j == 0) && (i != 0) && (i == 0) && (j != 0)) {
                        field_1[i][j] = " ";
                    }
                    if ((i == 0) && (j != 0)) {
                        field_empty_1[i][j] = alphabet_r[j];
                    }
                    if ((j == 0) && (i != 0)) {
                        field_empty_1[i][j] = numbers[i];
                    }
                    if (!(j == 0) && (i != 0) && (i == 0) && (j != 0)) {
                        field_empty_1[i][j] = " ";
                    }
                    if ((i == 0) && (j != 0)) {
                        field_empty_2[i][j] = alphabet_r[j];
                    }
                    if ((j == 0) && (i != 0)) {
                        field_empty_2[i][j] = numbers[i];
                    }
                    if (!(j == 0) && (i != 0) && (i == 0) && (j != 0)) {
                        field_empty_2[i][j] = " ";
                    }
                    field_in_s[i][j] = false;
                    field_in_s_empty[i][j]=0;
                }
            }
//Правила

            cout << R"(***Правила***
Цель игры состоит в том, чтобы утопить все боевые единицы противника.
Игрок выбирает, какую ячейку он хочет проверить.
После чего он сначала называет ее букву, а затем цифру (например, "E8").
Если у второго игрока есть корабль в такой ячейке, человек отвечает "сбит" или "убит".
Нападающий ставит крестик в нужном месте на нарисованном пустом поле.
После попадания человек получает право на еще один выстрел.

Когда он назовет ячейку, которая у противника пуста, он ответит "by".
После этого ход переходит ко второму игроку.
Побеждает тот, кто первым обнаружил все суда противника.

***Флот состоит из ***
один - четырехпалубный
два - трехпалубных
три - двухпалубных
четыре - однопалубных)";

            cout << "\nЕсли вы хотите продолжить, введите ваше имя, иначе введите 'выход' и вы проиграете!\n";
            cin >> name_first;
            if (name_first == "выход") {
                Lost();
                return 0;
            } else {
                cout << "Сейчас вы должны выбрать режим игры: два игрока (введите 'д') или один игрок (введите 'о'):\t";
                enter_the_mode_r:
                cin >> mode;
                if (mode == "д") {
                    cout << "OK, теперь введите имя второго игрока: ";
                    cin >> name_second;
                    cout << "ОК, сейчас вы должны расставить корабли. " << name_first << ", вы будете первым (-ой)" << endl;
                    cout << "Незаполненное поле:\n\n";
//Вывод незаполненного поля
                    for (int i = 0; i < 11; ++i) {
                        for (int j = 0; j < 11; ++j)
                            if (i == 0 && j != 0) {
                                cout << field[i][j] << " | ";
                            } else if (i != 10) {
                                cout << field[i][j] << " |  ";
                            } else {
                                cout << field[i][j] << "|   ";
                            }
                        cout << endl;
                    }
                    int j = 1;
                    int s = 1;
                    int trust = 0;
                    int domn = 0;
                    int sch = 1;

//Ввод координат, раставление плюсов на месте кораблей
                    do {
                        switch (j) {
                            case 1:
                                domn = 4;
                                break;
                            case 4:
                                domn = 4;
                                break;
                            case 2:
                                domn = 6;
                                break;
                            case 3:
                                domn = 6;
                                break;
                            default:
                                cerr << "ERROR IN SWITCH ";
                        }
                        do {
                            cout << "Введите координату " << j << "-палубного корабля, координату вводите с помощью клавиши 'enter' или пробела\n";
                            cin >> coordinate_letter >> coordinate_index;
                            array_numbers[index_numbers] = coordinate_index;
                            for (int i = 1; i < 11; i++) {
                                if (coordinate_letter == alphabet_r[i]) {
                                    array_letters[index_letters] = i;
                                }
                            }
                            index_letters++;
                            index_numbers++;
                            s++;
                        } while (s <= domn);
                        j++;
                        for (int i = 0; i <= domn - 1; i++) {
                            field[array_numbers[i]][array_letters[i]] = "+";
                        }
                        index_letters = 0;
                        index_numbers = 0;
                        sch = 1;
                        s = 1;
                    } while (j <= 4);


                    for (int i = 0; i < 11; ++i) {
                        for (int j = 0; j < 11; ++j) {
                            if (i == 0) {
                                cout << "|" << field[i][j];
                            } else {
                                if (j == 0) {
                                    cout << field[i][j];
                                } else {
                                    if (field[i][j] != "+" && j != 10) {
                                        cout << "  " << field[i][j];
                                    } else {
                                        if (field[i][j] != "+" && j == 10) {
                                            cout << " " << field[i][j];
                                        } else {
                                            if (field[i][j] == "+" && j != 10) {
                                                cout << " " << field[i][j];
                                            } else {
                                                cout << " " << field[i][j];
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        cout << endl;
                    }

//Второй игрок вводит свои координаты
                    j = 1;
                    s = 1;
                    domn = 0;
                    sch = 1;
                    do {
                        cout << j;
                        switch (j) {
                            case 1:
                                domn = 4;
                                break;
                            case 4:
                                domn = 4;
                                break;
                            case 2:
                                domn = 6;
                                break;
                            case 3:
                                domn = 6;
                                break;
                            default:
                                cerr << "ERROR IN SWITCH ";
                        }
                        do {
                            cout << "Введите координату " << j << "-палубного корабля, координату вводите с помощью клавиши 'enter' или пробела\n";
                            cin >> coordinate_letter >> coordinate_index;
                            array_numbers[index_numbers] = coordinate_index;
                            for (int i = 1; i < 11; i++) {
                                if (coordinate_letter == alphabet_r[i]) {
                                    array_letters[index_letters] = i;
                                }
                            }
                            index_letters++;
                            index_numbers++;
                            s++;
                        } while (s <= domn);
                        j++;
                        for (int i = 0; i <= domn - 1; i++) {
                            field_1[array_numbers[i]][array_letters[i]] = "+";
                        }
                        index_letters = 0;
                        index_numbers = 0;
                        sch = 1;
                        s = 1;
                    } while (j <= 4);

//Вывод массива с +
                    for (int i = 0; i < 11; ++i) {
                        for (int j = 0; j < 11; ++j) {
                            if (i == 0) {
                                cout << "|" << field_1[i][j];
                            } else {
                                if (j == 0) {
                                    cout << field_1[i][j];
                                } else {
                                    if (field_1[i][j] != "+" && j != 10) {
                                        cout << "  " << field_1[i][j];
                                    } else {
                                        if (field_1[i][j] != "+" && j == 10) {
                                            cout << " " << field_1[i][j];
                                        } else {
                                            if (field_1[i][j] == "+" && j != 10) {
                                                cout << " " << field_1[i][j];
                                            } else {
                                                cout << " " << field_1[i][j];
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        cout << endl;
                    }

                    cout << "Сейчас, когда все корабли расставлены, мы можем начинать игру! Удачи!\n";
                    cout << name_first << ", вы будете первым(-ой)\n";
                    int hit_1 = 0, hit_2 = 0;

//САМА ИГРА

                    while (true) {

//FIRST_PLAYER_COORDINATES

                        first_player_coordinates_r:
                        cin >> coordinate_letter >> coordinate_index;
//индекс по букве
                        for (int i = 1; i < 11; i++) {
                            if (coordinate_letter == alphabet_r[i]) {
                                index_letters = i;
                                break;
                            }
                        }
//Сначала строка потом столбец


                        if (field_1[coordinate_index][index_letters] == "+") {
                            cout << name_first << " Попал(-а)\n";
                            field_1[coordinate_index][index_letters] = "%";
                            field_empty_2[coordinate_index][index_letters] = "%";
                            hit_1 += 1;
                            hit = true;
                        } else {
                            cout << name_first << " Промахнулся(-ась)\n";
                            field_empty_2[coordinate_index][index_letters] = "¶";
                            field_1[coordinate_index][index_letters] = "¶";
                            hit = false;
                        }
//Безусловный переход на first_player_coordinates
                        if ((hit) && (hit_1 < 20)) {
                            cout << name_first << ", вы можете ввести координату еще раз!\n";
                            coordinate_index = 0;
                            index_letters = 0;
                            coordinate_letter = "0";
                            goto first_player_coordinates_r;
                        } else {
                            if (hit_1 == 20) {
                                goto label_for_exit_r;
                            }
                        }
//Вывод массива
                        for (int i = 0; i < 11; ++i) {
                            for (int j = 0; j < 11; ++j) {
                                if (i == 0) {
                                    cout << "|" << field_empty_2[i][j];
                                } else {
                                    if (j == 0) {
                                        cout << field_empty_2[i][j];
                                    } else {
                                        if ((field_1[i][j] != "+") && field_1[i][j] != "%" && field_1[i][j] != "¶" &&
                                            j != 10) {
                                            cout << "  " << field_empty_2[i][j];
                                        } else {
                                            if (field_1[i][j] != "+" && field_1[i][j] != "%" && field_1[i][j] != "¶" &&
                                                j == 10) {
                                                cout << " " << field_empty_2[i][j];
                                            } else {
                                                if ((field_1[i][j] == "+" || field_1[i][j] != "%" ||
                                                     field_1[i][j] != "¶") &&
                                                    j != 10) {
                                                    cout << " " << field_empty_2[i][j];
                                                } else {
                                                    cout << " " << field_empty_2[i][j];
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            cout << endl;
                        }


                        coordinate_index = 0;
                        index_letters = 0;
                        coordinate_letter = "0";


                        cout << name_second << ", вводите координату!\n";
//SECOND_PLAYER_COORDINATES
                        second_player_coordinates_r:
                        cin >> coordinate_letter >> coordinate_index;
//индекс по букве
                        for (int i = 1; i < 11; i++) {
                            if (coordinate_letter == alphabet_r[i]) {
                                index_letters = i;
                                break;
                            }
                        }

                        if (field[coordinate_index][index_letters] == "+") {
                            cout << name_second << " Попал(-а)\n";
                            field[coordinate_index][index_letters] = "%";
                            field_empty_1[coordinate_index][index_letters] = "%";
                            hit_2 += 1;
                            hit = true;
                        } else {
                            cout << name_second << " Промахнулся(-ась)\n";
                            field_empty_1[coordinate_index][index_letters] = "¶";
                            field[coordinate_index][index_letters] = "¶";
                            hit = false;
                        }
//Безусловный переход к SECOND_PLAYER_COORDINATES
                        if ((hit) && (hit_2 < 20)) {
                            cout << name_second << ", вы можете ввести координату еще раз!\n";
                            coordinate_index = 0;
                            index_letters = 0;
                            coordinate_letter = "0";
                            goto second_player_coordinates_r;
                        } else {
                            if (hit_2 == 20) {
                                goto label_for_exit_r;
                            }
                        }

                        for (int i = 0; i < 11; ++i) {
                            for (int j = 0; j < 11; ++j) {
                                if (i == 0) {
                                    cout << "|" << field_empty_1[i][j];
                                } else {
                                    if (j == 0) {
                                        cout << field_empty_1[i][j];
                                    } else {
                                        if ((field[i][j] != "+") && field[i][j] != "%" && field[i][j] != "¶" && j != 10) {
                                            cout << "  " << field_empty_1[i][j];
                                        } else {
                                            if (field[i][j] != "+" && field[i][j] != "%" && field[i][j] != "¶" && j == 10) {
                                                cout << " " << field_empty_1[i][j];
                                            } else {
                                                if ((field[i][j] == "+" || field[i][j] != "%" || field[i][j] != "¶") &&
                                                    j != 10) {
                                                    cout << " " << field_empty_1[i][j];
                                                } else {
                                                    cout << " " << field_empty_1[i][j];
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            cout << endl;
                        }

                        label_for_exit_r:

                        if (hit_1 == 20 || hit_2 == 20) {
                            break;
                        } else {
                            cout << name_first << ", вводите координату.\n";
                        }


                        coordinate_index = 0;
                        index_letters = 0;
                        coordinate_letter = "0";
                    }
                    if (hit_1 == 20) {
                        Winner(name_first);
                    } else {
                        Winner(name_second);
                    }


                } else if (mode == "о") {

//Вывод незаполненного поля

                    for (int i = 0; i < 11; ++i) {
                        for (int j = 0; j < 11; ++j)
                            if (i == 0 && j != 0) {
                                cout << field[i][j] << " | ";
                            } else if (i != 10) {
                                cout << field[i][j] << " |  ";
                            } else {
                                cout << field[i][j] << "|   ";
                            }
                        cout << endl;
                    }

                    int j = 1;
                    int s = 1;
                    int trust = 0;
                    int domn = 0;

//Неудачная попытка рандомного расположения кораблей
/*Четырехпалубный{

            index_numbers = GetRandomNumber(1, 10);
            index_letters = GetRandomNumber(1, 7);
            field_in_s[index_numbers][index_letters] = 1;
            field_in_s[index_numbers][index_letters + 1] = 1;
            field_in_s[index_numbers][index_letters + 2] = 1;
            field_in_s[index_numbers][index_letters + 3] = 1;
            //up
            field_in_s[index_numbers + 1][index_letters] = 0;
            field_in_s[index_numbers + 1][index_letters + 1] = 0;
            field_in_s[index_numbers + 1][index_letters + 2] = 0;
            field_in_s[index_numbers + 1][index_letters + 3] = 0;
            //down
            field_in_s[index_numbers - 1][index_letters] = 0;
            field_in_s[index_numbers - 1][index_letters + 1] = 0;
            field_in_s[index_numbers - 1][index_letters + 2] = 0;
            field_in_s[index_numbers - 1][index_letters + 3] = 0;
            //l+r
            field_in_s[index_numbers][index_letters - 1] = 0;
            field_in_s[index_numbers][index_letters + 4] = 0;
            //corner
            field_in_s[index_numbers - 1][index_letters - 1] = 0;
            field_in_s[index_numbers - 1][index_letters + 1] = 0;
            field_in_s[index_numbers + 1][index_letters + 4] = 0;
            field_in_s[index_numbers - 1][index_letters + 4] = 0;


            while (true){
                index_numbers= GetRandomNumber(1, 8);
                index_letters= GetRandomNumber(1, 10);
                if (field_in_s[index_numbers][index_letters]!=3){
                    continue;
                }else{
                    break;
                }
            }
*/
//заполнение 1 field_in_s
                    {
                        field_in_s[1][2] = true;
                        field_in_s[2][4] = true;
                        field_in_s[2][5] = true;
                        field_in_s[2][6] = true;
                        field_in_s[2][7] = true;
                        field_in_s[3][10] = true;
                        field_in_s[4][1] = true;
                        field_in_s[5][1] = true;
                        field_in_s[6][1] = true;
                        field_in_s[5][3] = true;
                        field_in_s[5][4] = true;
                        field_in_s[5][9] = true;
                        field_in_s[5][10] = true;
                        field_in_s[7][3] = true;
                        field_in_s[8][6] = true;
                        field_in_s[9][6] = true;
                        field_in_s[10][2] = true;
                        field_in_s[10][3] = true;
                        field_in_s[10][4] = true;
                        field_in_s[8][9] = true;
                    }



//Ввод координат игроком и вывод заполненного поля

                    do {
                        switch (j) {
                            case 1:
                                domn = 4;
                                break;
                            case 4:
                                domn = 4;
                                break;
                            case 2:
                                domn = 6;
                                break;
                            case 3:
                                domn = 6;
                                break;
                            default:
                                cerr << "ERROR IN SWITCH 2 ";
                        }
                        do {
                            cout << "Введите координату " << j << "-палубного корабля, координату вводите с помощью клавиши 'enter' или пробела\n";
                            cin >> coordinate_letter >> coordinate_index;
                            array_numbers[index_numbers] = coordinate_index;
                            for (int i = 1; i < 11; i++) {
                                if (coordinate_letter == alphabet_r[i]) {
                                    array_letters[index_letters] = i;
                                }
                            }
                            index_letters++;
                            index_numbers++;
                            s++;
                        } while (s <= domn);
                        j++;
                        for (int i = 0; i <= domn - 1; i++) {
                            field[array_numbers[i]][array_letters[i]] = "+";
                            field_in_s_empty[array_numbers[i]][array_letters[i]] = 1;
                        }
                        index_letters = 0;
                        index_numbers = 0;
                        s = 1;

                    } while (j <= 4);
//Вывод массива
                    for (int i = 0; i < 11; ++i) {
                        for (int j = 0; j < 11; ++j) {
                            if (i == 0) {
                                cout << "|" << field[i][j];
                            } else {
                                if (j == 0) {
                                    cout << field[i][j];
                                } else {
                                    if (field[i][j] != "+" && j != 10) {
                                        cout << "  " << field[i][j];
                                    } else {
                                        if (field[i][j] != "+" && j == 10) {
                                            cout << " " << field[i][j];
                                        } else {
                                            if (field[i][j] == "+" && j != 10) {
                                                cout << " " << field[i][j];
                                            } else {
                                                cout << " " << field[i][j];
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        cout << endl;
                    }
//САМА ИГРА

                    int hit_1 = 0, hit_2 = 0;

                    cout << "Вы будете первым(-ой).\n";
                    while (true) {
                        cout << name_first << ", вводите координату";
//player enter coordinates
                        player_enter_coordinates_r:
                        cin >> coordinate_letter >> coordinate_index;
//Индкекс по букве
                        for (int i = 1; i < 11; i++) {
                            if (alphabet_r[i] == coordinate_letter) {
                                index_letters = i;
                            }
                        }

//Проверка, попал игрок или нет

                        if (field_in_s[coordinate_index][index_letters]) {
                            cout << "Вы попали!\n";
                            field_in_s[coordinate_index][index_letters] = false;
                            hit_1 += 1;
                            hit = true;
                        } else {
                            cout << "Вы промахнулись(\n";
                            hit = false;
                        }
                        if (hit && hit_1 != 20) {
                            cout << name_first << ", вы можете ввести координату еще раз!\n";
                            goto player_enter_coordinates_r;
                        } else {
                            if (hit_1 == 20) {
                                break;
                            }
                        }
//bot enter coordinates
                        bot_enter_coordinates_r:
                        index_letters = GetRandomNumber(1, 10);
                        letter = alphabet_r[index_letters];
                        coordinate_index = GetRandomNumber(1, 10);
                        for_record = letter;
                        for_record += " ";
                        auto s = to_string(coordinate_index);
                        for_record += s;
                        if (field_in_s_empty[coordinate_index][index_letters] == 3) {
                            coordinate_index = 0;
                            index_letters = 0;
                            coordinate_letter = "";
                            hit = false;
                            goto bot_enter_coordinates_r;
                        } else {
                            if (field_in_s_empty[coordinate_index][index_letters] == 1) {
                                cout << for_record;
                                cout << "\nПопал!\n";
                                field_in_s_empty[coordinate_index][index_letters] = 3;
                                hit_2 += 1;
                                hit = true;
                                field[coordinate_index][index_letters] = "%";

                            } else {
                                cout << for_record;
                                cout << "\nПромахнулся\n";
                                field_in_s_empty[coordinate_index][index_letters] = 3;
                                hit = false;
                                goto player_enter_coordinates_r;
                            }
                        }
                        if (hit && hit_2 != 20) {
                            coordinate_index = 0;
                            index_letters = 0;
                            coordinate_letter = "";
                            goto bot_enter_coordinates_r;
                        } else {
                            if (hit_2 == 20) {
                                goto little_win_r;
                            } else {
                                continue;
                            }
                        }
                        little_win_r:
                        if (hit_1 != 20 && hit_2 != 20) {
                            continue;
                        } else {
                            break;
                        }

                    }
                    if (hit_1 == 20) {
                        WinR();
                    } else {
                        LostR();
                    }
                } else {
                    cerr << "Ошибка в выборе режима\n";
                    cout << "Хотите ли вы выбрать режим еще раз? да -> 'd'\n";
                    cin >> yes;
                    if (yes == 'd') {
                        cout << "Введите режим: ";
                        goto enter_the_mode_r;
                    } else {
                        LostR();
                    }
                }
            }
        }else{
            if (language=="i"){

//Заполнение полей
                for (int i = 0; i <= 10; i++) {
                    for (int j = 0; j <= 10; j++) {
                        if ((i == 0) && (j != 0)) {
                            field[i][j] = alphabet[j];
                        }
                        if ((j == 0) && (i != 0)) {
                            field[i][j] = numbers[i];
                        }
                        if (!(j == 0) && (i != 0) && (i == 0) && (j != 0)) {
                            field[i][j] = " ";
                        }
                        if ((i == 0) && (j != 0)) {
                            field_1[i][j] = alphabet[j];
                        }
                        if ((j == 0) && (i != 0)) {
                            field_1[i][j] = numbers[i];
                        }
                        if (!(j == 0) && (i != 0) && (i == 0) && (j != 0)) {
                            field_1[i][j] = " ";
                        }
                        if ((i == 0) && (j != 0)) {
                            field_empty_1[i][j] = alphabet[j];
                        }
                        if ((j == 0) && (i != 0)) {
                            field_empty_1[i][j] = numbers[i];
                        }
                        if (!(j == 0) && (i != 0) && (i == 0) && (j != 0)) {
                            field_empty_1[i][j] = " ";
                        }
                        if ((i == 0) && (j != 0)) {
                            field_empty_2[i][j] = alphabet[j];
                        }
                        if ((j == 0) && (i != 0)) {
                            field_empty_2[i][j] = numbers[i];
                        }
                        if (!(j == 0) && (i != 0) && (i == 0) && (j != 0)) {
                            field_empty_2[i][j] = " ";
                        }
                        field_in_s[i][j] = false;
                        field_in_s_empty[i][j]=0;
                    }
                }
//Правила

                cout << R"(***Regole***
L'obiettivo del gioco è quello di annegare tutte le unità di combattimento del nemico.
Il giocatore sceglie quale cella desidera controllare.
Dopo di che lo chiama prima una lettera e poi un numero (ad esempio, "E8").
Se il secondo giocatore ha una nave in una tale cella, la persona risponde "abbattuto " o"ucciso".
L'attaccante mette una X nel posto giusto sul campo vuoto disegnato.
Una volta colpito, la persona ha diritto a un altro colpo.

Quando nomina una cella che l'avversario ha vuota, risponderà con "by".
Successivamente, il turno passa al secondo giocatore.
Vince chi ha scoperto per PRIMO tutte le navi dell'avversario.

*** La flotta è composta da ***
da uno a quattro pian)";

                cout << "\nSe vuoi continuare, inserisci il tuo nome, altrimenti digita 'esci' e perderai!\n";
                cin >> name_first;
                if (name_first == "esci") {
                    Lost();
                    return 0;
                } else {
                    cout << "Ora devi scegliere la modalità di gioco: due giocatori (inserisci 'g') o un giocatore (inserisci 'u'):\t";
                    enter_the_mode_i:
                    cin >> mode;
                    if (mode == "g") {
                        cout << "OK, ora inserisci il nome del secondo giocatore: ";
                        cin >> name_second;
                        cout << "OK, ora devi sistemare le navi. " << name_first << ", sarai il primo" << endl;
                        cout << "Campo vuoto:\n\n";
//Вывод незаполненного поля
                        for (int i = 0; i < 11; ++i) {
                            for (int j = 0; j < 11; ++j)
                                if (i == 0 && j != 0) {
                                    cout << field[i][j] << " | ";
                                } else if (i != 10) {
                                    cout << field[i][j] << " |  ";
                                } else {
                                    cout << field[i][j] << "|   ";
                                }
                            cout << endl;
                        }
                        int j = 1;
                        int s = 1;
                        int trust = 0;
                        int domn = 0;
                        int sch = 1;

//Ввод координат, раставление плюсов на месте кораблей
                        do {
                            switch (j) {
                                case 1:
                                    domn = 4;
                                    break;
                                case 4:
                                    domn = 4;
                                    break;
                                case 2:
                                    domn = 6;
                                    break;
                                case 3:
                                    domn = 6;
                                    break;
                                default:
                                    cerr << "ERROR IN SWITCH ";
                            }
                            do {
                                cout << "Inserisci la coordinata. le coordinate della nave coperta vengono immesse con il tasto 'INVIO' o la barra spaziatrice\n";
                                cin >> coordinate_letter >> coordinate_index;
                                array_numbers[index_numbers] = coordinate_index;
                                for (int i = 1; i < 11; i++) {
                                    if (coordinate_letter == alphabet[i]) {
                                        array_letters[index_letters] = i;
                                    }
                                }
                                index_letters++;
                                index_numbers++;
                                s++;
                            } while (s <= domn);
                            j++;
                            for (int i = 0; i <= domn - 1; i++) {
                                field[array_numbers[i]][array_letters[i]] = "+";
                            }
                            index_letters = 0;
                            index_numbers = 0;
                            sch = 1;
                            s = 1;
                        } while (j <= 4);


                        for (int i = 0; i < 11; ++i) {
                            for (int j = 0; j < 11; ++j) {
                                if (i == 0) {
                                    cout << "|" << field[i][j];
                                } else {
                                    if (j == 0) {
                                        cout << field[i][j];
                                    } else {
                                        if (field[i][j] != "+" && j != 10) {
                                            cout << "  " << field[i][j];
                                        } else {
                                            if (field[i][j] != "+" && j == 10) {
                                                cout << " " << field[i][j];
                                            } else {
                                                if (field[i][j] == "+" && j != 10) {
                                                    cout << " " << field[i][j];
                                                } else {
                                                    cout << " " << field[i][j];
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            cout << endl;
                        }

//Второй игрок вводит свои координаты
                        j = 1;
                        s = 1;
                        domn = 0;
                        sch = 1;
                        do {
                            cout << j;
                            switch (j) {
                                case 1:
                                    domn = 4;
                                    break;
                                case 4:
                                    domn = 4;
                                    break;
                                case 2:
                                    domn = 6;
                                    break;
                                case 3:
                                    domn = 6;
                                    break;
                                default:
                                    cerr << "ERROR IN SWITCH ";
                            }
                            do {
                                cout << "Inserisci la coordinata. le coordinate della nave coperta vengono immesse con il tasto 'INVIO' o la barra spaziatrice\n";
                                cin >> coordinate_letter >> coordinate_index;
                                array_numbers[index_numbers] = coordinate_index;
                                for (int i = 1; i < 11; i++) {
                                    if (coordinate_letter == alphabet[i]) {
                                        array_letters[index_letters] = i;
                                    }
                                }
                                index_letters++;
                                index_numbers++;
                                s++;
                            } while (s <= domn);
                            j++;
                            for (int i = 0; i <= domn - 1; i++) {
                                field_1[array_numbers[i]][array_letters[i]] = "+";
                            }
                            index_letters = 0;
                            index_numbers = 0;
                            sch = 1;
                            s = 1;
                        } while (j <= 4);

//Вывод массива с +
                        for (int i = 0; i < 11; ++i) {
                            for (int j = 0; j < 11; ++j) {
                                if (i == 0) {
                                    cout << "|" << field_1[i][j];
                                } else {
                                    if (j == 0) {
                                        cout << field_1[i][j];
                                    } else {
                                        if (field_1[i][j] != "+" && j != 10) {
                                            cout << "  " << field_1[i][j];
                                        } else {
                                            if (field_1[i][j] != "+" && j == 10) {
                                                cout << " " << field_1[i][j];
                                            } else {
                                                if (field_1[i][j] == "+" && j != 10) {
                                                    cout << " " << field_1[i][j];
                                                } else {
                                                    cout << " " << field_1[i][j];
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            cout << endl;
                        }

                        cout << "Ora che tutte le navi sono sistemate, possiamo iniziare il gioco! Buona fortuna!\n";
                        cout << name_first << ". Sarai il primo\n";
                        int hit_1 = 0, hit_2 = 0;

//САМА ИГРА

                        while (true) {

//FIRST_PLAYER_COORDINATES

                            first_player_coordinates_i:
                            cin >> coordinate_letter >> coordinate_index;
//индекс по букве
                            for (int i = 1; i < 11; i++) {
                                if (coordinate_letter == alphabet[i]) {
                                    index_letters = i;
                                    break;
                                }
                            }
//Сначала строка потом столбец


                            if (field_1[coordinate_index][index_letters] == "+") {
                                cout << name_first << " Arrivato)\n";
                                field_1[coordinate_index][index_letters] = "%";
                                field_empty_2[coordinate_index][index_letters] = "%";
                                hit_1 += 1;
                                hit = true;
                            } else {
                                cout << name_first << " Mancare il bersaglio\n";
                                field_empty_2[coordinate_index][index_letters] = "¶";
                                field_1[coordinate_index][index_letters] = "¶";
                                hit = false;
                            }
//Безусловный переход на first_player_coordinates
                            if ((hit) && (hit_1 < 20)) {
                                cout << name_first << ", è possibile inserire nuovamente la coordinata!\n";
                                coordinate_index = 0;
                                index_letters = 0;
                                coordinate_letter = "0";
                                goto first_player_coordinates_i;
                            } else {
                                if (hit_1 == 20) {
                                    goto label_for_exit_i;
                                }
                            }
//Вывод массива
                            for (int i = 0; i < 11; ++i) {
                                for (int j = 0; j < 11; ++j) {
                                    if (i == 0) {
                                        cout << "|" << field_empty_2[i][j];
                                    } else {
                                        if (j == 0) {
                                            cout << field_empty_2[i][j];
                                        } else {
                                            if ((field_1[i][j] != "+") && field_1[i][j] != "%" && field_1[i][j] != "¶" &&
                                                j != 10) {
                                                cout << "  " << field_empty_2[i][j];
                                            } else {
                                                if (field_1[i][j] != "+" && field_1[i][j] != "%" && field_1[i][j] != "¶" &&
                                                    j == 10) {
                                                    cout << " " << field_empty_2[i][j];
                                                } else {
                                                    if ((field_1[i][j] == "+" || field_1[i][j] != "%" ||
                                                         field_1[i][j] != "¶") &&
                                                        j != 10) {
                                                        cout << " " << field_empty_2[i][j];
                                                    } else {
                                                        cout << " " << field_empty_2[i][j];
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                cout << endl;
                            }


                            coordinate_index = 0;
                            index_letters = 0;
                            coordinate_letter = "0";


                            cout << name_second << ", inserisci la coordinata!\n";
//SECOND_PLAYER_COORDINATES
                            second_player_coordinates_i:
                            cin >> coordinate_letter >> coordinate_index;
//индекс по букве
                            for (int i = 1; i < 11; i++) {
                                if (coordinate_letter == alphabet[i]) {
                                    index_letters = i;
                                    break;
                                }
                            }

                            if (field[coordinate_index][index_letters] == "+") {
                                cout << name_second << " Arrivato)!\n";
                                field[coordinate_index][index_letters] = "%";
                                field_empty_1[coordinate_index][index_letters] = "%";
                                hit_2 += 1;
                                hit = true;
                            } else {
                                cout << name_second << " Mancare il bersaglio\n";
                                field_empty_1[coordinate_index][index_letters] = "¶";
                                field[coordinate_index][index_letters] = "¶";
                                hit = false;
                            }
//Безусловный переход к SECOND_PLAYER_COORDINATES
                            if ((hit) && (hit_2 < 20)) {
                                cout << name_second << ", è possibile inserire nuovamente la coordinata!\n";
                                coordinate_index = 0;
                                index_letters = 0;
                                coordinate_letter = "0";
                                goto second_player_coordinates_i;
                            } else {
                                if (hit_2 == 20) {
                                    goto label_for_exit_i;
                                }
                            }

                            for (int i = 0; i < 11; ++i) {
                                for (int j = 0; j < 11; ++j) {
                                    if (i == 0) {
                                        cout << "|" << field_empty_1[i][j];
                                    } else {
                                        if (j == 0) {
                                            cout << field_empty_1[i][j];
                                        } else {
                                            if ((field[i][j] != "+") && field[i][j] != "%" && field[i][j] != "¶" && j != 10) {
                                                cout << "  " << field_empty_1[i][j];
                                            } else {
                                                if (field[i][j] != "+" && field[i][j] != "%" && field[i][j] != "¶" && j == 10) {
                                                    cout << " " << field_empty_1[i][j];
                                                } else {
                                                    if ((field[i][j] == "+" || field[i][j] != "%" || field[i][j] != "¶") &&
                                                        j != 10) {
                                                        cout << " " << field_empty_1[i][j];
                                                    } else {
                                                        cout << " " << field_empty_1[i][j];
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                cout << endl;
                            }

                            label_for_exit_i:

                            if (hit_1 == 20 || hit_2 == 20) {
                                break;
                            } else {
                                cout << name_first << ", inserisci la coordinata.\n";
                            }


                            coordinate_index = 0;
                            index_letters = 0;
                            coordinate_letter = "0";
                        }
                        if (hit_1 == 20) {
                            Winner(name_first);
                        } else {
                            Winner(name_second);
                        }


                    } else if (mode == "о") {

//Вывод незаполненного поля

                        for (int i = 0; i < 11; ++i) {
                            for (int j = 0; j < 11; ++j)
                                if (i == 0 && j != 0) {
                                    cout << field[i][j] << " | ";
                                } else if (i != 10) {
                                    cout << field[i][j] << " |  ";
                                } else {
                                    cout << field[i][j] << "|   ";
                                }
                            cout << endl;
                        }

                        int j = 1;
                        int s = 1;
                        int trust = 0;
                        int domn = 0;

//Неудачная попытка рандомного расположения кораблей
/*Четырехпалубный{

            index_numbers = GetRandomNumber(1, 10);
            index_letters = GetRandomNumber(1, 7);
            field_in_s[index_numbers][index_letters] = 1;
            field_in_s[index_numbers][index_letters + 1] = 1;
            field_in_s[index_numbers][index_letters + 2] = 1;
            field_in_s[index_numbers][index_letters + 3] = 1;
            //up
            field_in_s[index_numbers + 1][index_letters] = 0;
            field_in_s[index_numbers + 1][index_letters + 1] = 0;
            field_in_s[index_numbers + 1][index_letters + 2] = 0;
            field_in_s[index_numbers + 1][index_letters + 3] = 0;
            //down
            field_in_s[index_numbers - 1][index_letters] = 0;
            field_in_s[index_numbers - 1][index_letters + 1] = 0;
            field_in_s[index_numbers - 1][index_letters + 2] = 0;
            field_in_s[index_numbers - 1][index_letters + 3] = 0;
            //l+r
            field_in_s[index_numbers][index_letters - 1] = 0;
            field_in_s[index_numbers][index_letters + 4] = 0;
            //corner
            field_in_s[index_numbers - 1][index_letters - 1] = 0;
            field_in_s[index_numbers - 1][index_letters + 1] = 0;
            field_in_s[index_numbers + 1][index_letters + 4] = 0;
            field_in_s[index_numbers - 1][index_letters + 4] = 0;


            while (true){
                index_numbers= GetRandomNumber(1, 8);
                index_letters= GetRandomNumber(1, 10);
                if (field_in_s[index_numbers][index_letters]!=3){
                    continue;
                }else{
                    break;
                }
            }
*/
//заполнение 1 field_in_s
                        {
                            field_in_s[1][2] = true;
                            field_in_s[2][4] = true;
                            field_in_s[2][5] = true;
                            field_in_s[2][6] = true;
                            field_in_s[2][7] = true;
                            field_in_s[3][10] = true;
                            field_in_s[4][1] = true;
                            field_in_s[5][1] = true;
                            field_in_s[6][1] = true;
                            field_in_s[5][3] = true;
                            field_in_s[5][4] = true;
                            field_in_s[5][9] = true;
                            field_in_s[5][10] = true;
                            field_in_s[7][3] = true;
                            field_in_s[8][6] = true;
                            field_in_s[9][6] = true;
                            field_in_s[10][2] = true;
                            field_in_s[10][3] = true;
                            field_in_s[10][4] = true;
                            field_in_s[8][9] = true;
                        }



//Ввод координат игроком и вывод заполненного поля

                        do {
                            switch (j) {
                                case 1:
                                    domn = 4;
                                    break;
                                case 4:
                                    domn = 4;
                                    break;
                                case 2:
                                    domn = 6;
                                    break;
                                case 3:
                                    domn = 6;
                                    break;
                                default:
                                    cerr << "ERROR IN SWITCH 2 ";
                            }
                            do {
                                cout << "Inserisci la coordinata. le coordinate della nave coperta vengono immesse con il tasto 'INVIO' o la barra spaziatrice\n";
                                cin >> coordinate_letter >> coordinate_index;
                                array_numbers[index_numbers] = coordinate_index;
                                for (int i = 1; i < 11; i++) {
                                    if (coordinate_letter == alphabet[i]) {
                                        array_letters[index_letters] = i;
                                    }
                                }
                                index_letters++;
                                index_numbers++;
                                s++;
                            } while (s <= domn);
                            j++;
                            for (int i = 0; i <= domn - 1; i++) {
                                field[array_numbers[i]][array_letters[i]] = "+";
                                field_in_s_empty[array_numbers[i]][array_letters[i]] = 1;
                            }
                            index_letters = 0;
                            index_numbers = 0;
                            s = 1;

                        } while (j <= 4);
//Вывод массива
                        for (int i = 0; i < 11; ++i) {
                            for (int j = 0; j < 11; ++j) {
                                if (i == 0) {
                                    cout << "|" << field[i][j];
                                } else {
                                    if (j == 0) {
                                        cout << field[i][j];
                                    } else {
                                        if (field[i][j] != "+" && j != 10) {
                                            cout << "  " << field[i][j];
                                        } else {
                                            if (field[i][j] != "+" && j == 10) {
                                                cout << " " << field[i][j];
                                            } else {
                                                if (field[i][j] == "+" && j != 10) {
                                                    cout << " " << field[i][j];
                                                } else {
                                                    cout << " " << field[i][j];
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            cout << endl;
                        }
//САМА ИГРА

                        int hit_1 = 0, hit_2 = 0;

                        cout << "Sarai il primo\n";
                        while (true) {
                            cout << name_first << ", inserisci la coordinata";
//player enter coordinates
                            player_enter_coordinates_i:
                            cin >> coordinate_letter >> coordinate_index;
//Индкекс по букве
                            for (int i = 1; i < 11; i++) {
                                if (alphabet[i] == coordinate_letter) {
                                    index_letters = i;
                                }
                            }

//Проверка, попал игрок или нет

                            if (field_in_s[coordinate_index][index_letters]) {
                                cout << "Hai colpito!\n";
                                field_in_s[coordinate_index][index_letters] = false;
                                hit_1 += 1;
                                hit = true;
                            } else {
                                cout << "Hai mancato(\n";
                                hit = false;
                            }
                            if (hit && hit_1 != 20) {
                                cout << name_first << ", è possibile inserire nuovamente la coordinata!\n";
                                goto player_enter_coordinates_i;
                            } else {
                                if (hit_1 == 20) {
                                    break;
                                }
                            }
//bot enter coordinates
                            bot_enter_coordinates_i:
                            index_letters = GetRandomNumber(1, 10);
                            letter = alphabet[index_letters];
                            coordinate_index = GetRandomNumber(1, 10);
                            for_record = letter;
                            for_record += " ";
                            auto s = to_string(coordinate_index);
                            for_record += s;
                            if (field_in_s_empty[coordinate_index][index_letters] == 3) {
                                coordinate_index = 0;
                                index_letters = 0;
                                coordinate_letter = "";
                                hit = false;
                                goto bot_enter_coordinates_i;
                            } else {
                                if (field_in_s_empty[coordinate_index][index_letters] == 1) {
                                    cout << for_record;
                                    cout << "\nArrivato!\n";
                                    field_in_s_empty[coordinate_index][index_letters] = 3;
                                    hit_2 += 1;
                                    hit = true;
                                    field[coordinate_index][index_letters] = "%";

                                } else {
                                    cout << for_record;
                                    cout << "\nMancare il bersaglio\n";
                                    field_in_s_empty[coordinate_index][index_letters] = 3;
                                    hit = false;
                                    goto player_enter_coordinates_i;
                                }
                            }
                            if (hit && hit_2 != 20) {
                                coordinate_index = 0;
                                index_letters = 0;
                                coordinate_letter = "";
                                goto bot_enter_coordinates_i;
                            } else {
                                if (hit_2 == 20) {
                                    goto little_win_i;
                                } else {
                                    continue;
                                }
                            }
                            little_win_i:
                            if (hit_1 != 20 && hit_2 != 20) {
                                continue;
                            } else {
                                break;
                            }

                        }
                        if (hit_1 == 20) {
                            WinI();
                        } else {
                            LostI();
                        }
                    } else {
                        cerr << "Errore nella selezione della modalità\n";
                        cout << "Vuoi scegliere di nuovo la modalità? sì - > 's'\n";
                        cin >> yes;
                        if (yes == 's') {
                            cout << "Immettere la modalità: ";
                            goto enter_the_mode_i;
                        } else {
                            LostI();
                        }
                    }
                }
            }else{
                cout<<"Error in choosing language\n Do you want to enter it again? If yes, enter 'y'";
                cin>>language;
                if (language=="y"){
                    goto choose_language;
                }else{
                    Lost();
                }
            }
        }
    }
    return 0;
}

// библиотеки
#include <math.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>

// управляющие консолью библиотеки
#include <windows.h>
#include <conio.h>

// с помощью дефайнов объявляются размеры всех меню
#define MAIN_MENU_SIZE 3
#define GAME_MENU_SIZE 3
#define SETTINGS_MENU_SIZE 4

// основные ключи клавиш, которые могут пригодиться
#define NOT_KEY 67
#define KEY_EXIT 27
#define KEY_ENTER 13
#define ARROW_KEY 224
#define KEY_SPACE 0
#define KEY_BACKSPACE 8
#define KEY_ARROW_RIGHT 77
#define KEY_ARROW_LEFT 75
#define KEY_ARROW_UP 72
#define KEY_ARROW_DOWN 80

int main() {
  // 0. настройки

  // задаем название консольного окна
  system("title Arcade Game");

  // устанавливаем взаимодействие с русскими буквами (вместо setlocale)
  SetConsoleCP(1251);         // установка кодовой страницы win-cp 1251 в поток ввода
  SetConsoleOutputCP(1251);   // установка кодовой страницы win-cp 1251 в поток вывода

  // получаем консоль (правильнее сказать, дескриптор окна для обращения к консоли)
  HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

  // отключение мигания курсора в консоли (в нашем меню курсор не нужен)
  CONSOLE_CURSOR_INFO structCursorInfo;
  GetConsoleCursorInfo(console, &structCursorInfo);    // получаем курсор
  structCursorInfo.bVisible = FALSE;                   // выключаем его видимость
  SetConsoleCursorInfo(console, &structCursorInfo);    // устанавливаем изменЄнный курсор

  // задаем серый фон для окна консоли
  SetConsoleTextAttribute(console, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
  // очищаем экран, чтобы настройка цвета применилась
  system("cls");

  // 1. объявление переменных
  int choose_pos;                    // переменная для хранения текущего выбранного пункта меню
  int iKey;                          // переменная для запоминания нажатой клавиши
  int exit_flag, back_flag;          // флаг на завершение программы и флаг на возврат в прошлое меню
  COORD cursorPos;                   // положение курсора в консоли, чтобы менять выводимый текст

  // вложенные меню
  char *main_menu[MAIN_MENU_SIZE] = { "Game", "Settings", "Exit" };
  char *game_menu[GAME_MENU_SIZE] = { "Guessing game PC", "Guessing game USER", "Back" };
  char *settings_menu[SETTINGS_MENU_SIZE] = { "Difficulty Settings", "Color Settings", "Language", "Back" };
  
  /* 
  подменю конкретной настройки открывается на текущем выбранном режиме.
  режимы сложности:
  << обычный >>
     сложный
     хардкор
  цветовые темы:
       темная
    << светлая >>
       цветная
  языки:
    << русский >>
       английский
  */

  // 2. инициализация (ввод/заполнение значений)
  back_flag = 0;
  exit_flag = 0;
  choose_pos = 0;

  // 3. основная часть программы
  while (!exit_flag) {
    // сброс консоли в стартовое положение
    system("cls");
    cursorPos = (COORD) { 0, 0 };
    iKey = NOT_KEY;
    SetConsoleCursorPosition(console, cursorPos);

    // листание в меню до подтверждения выбора нажатием enter
    while (iKey != KEY_EXIT && iKey != KEY_ENTER) {
      switch (iKey) {
      case KEY_ARROW_UP:
        choose_pos--;
        break;
      case KEY_ARROW_DOWN:
        choose_pos++;
        break;
      default:
        break;
      }

      // зацикливание перелистывания меню
      if (choose_pos < 0) { choose_pos = MAIN_MENU_SIZE - 1; }
      if (choose_pos > MAIN_MENU_SIZE - 1) { choose_pos = 0; }

      // перед перерисовкой меню очистка
      system("cls");

      // перерисовка меню
      for (int i = 0; i < MAIN_MENU_SIZE; i++) {
        cursorPos = (COORD) { 3, i };
        SetConsoleCursorPosition(console, cursorPos);
        printf("%s \n", main_menu[i]);
      }

      // обозначение выбранной позиции
      cursorPos = (COORD) { 0, choose_pos };
      SetConsoleCursorPosition(console, cursorPos);
      printf("<<", iKey);
      cursorPos = (COORD) { strlen(main_menu[choose_pos]) + 3 + 1, choose_pos };  // "<< GAME " это "<< " = 3, "GAME" = strlen(main_menu[choose_pos]), " " = 1
      SetConsoleCursorPosition(console, cursorPos);
      printf(">>");

      // ожидание нового нажатия клавиши
      iKey = _getch();
    }

    // после нажатия enter выполнение выбранного действия
    switch (choose_pos) {
    case 0:
      system("cls");
      printf("Game part in development\n");
      system("pause");
      break;
    case 1:
      system("cls");
      printf("Settings part in development\n");
      system("pause");
      break;
    case 2:
      exit_flag = 1;
      break;
    }
  }

  // 4. вывод финального результата
  system("cls");
  printf("Goodbay!\n");

  // завершение программы
  system("pause");
  return 0;
}
